//
// Created by student on 13.11.2017.
//

#ifndef PROJECT2_CASHIERQUEUE_H
#define PROJECT2_CASHIERQUEUE_H

#include <string>
#include "Order.h"

class CashierQueue {
public:

    int _number_of_cashiers;
    int _number_of_baristas;
    int _number_of_orders;
    int _size;
    int _max_length;

    Order* head = nullptr;
    Order* tail = nullptr;

    CashierQueue(std::string filename);
    ~CashierQueue();

    void addTail(double arrival_time, double order_time, double brew_time, double price, int order_id );
    void removeHead();
    bool isEmpty();
    void lenCashierQueue(double global_time);
    void print();

};


#endif //PROJECT2_CASHIERQUEUE_H
