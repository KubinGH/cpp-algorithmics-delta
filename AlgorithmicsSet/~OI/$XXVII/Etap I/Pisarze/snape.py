import string
import random

import tqdm
import tensorflow as tf
import numpy as np

import pistestgen


alphabet = string.ascii_letters + ".!?-,;:"

def gen(group):
    return pistestgen.main(group, None, '.', random.randint(0, 2**64 - 1))

input_vector_size = len(alphabet) + 1

def process_fragment(frag, decay=0.9375):
    frag = [c.lower() for c in frag if c in alphabet]
    vec = np.zeros(input_vector_size)
    for c in frag:
        vec[alphabet.find(c)] += 1
        vec *= decay
    return vec

authors = ["Mickiewicz", "Sienkiewicz", "Prus"]
onehot = {a: np.array([float(i==j) for j in range(len(authors))]) for i, a in enumerate(authors)}

class OctaLayer:
    def __init_weights(self, in_size, out_size):
        return tf.Variable(np.random.normal(0, np.sqrt(2 / (in_size + out_size)), (in_size, out_size)))

    def __init_bias(self, out_size):
        return tf.Variable(np.random.normal(np.zeros((out_size, ))))

    def __init__(self, in_size, out_size, activation=lambda x: x):
        self.w = self.__init_weights(in_size, out_size)
        self.b = self.__init_bias(out_size)
        self.a = activation

    def __call__(self, x):
        return self.a(tf.matmul(x, self.w) + self.b)

    @property
    def variables(self):
        return [self.w, self.b]
class OctaModel:
    def __init__(self, sizes, activations):
        self.sizes = sizes
        self.layer_count = len(self.sizes) - 1
        assert self.layer_count == len(activations)
        self.layers = [OctaLayer(sizes[i], sizes[i+1], activations[i]) for i in range(self.layer_count)]
        self.loss = tf.losses.CategoricalCrossentropy()
        self.optimizer = tf.optimizers.Adam(learning_rate=0.03)
        self.variables = sum([layer.variables for layer in self.layers], [])

    def __call__(self, x):
        for layer in self.layers:
            x = layer(x)
        return x

    @tf.function
    def train(self, x, y):
        with tf.GradientTape() as tape:
            y_pred = self(x)
            loss = self.loss(y, y_pred)
        gradient = tape.gradient(loss, self.variables)
        self.optimizer.apply_gradients(zip(gradient, self.variables))

model = OctaModel([input_vector_size, 15, 15, 3], [tf.nn.relu, tf.nn.relu, tf.nn.softmax])

def next_batch(batch_size=16, group=4, generate=False):
    if generate:
        x, y = gen(group)
        x = np.array([process_fragment(f) for f in x[:batch_size]])
        y = np.array([onehot[a] for a in y[:batch_size]])
        return x, y
    else:
        index = np.random.randint(0, trainX.shape[0], batch_size)
        return trainX.take(index, axis=0), trainY.take(index, axis=0)

trainX, trainY = next_batch(1000, generate=True)

print(next_batch())
