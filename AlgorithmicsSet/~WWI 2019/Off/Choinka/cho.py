def main(n):
    o = []
    def part(m):
        for i in range(m):
            s = (n - i) * " "
            t = "*" * (2*i + 1)
            o.append(s + t)
    part(n)
    part(n + 1)
    part(1)
    part(1)
    return "\n".join(o)

if __name__ == "__main__":
    n = int(input().strip())
    print(main(n))
