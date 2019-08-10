#include <bits/stdc++.h>

using namespace std;

bool nul(long double x) { return abs(x) < 1e-9L; }

template<typename T>
struct simpoly
{
    vector<T> a;

    simpoly(initializer_list<T> _a) : a(_a) {}
    simpoly(size_t n) : a(n + 1) {}
    simpoly() : simpoly(0) {}

    size_t degree() const { return a.size() - 1; }
    T& operator[] (size_t i) { return a[i]; }
    const T& operator[] (size_t i) const { return a[i]; }

    operator bool() const
    {
        return degree() > 1 or not nul(a[0]);
    }

    T operator() (T x) const
    {
        T r = 0;
        for(size_t i = degree()+1; i --> 0; )
            r *= x, r += a[i];
        return r;
    }

    void normalize()
    {
        while(a.size() > 1 and nul(a.back()))
            a.pop_back();
    }

    friend simpoly operator* (const simpoly& P, const simpoly& Q)
    {
        simpoly R(P.degree() + Q.degree());
        for(size_t i = 0; i <= P.degree(); i++)
            for(size_t j = 0; j <= Q.degree(); j++)
                R[i+j] += P[i] * Q[j];
        return R;
    }

    friend simpoly operator+ (const simpoly& P, const simpoly& Q)
    {
        if(P.degree() > Q.degree())
            return Q + P;
        simpoly R = Q;
        for(size_t i = 0; i <= P.degree(); i++)
            R[i] += P[i];
        R.normalize();
        return R;
    }

    simpoly operator- () const
    {
        auto R = *this;
        for(size_t i = 0; i <= degree(); i++)
            R[i] = -R[i];
        return R;
    }

    friend simpoly operator- (const simpoly& P, const simpoly& Q)
    {
        auto R = P + (-Q);
        R.normalize();
        return R;
    }

    friend pair<simpoly, simpoly> divmod (const simpoly& N, const simpoly& D)
    {
        simpoly Q, R = N;
        while(R and R.degree() >= D.degree())
        {
            simpoly t(R.degree() - D.degree());
            t.a.back() += R.a.back() / D.a.back();
            Q = Q + t;
            R = R - t * D;
        }
        return {Q, R};
    }
    friend simpoly operator/ (const simpoly& P, const simpoly& Q)
    {
        return divmod(P, Q).first;
    }
    friend simpoly operator% (const simpoly& P, const simpoly& Q)
    {
        return divmod(P, Q).second;
    }

    simpoly derivative() const
    {
        if(not degree()) return {};
        simpoly R(degree() - 1);
        for(size_t i = degree()+1; i --> 1; )
            R[i-1] += a[i] * i;

        return R;
    }

    friend ostream& operator<< (ostream& out, const simpoly& P)
    {
        out << "(";
        bool initial = true;
        for(size_t i = P.degree()+1; i --> 1; )
        {
            if(nul(P[i]))
                continue;
            if(initial)
            {
                out << P[i];
                initial = false;
            }
            else
            {
                if(P[i] < 0)
                    out << " - ";
                else
                    out << " + ";
                out << abs(P[i]);
            }
            out << "x";
            if(i > 1) out << "^" << i;
        }
        if(initial)
            out << P[0];
        else
        {
            if(P[0] < 0)
                out << " - ";
            else
                out << " + ";
            out << abs(P[0]);
        }
        out << ")";
        return out;
    }

    T newton_find_root(T lo, T hi, size_t iterations = 32) const
    {
        static mt19937 guesser((size_t)unique_ptr<char>(new char).get() ^ 1337);

        auto Q = derivative();
        const auto& f = *this;
        const auto& f1 = Q;

        auto newton = [&](T x0) {
            return x0 - f(x0) / f1(x0);
        };
        auto guess = [&]() {
            return uniform_real_distribution<T>{lo, hi}(guesser);
        };
        T x = guess();

        for(size_t i = 0; i < iterations; i++)
        {
            x = newton(x);
            if(not (lo <= x and x <= hi))
                x = guess();
        }

        if(not nul(x - newton(x)) and not nul(f(x)))
            return newton_find_root(lo, hi, 2 * iterations);

        return x;
    }
};


int main()
{
    cout << fixed << setprecision(4);
    size_t n;
    using upoly = simpoly<long double>;

    size_t No = 1;
    while(cin >> n, n)
    {
        upoly P(n);
        for(size_t i = n+1; i --> 0; )
            cin >> P[i];

        vector<long double> roots;
        auto Q = P;
        for(size_t i = 0; i < n; i++)
        {
            auto r = Q.newton_find_root(-40, 40);
            Q = Q / upoly{-r, 1};
            roots.push_back(r);
        }

        sort(roots.begin(), roots.end());
        cout << "Equation " << No++ << ": ";
        for(auto r : roots)
            cout << r << " ";
        cout << '\n';
    }
}
