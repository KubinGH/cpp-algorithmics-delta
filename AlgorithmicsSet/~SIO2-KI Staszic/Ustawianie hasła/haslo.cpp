#include <bits/stdc++.h>
#include <ext/numeric>
#include <ext/functional>

using namespace std;
using __gnu_cxx::power;
using __gnu_cxx::identity;

// begin include <ktl/text/aho_corasick.cpp>

namespace aho_corasicks
{
    template<size_t N>
    struct static_node
    {
        size_t id;
        array<static_node*, N> edges;
        vector<size_t> edgelist;
        static_node *parent, *suflink, *dictlink; size_t match;
        static_node() : parent(nullptr), suflink(nullptr), dictlink(nullptr), match(-1u)
            { edges.fill(nullptr); }
        static_node* get_edge(size_t index) { return edges[index]; }

    };
    template<typename T>
    struct dynamic_node
    {
        size_t id;
        map<T, dynamic_node*> edges;
        vector<T> edgelist;
        dynamic_node *parent, *suflink, *dictlink; size_t match;
        dynamic_node() : parent(nullptr), suflink(nullptr), dictlink(nullptr), match(-1u) {}
        dynamic_node* get_edge(T value)
        {
            auto it = edges.find(value);
            return it == edges.end() ? nullptr : it->second;
        }
    };
    template<typename T, T minuend>
    struct partial_minus
    {
        T operator() (T x) const { return x - minuend; }
    };
}

template<typename T, typename Node, typename ElementFix>
struct aho_corasick
{
    static ElementFix fix;
    Node *nullnode, *root;
    vector<Node*> nodes, nodes_by_id;
    template<typename Iterator>
    aho_corasick(Iterator first, Iterator last)
    {
        nodes.push_back(new Node); nodes.push_back(new Node);
        nullnode = nodes[0]; root = nodes[1];
        nullnode->id = 0; root->id = 1;
        nullnode->parent = nullnode; root->parent = nullnode;
        nodes_by_id = {nullnode};
        size_t match_no = 0;

        while(first != last)
        {
            Node* curr = root;
            auto vfirst = first->first; auto vlast = first->second;
            do {
                T value = fix(*vfirst);
                if(curr->get_edge(value) == nullptr)
                {
                    nodes.push_back(new Node);
                    curr->edges[value] = nodes.back();
                    curr->edgelist.push_back(value);
                    nodes.back()->parent = curr;
                }
                curr = curr->get_edge(value);
            } while(++vfirst != vlast);
            if(curr->match == -1u) curr->match = match_no;
            match_no++; first++;
        }

        queue<pair<Node*, T>> Q; Q.emplace(root, T());
        root->suflink = nullnode; root->dictlink = nullnode;
        nullnode->suflink = nullnode; nullnode->dictlink = nullnode;
        while(not Q.empty())
        {
            Node* curr; T value; tie(curr, value) = Q.front(); Q.pop();
            curr->id = nodes_by_id.size();
            nodes_by_id.push_back(curr);
            for(T next_value : curr->edgelist)
                if(curr->get_edge(next_value) != nullptr)
                    Q.emplace(curr->get_edge(next_value), next_value);
            if(curr == root) continue;

            curr->suflink = curr->parent->suflink;
            while(curr->suflink != nullnode and curr->suflink->get_edge(value) == nullptr)
                curr->suflink = curr->suflink->suflink;
            curr->suflink = curr->suflink == nullnode ? root : curr->suflink->get_edge(value);

            if(curr->suflink->match != -1u)
                curr->dictlink = curr->suflink;
            else
                curr->dictlink = curr->suflink->dictlink;
        }
    }
    ~aho_corasick()
    {
        for(Node* node : nodes)
            delete node;
    }


    struct state
    {
        aho_corasick* owner;
        Node* node;
        state advance(T value) const
        {
            value = fix(value);
            for(Node* backtrack = node; backtrack != owner->nullnode; backtrack = backtrack->suflink)
            {
                Node* extend = backtrack->get_edge(value);
                if(extend != nullptr)
                    return {owner, extend};
            }
            return {owner, owner->root};
        }
        bool valid() const { return node != owner->nullnode; }
        bool valid_match() const { return valid() and node != owner->root; }
        bool matches() const { return node->match != -1u; }
        size_t match() const { return node->match; }
        state next_match() const { return {owner, node->dictlink}; }
    };

    state begin() { return {this, root}; }
};
template<typename T, typename Node, typename ElementFix>
ElementFix aho_corasick<T, Node, ElementFix>::fix;

// end include <ktl/text/aho_corasick.cpp>

const uint64_t MOD = 1e9 + 7;

struct matrix
{
    size_t n;
    vector<uint64_t> A;
    bool is_identity = false;
    matrix(size_t _n) : n(_n), A(n*n) {}
    uint64_t& operator() (size_t i, size_t j) { return A[i*n + j]; }
    const uint64_t& operator() (size_t i, size_t j) const { return A[i*n + j]; }
};
matrix identity_element(multiplies<matrix>) { matrix m(0); m.is_identity = true; return m; }

matrix operator* (const matrix& a, const matrix& b)
{
    if(a.is_identity) return b;
    if(b.is_identity) return a;
    const size_t n = a.n, g = n - 1;
    matrix c(n);
    fill(c.A.begin(), c.A.end(), 0);
    for(size_t i = 0; i < n; i++)
        for(size_t j = 0; j < n; j++)
            for(size_t k = 0; k < n; k++)
    {
        c(i, j) += a(i, k)*b(k, j);
        if((g - k) % 16 == 0)
            c(i, j) %= MOD;
    }
    return c;
}

int main()
{
    size_t n, m;
    cin >> n >> m;

    vector<string> dict(m);
    vector<pair<string::iterator, string::iterator>> iters;
    for(size_t i = 0; i < m; i++)
    {
        cin >> dict[i];
        iters.emplace_back(dict[i].begin(), dict[i].end());
    }

    using my_aho_corasick = aho_corasick<
        char, aho_corasicks::dynamic_node<char>, identity<char>
    >;
    my_aho_corasick A(iters.begin(), iters.end());

    const size_t k = A.nodes.size() - 1;

    auto has_match = [](const my_aho_corasick::state& c) {
        return c.matches() or c.next_match().valid_match();
    };

    matrix G(k+1);
    vector<bool> vis(k);
    queue<size_t> Q;
    Q.push(0);
    vis[0] = true;
    while(not Q.empty())
    {
        size_t i = Q.front();
        Q.pop();
        my_aho_corasick::state c = {&A, A.nodes_by_id[i + 1]};
        for(char v = 'a'; v <= 'z'; v++)
        {
            auto x = c.advance(v);
            size_t j = x.node->id - 1;
            if(has_match(x))
                G(i, k)++;
            else
                G(i, j)++;
            if(not vis[j])
                vis[j] = true, Q.push(j);
        }
    }
    G(k, k) += 'z'-'a'+1;

    matrix P = power(G, n);

    uint64_t result = 0;

    for(size_t i = 0; i < k; i++)
        result += P(0, i), result %= MOD;

    cout << result;
}
