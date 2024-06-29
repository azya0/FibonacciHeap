#include <iostream>
#include "heap/heap.h"


int main() {
    auto data1 = FibbonachiHeap<float>();
    data1.insert(1);

    data1.insert(2);
    data1.insert(3);
    data1.insert(0.5f);

    auto data2 = FibbonachiHeap<float>();
    data2.insert(1234);

    data2.insert(232);
    data2.insert(43);
    data2.insert(0.25f);

    FibbonachiHeap<float>::join(&data1, &data2);
    
    data1.printTop();
    std::cout << '\n' << data1.getMin() << '\n';
    
    data1.compress();

    data1.printTop();

    std::cout << '\n' << data1.popMin() << '\n';
    std::cout << data1.getSize() << '\n';

    return 0;
}
