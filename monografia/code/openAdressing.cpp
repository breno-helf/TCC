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
      return hash<string>()(s) % m;
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
      table[idx].first = pair<string, int>("", 0);
      n--;
   }
   
private:
   void resizeIfNecessary() {
      if (n == m)
         m *= 2;
   }
};
   
int main() {
   HashTable HT = HashTable();
   HT.insert("Abacate", 10);
   HT.insert("Banana", 7);
   HT.insert("Morango", 2);
   for (int i = 0; i < HT.m; i++) {
      printf("--> %s -- %d\n", HT.table[i].first.c_str(), HT.table[i].second);
   }
}
