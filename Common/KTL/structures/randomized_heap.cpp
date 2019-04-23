// Pointer-based randomized heap implementation
// Allows for merging heaps in O(log n) - can be quite useful.
// Uses the same interface as ktl::heap

// Last revision: November 2018

#pragma once

#include <cstddef>
#include <functional>
#include <algorithm>
#include <random>

using std::mt19937; using std::size_t;
using std::less; using std::swap;
using std::uint32_t; using std::uint64_t;

template<typename T, typename Compare = less<T>>
struct randomized_heap
{
    struct node
    {
        node *left, *right; T value;
    } *root = nullptr;
    Compare C;
    mt19937 gen; uint32_t bits_ready = 0; uint32_t bits;
    template<typename Iterator>
    randomized_heap(Iterator first, Iterator last, uint64_t seed = 42, Compare c = {})
    {
        gen.seed(seed);
        C = move(c);
        while(first != last)
            insert(*first++);
    }
    randomized_heap(uint64_t seed = 42, Compare c = {})
        : randomized_heap((T*)0, (T*)0, seed, c) {}
    // Return a random bit (0 or 1) with uniform probability
    bool next_bit()
    {
        if(not bits_ready)
            bits_ready = 32, bits = gen();
        bits_ready--; bool r = bits&1; bits >>= 1;
        return r;
    }
    node* merge(node* first, node* second)
    {
        if(not first or not second)
            return first ? first : second;
        if(C(second->value, first->value)) // `first` must be the new root
            swap(first, second);
        if(next_bit())
            swap(first->left, first->right); // `right` is kept, `left` is merged with `second`
        first->left = merge(first->left, second);
        return first;
    }
    void merge(randomized_heap& other) { root = merge(root, other.root); other.root = nullptr; }
    void insert(T x) { root = merge(root, new node {nullptr, nullptr, x}); }
    void pop() { node* pre = root; root = merge(pre->left, pre->right); delete pre; }
    const T& top() const { return root->value; };
    bool empty() const { return root == nullptr; };
};
