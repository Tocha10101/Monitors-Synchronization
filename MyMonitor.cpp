#include <iostream>
#include <queue>
#include <cstring>
#include "monitor.h"
#include "source.h"


using namespace std;

MyMonitor::MyMonitor(int full_a_v, int full_b_v, int empty_a_v, int empty_b_v, int even_space_v, int diff_even_odd_v) :
full_a(full_a_v), full_b(full_b_v), empty_a(empty_a_v), empty_b(empty_b_v), even_space(even_space_v), diff_even_odd(diff_even_odd_v)
{}

MyMonitor::~MyMonitor() {}

int MyMonitor::generateA() {
    int value = rand() % 100;
    return value % 2 ? value + 1: value;
}

int MyMonitor::generateB() {
    int value = rand() % 100;
    return value % 2 ? value : value + 1;
}

void MyMonitor::printQ() {
    cout << "Elements: ";
    for (int i = 0; i < buffer.size(); i++) {
        cout << buffer[i] << " ";
    }
    cout << "\n\n";
}

void MyMonitor::enterItem(int& i, char c) {
    enter();
    if (c == 'A') {
        wait(empty_a);
        wait(even_space);
        buffer.push_back(i);
        cout << "Just added element " << i << "\n";
        printQ();
        signal(diff_even_odd);
        sleepRandTime();
        signal(full_a);
    } else if (c == 'B') {   
        wait(empty_b);
        buffer.push_back(i);
        cout << "Just added element " << i << "\n";
        printQ();
        wait(diff_even_odd);
        sleepRandTime();
        signal(full_b);
    }
    leave();
    sleepRandTime();
}

void MyMonitor::popItem(char c) {
    int popped = -1;
    enter();
    if (c == 'A') {
        if (buffer.size() >= 3 && checkHead() == 0) {
            wait(full_a);
            popped = buffer.front();
            buffer.pop_front();
            cout << "Just popped element " << popped << "\n";
            printQ();
            signal(even_space);
            wait(diff_even_odd);
            signal(empty_a);
        }
    } else if (c == 'B') {
        if (buffer.size() >= 7 && checkHead() == 1) {
            wait(full_b);
            popped = buffer.front();
            buffer.pop_front();
            cout << "Just popped element " << popped << "\n";
            printQ();
            signal(diff_even_odd);
            signal(empty_b);
        }
    }
    leave();
    sleepRandTime();
}

void MyMonitor::sleepRandTime() {
    int quantum = 1 + rand() % 5;
    sleep(quantum);
}


int MyMonitor::checkHead() {
    return buffer.front() % 2;
}
