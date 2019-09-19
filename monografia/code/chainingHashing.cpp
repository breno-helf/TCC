#include<bits/stdc++.h>
using namespace std;

class Node {
public:
   string key;
   int value;
   Node* nxt;

   Node(string KEY = "", int VALUE = 0, Node* NXT = NULL) {
      key = KEY;
      value = VALUE;
      nxt = NXT;
   }

   ~Node();
};

class ChainingHashTable {
public:
   vector<Node*> table;
   int m, n;
   
   ChainingHashTable() {
      m = 16;
      table.resize(m);
      n = 0;
   }

   unsigned int hashFunction(string s) {
      return 1;
   }
   
   void insert(string key, int value) {
      unsigned int idx = hashFunction(key);
      if (table[idx] == NULL) {
         table[idx] = new Node(key, value);
      } else {
         Node* cur = table[idx];
         while (cur->nxt != NULL)
            cur = cur->nxt;
         cur->nxt = new Node(key, value);
      }
      
      n++;
      resizeIfNecessary();
   }
   
   int find(string key) {
      unsigned int idx = hashFunction(key);
      Node* cur = table[idx];

      while (cur->key != key)
         cur = cur->nxt;
      
      if (cur->key == key)
         return cur->value;
      return 0;
   }
   
   void remove(string key) {
      unsigned int idx = hashFunction(key);
      // Empty bucket
      if (table[idx] == NULL)
         return;

      // Remove head of bucket
      if (table[idx]->key == key) {
         Node* rem = table[idx];
         table[idx] = table[idx]->nxt;
         free(rem);
         return;
      }

      // General case
      Node* cur = table[idx];      
      while (cur->nxt != NULL && cur->nxt->key != key)
         cur = cur->nxt;      
      if (cur->nxt != NULL) {
         Node* rem = cur->nxt;
         cur->nxt = rem->nxt;
         free(rem);
      }
      
   }
   
private:
   void resizeIfNecessary() {
      if (n == m)
         m *= 2;
   }
};
   
int main() {
   ChainingHashTable table = ChainingHashTable();
   table.insert("Kobus", 7);
   table.insert("Estrela", 2);
   printf("--> %s %d\n", "Kobus", table.find("Kobus"));
   printf("--> %s %d\n", "Estrela", table.find("Estrela"));
   table.remove("Estrela");
   table.remove("Kobus");
}
