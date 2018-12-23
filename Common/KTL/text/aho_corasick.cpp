#include <bits/stdc++.h>

using namespace std;
namespace aho_corasicks
{
    template<size_t N>
    struct static_node
    {
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
}

template<typename T, typename Node, typename ElementFix>
struct aho_corasick
{
    static ElementFix fix;
    Node *nullnode, *root;
    vector<Node*> nodes;
    template<typename Iterator>
    aho_corasick(Iterator first, Iterator last)
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
    ~aho_corasick()
    {
        for(Node* node : nodes)
            delete node;
    }


    struct state
    {
        aho_corasick* owner;
        Node* node;
        state advance(T value)
        {
            value = fix(value);
            Node* backtrack = node;
            while(backtrack != owner->nullnode)
            {
                Node* extend = backtrack->get_edge(value);
                if(extend != nullptr)
                    return {owner, extend};
                backtrack = backtrack->suflink;
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

template<typename T, T minuend>
struct partial_minus
{
    T operator() (T x) const { return x - minuend; }
};
/*
abccab
7
a
ab
bab
bc
bca
c
caa
*/

int main()
{
    string M;
    cin >> M;
    uint32_t n;
    cin >> n;
    vector<string> D(n); vector<pair<string::iterator, string::iterator>> DI(n);
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> D[i];
        DI[i] = {D[i].begin(), D[i].end()};
    }
    aho_corasick<char, aho_corasicks::static_node<26>, partial_minus<char, 'a'>>
        T(DI.begin(), DI.end());
    auto curr = T.begin();
    for(uint32_t i = 0; i < M.size(); i++)
    {
        curr = curr.advance(M[i]);
        cout << "curr @ " << curr.node << endl;
        auto temp = curr.matches() ? curr : curr.next_match();
        while(temp.valid_match())
        {
            cout << temp.match() << " @ " << i << endl;
            temp = temp.next_match();
        }
    }
}
