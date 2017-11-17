//
// Created by student on 13.11.2017.
//

#include <iostream>
#include "Barista.h"
#include "BaristaQueue.h"


Barista:: Barista(){
    _time_utilization = -1.0;
    _status = -1;
    _barista_id = -1;
    _deadline = -1;
}

Barista:: Barista( int barista_id ){
    _time_utilization = 0;
    _status = 0;
    _deadline = 0;
    _barista_id = barista_id;

}

Barista:: Barista(const Barista& other){
    _time_utilization = other._time_utilization;
    _deadline = other._deadline;
    _status = other._status;
    _barista_id = other._barista_id;
}

Barista:: ~Barista(){
    //not much
}

bool Barista:: isBusy(){
    if(_status == 1){
        return true;
    }
    else {
        return false;
    }
}


void Barista:: process_barista( double global_time, BaristaQueue& b_queue ){ //toggle the status
    if ( global_time*10000 >= _deadline*10000 && _status == 1 ){ //milestone reached
        _status = 0; //set barista free
        _deadline = 0;

        if( b_queue._size > b_queue._max_length ) { //after an order is done, check for the other waiting orders in the queue
            b_queue._max_length = b_queue._size;
        }
        
    }
}


bool Barista:: getTask( BaristaQueue& b_queue, double global_time, double turnaround[] ){
    if( !b_queue.isEmpty() && _status == 0 ){
        _status = 1;
        double _brew_time  = ((b_queue._b_queue).top())._brew_time;
        double _arrival_time  = ((b_queue._b_queue).top())._arrival_time;
        int _order_id  = ((b_queue._b_queue).top())._order_id;
        (b_queue._b_queue).pop();
        b_queue._size--;
        _time_utilization = _time_utilization + _brew_time;
        _deadline = global_time + _brew_time;
        turnaround[_order_id] = _deadline - _arrival_time;
        printf("%d  - %lf\n", _order_id, turnaround[_order_id] );
        return true;
    }
    else {
        return false;
    }
}

