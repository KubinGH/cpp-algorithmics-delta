n = int(input().strip())

def part(m):
    for i in range(m):
        s = (n - i) * " "
        t = "*" * (2*i + 1)
        print(s + t + s)

part(n)
part(n + 1)
part(1)
part(1)
