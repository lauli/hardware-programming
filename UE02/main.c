//*****************************************************************************
//
// MSP432 main.c template - Empty main
//
//****************************************************************************

#include <assert.h>
#include "msp.h"
#include "queue.h"

int main(void)
{
	
    int v;
    queue_init();
    assert(queue_empty());

    assert(queue_put(1));
    assert(queue_put(2));
    assert(queue_put(3));
    assert(!queue_put(4));
    assert(!queue_empty());
    assert(queue_get(&v) && v == 1);
    assert(!queue_empty());
    assert(queue_put(4));

    assert(!queue_empty());
    assert(queue_get(&v) && v == 2);
    assert(queue_get(&v) && v == 3);
    assert(queue_get(&v) && v == 4);
    assert(queue_empty());
    return 0;

	
}
