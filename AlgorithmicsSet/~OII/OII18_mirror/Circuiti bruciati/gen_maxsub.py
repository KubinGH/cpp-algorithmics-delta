from os import system

n = 7
FILE = None
silent = False
#n = int(input())

comcount = 0
def comprint(*args, **kwargs):
    global comcount
    comcount += 1
    if FILE is not None:
        print(*args, **kwargs, file=FILE)
    if not silent:
        print(*args, **kwargs)

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
        comprint(f"pref[{first}] = in[{first}] + 0")
        return f"pref[{first}]"
    else:
        split = get_split(first, last)
        left = parallel_prefix_sum(first, split)
        right = parallel_prefix_sum_dep(split, last)
        for i, sub_right in zip(range(split, last), right):
            comprint(f"pref[{i}] = {left} + {sub_right}")
        return f"pref[{last-1}]"

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

p = 0
q = 1
def parallel_max_subarray(first, last):
    global p, q
    assert first != last
    if first + 1 == last:
        comprint(f"run[{q}] = in[{first}] max run[{q-1}]"); q += 1
        comprint(f"hold[{p}] = in[{first}] max 0"); p += 1
        return f"hold[{p-1}]", f"hold[{p-1}]"
    else:
        split = get_split(first, last)
        left = parallel_max_subarray(first, split)
        right = parallel_max_subarray(split, last)
        comprint(f"hold[{p}] = {left[1]} + {right[0]}"); p += 1
        comprint(f"run[{q}] = hold[{p-1}] max run[{q-1}]"); q += 1
        comprint(f"hold[{p}] = pref[{split-1}] - pref[{2*n if first-1 == -1 else first-1}]"); p += 1
        comprint(f"hold[{p}] = hold[{p-1}] + {right[0]}"); p += 1
        comprint(f"hold[{p}] = hold[{p-1}] max {left[0]}"); p += 1
        comprint(f"hold[{p}] = pref[{last-1}] - pref[{2*n if split-1 == -1 else split-1}]"); p += 1
        comprint(f"hold[{p}] = hold[{p-1}] + {left[1]}"); p += 1
        comprint(f"hold[{p}] = hold[{p-1}] max {right[1]}"); p += 1
        return f"hold[{p-4}]", f"hold[{p-1}]"

def main():
    parallel_prefix_sum(0, n)
    comprint(f"pref[{2*n}] = 0 + 0")
    comprint("run[0] = 0 + 0")
    parallel_max_subarray(0, n)
    comprint(f"out[0] = run[{q-1}] + 0")
    print("\n\nTotal cost:", comcount)

if __name__ == "__main__":
    main()
