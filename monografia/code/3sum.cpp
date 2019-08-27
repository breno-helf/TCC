#include<bits/stdc++.h>
using namespace std;

const int MAX_NUMBER = 1e8 + 5;
const int NUM_TRIALS = 100;

int randomInt(int max) {
   double d = (double) rand() / ((double) RAND_MAX + 1); 
   int k = d * (max + 1);
   return k;
}

vector<int> getRandomArray(int size) {
   vector<int> v;
   for (int i = 0; i < size; i++)
      v.push_back(randomInt(MAX_NUMBER));
   return v;
}

bool threeSumWithoutHashTable(vector<int> v, int S) {
   for (int i = 0; i < v.size(); i++) {
      for (int j = i + 1; j < v.size(); j++) {
         for (int k = j + 1; k < v.size(); k++) {
            if (v[i] + v[j] + v[k] == S) return true;
         }
      }
   }

   return false;
}

bool threeSumWithHashTable(vector<int> v, int S) {
   unordered_map<int, int> hashTable;
   
   for (int i = 0; i < v.size(); i++) {
      hashTable[v[i]]++;
   }

   for (int i = 0; i < v.size(); i++) {
      for (int j = i + 1; j < v.size(); j++) {
         hashTable[v[i]]--;
         hashTable[v[j]]--;

         
         if (hashTable.find(S - v[i] - v[j]) != hashTable.end() &&
             hashTable[S - v[i] - v[j]] > 0) return true;

         hashTable[v[i]]++;
         hashTable[v[j]]++;
      }
   }

   return false;
}

double calculateSingleTimeThreeSum(int arraySize,
                             bool (*threeSumSolution)(vector<int>, int)) {
   vector<int> v = getRandomArray(arraySize);
   int S = randomInt(3 * MAX_NUMBER);
   
   double start = (double) clock () / CLOCKS_PER_SEC;
   threeSumSolution(v, S);
   double stop = (double) clock () / CLOCKS_PER_SEC;

   return stop - start;
}

double calculateAverageTimeThreeSum(int arraySize,
                             bool (*threeSumSolution)(vector<int>, int)) {
   double result = 0;
   
   for (int i = 0; i < NUM_TRIALS; i++) {
      result += calculateSingleTimeThreeSum(arraySize, threeSumSolution);
   }
   result /= NUM_TRIALS;
   
   return result;
}


int main() {
   for (int i = 128; i < 7000; i *= 2) {
      printf("Times for arraySize = %d\n", i);
      printf("\tWithout Hash Table: %.3lfms\n",
             1000*calculateAverageTimeThreeSum(i, threeSumWithoutHashTable));
      printf("\tWith Hash Table:    %.3lfms\n\n",
             1000*calculateAverageTimeThreeSum(i, threeSumWithHashTable));
   }

   return 0;
}
