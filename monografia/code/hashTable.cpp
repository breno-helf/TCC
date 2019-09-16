#include<bits/stdc++.h>
using namespace std;

class HashTable {
   vector< pair<string, int> > table;
   int m, n;
   
   HashTable() {
      m = 16;
      table.resize(m);
      n = 0;
   }

   unsigned int hashFunction(string s) {
      return 1;
   }
   
   void insert(string key, int value) {
      unsigned int idx = hashFunction(key);
      table[idx] = pair<string, int>(key, value);
      n++;
      resizeIfNecessary();
   }
   
   int find(string key) {
      unsigned int idx = hashFunction(key);
      if (table[idx].first == key)
         return table[idx].second;
      return 0;
   }
   
   void remove(string key) {
      unsigned int idx = hashFunction(key);
      table[idx].first = "";
   }
   
private:
   void resizeIfNecessary() {
      if (n == m)
         m *= 2;
   }
};
   
int main() {
   vector< pair<string, int> > table;
   table.resize(16);
   for (int i = 0; i < 10; i++) {
      printf("--> %d -- %d\n", table[i].first.c_str(), table[i].second);
   }
}
