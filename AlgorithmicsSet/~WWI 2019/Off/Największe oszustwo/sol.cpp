#include <bits/stdc++.h>
#include <ktl/util/debug_macros.cpp>
#include <ktl/util/extio.cpp>

using namespace std;

namespace f1
{
    unsigned hash(std::string const& S) {
        unsigned val = 0;
        for(char c: S) {
            val = ((val << 5) | (val >> 27)) ^ c;
        }
        return val;
    }

    bool eq(std::string const& A, std::string const& B) {
        if (A.length() != B.length()) return false;
        return hash(A) == hash(B);
    }
}

namespace f2
{
    unsigned long long hash(std::string const& S) {
        unsigned long long val = 0;
        const long long P = 125097457;
        const long long Q = 989249411;
        for(char c: S) {
            val = (val * P + c) % Q;
        }
        return val;
    }
    unsigned long long hash(char* a, char *b) {
        return hash(string(a, b));
    }
    bool eq(std::string const& A, std::string const& B) {
        if (A.length() != B.length()) return false;
        return hash(A) == hash(B);
    }
}

namespace f3
{
    unsigned long long hash(std::string const& s) {
        unsigned long long val = 0;
        const long long p = 1235031313;
        for(char c: s) {
            val = val * p + c;
        }
        return val;
    }
    unsigned long long hash(char* a, char *b) {
        return hash(string(a, b));
    }
    bool eq(std::string const& a, std::string const& b) {
        if (a.length() != b.length()) return false;
        return hash(a) == hash(b);
    }
}

namespace f4
{
    unsigned long long hash(std::string const& S) {
        unsigned long long val = 0;
        const long long P = 123456789129921817ll;
        const long long Q = 987654321990767903ll;
        for(char c: S) {
            val = (static_cast<__uint128_t>(val) * P + c) % Q;
        }
        return val;
    }
    unsigned long long hash(char *first, char *last) {
        unsigned long long val = 0;
        const long long P = 123456789129921817ll;
        const long long Q = 987654321990767903ll;
        for(char* it = first; it != last; ++it) {
            val = (static_cast<__uint128_t>(val) * P + *it) % Q;
        }
        return val;
    }
    bool eq(std::string const& A, std::string const& B) {
        if (A.length() != B.length()) return false;
        return hash(A) == hash(B);
    }
}

namespace f5
{
    std::vector<long long unsigned> Ps = {
        195688749456722940llu,
        10171877582990714540llu,
        12881977372630504442llu,
        14992807499564125639llu,
        8533976720013886615llu,
        18146351945582388344llu,
        8852360169711692322llu,
        6046410735046753737llu,
        101593162357938336llu,
        17366427465974227976llu,
        14473938324428218966llu,
        9448466573266392919llu,
        15873389189717648135llu,
        5815835263440967534llu,
        12080672730796021322llu,
        452672781690685990llu}, Qs = {
        2009393647044798450llu,
        14772471554262078307llu,
        3868942717470439770llu,
        10116414958431080609llu,
        12240684982096309196llu,
        13927438274629806502llu,
        15394825880068674429llu,
        17900932972021141111llu,
        2389526654270988215llu,
        7983949436602086553llu,
        6812212898381342636llu,
        17185183462413892013llu,
        11992997003736263135llu,
        4322996945210141216llu,
        13937631880559704775llu,
        14593148736838752946llu
    };
    std::array<unsigned long long, 16> hash(std::string const& S) {
        std::array<unsigned long long, 16> res;
        for(int i=0; i<16; i++) {
            unsigned long long val = 0;
            for(char c: S) {
                val = (static_cast<__uint128_t>(val) * Ps[i] + c) % Qs[i];
            }
            res[i] = val;
        }
        return res;
    }
    bool eq(std::string const& A, std::string const& B) {
        if (A.length() != B.length()) return false;
        return hash(A) == hash(B);
    }
}

size_t count_letters(string a)
{
    return count_if(a.begin(), a.end(), [](char c) { return 'a' <= c and c <= 'z'; });
}

