#include<bits/stdc++.h>
using namespace std;

#if !defined (get16bits)
#define get16bits(d) ((((uint32_t)(((const uint8_t *)(d))[1])) << 8)\
                       +(uint32_t)(((const uint8_t *)(d))[0]) )
#endif

// Copied from http://www.azillionmonkeys.com/qed/hash.html
unsigned int paulHesiehHash (string str) {
   unsigned int hash = str.size(), tmp, len = str.size();
   int rem;
   const char *data = str.c_str();
   
   if (len <= 0 || str == "") return 0;

   rem = len & 3;
   len >>= 2;
   
   /* Main loop */
   for (;len > 0; len--) {
      hash  += get16bits (data);
      tmp    = (get16bits (data+2) << 11) ^ hash;
      hash   = (hash << 16) ^ tmp;
      data  += 2*sizeof (uint16_t);
      hash  += hash >> 11;
   }
   
   /* Handle end cases */
   switch (rem) {
   case 3: hash += get16bits (data);
      hash ^= hash << 16;
      hash ^= ((signed char)data[sizeof (uint16_t)]) << 18;
      hash += hash >> 11;
      break;
   case 2: hash += get16bits (data);
      hash ^= hash << 11;
      hash += hash >> 17;
      break;
   case 1: hash += (signed char)*data;
      hash ^= hash << 10;
      hash += hash >> 1;
   }
   
   /* Force "avalanching" of final 127 bits */
   hash ^= hash << 3;
   hash += hash >> 5;
   hash ^= hash << 4;
   hash += hash >> 17;
   hash ^= hash << 25;
   hash += hash >> 6;
   
   return hash;
}


class HashTable {
public:
   vector< vector< pair<string, int> > > table;
   int m, n;
   unsigned int numTables = 2;
   
   HashTable() {
      table.resize(numTables);
      m = 16;
      for (int j = 0; j < numTables; j++)
         table[j].resize(m);
      n = 0;
   }

   unsigned int hashFunction(string s, unsigned int i) {
      if (i == 0)
         return hash<string>()(s) % m;
      else
         return paulHesiehHash(s) % m;   
   }
   
   void insert(string key, int value) {
      unsigned int j = 0, it = 0;
      unsigned int idx = hashFunction(key, j), lim = maxLoop();
      pair<string, int> toInsert = pair<string, int>(key, value);
      
      
      while (table[j][idx] != pair<string, int>("", 0) && it < lim) {
         swap(table[j][idx], toInsert);
         j = (j + 1) % numTables;
         idx = hashFunction(toInsert.first, j);
         it++;
      }
      
      if (it == lim)
         resize();
      
      table[j][idx] = toInsert;
      n++;
      resizeIfNecessary();
   }
   
   int find(string key) {
      for (unsigned int j = 0; j < numTables; j++) {
         unsigned int idx = hashFunction(key, j);
         if (table[j][idx].first == key)
            return table[j][idx].second;
      }

      return 0;
   }
   
   void remove(string key) {
      for (unsigned int j = 0; j < numTables; j++) {
         unsigned int idx = hashFunction(key, j);
         if (table[j][idx].first == key) {
            table[j][idx] = pair<string, int>("", 0);
            n--;
         }
      }
   }
   
private:
   double alpha = .3;
   void resizeIfNecessary() {
      if (n >= m * alpha)
         resize();
   }
   
   void resize() {
      vector< vector< pair<string, int> > > oldTable = table;
      int oldM = m;
      table.clear();
      m *= 2;
      table.resize(2);
      for (int j = 0; j < numTables; j++)
         table[j].resize(m);
      for (int j = 0; j < numTables; j++)
         for (int i = 0; i < oldM; i++)
            if (oldTable[j][i] != pair<string, int>("", 0))
               insert(oldTable[j][i].first, oldTable[j][i].second);
   }
      
   unsigned int maxLoop() {
      unsigned int maxLoop = (unsigned int) log(n);
      return maxLoop > 10 ? maxLoop : 10;
   }

};
   
int main() {
   HashTable HT = HashTable();
   HT.insert("Abacate", 10);
   HT.insert("Banana", 7);
   HT.insert("Morango", 2);
   HT.insert("Colidexxx", 3);
   for (unsigned int j = 0; j < HT.numTables; j++) {
      printf("Table (%d)\n", j);
      for (unsigned int i = 0; i < HT.m; i++) {
         printf("--> %s -- %d\n", HT.table[j][i].first.c_str(), HT.table[j][i].second);
      }
      printf("\n\n");
   }
}
