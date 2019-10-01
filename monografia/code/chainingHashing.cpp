#include<bits/stdc++.h>
using namespace std;

class ChainingHashTable {
public:
   vector< list< pair<string, int> > > table;
   int m, n;
   
   ChainingHashTable() {
      m = 16;
      table.resize(m);
      n = 0;
   }

   unsigned int hashFunction(string s) {
      return hash<string>()(s) % m;
   }
   
   void insert(string key, int value) {
      unsigned int idx = hashFunction(key);      
      table[idx].emplace_front(key, value);
      n++;
      resizeIfNecessary();
   }
   
   int find(string key) {
      unsigned int idx = hashFunction(key);
      auto it = find_if(table[idx].begin(), table[idx].end(),
                        [&key](auto kv) { return kv.first == key; });
      if (it != table[idx].end())
         return it->second;
      return 0;
   }
   
   void remove(string key) {
      unsigned int idx = hashFunction(key);
      auto it = find_if(table[idx].begin(), table[idx].end(),
                        [&key](auto kv) { return kv.first == key; });
      if (it != table[idx].end()) {
         table[idx].erase(it);
         n--;
      }
   }
   
private:
   double alpha = 1;
   void resizeIfNecessary() {
      if (n >= m * alpha) {
         vector< list< pair<string, int> > > oldTable = table;
         int oldM = m;
         table.clear();
         m *= 2;
         table.resize(m);
         for (int i = 0; i < oldM; i++) {
            for (auto kv : oldTable[i])
               insert(kv.first, kv.second);
         }
      }
   }
};
   
int main() {
   ChainingHashTable HT = ChainingHashTable();
   HT.insert("Kobus", 7);
   HT.insert("Estrela", 2);
   printf("--> %s %d\n", "Kobus", HT.find("Kobus"));
   printf("--> %s %d\n", "Estrela", HT.find("Estrela"));
   HT.remove("Estrela");
   HT.remove("Kobus");
   HT.insert("Abacate", 10);
   HT.insert("Banana", 7);
   HT.insert("Morango", 2);
   HT.insert("Colidexxx", 3);

   printf("--> %s %d\n", "Morango", HT.find("Morango"));
   printf("--> %s %d\n", "Colidexxx", HT.find("Colidexxx"));
}
