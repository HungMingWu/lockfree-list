/*
 * lock-free order-list sample implementation based on 
 * http://www.research.ibm.com/people/m/michael/spaa-2002.pdf
 * Kevin Lynx 2015.05.02
 */

#ifndef __l_list_h
#define __l_list_h

#include "common.h"

/* test purpose */
typedef int key_t;
typedef int value_t;
#define NULL_VALUE 0

#define KEY_CMP(k1, k2) (k1 - k2)

typedef struct node_t {
    key_t key;
    value_t val;
    struct node_t *next;
} node_t;

class list_t {
	node_t *head;
public:
	list_t();
	~list_t();
	int insert(key_t key, value_t val);
	int remove(key_t key);
	value_t lookup(key_t key);
	bool exist(key_t key);
	int count() const;
};

#endif
