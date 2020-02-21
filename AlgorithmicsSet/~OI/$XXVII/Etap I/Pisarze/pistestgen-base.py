#!/usr/bin/python

import sys
import random
import os

MAX_LENGTH = 2000000

author_names = ['Sienkiewicz', 'Mickiewicz', 'Prus']

# Read args
if len(sys.argv) < 2:
    raise Exception("Please specify the test group")
if len(sys.argv) < 3:
    raise Exception("Please specify the testname")
if len(sys.argv) < 4:
    raise Exception("Please specify the folder with texts")

group = int(sys.argv[1])
assert (1 <= group <= 4)

testname = sys.argv[2]

folder = sys.argv[3]

if len(sys.argv) == 5:
    seeder = sys.argv[4]
    seed = 0
    for char in seeder:
        seed += ord(char)
        seed *= 256
        seed %= 100000015333
    random.seed(seed)

# Read the data
text = {}
sentences = {}
for author_name in author_names:
    with open(os.path.join(folder, author_name + '.txt')) as textF:
        text[author_name] = textF.readline().split()
        sentences[author_name] = ' '.join(text[author_name]).replace('. ', '.#$%').replace('! ', '!#$%').replace('? ', '?#$%').split('#$%')

# Generate a testcase
def generate(corpus, min_words, max_words):
    retries_global = -1
    while True:
        retries_global += 1
        if retries_global > 20:
            raise Exception("Cannot choose a sentence that's long enough.")
        whom = random.choice(author_names)
        start = random.randrange(len(corpus[whom]))
        retries = 0
        while (len(corpus[whom][start]) > max_words):
            retries += 1
            if retries > 100:
                raise Exception("Choice error --- can't choose smaller than max.")
            start = random.randrange(len(corpus[whom]))

        sum_length = len(corpus[whom][start].split())

        end = start + 1
        while sum_length < min_words:
            if random.randrange(2) == 0 and start != 0:
                if sum_length + len(corpus[whom][start - 1].split()) > max_words:
                    break
                else:
                    start -= 1
                    sum_length += len(corpus[whom][start].split())
            elif end < len(corpus[whom]):
                if sum_length + len(corpus[whom][end].split()) > max_words:
                    break
                else:
                    sum_length += len(corpus[whom][end].split())
                    end += 1
            elif start == 0 and sum_length < min_words:
                raise Exception("Corpus too short? min_words too big?")

        if sum_length < min_words:
            continue
        return ' '.join(corpus[whom][start:end]), whom

# Generate the whole test
inputs = []
characters = 0
outputs = []
if group == 1:
    while len(inputs) < 101 and characters <= MAX_LENGTH:
        inp, out = generate(text, 500 + len(inputs) % 15 * 100, 600 + len(inputs) % 15 * 100)
        inputs.append(inp)
        outputs.append(out)
        characters += len(inp)
elif group == 2:
    if random.randrange(4) < 3:
        mn, mx = 10, 80
    else:
        mn, mx = 30, 100
    while len(inputs) < 1001 and characters <= MAX_LENGTH:
        inp, out = generate(sentences, mn, mx)
        inputs.append(inp)
        outputs.append(out)
        characters += len(inp)
elif group == 3:
    while len(inputs) < 1001 and characters <= MAX_LENGTH:
        inp, out = generate(text, 30 + len(inputs) % 6 * 2, 50 + len(inputs) % 6 * 2)
        inputs.append(inp)
        outputs.append(out)
        characters += len(inp)
elif group == 4:
    rng = random.randrange(8)
    if rng < 5:
        mn, mx = 10, 50
    elif rng < 8:
        mn, mx = 15, 50
    while len(inputs) < 1001 and characters <= MAX_LENGTH:
        randlength = random.randint(10, 1500)
        inp, out = generate(text, mn, mx) if random.randrange(20) != 0 else generate(text, randlength, randlength + 30)
        inputs.append(inp)
        outputs.append(out)
        characters += len(inp)

inputs[-1:] = []
outputs[-1:] = []

with open(testname + '.in', 'w') as inF:
    print(len(inputs), file=inF)
    for s_input in inputs:
        print(s_input, file=inF)

with open(testname + '.out', 'w') as outF:
    for s_output in outputs:
        print(s_output, file=outF)
