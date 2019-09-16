#include<bits/stdc++.h>
using namespace std;

typedef unsigned int UI;
typedef long double LD;
typedef pair<string, UI (*)(string)> hashFunc;

const vector<string> testFiles = {"data/dic_Shakespeare.txt",
                              "data/dic_common_words.txt",
                              "data/dic_fr.txt",
                              "data/dic_ip.txt",
                              "data/dic_numbers.txt",
                              "data/dic_postfix.txt",
                              "data/dic_prefix.txt",
                              "data/dic_variables.txt",
                              "data/dic_win32.txt"};

const vector<int> tableSizes = {1031, 16411, 131101};

UI hashFunctionTemplate(string str,
                        UI initialValue,
                        UI multiplier,
                        UI (*combine)(UI, UI)) {
   UI hash = initialValue;
   for (char c : str) {
      hash = combine(multiplier * hash, (UI) c);
   }
   return hash;
}

UI combineXOR(UI a, UI b) {
   return a ^ b;
}

UI combineADD(UI a, UI b) {
   return a + b;
}

UI bernsteinHashADD(string str) {
   UI hash = hashFunctionTemplate(str, 5381, 33, combineADD); 
   return hash ^ (hash >> 16);
}

UI bernsteinHashXOR(string str) {
   UI hash = hashFunctionTemplate(str, 5381, 33, combineXOR); 
   return hash ^ (hash >> 16);
}

UI kernighanRitchieHashADD(string str) {
   return hashFunctionTemplate(str, 0, 31, combineADD);
}

UI kernighanRitchieHashXOR(string str) {
   return hashFunctionTemplate(str, 0, 31, combineXOR);
}

UI redDragonBookHash(string str) {
   UI hash = hashFunctionTemplate(str, 0, 65599, combineADD);
   return hash ^ (hash >> 16);
}

UI defaultHash(string str) {
   return hash<string>()(str);
}

UI dumbHashADD(string str) {
   return hashFunctionTemplate(str, 0, 1, combineADD);
}

UI dumbHashXOR(string str) {
   return hashFunctionTemplate(str, 0, 1, combineXOR);
}

#if !defined (get16bits)
#define get16bits(d) ((((uint32_t)(((const uint8_t *)(d))[1])) << 8)\
                       +(uint32_t)(((const uint8_t *)(d))[0]) )
#endif

UI identityHash(string str) {
   const char *data = str.c_str();
   return (get16bits(data + 2) << 16) + get16bits(data);
}

// Copied from http://www.azillionmonkeys.com/qed/hash.html
UI paulHesiehHash (string str) {
   UI hash = str.size(), tmp, len = str.size();
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

vector<string> parseFile(string filename) {
   vector<string> lines;
   ifstream inputFileStream(filename);
   
   string line;
   while (getline(inputFileStream, line)) {
      lines.push_back(line);
   }

   return lines;
}

// Calculate the benchmark by the dragon book func
LD benchMarkHashFunctions(hashFunc f, int m, vector<string> entries) {
   vector<int> collisions(m);
   
   for (string entry : entries) {
      collisions[f.second(entry) % m]++;
   }

   int n = entries.size();
   LD sum = 0;
   // Denominator
   LD den = ((LD) n) / ((LD) 2 * m) * ((LD) (n + 2*m - 1));
   for (int bj : collisions) {
      sum += ((LD)(bj * (bj + 1)) / 2.0);
   }

   cout << fixed;
   cout << setprecision(3);
   cout << "--->  " << f.first << " (n = " << n << ", m = " << m
        << ")  --  " << sum << " / " << den << " = " << sum/den << "\n";
   return sum / den;
}


int main() {
   const string output = "hashFuncResults.txt";
   
   vector<hashFunc> hashFunctions =
      {{"bernsteinHashADD", bernsteinHashADD},
       {"bernsteinHashXOR", bernsteinHashXOR},
       {"kernighanRitchieHashADD", kernighanRitchieHashADD},
       {"kernighanRitchieHashXOR", kernighanRitchieHashXOR},
       {"redDragonBookHash", redDragonBookHash},
       {"defaultHash", defaultHash},
       {"paulHesiehHash", paulHesiehHash},
       {"dumbHashADD", dumbHashADD},
       {"dumbHashXOR", dumbHashXOR},
       {"identityHash", identityHash}};

   vector<string> testStrings = {"breno0", "breno1", "breno2",
                                 "rabbit", "rabbiu", "rabbiv"};

   for (string str : testStrings) {  
      for (hashFunc f : hashFunctions) {
         cout << "For function " << f.first << "("
              << str << ") = " << f.second(str) << "\n";
      }
      cout << "\n\n";
   }
      
   ofstream outputFileStream(output);
   outputFileStream << fixed;
   outputFileStream << setprecision(3);

   for (string filename : testFiles) {
      vector<string> entries = parseFile(filename);
      outputFileStream << "Testing for file " << filename << "\n";
      cout << "\n" << filename << "\n";
      for (int tableSize : tableSizes) {
         outputFileStream << "\n\tFor table size = " << tableSize << "\n";
         for (hashFunc f : hashFunctions) {
            LD res = benchMarkHashFunctions(f, tableSize, entries);
            outputFileStream << "\t\t" << f.first << " = " << res << "\n"; 
         }
      }
      outputFileStream << "\n-------------------------------------------------\n";
   }
   
   return 0;   
}
