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
   vector< pair<string, int> > table;
   int m, n;
   
   HashTable() {
      m = 16;
      table.resize(m);
      n = 0;
   }

   unsigned int h1(string s) {
      return hash<string>()(s) % m;
   }

   unsigned int h2(string s) {
      return paulHesiehHash(s) % m;
   }
   
   void insert(string key, int value) {
      unsigned int idx = h1(key);
      unsigned int add = h2(key);
      while (table[idx] != pair<string, int>("", 0) &&
             table[idx] != pair<string, int>("==TOMBSTONE==", 0))
         idx = (idx + add) % m;      
      table[idx] = pair<string, int>(key, value);
      n++;
      resizeIfNecessary();
   }
   
   int find(string key) {
      unsigned int idx = h1(key);
      unsigned int add = h2(key);
      while (table[idx] != pair<string, int>("", 0)) {
         if (table[idx].first == key) 
            return table[idx].second;
         idx = (idx + add) % m;
      }
      return 0;
   }
   
   void remove(string key) {
      unsigned int idx = h1(key);
      unsigned int add = h2(key);
      while (table[idx] != pair<string, int>("", 0)) {
         if (table[idx].first == key) 
            break;
         idx = (idx + add) % m;
      }
            
      if (table[idx].first == key) {
         table[idx] = pair<string, int>("==TOMBSTONE==", 0);
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
