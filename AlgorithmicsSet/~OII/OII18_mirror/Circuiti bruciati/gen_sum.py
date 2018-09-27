from os import system

n = 1093
#n = int(input())

r = 0
def parallel_sum(first, last):
    global r
    assert first != last
    if first + 1 == last:
        return f"in[{first}]"
    else:
        k = (last-first).bit_length() - 1
        if 2**k == last - first:
            k -= 1
        left = parallel_sum(first, first + 2**k)
        right = parallel_sum(first + 2**k, last)
        if last - first < n:
            print(f"semi[{r}] = {left} + {right}")
        else:
            print(f"out[0] = {left} + {right}")
        r += 1
        return f"semi[{r-1}]"
parallel_sum(0, n)

#system("pause")
