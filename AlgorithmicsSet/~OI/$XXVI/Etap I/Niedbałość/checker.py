import sys

alphabet = 'ATCG'

def is_sub_seq(x, y):
    """Test whether x is a subsequence of y"""
    x = list(x)
    for letter in y:
        if x and x[0] == letter:
            x.pop(0)
    return not x


def check_solution(a, b, r):
    witnesses = []
    for i in range(len(r) + 1):
        for c in alphabet:
            extended = r[:i] + c + r[i:]
            if is_sub_seq(extended, a) and is_sub_seq(extended, b):
                witnesses.append(extended)
    return not witnesses and is_sub_seq(r, a) and is_sub_seq(r, b), witnesses

if __name__ == "__main__":
    r = check_solution(*sys.stdin.read().split())
    if r[0]:
        exit(0)
    else:
        print("Witness:", r[1], file=sys.stderr)
        exit(1)
