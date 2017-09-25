/*
 * queue.c
 *
 *  Created on: 08.05.2017
 *      Author: Martin
 */
#include "queue.h"

int head;
int tail;
int queue[QUEUE_MAX_SIZE];

void queue_init(){
    head = -1;
    tail = -1;
}

int queue_put(int v){
    if(head ==-1 && tail == -1){
        queue[0] = v;
        head = 0;
        tail = 1;
    } else if (head != tail){
        queue[tail] = v;
        tail++;
        if(tail == QUEUE_MAX_SIZE){
            tail = 0;
        }
    } else if (head == tail){
        return 0;
    }
    return 1;
}
int queue_get(int* v){
    if(head == -1){
        return 0;
    } else {
        *v = queue[head];
        head++;
        if(head==QUEUE_MAX_SIZE){
            head = 0;
        }if( head == tail){
            head = -1;
            tail = -1;
        }
        return 1;
    }
    return 0;
}

int queue_empty(){
    if(head == -1 && tail == -1){
        return 1;
    }
    return 0;
}

