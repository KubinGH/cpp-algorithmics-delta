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
def parallel_prefix_sum(first, last):
    global r
    assert first != last
    if first + 1 == last:
        comprint(f"out[{first}] = in[{first}] + 0")
        return f"out[{first}]"
    else:
        split = get_split(first, last)
        left = parallel_prefix_sum(first, split)
        right = parallel_prefix_sum_dep(split, last)
        for i, sub_right in zip(range(split, last), right):
            comprint(f"out[{i}] = {left} + {sub_right}")
        return f"out[{last-1}]"

def parallel_prefix_sum_dep(first, last):
    global r
    assert first != last
    if first + 1 == last:
        return [f"in[{first}]"]
    else:
        split = get_split(first, last)
        left = parallel_prefix_sum_dep(first, split)
        right = parallel_prefix_sum_dep(split, last)
        subs = []
        for i, sub_right in zip(range(split, last), right):
            comprint(f"prel[{r}] = {left[-1]} + {sub_right}")
            subs.append(f"prel[{r}]")
            r += 1
        return left + subs

parallel_prefix_sum(0, n)
print("Total cost:", comcount)

#system("pause")
