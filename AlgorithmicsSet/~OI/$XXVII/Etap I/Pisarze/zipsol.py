import sys, bz2, base64, codecs

template = """\
import bz2, base64, codecs
data = {data}
code = bz2.decompress(base64.a85decode(data))
exec(code)
"""

def chunks(data, k):
    it = []
    for a in data:
        it.append(a)
        if len(it) == k:
            yield it
            it = []
    if it:
        yield it

def escaped(data):
    return data.replace('\\', '\\\\').replace('\'', '\\\'')

source = sys.stdin.read()
csource = bz2.compress(source.encode())
csource_enc = base64.a85encode(csource)
data = ""
for chunk in chunks(csource_enc.decode(), 4096):
    st = escaped(''.join(chunk))
    data += (len("data = ") * " ") + "b'" + st + "'\\\n"
data = data.strip(" \n\\")

print(template.format(data=data))
