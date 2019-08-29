#define M(n) N(n), N(n + (1 << 12))
#define N(n) O(n), O(n + (1 << 11))
#define O(n) P(n), P(n + (1 << 10))
#define P(n) Q(n), Q(n + (1 << 9))
#define Q(n) R(n), R(n + (1 << 8))
#define R(n) S(n), S(n + (1 << 7))
#define S(n) T(n), T(n + (1 << 6))
#define T(n) U(n), U(n + (1 << 5))
#define U(n) V(n), V(n + (1 << 4))
#define V(n) W(n), W(n + (1 << 3))
#define W(n) X(n), X(n + (1 << 2))
#define X(n) Y(n), Y(n + (1 << 1))
#define Y(n) Z(n), Z(n + (1 << 0))
#define Z(n) (8*(n)+0), (8*(n)+1), (8*(n)+2), (8*(n)+3), \
	     (8*(n)+4), (8*(n)+5), (8*(n)+6), (8*(n)+7)

template<int... p>
class t 
{
	t()
	{
		p = 0;
	}
};

t<N(0)> x;
