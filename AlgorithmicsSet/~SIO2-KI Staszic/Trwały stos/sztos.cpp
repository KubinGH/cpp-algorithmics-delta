#include <iostream>
#include <vector>

using namespace std;

template<typename T>
struct node
{
    T value;
    node *below;
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t q;
    cin >> q;

    vector<node<int>*> heads;
    heads.push_back(new node<int> {-1, nullptr});

    for(uint32_t i = 0; i < q; i++)
    {
        char c;
        cin >> c;
        if(c == '+')
        {
            int value;
            cin >> value;
            heads.push_back(new node<int> { value, heads.back() });
        }
        else if(c == '-')
        {
            heads.push_back(new node<int> (*heads.back()->below));
        }
        else if(c == '*')
        {
            uint32_t r;
            cin >> r;
            heads.push_back(new node<int> (*heads[i - r]));
        }
        cout << heads.back()->value << "\n";
    }
}
