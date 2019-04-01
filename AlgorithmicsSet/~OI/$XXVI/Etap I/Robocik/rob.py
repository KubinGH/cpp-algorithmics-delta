import sys
import numpy

dirs = ((0, 1), (1, 0), (0, -1), (-1, 0))

# a <= bk <= c, assume b > 0
def count_multiples(a, b, c):
    p = a + (b - a%b) % b; q = c - c%b
    return (q - p)//b + 1 if a <= c and p <= q else 0

def main():
    ints = [int(d) for d in sys.stdin.read().split()]
    n, t = ints[0], ints[1]
    D = ints[2:n+2]
    xt, yt = ints[n+2], ints[n+3]
    D *= 4; n *= 4;

    ts = sum(D)
    p_base, t_after = divmod(t, (ts + n))
    i_after = n;
    P = [p_base for _ in range(n)]
    for i in range(n):
        if t_after >= D[i] + 1:
            P[i] += 1; t_after -= D[i] + 1
        else:
            i_after = i; break

    r = 0
    if (xt, yt) == (0, 0): r += 1

    XS, YS = [0 for _ in range(n+1)], [0 for _ in range(n+1)]
    xg, yg = 1, 1
    for i in range(n):
        XS[i+1], YS[i+1] = XS[i] + dirs[i%4][0] * D[i], YS[i] + dirs[i%4][1] * D[i]
    for rot in range(4):
        xs, ys = xg*XS[-1], yg*YS[-1]
        it = range((5-rot)%4, n, 4)
        if xs == 0 and ys == 0:
            for i in it:
                if P[i] and yt == yg*YS[i] and xt - D[i] <= xg*XS[i] < xt:
                    r += P[i]
        elif xs == 0:
            for i in it:
                if P[i] and (yt-yg*YS[i]) % ys == 0 and 0 <= (yt - yg*YS[i]) // ys < P[i] and xt - D[i] <= xg*XS[i] < xt:
                    r += 1
        elif ys == 0:
            for i in it:
                if P[i] and yt == yg*YS[i]:
                    e, f = xt - xg*XS[i] - D[i], xt - xg*XS[i]
                    # e <= xs * k < f and 0 <= k < P[i]
                    if xs > 0:
                        r += count_multiples(max(e, 0), xs, min(f-1, xs*P[i]-1))
                    else:
                        r += count_multiples(max(-f+1, 0), -xs, min(-e, -xs*P[i]-1))
        else:
            for i in it:
                k, e, f = (yt - yg*YS[i]) // ys, xt - xg*XS[i] - D[i], xt - xg*XS[i]
                if P[i] and (yt-yg*YS[i]) % ys == 0 and 0 <= (yt - yg*YS[i]) // ys < P[i] and e <= k*xs < f:
                    r += 1

        if i_after < n and i_after%4 == (5-rot)%4:
            k = P[i_after]
            if yt == ys*k + yg*YS[i_after] and xs*k + xg*XS[i_after] < xt <= xs*k + xg*XS[i_after] + t_after:
                r += 1

        xt, yt = yt, -xt
        xg = -xg
        XS, YS = YS, XS
        xg, yg = yg, xg

    print(r)

main()
