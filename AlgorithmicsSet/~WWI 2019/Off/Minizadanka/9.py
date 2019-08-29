import dis
import z9
import re
import io

out = io.StringIO()
dis.dis(z9.fun, file=out)
print(re.findall('\(\d+\)', out.getvalue())[0][1:-1])
