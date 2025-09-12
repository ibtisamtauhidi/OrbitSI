#ifndef ORCA_CORE_H
#define ORCA_CORE_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <ctime>
#include <iostream>
#include <fstream>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <utility>

typedef long long int64;
typedef std::pair<int, int> PII;

struct TIII {
    int first, second, third;
};

struct PAIR {
    int a, b;
    PAIR(int a0, int b0) {
        a = std::min(a0, b0);
        b = std::max(a0, b0);
    }
};

bool operator<(const PAIR& x, const PAIR& y);
bool operator==(const PAIR& x, const PAIR& y);

struct hash_PAIR {
    size_t operator()(const PAIR& x) const;
};

struct TRIPLE {
    int a, b, c;
    TRIPLE(int a0, int b0, int c0);
};

bool operator<(const TRIPLE& x, const TRIPLE& y);
bool operator==(const TRIPLE& x, const TRIPLE& y);

struct hash_TRIPLE {
    size_t operator()(const TRIPLE& x) const;
};

// External global variables
extern std::unordered_map<PAIR, int, hash_PAIR> common2;
extern std::unordered_map<TRIPLE, int, hash_TRIPLE> common3;
extern int n, m;
extern int* deg;
extern PAIR* edges;
extern int** adj;
extern PII** inc;
extern int* adj_matrix;
extern bool (*adjacent)(int, int);
extern int64** orbit;
extern int64** eorbit;

// Function declarations
bool adjacent_list(int x, int y);
bool adjacent_matrix(int x, int y);
int getEdgeId(int x, int y);
void count4();
void count5();

#define common3_get(x) (((common3_it=common3.find(x))!=common3.end())?(common3_it->second):0)
#define common2_get(x) (((common2_it=common2.find(x))!=common2.end())?(common2_it->second):0)

#endif
