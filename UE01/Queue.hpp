
#ifndef HACKSLASH_TESTQUEUE_HPP
#define HACKSLASH_TESTQUEUE_HPP

#endif //HACKSLASH_TESTQUEUE_HPP

#include <cstddef>
#include <stddef.h>

template<class T, size_t size = 16>
class Queue {

public:
    Queue() :
            head(-1), tail(-1) {

    }

    bool put(const T &t) {
        if (head == -1 && tail == -1) {
            // queue completely empty
            buffer[0] = t;
            head = 0;
            tail = 1;

        } else if (head != tail) {
            // space available
            buffer[tail] = t;
            increaseTail();

        } else {
            // queue is full
            return false;
        }
        return true;
    }



    bool get(T &t) {
        if (head != -1 && tail != -1) {
            // queue is not empty
            t = buffer[head];
            buffer[head] = NULL;
            increaseHead();
            if(head == tail){
                // now empty queue
                tail = -1;
                head = -1;
            }

            return true;
        } else {
            return false;
        }
    }

    bool setToEmpty() {
        while (head != NULL && tail != NULL){
            // is not empty yet
            T dummy;
            get(dummy);
        }
        return true;
    }

    bool empty() {
       if (head == -1 && tail == -1){
           // empty because auf dequeue
           return true;
       } else {
           // something is still in there
           return false;
       }
    }

    void increaseTail(){
        if(tail == size-1){
            tail = 0;
        } else {
            tail++;
        }
    }

    void increaseHead(){
        if(head == size-1){
            head = 0;
        } else {
            head++;
        }
    }

private:
    size_t head;
    size_t tail;
    T buffer[size];
};
