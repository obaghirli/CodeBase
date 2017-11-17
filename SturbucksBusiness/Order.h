//
// Created by student on 13.11.2017.
//

#ifndef PROJECT2_ORDER_H
#define PROJECT2_ORDER_H



class Order {
public:
    double _arrival_time;
    double _order_time;
    double _brew_time;
    double _price;
    int _order_id;

    Order* next = nullptr;

    Order();
    Order(double arrival_time, double order_time, double brew_time, double price, int order_id );
    Order(const Order& other);
    Order& operator=(const Order& other);
    ~Order();
    void print() const;

};


#endif //PROJECT2_ORDER_H
