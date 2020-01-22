#include <iostream>
#include <thread>
#include <ctime>
#include "monitor.h"
#include "source.h"


using namespace std;

MyMonitor monitor(0, 0, BUFF_SIZE / 2, BUFF_SIZE / 2, 9, 0);

void produceA() {
    int num;
    while(true) {
        num = monitor.generateA();
        monitor.enterItem(num, 'A');
    }
}

void produceB() {
    int num;
    while(true) {
        num = monitor.generateB();
        monitor.enterItem(num, 'B');
    }
}

void consumeA() {
    while(true) {
        monitor.popItem('A');
    }
}

void consumeB() {
    while (true) {
        monitor.popItem('B');
    }
}

int main() {

    void * ptr;
    srand(time(NULL));
    
    std::thread prodA(produceA);
    std::thread prodB(produceB);
    std::thread consA(consumeA);
    std::thread consB(consumeB);

    // pthread_t producer_a_thr, producer_b_thr, consumer_a_thr, consumer_b_thr, producer_c_thr, producer_d_thr;
    // pthread_create(&producer_a_thr, NULL, produceA, ptr);
    // pthread_create(&producer_b_thr, NULL, produceB, ptr);
    // pthread_create(&consumer_a_thr, NULL, consumeA, ptr);
    // pthread_create(&consumer_b_thr, NULL, consumeB, ptr);

    // pthread_exit(nullptr);
    prodA.join();
    prodB.join();
    consA.join();
    consB.join();
    return 0;
}