#include<bits/stdc++.h>
using namespace std;

class Node {
public:
   string key;
   int value;
   int next;

   Node(string K = "", int V = 0, int N = -1):
      key(K), value(V), next(N) {}

   bool isDefaultNode() {
      return key == "" && value == 0;
   }

   bool isTombstone() {
      return key == "==TOMBSTONE==" && value == 0;
   }

   void transformTombstone() {
      key = "==TOMBSTONE==";
      value = 0;
   }
   
   bool operator == (const Node& ot) {
      return key == ot.key && value == ot.value && next == ot.next;
   }

   bool operator != (const Node& ot) {
      return key != ot.key || value != ot.value || next != ot.next;
   }
};

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

   int nextFreeBucket() {
      for (int i = m - 1; i >= 0; i--) {
         if (table[i].isDefaultNode())
            return (unsigned int)i;
      }
      return -1; // error
   }
   
   void insert(string key, int value) {
      unsigned int idx = hashFunction(key);
      Node toInsert = Node(key, value, -1);


      if (!table[idx].isDefaultNode()) {
         while (table[idx].next != -1 && !table[idx].isTombstone())
            idx = table[idx].next; 

         if (!table[idx].isTombstone()) {
            table[idx].next = nextFreeBucket();
            idx = table[idx].next;
         }
      }

      table[idx] = toInsert;
      n++;
      resizeIfNecessary();
   }
   
   int find(string key) {
      unsigned int idx = hashFunction(key);

      while (idx != -1) {
         if (table[idx].key == key) 
            return table[idx].value;
         idx = table[idx].next;         
      }
      
      return 0;
   }
      
   void remove(string key) {
      unsigned int idx = hashFunction(key);
      while (idx != -1) {
         if (table[idx].key == key) 
            break;
         idx = table[idx].next;         
      }

      if (table[idx].key == key) {
         table[idx].transformTombstone();
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
            if (!oldTable[i].isDefaultNode() && !oldTable[i].isTombstone()) {
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
      printf("--> %s -- %d -- %d -- (%d)\n", HT.table[i].key.c_str(), HT.table[i].value, HT.table[i].next, HT.table[i].key == "" ? -1 : HT.hashFunction(HT.table[i].key));
   }
}
