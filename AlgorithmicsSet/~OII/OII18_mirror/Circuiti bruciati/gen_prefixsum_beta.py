from os import system

n = 371
#n = int(input())

comcount = 0
def comprint(*args, **kwargs):
    global comcount
    comcount += 1
    return print(*args, **kwargs)

def get_split(first, last): 
    k = (last-first).bit_length() - 1
    if 2**k == last - first:
        k -= 1
    return first + 2**k

r = 0
semi = {}
def parallel_sum(first, last):
    global r
    if (first, last) in semi:
        return semi[first, last]
    assert first != last
    if first + 1 == last:
        return f"in[{first}]"
    else:
        split = get_split(first, last)
        left = parallel_sum(first, split)
        right = parallel_sum(split, last)
        semi[first, last] = r
        comprint(f"semi[{r}] = {left} + {right}")
        r += 1
        return f"semi[{r-1}]"

s = 0
def parallel_prefix_sum(n):
    global s
    comprint("out[0] = in[0] + 0")
    for i in range(1, n):
        j = i + 1
        curr = None; it = 0
        b = 0
        while b < j:
            k = (j - b).bit_length() - 1
            p = parallel_sum(b, b + 2**k)
            if curr is None:
                curr = f"semi[{p}]"
            elif b + 2**k < j:
                comprint(f"re[{s}] = {curr} + {p}")
                curr = f"re[{s}]"
                s += 1
            else:
                comprint(f"out[{i}] = {curr} + {p}")
            b += 2**k
            it += 1
        if it == 1:
            comprint(f"out[{i}] = {curr}")

parallel_prefix_sum(n)
print("Total cost:", comcount)

#system("pause")
