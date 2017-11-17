//
// Created by student on 13.11.2017.
//

#ifndef PROJECT2_BARISTAQUEUE_H
#define PROJECT2_BARISTAQUEUE_H

#include <vector>
#include <queue>
#include "Order.h"

struct ByPrice { // condition for sorting, building maxHeap of Price
    bool operator()( const Order& lhs, const Order& rhs ) const {
        return lhs._price < rhs._price;
    }
};

class BaristaQueue {
public:
    int _b_queue_id;
    int _size = 0;
    int _max_length = 0;
    std::priority_queue< Order, std::vector<Order>, ByPrice > _b_queue;

    BaristaQueue();
    BaristaQueue(int b_queue_id);
    BaristaQueue( const BaristaQueue& other );
    BaristaQueue& operator=( const BaristaQueue& other );
    ~BaristaQueue();

    bool isEmpty();
    int getSize();
};


#endif //PROJECT2_BARISTAQUEUE_H
