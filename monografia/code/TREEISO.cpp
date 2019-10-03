#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;

const int MAX = 1e5 + 10;
const ll  MOD = 1e9 + 7;

vector<int> adj[2][MAX];
vector<int> centroids[2];
int n, h[2][MAX], sz[2][MAX];
ll x[MAX];

ll randomLL(ll max) {
   double d = (double) rand() / ((double) RAND_MAX + 1); 
   ll k = d * (max + 1);
   return k;
}
 
void calcDepth(int u, int tree, int p) {
   for (int v : adj[tree][u]) {
      if (v != p) {
         h[tree][v] = h[tree][u] + 1;
         calcDepth(v, tree, u);
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

void calcCentroids(int u, int tree, int p) {
   sz[tree][u] = 1;
   bool is_centroid = true;
   for (int v : adj[tree][u]) {
      if (v != p) {
         calcCentroids(v, tree, u);
         sz[tree][u] += sz[tree][v];
         if (sz[tree][v] > n / 2)
            is_centroid = false;
      }
   }   
   if ((n - sz[tree][u]) > n / 2)
      is_centroid = false;
   
   if (is_centroid)
      centroids[tree].push_back(u);
}        

int main() {
   srand(time(NULL));
   for (int i = 0; i < MAX; i++)
      x[i] = randomLL(MOD);
   memset(h, 0, sizeof(h));

   int cases = 0;
   scanf("%d", &cases);
   for (int T = 0; T < cases; T++) {          
      scanf("%d", &n);
      
      for (int t = 0; t < 2; t++) {
         for (int i = 1; i < n; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            u--; v--;
            adj[t][u].push_back(v);
            adj[t][v].push_back(u);
         }
      }

      bool isomorphic = false;
      calcCentroids(0, 0, -1);
      calcCentroids(0, 1, -1);      
      
      for (int c1 : centroids[0]) {
         for (int c2 : centroids[1]) {
            memset(h, 0, sizeof(h));
            calcDepth(c1, 0, -1);
            calcDepth(c2, 1, -1);
            
            ll hash1 = hashTree(c1, 0, -1);
            ll hash2 = hashTree(c2, 1, -1);
            if (hash1 == hash2) {
               isomorphic = true;
               break;
            }
         }
         if (isomorphic) break;
      }
      
      if (isomorphic && centroids[0].size() == centroids[1].size())
         puts("YES");
      else
         puts("NO");

      for (int t = 0; t < 2; t++) {
         centroids[t].clear();
         for (int i = 0; i <= n; i++) {
            adj[t][i].clear();
            h[t][i] = 0;
            sz[t][i] = 0;
         }
      }
   }

   return 0;
}
