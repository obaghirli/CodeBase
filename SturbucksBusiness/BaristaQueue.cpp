//
// Created by student on 13.11.2017.
//

#include <iostream>
#include "BaristaQueue.h"



BaristaQueue:: BaristaQueue(){ // will not use this, just in case
    _b_queue_id = -1;
    _size = -1;
    _max_length = -1;
}

BaristaQueue:: BaristaQueue( int b_queue_id ){
    _b_queue_id = b_queue_id;
    _size = 0;
    _max_length = 0;
}

BaristaQueue:: BaristaQueue( const BaristaQueue& other ){
    _b_queue_id = other._b_queue_id;
    _b_queue = other._b_queue;
    _size = other._size;
    _max_length = other._max_length;
}

BaristaQueue& BaristaQueue::operator=( const BaristaQueue& other ){
    _b_queue_id = other._b_queue_id;
    _b_queue = other._b_queue;
    _size = other._size;
    _max_length = other._max_length;

    return *this;
}

BaristaQueue:: ~BaristaQueue(){
    //not much
}

bool BaristaQueue:: isEmpty(){
    return (_size == 0);
}

int BaristaQueue:: getSize(){
        return _size;
}
