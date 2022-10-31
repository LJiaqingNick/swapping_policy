//
// Created by Nick Liu on 2022-10-30.
//

#include <stdlib.h>
#include "Swapping.h"
#define INF 99999

static const char* enumStr[] = {"OPT", "FIFO", "LRU", "RAND", "CLOCK"};
Swapping::Swapping(vector<int> addresses_i, Policy policy_i, int cacheSize_i) {
    addresses = addresses_i;
    policy = policy_i;
    cache = vector<int>();
    cacheSize = cacheSize_i;
}

void Swapping::run() {
    cout<<"Current Policy is "<<enumStr[policy]<<endl;
    cout<<"Addresses are ["<<(vecToString(addresses)).str()<<endl;
    int miss = 0;
    int hits = 0;
    if (addresses.size() <= cacheSize) {
        for (int i = 0; i < cacheSize; i++) {
            cache.push_back(addresses[i]);
            miss++;
            cout<<"Access " <<addresses[i]<<" MISS "<<enumStr[policy]<<"->["<<(vecToString(cache)).str()
                <<"] Replace- [Hits:"<<hits<<" Miss:"<<miss<<"]"<<endl;
        }
        cache.clear();
        return;
    }
    if (policy == OPT) {
        bool isEvict = false;
        for (int i = 0; i < addresses.size(); i++) {
            if (i > cacheSize - 1) {
                if (firstShowUpIndex(0, cache, addresses[i]) == -1) {
                    isEvict = true;
                }
                if (isEvict) {
                    int nearestIndex;
                    int evictCacheAddress = cache[0];
                    auto evictCacheIndex = 0;
                    int lastShowUpDist = i;
                    int j;
                    for (j = 0; j < cacheSize; j++) {
                        nearestIndex = firstShowUpIndex(i, addresses, cache[j]);
                        if (nearestIndex == -1) {
                            lastShowUpDist = nearestIndex;
                            evictCacheIndex = j;
                            evictCacheAddress = cache[j];
                            break;
                        } else {
                            if (nearestIndex >= lastShowUpDist) {
                                lastShowUpDist = nearestIndex;
                                evictCacheIndex = j;
                                evictCacheAddress = cache[j];
                            }
                        }
                    }
                    isEvict = false;
                    miss++;
                    cache[evictCacheIndex] = addresses[i];
                    cout << "Access " << addresses[i] << " MISS " << enumStr[policy] << "->[" << (vecToString(cache)).str()
                         << "] Replace-" << evictCacheAddress << " [Hits:" << hits << " Miss:" << miss << "]" << endl;
                } else {
                    hits++;
                    cout<<"Access " <<addresses[i]<<" Hits "<<enumStr[policy]<<"->["<<(vecToString(cache)).str()
                        <<"] Replace- [Hits:"<<hits<<" Miss:"<<miss<<"]"<<endl;
                }
            } else {
                cache.push_back(addresses[i]);
                miss++;
                cout<<"Access " <<addresses[i]<<" MISS "<<enumStr[policy]<<"->["<<(vecToString(cache)).str()
                    <<"] Replace- [Hits:"<<hits<<" Miss:"<<miss<<"]"<<endl;
            }
        }
    } else if (policy == FIFO) {
        bool isEvict = false;
        for (int i = 0; i < addresses.size(); i++) {
            if (i > cacheSize - 1) {
                if (firstShowUpIndex(0, cache, addresses[i]) == -1) {
                    isEvict = true;
                }
                if (isEvict) {
                    isEvict = false;
                    miss++;
                    int evictCacheAddress = cache.front();
                    cache.erase(cache.begin());
                    cache.push_back(addresses[i]);
                    cout << "Access " << addresses[i] << " MISS " << enumStr[policy] << "->[" << (vecToString(cache)).str()
                         << "] Replace-" << evictCacheAddress << " [Hits:" << hits << " Miss:" << miss << "]" << endl;
                } else {
                    hits++;
                    cout<<"Access " <<addresses[i]<<" Hits "<<enumStr[policy]<<"->["<<(vecToString(cache)).str()
                        <<"] Replace- [Hits:"<<hits<<" Miss:"<<miss<<"]"<<endl;
                }
            } else {
                cache.push_back(addresses[i]);
                miss++;
                cout<<"Access " <<addresses[i]<<" MISS "<<enumStr[policy]<<"->["<<(vecToString(cache)).str()
                    <<"] Replace- [Hits:"<<hits<<" Miss:"<<miss<<"]"<<endl;
            }
        }
    } else if (policy == LRU) {
        vector<int> cacheFreq(cacheSize, 0);
        int count = 0;
        for (int i = 0; i < addresses.size(); i++) {
            if (i > cacheSize - 1) {
                int cacheIndexHitPos = firstShowUpIndex(0, cache, addresses[i]);
                if (cacheIndexHitPos == -1) {
                    miss++;
                    int lowestFreqIndex = findLowesIndex(cacheFreq);
                    int lowestFreqAddress = cache[lowestFreqIndex];
                    cache[lowestFreqIndex] = addresses[i];
                    count++;
                    cacheFreq[lowestFreqIndex] = count;
                    cout << "Access " << addresses[i] << " MISS " << enumStr[policy] << "->[" << (vecToString(cache)).str()
                         << "] Replace-" << lowestFreqAddress << " [Hits:" << hits << " Miss:" << miss << "]" << endl;
                } else {
                    count++;
                    cacheFreq[cacheIndexHitPos] = count;
                    hits++;
                    cout<<"Access " <<addresses[i]<<" Hits "<<enumStr[policy]<<"->["<<(vecToString(cache)).str()
                        <<"] Replace- [Hits:"<<hits<<" Miss:"<<miss<<"]"<<endl;
                }
            } else {
                count++;
                cacheFreq[i] = count;
                cache.push_back(addresses[i]);
                miss++;
                cout<<"Access " <<addresses[i]<<" MISS "<<enumStr[policy]<<"->["<<(vecToString(cache)).str()
                    <<"] Replace- [Hits:"<<hits<<" Miss:"<<miss<<"]"<<endl;
            }
        }
    } else if (policy == RAND) {
        bool isEvict = false;
        for (int i = 0; i < addresses.size(); i++) {
            if (i > cacheSize - 1) {
                if (firstShowUpIndex(0, cache, addresses[i]) == -1) {
                    isEvict = true;
                }
                if (isEvict) {
                    isEvict = false;
                    miss++;
                    int evictCacheIndex = (rand() % cacheSize);
                    int evictCacheAddress = cache[evictCacheIndex];
                    cache[evictCacheIndex] = addresses[i];
                    cout << "Access " << addresses[i] << " MISS " << enumStr[policy] << "->[" << (vecToString(cache)).str()
                         << "] Replace-" << evictCacheAddress << " [Hits:" << hits << " Miss:" << miss << "]" << endl;
                } else {
                    hits++;
                    cout<<"Access " <<addresses[i]<<" Hits "<<enumStr[policy]<<"->["<<(vecToString(cache)).str()
                        <<"] Replace- [Hits:"<<hits<<" Miss:"<<miss<<"]"<<endl;
                }
            } else {
                cache.push_back(addresses[i]);
                miss++;
                cout<<"Access " <<addresses[i]<<" MISS "<<enumStr[policy]<<"->["<<(vecToString(cache)).str()
                    <<"] Replace- [Hits:"<<hits<<" Miss:"<<miss<<"]"<<endl;
            }
        }
    } else {
        vector<int> cacheFreq(cacheSize, 0);
        for (int i = 0; i < addresses.size(); i++) {
            if (i > cacheSize - 1) {
                int cacheIndexHitPos = firstShowUpIndex(0, cache, addresses[i]);
                if (cacheIndexHitPos == -1) {
                    miss++;
                    int clock = (rand() % cacheSize);
                    int bit = 1;
                    while (bit != 0) {
                        if (cacheFreq[clock] != 0) {
                            cacheFreq[clock] = 0;
                            clock = (clock + 1) % cacheSize;
                        } else {
                            bit = 0;
                        }
                    }
                    int evictCacheAddr = cache[clock];
                    cache[clock] = addresses[i];
                    cacheFreq[clock] = 1;
                    cout << "Access " << addresses[i] << " MISS " << enumStr[policy] << "->[" << (vecToString(cache)).str()
                         << "] Replace-" << evictCacheAddr << " [Hits:" << hits << " Miss:" << miss << "]" << endl;
                } else {
                    cacheFreq[cacheIndexHitPos] = 1;
                    hits++;
                    cout<<"Access " <<addresses[i]<<" Hits "<<enumStr[policy]<<"->["<<(vecToString(cache)).str()
                        <<"] Replace- [Hits:"<<hits<<" Miss:"<<miss<<"]"<<endl;
                }
            } else {
                cacheFreq[i] = 1;
                cache.push_back(addresses[i]);
                miss++;
                cout<<"Access " <<addresses[i]<<" MISS "<<enumStr[policy]<<"->["<<(vecToString(cache)).str()
                    <<"] Replace- [Hits:"<<hits<<" Miss:"<<miss<<"]"<<endl;
            }
        }
    }
    cout<<"Total hits are "<<hits<<", and total misses are "<<miss<<endl;
    cout<<"Total hit rate are "<<(((float)hits)/(hits+miss))*100<<"%"<<endl;
}

stringstream Swapping::vecToString(vector<int> vec) {
    std::stringstream  ss;
    for (size_t i = 0; i < vec.size(); i++) {
        if (i != 0) {
            ss << ", ";
        }
        ss << vec[i];
    }
    return ss;
}

int Swapping::firstShowUpIndex(int start, vector<int> vec, int address) {
    while (start < vec.size()) {
        if (vec[start] == address) {
            return start;
        }
        start++;
    }
    return -1;
}

int Swapping::findLowesIndex(vector<int> vec) {
    int lowest = INF;
    int resultIndex = 0;
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] < lowest) {
            lowest = vec[i];
            resultIndex = i;
        }
    }
    return resultIndex;
}
