/*
 * lock-free order-list sample implementation based on 
 * http://www.research.ibm.com/people/m/michael/spaa-2002.pdf
 * Kevin Lynx 2015.05.02
 */

#include "l_list.h"
#include "common.h"
#include "haz_ptr.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <vector>
#include <atomic>
#define ASSERT assert

std::atomic<bool> wait(false);
int _tcount = 10;
int _ttimes = 1000;

void worker(list_t &list) {
    unsigned int seed = (unsigned int) time(NULL);
    int max = _ttimes, i;
    while (!wait.load(std::memory_order_relaxed)) ;
    for (i = 1; i <= _ttimes; ++i) {
        int r = rand_r(&seed) % max;
        if (r % 2) {
            list.insert(r, i);
        } else {
            list.remove(r);
        }
    }
    printf("list size: %d\n", list.count());
    haz_gc();
}

int main(int argc, char **argv) {
    {
	list_t list;
        ASSERT(list.insert(1, 1) == 1);
        ASSERT(list.insert(2, 2) == 2);
        ASSERT(list.insert(2, 3) == 2);
        ASSERT(list.lookup(1) == 1); 
        ASSERT(list.lookup(2) == 3); 
        ASSERT(list.remove(3) == false);
        ASSERT(list.remove(1) == true);
        ASSERT(list.lookup(1) == NULL_VALUE); 
        ASSERT(list.insert(1, 2) == 2);
    }
    {
        list_t list;;
        if (argc > 1)
            _tcount = atoi(argv[1]);
        if (argc > 2)
            _ttimes = atoi(argv[2]);
	std::vector<std::thread> thread(_tcount);
	int i;
        printf("thread count %d, loop count %d\n", _tcount, _ttimes);
        for (i = 0; i < _tcount; ++i) 
	    thread[i] = std::thread(worker, std::ref(list));
	wait.store(true, std::memory_order_relaxed);
        for (i = 0; i < _tcount; ++i) 
	    thread[i].join();
    }
    return 0;
}
