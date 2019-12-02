#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;

const int MAX = 1e5 + 10;
const ll  MOD = 103;

vector<int> adj[2][MAX];
int n, h[2][MAX], sz[2][MAX];
ll x[MAX];

ll randomLL(ll max) {
   double d = (double) rand() / ((double) RAND_MAX + 1); 
   ll k = d * (max + 1);
   return k;
}

void calcHeight(int u, int tree, int p) {
   for (int v : adj[tree][u]) {
      if (v != p) {
         calcHeight(v, tree, u);
         h[tree][u] = max(h[tree][v] + 1, h[tree][u]);
      }
   }
}

ll hashTree(int u, int tree, int p) {
   ll myHash = 1;
   for (int v : adj[tree][u]) {
      if (v != p) {
         myHash = (myHash * (x[h[tree][u]] + hashTree(v, tree, u))) % MOD;
      }
   }
   return myHash;
}

int main() {
   srand(time(NULL));
   for (int i = 0; i < MAX; i++)
      x[i] = randomLL(15);
   memset(h, 0, sizeof(h));

   int cases = 0;
   scanf("%d", &cases);
   for (int T = 0; T < cases; T++) {          
      scanf("%d", &n);
      
      for (int t = 0; t < 2; t++) {
         for (int i = 1; i < n; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            adj[t][u].push_back(v);
            adj[t][v].push_back(u);
         }
      }

      bool isomorphic = false;

      memset(h, 0, sizeof(h));
      calcHeight(1, 0, -1);
      calcHeight(1, 1, -1);
            
      ll hash1 = hashTree(1, 0, -1);
      ll hash2 = hashTree(1, 1, -1);
      if (hash1 == hash2) {
         isomorphic = true;
      }
      
      if (isomorphic)
         puts("YES");
      else
         puts("NO");

      printf("Hash --> %lld %lld\n", hash1, hash2);
      printf("maxHeight %d\n", h[0][1] > h[1][1] ? h[0][1] : h[1][1]);
      printf("x --> %lld %lld %lld %lld %lld %lld\n", x[0], x[1], x[2], x[3], x[4], x[5]);
      
      for (int t = 0; t < 2; t++) {         
         for (int i = 0; i <= n; i++) {
            adj[t][i].clear();
            h[t][i] = 0;
            sz[t][i] = 0;
         }
      }
   }

   return 0;
}
