#include <iostream>
#include <vector>
#include <cstdint>
#include <stack>

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, s;
    cin >> n >> s;
    vector<uint64_t> V[2];
    V[0].resize(n - 1); V[1].resize(n - 1);
    for(uint32_t i = 0; i < n - 1; i++)
        cin >> V[0][i] >> V[1][i];
	
	auto first_right_solve = [&]() {
		pair<uint64_t, vector<uint32_t>> result = {0, {}};
		
		vector<uint64_t> suff_min(n);
		vector<bool> suff_back(n);
		
		for(uint32_t i = 1; i <= n - 1; i++)
		{
			bool ch = V[0][n-i-1] >= V[1][n-i-1];
			suff_min[i] = suff_min[i-1] + V[ch][n-i-1];
			suff_back[i] = ch;
		}
		
		uint32_t opt = 0; 
		uint64_t opt_result = -1llu, left_sum = V[0][0];
		for(uint32_t i = 2; i <= min(n - 1, s); i++)
		{
			uint64_t curr = left_sum + V[1][i-1] + suff_min[n-i-1];
			if(curr < opt_result)
				opt = i, opt_result = curr;
			left_sum += V[0][i-1];
		}
		if(n == s and left_sum < opt_result)
		{
			result.first = left_sum;
			for(uint32_t i = n+1; i --> 1; )
				result.second.push_back(i);
			return result;
		}
		result.first = opt_result;
		
		deque<uint32_t> to_visit;
		for(uint32_t i = 1; i <= n; i++) if(i != s)
			to_visit.push_back(i);
			
		vector<bool> plan; plan.reserve(n-1);
		for(uint32_t i = 1; i < opt; i++)
			plan.push_back(0);
		plan.push_back(1);
		for(uint32_t k = n-opt; k --> 1; )
			plan.push_back(suff_back[k]);
		
		result.second.push_back(s);
		
		for(uint32_t i = 0; i < n - 1; i++)
		{
			uint32_t j = i;
			while(j < n - 1 and plan[i] == plan[j])
				j++;
			uint32_t len = j - i;
			i += len - 1;
			stack<uint32_t> S;
			if(plan[i] == 0)
			{
				for(uint32_t t = 0; t < len; t++)
				{
					S.push(to_visit.front());
					to_visit.pop_front();
				}
			}
			else
			{
				for(uint32_t t = 0; t < len; t++)
				{
					S.push(to_visit.back());
					to_visit.pop_back();
				}
			}
			while(not S.empty())
				result.second.push_back(S.top()), S.pop();
		}
		return result;
	};
	
	pair<uint64_t, vector<uint32_t>> first = first_right_solve();
	
	for(uint32_t i = 0; i < n - 1; i++)
		swap(V[0][i], V[1][i]);
	s = n - s + 1;
	pair<uint64_t, vector<uint32_t>> second = first_right_solve();
	for(uint32_t i = 0; i < n - 1; i++)
		swap(V[0][i], V[1][i]);
	s = n - s + 1;
	for(uint32_t i = 0; i < n; i++)
		second.second[i] = n - second.second[i] + 1;

	auto sol = min(first, second);	
	cout << sol.first << "\n";
	for(auto x : sol.second)
		cout << x << " ";
}