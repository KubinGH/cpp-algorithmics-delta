#include <iostream>

using namespace std;

template<typename T>
struct k_queue
{
    struct node
    {
        node* next = nullptr;
        T value;
    } *head = nullptr, *tail = nullptr;

    k_queue() {}

    void push(T value)
    {
        node* curr = new node;
        curr->next = nullptr; curr->value = value;
        if(tail)
            tail->next = curr, tail = curr;
        else
            head = tail = curr;
    }

    void pop()
    {
        node* curr = head->next;
        delete head;
        head = curr;
        if(not curr)
            tail = nullptr;
    }

    T& front()
    {
        return head->value;
    }
    const T& front() const
    {
        return head->value;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t q;
    cin >> q;
    k_queue<int> Q;
    while(q --> 0)
    {
        char c;
        cin >> c;
        if(c == '+')
        {
            int x;
            cin >> x;
            Q.push(x);
        }
        else if(c == '-')
        {
            cout << Q.front() << "\n";
            Q.pop();
        }
    }
}
