#include<bits/stdc++.h>
using namespace std;

class HashTable {
public:
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
      while (table[idx] != pair<string, int>("", 0) &&
             table[idx] != pair<string, int>("==TOMBSTONE==", 0))
         idx = (idx + 1) % m;      
      table[idx] = pair<string, int>(key, value);
      n++;
      resizeIfNecessary();
   }
   
   int find(string key) {
      unsigned int idx = hashFunction(key);
      while (table[idx] != pair<string, int>("", 0)) {
         if (table[idx].first == key) 
            return table[idx].second;
         idx = (idx + 1) % m;
      }
      return 0;
   }
   
   void remove(string key) {
      unsigned int idx = hashFunction(key);
      while (table[idx] != pair<string, int>("", 0)) {
         if (table[idx].first == key) 
            break;
         idx = (idx + 1) % m;
      }
            
      if (table[idx].first == key) {
         string nextKey = table[(idx + 1) % m].first;
         if (nextKey != "" && hashFunction(nextKey) == hashFunction(key))
            table[idx] = pair<string, int>("==TOMBSTONE==", 0);
         else
            table[idx] = pair<string, int>("", 0);
         n--;
      }
   }
   
private:
   double alpha = 1;
   void resizeIfNecessary() {
      if (n >= m * alpha) {
         vector< pair<string, int> > oldTable = table;
         int oldM = m;
         table.clear();
         m *= 2;
         table.resize(m);
         for (int i = 0; i < oldM; i++) {
            if (oldTable[i] != pair<string, int>("", 0) &&
                oldTable[i] != pair<string, int>("==TOMBSTONE==", 0)) {
               insert(oldTable[i].first, oldTable[i].second);
            }               
         }
      }
   }
};
   
int main() {
   HashTable HT = HashTable();
   HT.insert("Abacate", 10);
   HT.insert("Banana", 7);
   HT.insert("Morango", 2);
   HT.insert("Colidexxx", 3);
   for (int i = 0; i < HT.m; i++) {
      printf("--> %s -- %d\n", HT.table[i].first.c_str(), HT.table[i].second);
   }
}
