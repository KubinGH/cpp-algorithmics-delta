#include <bits/stdc++.h>

using namespace std;

template<typename T, size_t N, typename ElementFix>
struct advmemo_aho_corasick
{
    struct Node
    {
        array<Node*, N> edges, advmemo;
        vector<size_t> edgelist;
        Node *parent, *suflink, *dictlink; size_t match;
        Node() : parent(nullptr), suflink(nullptr), dictlink(nullptr), match(-1u)
            { edges.fill(nullptr); advmemo.fill(nullptr); }
        Node* get_edge(size_t index) { return edges[index]; }

    };
    static ElementFix fix;
    Node *nullnode, *root;
    vector<Node*> nodes;
    template<typename Iterator>
    advmemo_aho_corasick(Iterator first, Iterator last)
    {
        nodes.push_back(new Node); nodes.push_back(new Node);
        nullnode = nodes[0]; root = nodes[1];
        root->parent = nullnode; nullnode->parent = nullnode;
        size_t match_no = 0;

        do {
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
            match_no++;
        } while(++first != last);

        queue<pair<Node*, T>> Q; Q.emplace(root, T());
        root->suflink = nullnode; root->dictlink = nullnode;
        nullnode->suflink = nullnode; nullnode->dictlink = nullnode;
        while(not Q.empty())
        {
            Node* curr; T value; tie(curr, value) = Q.front(); Q.pop();
            for(T next_value : curr->edgelist)
                if(curr->get_edge(next_value) != nullptr)
                    Q.emplace(curr->get_edge(next_value), next_value);
            if(curr == root) continue;
            //Node* extend = backtrack == nullnode ? root : backtrack->get_edge(value);
            curr->suflink = curr->parent->suflink;
            while(curr->suflink != nullnode and curr->suflink->get_edge(value) == nullptr)
                curr->suflink = curr->suflink->suflink;
            auto extend = curr->suflink == nullnode ? root : curr->suflink->get_edge(value);
            if(extend != nullptr)
                curr->suflink = extend;
            if(curr->suflink->match != -1u)
                curr->dictlink = curr->suflink;
            else
                curr->dictlink = curr->suflink->dictlink;
        }
    }
    ~advmemo_aho_corasick()
    {
        for(Node* node : nodes)
            delete node;
    }


    struct state
    {
        advmemo_aho_corasick* owner;
        Node* node;
        state advance(T value)
        {
            if(node == owner->nullnode)
                return {owner, owner->root};
            T fvalue = fix(value);
            if(node->advmemo[fvalue] != nullptr)
                return {owner, node->advmemo[fvalue]};
            Node* extend = node->get_edge(fvalue);
            if(extend != nullptr)
                return {owner, node->advmemo[fvalue] = extend};
            else
            {
                state result = state{owner, node->suflink}.advance(value);
                node->advmemo[fvalue] = result.node;
                return result;
            }
        }
        bool valid() const { return node != owner->nullnode; }
        bool valid_match() const { return valid() and node != owner->root; }
        bool matches() const { return node->match != -1u; }
        size_t match() const { return node->match; }
        state next_match() const { return {owner, node->dictlink}; }
    };

    state begin() { return {this, root}; }
};

template<typename T, T minuend>
struct partial_minus
{
    T operator() (T x) const { return x - minuend; }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string S;
    cin >> S;
    uint32_t n;
    cin >> n;
    vector<string> D(n);
    vector<pair<string::iterator, string::iterator>> DI(n);
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> D[i];
        DI[i] = {D[i].begin(), D[i].end()};
    }
    advmemo_aho_corasick<char, 26, partial_minus<char, 'a'>>
        T(DI.begin(), DI.end());
    stack<decltype(T)::state> states;
    states.push(T.begin());
    string Z; Z.reserve(S.size());
    for(uint32_t i = 0; i < S.size(); i++)
    {
        Z += S[i];
        auto next = states.top().advance(S[i]);
        states.push(next);
        auto temp = next.matches() ? next : next.next_match();
        if(temp.valid_match())
        {
            uint32_t k = D[temp.match()].size();
            while(k --> 0)
                Z.pop_back(), states.pop();
        }
    }
    cout << Z;
}
