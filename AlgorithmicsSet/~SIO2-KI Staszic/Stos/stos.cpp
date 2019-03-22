#include <iostream>

using namespace std;

template<typename T>
struct k_stack
{
    struct node
    {
        T value;
        node *below;
    } *head = nullptr;

    void push(T value)
    {
        node* curr = new node;
        curr->below = head; curr->value = value;
        head = curr;
    }

    void pop()
    {
        head = head->below;
    }

    T& top()
    {
        return head->value;
    }

    const T& top() const
    {
        return head->value;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t q;
    cin >> q;

    k_stack<int> S;
    while(q --> 0)
    {
        char c;
        cin >> c;
        if(c == '+')
        {
            int x;
            cin >> x;
            S.push(x);
        }
        else if(c == '-')
        {
            cout << S.top() << "\n";
            S.pop();
        }
    }
}