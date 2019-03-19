# creates tro-generated.cpp from tro{0,1,2,3,4,5,6,7,8,9,10}.out

import os
import sys


TASK_ID = "tro"
Ids = "0 1 2 3 4 5 6 7 8 9 10".split(" ")
Ts = [(5, 12, 12345, 27470),
      (100, 100, 100, 20000),
      (500, 600, 500, 30000),
      (5000, 8000, 47, 31500),
      (10000, 20000, 47, 32760),
      (20000, 40000, 4747, 32755),
      (25000, 50000, 47, 32766),
      (33300, 66600, 666, 32759),
      (40000, 80000, 7447, 32755),
      (50000, 100000, 74, 27660),
      (50000, 100000, 7474, 32761)]


def condition(**kwargs):
    return " and ".join(["%s == %d" % (k, v) for (k, v) in kwargs.items()])


generated_path = TASK_ID+"-generated.cpp"
# assert(not(os.path.exists(generated_path)))
with open(generated_path, "w") as f:
    f.write('#include "bits/stdc++.h"\n\n')
    f.write('using namespace std;\n\n')
    f.write('int main() {\n')
    f.write('  int r, c, s, t;\n')
    f.write('  scanf("%d %d %d %d", &r, &c, &s, &t);\n')
    for _id, (r, c, s, t) in zip(Ids, Ts):
        file_path = TASK_ID+"%s.out" % _id
        if os.path.exists(file_path):
            with open(file_path) as g:
                out = "".join(g.readlines()).replace("\n", "\\n")
                f.write('  if(%s) printf("%s");\n'
                        % (condition(r=r, c=c, s=s, t=t), out))
        else:
            print("WARN:", file_path+" missing.", file=sys.stderr)
    f.write("}\n")
os.system("pause")
