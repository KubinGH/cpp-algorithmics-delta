#include "min.cpp"
#include "bits/stdc++.h"

using namespace std;

static void WA(int no) {
  cerr << "Wrong answer [" << no << "].\n";
  exit(1);
}

namespace minzaw {

  const int MAX_QUERIES = 1000*1000;

  int N;
  vector <int> type, inside;
  vector <bool> used, answered;
  int no_queries = 0, no_inside = 0;

  int Query(int x) {
    //cerr << "Query(" << x << ")" << endl;
    if(not(1 <= x and x <= 2*N)) cerr << "Query out of range: " << x << endl, WA(1);
    no_queries++;
    //if(no_queries > MAX_QUERIES) WA(2);
    if(used[x]) {
      used[x] = false;
      inside[type[x]]--;
      if(inside[type[x]] == 0) no_inside--;
    } else {
      used[x] = true;
      inside[type[x]]++;
      if(inside[type[x]] == 1) no_inside++;
    }
    return no_inside;
  }

  void Answer(int a, int b) {
    //cerr << "Answer(" << a << ", " << b << ")" << endl;
    if(not(1 <= a and a <= 2*N)) cerr << "Answer a out of range: " << a << endl, WA(3);
    if(not(1 <= b and b <= 2*N)) cerr << "Answer a out of range: " << b << endl, WA(3);
    if(answered[a] or answered[b]) cerr << "a/b already bound: " << a << " " << b << endl, WA(4);
    if(type[a] != type[b]) cerr << "Answer is incorrect: " << a << " " << b << endl, WA(5);
    answered[a] = answered[b] = true;
  }

  void Work() {
    cin >> N;
    inside.resize(N+1);
    type.resize(2*N+1);
    used.resize(2*N+1);
    answered.resize(2*N+1);
    for(int i=1; i<=N; i++) {
      int x, y;
      x = i; y = i + N;
      cin >> x >> y;
      type[x] = type[y] = i;
    }
    Solve(N);
    for(int i=1; i<=2*N; i++) if(!answered[i]) WA(6);
    cerr << "Accepted: " << no_queries << "\n";
  }

}

int Query(int x) {
  return minzaw::Query(x);
}

void Answer(int a, int b) {
  minzaw::Answer(a, b);
}

int main() {
  minzaw::Work();
}
