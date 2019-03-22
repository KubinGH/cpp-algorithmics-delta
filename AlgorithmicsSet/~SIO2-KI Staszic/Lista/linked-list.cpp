#include <iostream>
#include <vector>

using namespace std;

template<typename T>
struct linked_list
{
    struct node
    {
        T value;
        node *prev, *next;
    } *head = nullptr;

    node* push_front(T value)
    {
        node* curr = new node { value, nullptr, head };
        if(head)
            head->prev = curr;
        return head = curr;
    }

    node* push_after(T value, node* pre)
    {
        node* curr = new node { value, pre, pre->next };
        if(pre->next)
            pre->next->prev = curr;
        pre->next = curr;
        return curr;
    }

    void pop_front()
    {
        erase(head);
    }

    void erase(node* curr)
    {
        if(curr->prev)
            curr->prev->next = curr->next;
        else
            head = curr->next;
        if(curr->next)
            curr->next->prev = curr->prev;
        delete curr;
    }

    template<typename Callback>
    void for_each(Callback F)
    {
        auto curr = head;
        while(curr)
        {
            F(*curr);
            curr = curr->next;
        }
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t q;
    cin >> q;
    linked_list<int> L;
    vector<linked_list<int>::node*> nodes;
    nodes.reserve(q);
    while(q --> 0)
    {
        char c;
        cin >> c;
        if(c == '>')
        {
            int x;
            cin >> x;
            nodes.push_back(L.push_front(x));
        }
        else if(c == '+')
        {
            int x; uint32_t i;
            cin >> x >> i; i--;
            nodes.push_back(L.push_after(x, nodes[i]));
        }
        else if(c == '<')
        {
            L.pop_front();
            nodes.push_back(nullptr);
        }
        else if(c == '-')
        {
            uint32_t i;
            cin >> i; i--;
            L.erase(nodes[i]);
            nodes.push_back(nullptr);
        }
    }
    L.for_each([&](const linked_list<int>::node& curr) {
        cout << curr.value << " ";
    });
}
