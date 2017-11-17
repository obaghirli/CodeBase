//
// Created by student on 13.11.2017.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "CashierQueue.h"

 CashierQueue:: CashierQueue(std::string filename){
     std::ifstream  inputfile;
     inputfile.open(filename);

     std::string line;

     double arrival_time;
     double order_time;
     double brew_time;
     double price;

     _max_length = 0;
     int counter = 0;
     while(std::getline(inputfile, line)) {

         std::istringstream iss(line);

         if(counter == 0){
             iss>>_number_of_cashiers;
             _number_of_baristas = _number_of_cashiers / 3;
         }

         else if(counter == 1){
             iss>>_number_of_orders;
             _size = _number_of_orders;
         }

         else {
             iss>>arrival_time>>order_time>>brew_time>>price;
             addTail( arrival_time, order_time, brew_time, price, counter-2 );

         }

         counter++;

     }

     inputfile.close();
 }


CashierQueue:: ~CashierQueue(){
     if(head){
         delete head;
         head = nullptr;
     }
 }

void CashierQueue::addTail( double arrival_time, double order_time, double brew_time, double price, int order_id ) {
    if(head == nullptr){
        head = new Order( arrival_time, order_time, brew_time, price, order_id  );
        tail = head;
    }
    else {
        tail->next = new Order( arrival_time, order_time, brew_time, price, order_id  );
        tail = tail->next;
    }
}

void CashierQueue::removeHead() {
    Order* target = head;

    if ( head!=nullptr && head!=tail  ){
        head = head->next;
        target->next = nullptr;
        delete target;
        target = nullptr;
    }

    else if( head!=nullptr && head==tail  ){
        head = head->next;
        target->next = nullptr;
        delete target;
        tail = head;
        target = nullptr;
    }
}

bool CashierQueue::isEmpty(){
    if(head){
        return false;
    }
    else {
        return true;
    }
}

void CashierQueue:: lenCashierQueue( double global_time ){
    Order* walker = head;
    int counter = 0;
    while (walker){
        if( global_time > walker->_arrival_time ){
            counter++;
        }
        walker = walker->next;
    }
    if( counter > _max_length ){
        _max_length = counter;
    }
}

void CashierQueue:: print(){
    Order* temp = head;
    while(temp){
        std::cout<<temp->_arrival_time<<" "<<temp->_order_time<<" "<<temp->_brew_time<<" "<<temp->_price<<" "<<temp->_order_id<<std::endl;
        temp = temp->next;
    }
}