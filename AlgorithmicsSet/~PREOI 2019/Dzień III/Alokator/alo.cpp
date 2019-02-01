#include "calolib.h"
#ifdef XHOVA
#define _GLIBCXX_DEBUG
#include "calozaw.cpp"
#endif // XHOVA
#include <bits/stdc++.h>

using namespace std;

// Wedlug mnie to nie jest tak, ze zadanie jest ciekawe albo nie ciekawe.
// Gdybym mial powiedziec, co cenie w zadankach najbardziej, to powiedzialbym,
// ze nie powinienem marnowac czasu na pisanie copypasty na kontescie.

struct Allocator
{
    static void perform_alloc(uint32_t pos) { dodaj(pos + 1); }
    static void finalize_dealloc() { zrobione(); }

    uint32_t n, counter = 0;
    deque<uint32_t> singles, doubles, triples;
    vector<uint32_t> owner_of, alloc_type, alloc_pos;

    Allocator(uint32_t _n) : n(_n), owner_of(n, -1u), alloc_type(n) { alloc_pos.reserve(1<<20); }

    void mem_move(uint32_t source, uint32_t dest, bool dest_in_reg = false)
    {
        uint32_t length = alloc_type[source];
        deque<uint32_t>& reg = (length == 1 ? singles : (length == 2 ? doubles : triples));
        uint32_t owner = owner_of[source];
        alloc_type[source] = 0; alloc_type[dest] = length;
        owner_of[source] = -1u; owner_of[dest] = owner;
        if(source == reg.front()) reg.pop_front();
        else if(source == reg.back()) reg.pop_back();
        else reg.erase(find(reg.begin(), reg.end(), source));
        if(not dest_in_reg)
        {
            if(reg.empty() or dest > reg.back()) reg.push_back(dest);
            else if(dest < reg.front()) reg.push_front(dest);
        }
        alloc_pos[owner] = dest;
        przesun(source + 1, dest + 1);
    }

    void push_singles(uint32_t allowed)
    {
        while(not singles.empty() and allowed --> 0)
        {
            uint32_t pos = doubles.empty() ? n - 1 : (doubles.front() - 1);
            if(singles.back() != pos)
                mem_move(*singles.begin(), singles.back() + 1);
        }
    }

    void dealloc(uint32_t pos)
    {
        alloc_pos.emplace_back();
        if(alloc_type[pos] == 1)
            dealloc1(pos);
        else if(alloc_type[pos] == 2)
            dealloc2(pos);
        else if(alloc_type[pos] == 3)
            dealloc3(pos);
    }

    void dealloc1(uint32_t pos)
    {
        alloc_pos[owner_of[pos]] = -1u;
        alloc_type[pos] = 0;
        uint32_t allowed = 2;
        if(pos != singles.front())
            mem_move(singles.front(), pos, true), allowed--;
        else
            owner_of[pos] = -1u, singles.pop_front();
        push_singles(allowed);
        finalize_dealloc();
    }
    void dealloc2(uint32_t pos)
    {
        alloc_pos[owner_of[pos]] = -1u;
        alloc_type[pos] = 0;
        uint32_t allowed = 2;
        if(pos != doubles.front())
            mem_move(doubles.front(), pos, true), allowed--;
        else
            owner_of[pos] = -1u, doubles.pop_front();
        push_singles(allowed);
        finalize_dealloc();
    }
    void dealloc3(uint32_t pos)
    {
        alloc_pos[owner_of[pos]] = -1u;
        alloc_type[pos] = 0;
        uint32_t allowed = 2;
        if(pos != triples.back())
            mem_move(triples.back(), pos, true), allowed--;
        else
            owner_of[pos] = -1u, triples.pop_back();
        push_singles(allowed);
        finalize_dealloc();
    }

    void alloc(uint32_t length)
    {
        if(length == 1)
            alloc1();
        else if(length == 2)
            alloc2();
        else if(length == 3)
            alloc3();
    }

    void alloc1()
    {
        alloc_pos.emplace_back();
        uint32_t owner = alloc_pos.size() - 1;
        if(not singles.empty())
        {
            uint32_t after = doubles.empty() ? n - 1 : (doubles.front() - 1);
            if(singles.back() == after)
                singles.push_front(alloc_pos[owner] = singles.front() - 1);
            else
                singles.push_back(alloc_pos[owner] = singles.back() + 1);
        }
        else
            singles.push_back(alloc_pos[owner] = doubles.empty() ? n - 1 : (doubles.front() - 1));
        alloc_type[alloc_pos[owner]] = 1;
        owner_of[alloc_pos[owner]] = owner;
        push_singles(2);
        perform_alloc(alloc_pos[owner]);
    }
    void alloc2()
    {
        alloc_pos.push_back(doubles.empty() ? n - 2 : (*doubles.begin() - 2));
        uint32_t owner = alloc_pos.size() - 1;
        uint32_t allowed = 2;
        if(not singles.empty() and singles.back() == alloc_pos[owner] + 1)
        {
            uint32_t dest = min(alloc_pos[owner] - 1, singles.front() - 1);
            mem_move(alloc_pos[owner] + 1, dest); allowed--;
        }
        if(not singles.empty() and singles.back() == alloc_pos[owner])
        {
            uint32_t dest = min(alloc_pos[owner] - 1, singles.front() - 1);
            mem_move(alloc_pos[owner], dest); allowed--;
        }
        alloc_type[alloc_pos[owner]] = 2;
        owner_of[alloc_pos[owner]] = owner;
        doubles.push_front(alloc_pos[owner]);
        push_singles(allowed);
        perform_alloc(alloc_pos[owner]);
    }
    void alloc3()
    {
        alloc_pos.push_back(triples.empty() ? 0 : triples.back() + 3);
        uint32_t owner = alloc_pos.size() - 1;
        alloc_type[alloc_pos[owner]] = 3;
        owner_of[alloc_pos[owner]] = owner;
        triples.push_back(alloc_pos[owner]);
        push_singles(2);
        perform_alloc(alloc_pos[owner]);
    }
};

int main()
{
    uint32_t n = inicjuj();
    Allocator sir_allocator(n);
    while(true)
    {
        int32_t query = zapytanie();
        if(query < 0)
            sir_allocator.dealloc(sir_allocator.alloc_pos[-query - 1]);
        else
            sir_allocator.alloc(query);
#ifdef XHOVA
        for(uint32_t i = 0; i < n; i++)
        {
            if(sir_allocator.alloc_type[i])
            {
                cerr << '#';
                for(uint32_t j = 1; j < sir_allocator.alloc_type[i-j+1]; i++, j++)
                    cerr << '|';
            }
            else
                cerr << '.';
        }
        cerr << '\n';
#endif
    }
}
