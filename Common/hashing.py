prime = 313
mod = int(1e9 + 7)
def hashf(s):
    n = len(s)
    s_hash = [0 for _ in range(n)]
    S = [ord(c)-ord('a') for c in s]
    s_hash[0] = S[0]
    for i in range(1, n):
        s_hash[i] = (((s_hash[i - 1] * prime) % mod) + S[i]) % mod
    def H(i, j):
        if i == 0:
            return s_hash[j]
        return (mod + s_hash[j] - s_hash[i - 1] * (prime ** (j - i + 1))) % mod
    return H

H = hashf("abcdeabcde")
print(H(0, 2), H(5, 7))
print(H(0, 4), H(5, 9))