auto random_letter()
{
    static mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());
    return uniform_int_distribution<char>{'a', 'z'}(gen);
}

auto random_word(size_t len)
{
    char* s = new char[len];
    generate(s, s + len, random_letter);
    return s;
}

template<typename Hash>
pair<string, string> birthday_attack(size_t len, size_t space_size, Hash hash)
{
    map<result_of_t<Hash(char*, char*)>, char*> space;
    cout << "Filling up space . . . " << endl;
    for(size_t i = 0; i < space_size; i++)
    {
        if(i == 0 or i*100 / space_size != (i+1)*100 / space_size)
            cout << "\r" << i*100/space_size << "%" << flush;
        auto wd = random_word(len);
        space[hash(wd, wd + len)] = wd;
    }
    cout << "\rDone!" << endl;

    cout << "Looking for collisions . . . " << endl;
    cout << "Iteration: " << endl;

    pair<string, string> result;

    size_t i = 0;
    while(++i)
    {
        if((i-1) % 10000 == 0)
            cout << "\r " << i << flush;
        auto wd = random_word(len);
        auto it = space.find(hash(wd, wd + len));
        if(it != space.end() and wd != it->second)
        {
            result = {string(wd, wd + len), string(it->second, it->second + len)};
            break;
        }
        delete wd;
    }
    cout << "\r " << i << endl;
    cout << endl << "Found collision! (after " << i << " iterations)" << endl;

    for(auto p : space)
        delete p.second;

    return result;
}

// Pierwsze 5 bitów na koniec
pair<string, string> solve1()
{
    const size_t k = 5;
    return {string(k*32, 'a'), string(k*32, 'b')};
}

pair<string, string> solve2()
{
    return birthday_attack(16, (1 << 20), [](char* a, char* b) { return f2::hash(a, b); });
}
pair<string, string> solve3()
{
    const int Q = 9;
    const int N = 1 << Q;
    std::string S(N, ' '), T(N, ' ');

    for (int i = 0; i < N; i++)
        S[i] = 'a' + __builtin_popcount(i) % 2;
    for (int i = 0; i < N; i++)
        T[i] = 'b' - __builtin_popcount(i) % 2;

    return {S, T};
}
pair<string, string> solve4()
{
    return birthday_attack(12, (1ul << 24), [](char* a, char* b) { return f4::hash(a, b); });
}
pair<string, string> solve5() {}

int main()
{
    size_t n;
    cout << "Solve: ";
    cin >> n;
    function<pair<string, string>()> solvers[] = {
        solve1, solve2, solve3, solve4, solve5
    };
    auto p = solvers[n - 1]();
    string a, b;
    tie(a, b) = p;

    //cout << a << endl << b << endl;

    bool same_size = a.size() == b.size(), inequal = a != b,
         size_ok = 10 <= a.size() and a.size() <= 1000, is_collision = true,
         letters_only = count_letters(a) == a.size() and count_letters(b) == b.size();

    cout << note(same_size) << ": " << a.size() << ", " << b.size() << endl;
    cout << note(inequal) << endl;
    cout << note(size_ok) << endl;
    cout << note(letters_only) << endl << ": " << count_letters(a) << "/" << a.size() << ", " << count_letters(b) << "/" << b.size() << endl;
    #define F(__n, __ns) \
    if(n == __n) \
    { \
        auto A = __ns::hash(a), B = __ns::hash(b); \
        is_collision = A == B; \
        cout << "hashes: " << A << ", " << B << endl; \
    }
    F(1, f1); F(2, f2); F(3, f3); F(4, f4); F(5, f5);
    #undef F

    cout << note(is_collision) << endl;

    if(same_size and inequal and size_ok and letters_only and is_collision)
    {
        string name = "sol" + to_string(n) + "!" + to_string(time(0)) + ".txt";
        cout << "All OK, writing to `" << name << "`" << endl;
        ofstream fout(name);
        fout << a << endl << b << flush;
        fout.close();
        cout << "Done :)" << endl;
    }
    else
        cout << ":(" << endl;
}
