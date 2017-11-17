//
// Created by student on 13.11.2017.
//

#ifndef PROJECT2_CASHIER_H
#define PROJECT2_CASHIER_H

#include <cstddef>
#include "Order.h"
#include "BaristaQueue.h"

class Cashier {
public:

    int _cashier_id;
    int _b_queue_id; //which barista queue this cashier assigns orders
    double _time_utilization;
    double _deadline;
    Order* _order = nullptr ;
    int _status;


    Cashier();
    Cashier(int cashier_id, int b_queue_id, double time_utilization, int status);
    Cashier(const Cashier& other);
    ~Cashier();

    bool getTask(CashierQueue& cashier_queue, double global_time);
    void assignBarista(std::vector<BaristaQueue>& b_queue_vector);
    void process_cashier( double global_time, std::vector<BaristaQueue>& b_queue_vector );
    bool isBusy();

};


#endif //PROJECT2_CASHIER_H
