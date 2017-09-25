/*
 * queue.h
 *
 *  Created on: 08.05.2017
 *      Author: Martin
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#define QUEUE_MAX_SIZE 16
void queue_init();
int queue_put(int v);
int queue_get(int* v);
int queue_empty();

#endif /* QUEUE_H_ */
