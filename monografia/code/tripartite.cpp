#include<bits/stdc++.h>
using namespace std;

const int MAX = 1e5 + 10;
const int MOD = 1e9 + 7;
vector<int> adj[MAX];
int n, m;
int code[MAX], C[MAX];

int hashAdjacencyList(vector<int>& v) {
   int res = 0;
   for (int x : v) {
      res ^= code[x];
   }
   return res;
}

int main() {
   srand(time(NULL));
   scanf("%d%d", &n, &m);
   for (int i = 0; i < m; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      adj[u].push_back(v);
      adj[v].push_back(u);
   }
   for (int i = 1; i <= n; i++) {
      code[i] = rand() % MOD;
   }

   map<int, int> M, cnt;
   int qtd = 0;
   for (int i = 1; i <= n; i++) {
      int val = hashAdjacencyList(adj[i]);
      if (M.find(val) == M.end()) {
         M[val] = ++qtd;
      }
      C[i] = M[val];
      cnt[M[val]]++;
   }
   bool trip = true;
   
   if (M.size() == 3) {
      for (int i = 1; i <= n; i++){
         if (adj[i].size() != (n - cnt[C[i]]))
            trip = false;
      }
   } else {
      trip = false;
   }

   if (trip) {
      for (int i = 1; i <= n; i++) 
         printf("%d ", C[i]);
      printf("\n");
   } else {
      puts("-1");
   }
   
   return 0;
}
