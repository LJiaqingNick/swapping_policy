#include "Swapping.h"
int main() {
    vector<int> addresses{0, 1, 2, 0, 1, 3, 0, 3, 1, 2, 1};
    Swapping simulator = Swapping(addresses, FIFO);
    simulator.run();

    return 0;
}
