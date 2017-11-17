//
// Created by student on 13.11.2017.
//
#include <iostream>
#include "Order.h"
#include "CashierQueue.h"
#include "Cashier.h"
#include "BaristaQueue.h"


Cashier:: Cashier(){ //this will not be used, unless required by any of the STL container
    _cashier_id = -1;
    _b_queue_id = -1;
    _time_utilization = -1.0;
    _deadline = -1.0;
    _status = -1;
    _order = nullptr;

}


Cashier:: Cashier(int cashier_id, int b_queue_id, double time_utilization, int status){
    _cashier_id = cashier_id;
    _b_queue_id = b_queue_id;
    _time_utilization = time_utilization;
    _deadline = 0;
    _status = status;
}

Cashier:: Cashier(const Cashier& other){ //this will not be used, unless required by any of the STL container
    _cashier_id = other._cashier_id;
    _b_queue_id = other._b_queue_id;
    _time_utilization = other._time_utilization;
    _deadline = other._deadline;
    _status = other._status;
}

Cashier:: ~Cashier(){
    if(_order){
        delete _order;
        _order = nullptr;
    }
}


void Cashier:: process_cashier( double global_time, std::vector<BaristaQueue>& b_queue_vector ){ //toggles the status
    if ( global_time*10000 >= _deadline*10000 && _status == 1 ){ //milestone reached
        _status = 0; //set cashier free
        _deadline = 0;
        if( _order ){ //if there was as order assigned to it, send it
            Cashier:: assignBarista(b_queue_vector);
        }
    }
}


bool Cashier:: getTask( CashierQueue& cashier_queue, double global_time ){
    if(_status == 0 && cashier_queue.isEmpty() == false ) {
        if( global_time*10000 >= 10000*cashier_queue.head->_arrival_time ){
            double art = cashier_queue.head->_arrival_time;
            _order = new Order(*(cashier_queue.head));
            cashier_queue.removeHead();
            cashier_queue._size--;
            _status = 1;
            _time_utilization = _time_utilization + _order->_order_time; //consume time
            _deadline = global_time + _order->_order_time;
            return true; //new task assigned
        }
    }

    else {
        return false;   //task assignment failed
    }
}

void Cashier:: assignBarista( std::vector<BaristaQueue>& b_queue_vector ){
    (b_queue_vector[_b_queue_id]._b_queue).push(*_order);

    ++b_queue_vector[_b_queue_id]._size;

    if(_order){
        delete _order;
        _order = nullptr;
    }
}

bool Cashier:: isBusy( ) {
    if( _status == 1 ){
        return true;
    }
    else{
        return false;
    }
}

