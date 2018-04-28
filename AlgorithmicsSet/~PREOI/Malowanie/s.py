def run_test(test):
    best = float("inf")
    for i in range(2**len(test)):
        i |= 1
        ci = i
        counter = 0; result = 0
        for b in range(len(test)-1, -1, -1):
            if i % 2:
                result += test[b]
                counter = 1
            else:
                result += counter
                counter += 1
            i //= 2
        best = min(best, result)
        if result == best:
            print("new best", bin(ci)[2:].zfill(len(test)), result)
    return best

run_test([9, 10, 6, 9, 5, 4, 4, 9])
