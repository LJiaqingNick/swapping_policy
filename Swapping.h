//
// Created by Nick Liu on 2022-10-30.
//

#ifndef SWAPPING_POLICY_SWAPPING_H
#define SWAPPING_POLICY_SWAPPING_H
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

enum Policy {OPT, FIFO, LRU, RAND, CLOCK};

class Swapping {
private:
    vector<int> addresses;
    Policy policy;
    vector<int> cache;
    int cacheSize;
    int hits;
    int miss;
public:
    Swapping(vector<int> addresses_i, Policy policy_i = OPT, int cacheSize_i = 3);
    void run();
    stringstream vecToString(vector<int> vec);
    void print();
    int firstShowUpIndex(int start, vector<int> vec, int address);
    int findLowesIndex(vector<int> vec);
};


#endif //SWAPPING_POLICY_SWAPPING_H
