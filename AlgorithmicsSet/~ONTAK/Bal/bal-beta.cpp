#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct implicit_treap
{
    struct node
    {
        T value;
        uint_fast32_t priority;
        node *left, *right;
        size_t count;
        bool reverse;

        void touch()
        {
            if(reverse)
            {
                swap(left, right);
                if( left)  left->reverse ^= 1;
                if(right) right->reverse ^= 1;
                reverse = false;
            }
        }
        size_t lcount() const { return left  ? left ->count : 0; }
        size_t rcount() const { return right ? right->count : 0; }
        void update()
        {
            count = lcount() + rcount() + 1;
        }

        static pair<node*, node*> split(node* that, size_t point, size_t fix = 0)
        {
            if(not that) return {nullptr, nullptr};
            that->touch();
            const size_t c = that->lcount() + 1;
            if(fix + c <= point)
            {
                auto sub = split(that->right, point, fix + c);
                that->right = sub.first; that->update();
                if(sub.second) sub.second->touch();
                return {that, sub.second};
            }
            else
            {
                auto sub = split(that->left, point, fix);
                that->left = sub.second; that->update();
                if(sub.first) sub.first->touch();
                return {sub.first, that};
            }
        }

        static node* meld(node* lhs, node* rhs)
        {
            if(not lhs) return rhs;
            if(not rhs) return lhs;

            lhs->touch(); rhs->touch();
            if(lhs->priority > rhs->priority)
            {
                lhs->right = meld(lhs->right, rhs); lhs->update();
                return lhs;
            }
            else
            {
                rhs->left = meld(lhs, rhs->left); rhs->update();
                return rhs;
            }
        }
    } *root = nullptr;

    mt19937 gen;
    implicit_treap(uint_fast32_t seed = 0)
    {
        gen.seed(seed);
    }


    node* new_node(T value)
    {
        return new node {
            value, gen(), nullptr, nullptr, 1, false
        };
    }

    void heapify(node* curr)
    {
        if(not curr) return;
        auto mx = curr;
        if(curr->left and curr->left->priority > mx->priority)
            mx = curr->left;
        if(curr->right and curr->right->priority > mx->priority)
            mx = curr->right;
        if(mx != curr)
            swap(curr->priority, mx->priority), heapify(mx);
    }

    template<typename It>
    node* build(It first, It last)
    {
        if(first == last) return nullptr;
        It mid = first + (last - first) / 2;
        auto curr = new_node(*mid);
        curr->left  = build(first, mid);
        curr->right = build(mid+1, last);
        heapify(curr);
        curr->update();
        return curr;
    }

    template<typename It>
    implicit_treap(It first, It last, uint_fast32_t seed = 0)
    {
        gen.seed(seed);
        root = build(first, last);
    }

    tuple<node*, node*, node*> get_segment(size_t i, size_t j)
    {
        node *a, *bc, *b, *c;
        tie(a, bc) = node::split(root, i);
        tie(b, c) = node::split(bc, j-i+1);
        return make_tuple(a, b, c);
    }
    void repair(node* a, node* b, node* c)
    {
        root = node::meld(a, node::meld(b, c));
    }


    void insert(size_t i, T value)
    {
        node *lo, *hi;
        tie(lo, hi) = node::split(root, i);
        root = node::meld(node::meld(lo, new_node(value)), hi);
    }

    T operator[] (size_t i)
    {
        node *a, *b, *c;
        tie(a, b, c) = get_segment(i, i);
        auto value = b->value;
        repair(a, b, c);
        return value;
    }

    void reverse(size_t i, size_t j)
    {
        node *a, *b, *c;
        tie(a, b, c) = get_segment(i, j);
        b->reverse = true;
        repair(a, b, c);
    }

    void dealloc_tree(node* curr)
    {
        if(curr->left)  dealloc_tree(curr->left);
        if(curr->right) dealloc_tree(curr->right);
        delete curr;
    }

    ~implicit_treap()
    {
        if(root) dealloc_tree(root);
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    cin >> n >> q;

    vector<int> A(n);
    for(auto& a : A)
        cin >> a;

    implicit_treap<int> ent(A.begin(), A.end(), n ^ q);

    while(q --> 0)
    {
        char c;
        cin >> c;
        if(c == 'Q')
        {
            size_t i;
            cin >> i; i--;
            cout << ent[i] << '\n';
        }
        else if(c == 'I')
        {
            size_t i, j;
            cin >> i >> j; i--; j--;
            ent.reverse(i, j);
        }
    }
}
