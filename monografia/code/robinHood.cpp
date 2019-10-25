#include<bits/stdc++.h>
using namespace std;

class Node {
public:
   string key;
   int value;
   unsigned int PSL;

   Node(string K = "", int V = 0, unsigned int P = 0):
      key(K), value(V), PSL(P) {}

   bool operator == (const Node& ot) {
      return key == ot.key && value == ot.value && PSL == ot.PSL;
   }

   bool operator != (const Node& ot) {
      return key != ot.key || value != ot.value || PSL != ot.PSL;
   }
};

const Node defaultNode = Node();

class HashTable {
public:
   vector<Node> table;
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
      Node toInsert = Node(key, value, 0);
      
      while (table[idx] != defaultNode) {
         if (toInsert.PSL > table[idx].PSL)
            swap(toInsert, table[idx]);         
         idx = (idx + 1) % m;
         toInsert.PSL++;
      }
      table[idx] = toInsert;
      n++;
      resizeIfNecessary();
   }
   
   int find(string key) {
      unsigned int idx = hashFunction(key);
      unsigned int curPSL = 0;
      while (table[idx] != defaultNode) {
         if (table[idx].key == key) 
            return table[idx].value;
         // If the key were inserted it would be before this Node.
         if (table[idx].PSL > curPSL)
            break; 
         idx = (idx + 1) % m;
         curPSL++;
      }
      return 0;
   }
      
   void remove(string key) {
      unsigned int idx = hashFunction(key);
      while (table[idx] != defaultNode) {
         if (table[idx].key == key) 
            break;
         idx = (idx + 1) % m;
      }
            
      if (table[idx].key == key) {
         table[idx] = defaultNode;
         while (table[(idx + 1) % m] != defaultNode &&
                table[(idx + 1) % m].PSL != 0) {
            swap(table[idx], table[(idx + 1) % m]);
            table[idx].PSL--;
            idx = (idx + 1) % m;
         }
         n--;
      }
   }
   
private:
   double alpha = .8;
   void resizeIfNecessary() {
      if (n >= m * alpha) {
         vector<Node> oldTable = table;
         int oldM = m;
         table.clear();
         m *= 2;
         table.resize(m);
         for (int i = 0; i < oldM; i++) {
            if (oldTable[i] != defaultNode) {
               insert(oldTable[i].key, oldTable[i].value);
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
   HT.insert("chute", 5);
   HT.insert("PSLxxx", 4);
   HT.insert("Robin", 1);
   HT.insert("Hood", -1);
   HT.remove("Colidexxx");
   for (int i = 0; i < HT.m; i++) {
      printf("--> %s -- %d -- %d -- (%d)\n", HT.table[i].key.c_str(), HT.table[i].value, HT.table[i].PSL, HT.table[i].key == "" ? -1 : HT.hashFunction(HT.table[i].key));
   }
}
