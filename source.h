#ifndef _source_h
#define _source_h

#include <deque>
#include "monitor.h"

#define BUFF_SIZE 20


class MyMonitor: public Monitor {

    public:
        MyMonitor();
        MyMonitor(int, int, int, int, int, int);
        ~MyMonitor();
        int generateA();
        int generateB();
        void enterItem(int& element, char procChr);
        void popItem(char procChr);
        
    private:
        
        /* definicje kolejki */
        void sleepRandTime();
        std::deque<int> buffer;
        void printQ();
        int checkHead();
        int total = 0;

    protected:
        Condition full_a, full_b, empty_a, empty_b;
        Condition even_space, diff_even_odd;

};

#endif