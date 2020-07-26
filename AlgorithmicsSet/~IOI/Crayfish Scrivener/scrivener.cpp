#include <bits/stdc++.h>

using namespace std;

constexpr size_t MAX = 1 << 20, MAX_LOG = __lg(MAX);

struct node
{
    char ch;
    node* ptr[MAX_LOG];
} epsilon, prealloc[MAX];
size_t prealloc_i;

size_t length(node* curr)
{
    if(curr == &epsilon)
        return 0;

    size_t r = 0;
    for(size_t k = MAX_LOG; k --> 0; )
        if(curr->ptr[k] != &epsilon)
            curr = curr->ptr[k], r += 1 << k;
    return r + 1;
}

vector<node*> history;

void Init()
{
    history.reserve(MAX);

    epsilon.ch = 0;
    fill(begin(epsilon.ptr), end(epsilon.ptr), &epsilon);
    history.push_back(&epsilon);

    prealloc_i = 0;
}

void TypeLetter(char c)
{
    node* next = &prealloc[prealloc_i++];
    next->ch = c;
    next->ptr[0] = history.back();
    for(size_t k = 1; k < MAX_LOG; k++)
        next->ptr[k] = next->ptr[k-1]->ptr[k-1];
    history.push_back(next);
}

void UndoCommands(int i)
{
    history.push_back(history.rbegin()[i]);
}

char GetLetter(int i)
{
    node* curr = history.back();

    i = length(curr) - i - 1;
    for(size_t k = MAX_LOG; k --> 0; )
        if(i >> k & 1)
            curr = curr->ptr[k];

    return curr->ch;
}
