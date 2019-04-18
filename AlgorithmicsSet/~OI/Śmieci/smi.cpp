#include <bits/stdc++.h>

using namespace std;

struct node
{
    size_t index;
    unordered_set<node*> incident;

    bool stacked = false;

    void eulerian_travel(vector<node*>& out)
    {
        out.push_back(this);

        if(incident.empty())
            return;

        node* next = *incident.begin();
        incident.erase(incident.begin());
        next->incident.erase(this);

        next->eulerian_travel(out);
    }
};

bool eulerian_cycle_exists(const vector<node*>& graph)
{
    for(auto u : graph)
        if(u->incident.size() % 2)
            return false;
    return true;
}

vector<vector<node*>> cycle_factorization(const vector<node*>& graph)
{
    vector<vector<node*>> cycles;
    vector<node*> traversal;
    for(const auto& s : graph)
    {
        while(not s->incident.empty())
        {
            s->eulerian_travel(traversal);

            stack<node*> run;
            for(auto u : traversal)
            {
                if(u->stacked)
                {
                    cycles.emplace_back();
                    do {
                        cycles.back().push_back(run.top());
                        run.top()->stacked = false;
                        run.pop();
                    } while(run.top() != u);
                    cycles.back().push_back(run.top()); run.pop();
                    reverse(cycles.back().begin(), cycles.back().end());
                }
                u->stacked = true;
                run.push(u);
            }
            traversal.clear();
        }
    }

    return cycles;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    size_t n, m;
    cin >> n >> m;

    vector<node*> graph(n);
    for(size_t i = 0; i < n; i++)
        graph[i] = new node, graph[i]->index = i;

    auto dealloc_graph = [&]() {
        for(auto u : graph)
            delete u;
    };

    for(size_t i = 0; i < m; i++)
    {
        size_t a, b; bool s, t;
        cin >> a >> b >> s >> t; a--; b--;
        if(s != t)
        {
            graph[a]->incident.insert(graph[b]);
            graph[b]->incident.insert(graph[a]);
        }
    }

    if(eulerian_cycle_exists(graph))
    {
        auto cycles = cycle_factorization(graph);
        cout << cycles.size() << endl;
        for(const auto& cycle : cycles)
        {
            cout << cycle.size() << " ";
            for(auto u : cycle)
                cout << u->index + 1 << " ";
            cout << cycle.front()->index + 1 << "\n";
        }
    }
    else
        cout << "NIE" << endl;

    dealloc_graph();
}