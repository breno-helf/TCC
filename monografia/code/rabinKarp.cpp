#include<bits/stdc++.h>
using namespace std;

const int NUM_TRIALS = 100;

int randomInt(int max) {
   double d = (double) rand() / ((double) RAND_MAX + 1); 
   int k = d * (max + 1);
   return k;
}

char randomAlphaChar() {
   return 'a' + randomInt(25);
}

string getRandomString(int size) {
   string s = "";
   for (int i = 0; i < size; i++) {
      char c = randomAlphaChar();
      for (int j = 0; j < 100; j++)
         s.push_back(c);
   }
   return s;
}

int findPatternBruteForce(string& t, string& p) {
   for (int i = 0; i <= t.size() - p.size(); i++) {
      bool match = true;
      for (int j = 0; j < p.size(); j++) {
         if (t[i + j] != p[j]) {
            match = false;
            break;
         }
      }
      if (match) return i;
   }

   return -1;
}

const int PRIME = 33;
const int MOD = 1000033;
int findPatternRabinKarp(string& t, string& p) {
   int textHash = 0, patternHash = 0;
   int pot = 1;

   // pot will be PRIME^{p.size() - 1}
   for (int i = 0; i < p.size() - 1; i++)
      pot = (pot * PRIME) % MOD;

   for (int i = 0; i < p.size(); i++) {
      textHash = (textHash * PRIME + t[i]) % MOD;
      patternHash = (patternHash * PRIME + p[i]) % MOD;
   }

   for (int i = 0; i <= t.size() - p.size(); i++) {      
      if (textHash == patternHash) {
         bool match = true;
         for (int j = 0; j < p.size(); j++) {
            if (t[i + j] != p[j]) {
               match = false;
               break;
            }
         }
         if (match) return i;
      }

      textHash = (PRIME * (textHash - pot * t[i]) + t[i + p.size()] + MOD) % MOD;
   }

   return -1;
}

double calculateSingleTimeFindPattern(int textSize, int patternSize,
                                      int (*findPatternSolution)(string&, string&)) {
   string t = getRandomString(textSize);
   string p = getRandomString(patternSize);

   //printf("--> %s\n --> %s\n\n", t.c_str(), p.c_str());
   
   assert(t.size() >= p.size());
   
   double start = (double) clock () / CLOCKS_PER_SEC;
   findPatternSolution(t, p);
   double stop = (double) clock () / CLOCKS_PER_SEC;

   return stop - start;
}

double calculateAverageTimeFindPattern(int textSize, int patternSize,
                                       int (*findPatternSolution)(string&, string&)) {
   double result = 0;
   
   for (int i = 0; i < NUM_TRIALS; i++) {
      result += calculateSingleTimeFindPattern(textSize, patternSize, findPatternSolution);
   }
   result /= NUM_TRIALS;
   
   return result;
}


int main() {
   for (int i = 128; i < 100000; i *= 2) {
      for (int j = 2; 10 * j < i; j *= 2) {
         printf("Times for textSize = %d and patternSize = %d\n", i, j);
         printf("\tWithout Hashing: %.3lfms\n",
                1000*calculateAverageTimeFindPattern(i, j, findPatternBruteForce));
         printf("\tWith Hashing (RabinKarp):    %.3lfms\n\n",
                1000*calculateAverageTimeFindPattern(i, j, findPatternRabinKarp));
      }
   }
   
   return 0;
}
