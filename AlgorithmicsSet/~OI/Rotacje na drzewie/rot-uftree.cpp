#include <bits/stdc++.h>

using namespace std;

const uint32_t W = 1 << 17;

void unite(set<uint32_t>& first, set<uint32_t>& second)
{
    if(first.size() > second.size())
        swap(first, second);
    for(uint32_t x : second)
        first.insert(x);
}

struct set_tree
{
    struct node
    {
        uint32_t value = 0;
        node *left_ptr = nullptr, *right_ptr = nullptr;
        node*  left() { return  left_ptr ?  left_ptr :  left_ptr = new node; }
        node* right() { return right_ptr ? right_ptr : right_ptr = new node; }
        ~node()
        {
            if( left_ptr) delete  left_ptr;
            if(right_ptr) delete right_ptr;
            delete this;
        }
    } *root;
    set<uint32_t> elem;

    set_tree() : root(new node) {}

    void clear(bool e = true) { if(e) elem.clear(); delete root; root = new node; }
    void insert(uint32_t x)
    {
        node* curr = root; curr->value++;
        uint32_t nodeL = 0, nodeR = W - 1;
        while(nodeL < nodeR)
        {
            uint32_t mid = (nodeL + nodeR) / 2;
            if(x <= mid)
                curr = curr->left(), nodeR = mid;
            else
                curr = curr->right(), nodeL = mid+1;
            curr->value++;
        }
        elem.insert(x);
    }
    static void root_join(node* A, node* B, node* C)
    {
        C->value = A->value + B->value;
        #define ptrjoin(__name, __name_attr)                        \
            if(A->__name and B->__name)                             \
                root_join(A->__name, B->__name, C->__name_attr());  \
            else if(A->__name)                                      \
                C->__name = A->__name;                              \
            else if(B->__name)                                      \
                C->__name = B->__name;
        ptrjoin(left_ptr, left);
        ptrjoin(right_ptr, right);
    }
    void join(set_tree& other)
    {
        /*
        node* new_root = new node;
        root_join(root, other.root, new_root);
        unite(elem, other.elem);
        clear(false); other.clear();
        root = new_root;
        */
        if(elem.size() < other.elem.size())
            swap(*this, other);
        unite(elem, other.elem);
        for(uint32_t x : other.elem)
            insert(x);
    }
    uint32_t get(node* curr, uint32_t nodeL, uint32_t nodeR, uint32_t getR) const
    {
        if(nodeL > getR)
            return 0;
        else if(nodeR <= getR)
            return curr->value;
        else
            return (curr-> left_ptr ? get(curr-> left(), nodeL, (nodeL+nodeR)/2, getR) : 0) +
                   (curr->right_ptr ? get(curr->right(), (nodeL+nodeR)/2+1, nodeR, getR) : 0);
    }
    uint32_t get(uint32_t getR) const { return get(root, 0, W-1, getR); }
};

uint64_t
count_inv(const set_tree& A, const set_tree& B)
{
    uint64_t result = 0;
    if(A.elem.size() <= B.elem.size())
        for(uint32_t a : A.elem)
            result += B.get(a - 1);
    else
        for(uint32_t b : B.elem)
            result += A.elem.size() - A.get(b - 1);
    return result;
}

pair<uint64_t, set_tree>
solve_tree()
{
    int32_t z;
    cin >> z;
    if(z == 0)
    {
        auto sA = solve_tree(), sB = solve_tree();
        uint64_t result = sA.first + sB.first;
        auto A = sA.second, B = sB.second;
        auto r1 = count_inv(A, B), r2 = count_inv(B, A);
        A.join(B);

        if(r1 <= r2)
            return {result + r1, A};
        else
            return {result + r2, A};
    }
    else
    {
        set_tree A;
        A.insert(z);
        return {0, A};
    }
}


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t _; cin >> _;
    cout << solve_tree().first;
}
