#include "TestQueue.hpp"
#include "Queue.hpp"

#include <assert.h>

void TestQueue::testAll() {
    testPut();
    testGet();
    testEmpty();
}

void TestQueue::testPut() {
    Queue<int, 4> queue;

    // test normal insertion
    assert(queue.put(1) == true);
    assert(queue.put(2) == true);
    assert(queue.put(3) == true);
    assert(queue.put(4) == true);

    // test insertion to full queue
    assert(queue.put(5) == false);
    assert(queue.put(6) == false);

    // test removing and inserting again
    int result;
    assert(queue.get(result) == true);
    assert(queue.put(7) == true);
}

void TestQueue::testGet() {
    Queue<int, 4> queue;

    // test normal get
    assert(queue.put(1) == true);
    assert(queue.put(2) == true);
    int firstInQueue;
    assert(queue.get(firstInQueue) == true);
    assert(firstInQueue == 1);
    assert(queue.get(firstInQueue) == true);
    assert(firstInQueue == 2);

    // test get of empty list.
    assert(queue.get(firstInQueue) == false);
    assert(firstInQueue == 2);
    assert(queue.get(firstInQueue) == false);
    assert(firstInQueue == 2);

    // test inserting again
    assert(queue.put(1) == true);
    assert(queue.get(firstInQueue) == true);
    assert(firstInQueue == 1);
}

void TestQueue::testEmpty() {
    Queue<int, 4> queue;

    // test empty queue
    assert(queue.empty() == true);

    // test not empty list
    assert(queue.put(1) == true);
    assert(queue.empty() == false);
    assert(queue.put(2) == true);
    assert(queue.empty() == false);
    assert(queue.put(3) == true);
    assert(queue.empty() == false);

    // test full queue
    assert(queue.put(4) == true);
    assert(queue.empty() == false);
    assert(queue.put(5) == false);
    assert(queue.empty() == false);

    // test removing all items from full queue
    int result;
    assert(queue.get(result) == true);
    assert(queue.empty() == false);
    assert(queue.get(result) == true);
    assert(queue.empty() == false);
    assert(queue.get(result) == true);
    assert(queue.empty() == false);
    assert(queue.get(result) == true);
    assert(queue.empty() == true);
}
