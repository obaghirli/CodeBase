//
// Created by student on 13.11.2017.
//

#include <iostream>
#include "Order.h"

Order::Order(){
    _arrival_time = -1;
    _order_time  = -1;
    _brew_time = -1;
    _price = -1;
    _order_id = -1;

}

Order::Order(double arrival_time, double order_time, double brew_time, double price, int order_id ){
    _arrival_time = arrival_time;
    _order_time = order_time;
    _brew_time = brew_time;
    _price = price;
    _order_id = order_id;
}

Order::Order(const Order& other){

    _arrival_time = other._arrival_time;
    _order_time = other._order_time;
    _brew_time = other._brew_time;
    _price = other._price;
    _order_id = other._order_id;

}

Order& Order:: operator=(const Order& other){
    _arrival_time = other._arrival_time;
    _order_time = other._order_time;
    _brew_time = other._brew_time;
    _price = other._price;
    _order_id = other._order_id;

    return *this;
}

void Order:: print() const {
    std::cout<<_arrival_time<<" "<<_order_time<<" "<<_brew_time<<" "<<_price<<" "<<_order_id<<std::endl;
}

Order::~Order(){

}