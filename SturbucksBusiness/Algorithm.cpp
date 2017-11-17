//
// Created by student on 13.11.2017.
//

#include <iostream>
#include <vector>
#include "Algorithm.h"
#include "CashierQueue.h"
#include "Cashier.h"
#include "BaristaQueue.h"
#include "Barista.h"
#include "fstream"
#include <sstream>
#include <iomanip>

int Algorithm:: temp = 0;

Algorithm:: Algorithm(int mode, std::string inputfile, std::string outputfile ){

    std:: ofstream outfile;
    outfile.open(outputfile, std::ios::app);

    double _global_time = 0.00000;
    double _time_step =   0.00001;

    const char* case_id;

    CashierQueue cashier_queue(inputfile);

    int _number_of_cashiers = cashier_queue._number_of_cashiers;
    int _number_of_baristas = cashier_queue._number_of_baristas;
    int _number_of_orders = cashier_queue._number_of_orders;

    std::vector<Cashier> cashier_vector;
    std::vector<BaristaQueue> b_queue_vector;
    std::vector<Barista> b_vector;

    std::vector<Cashier> :: iterator it_cv = cashier_vector.begin();
    std::vector<BaristaQueue>:: iterator it_bqv = b_queue_vector.begin();
    std::vector<Barista> :: iterator it_bv = b_vector.begin();


    if(mode == 0) {
        for (int i = 0; i < _number_of_cashiers; i++) {
            cashier_vector.push_back(Cashier(i, 0, 0, 0));
        }
    }

    else {
        int _b_queue_id = 0;
        for (int i = 0; i< _number_of_cashiers; i++){
            cashier_vector.push_back(Cashier(i, _b_queue_id, 0, 0));
            if( i%3 ==2 ){
                _b_queue_id++;
            }
        }
    }

    if(mode == 0){
        b_queue_vector.push_back( BaristaQueue( 0 ) );
    }

    else {
        for (int i=0; i<_number_of_baristas; i++){
            b_queue_vector.push_back(BaristaQueue(i) );
        }
    }

    for (int i=0; i<_number_of_baristas; i++){
        b_vector.push_back( Barista(i) );
    }

    double turnaround[_number_of_orders];

    while( true ){



        for(it_cv = cashier_vector.begin(); it_cv < cashier_vector.end(); it_cv++){
            (*it_cv).process_cashier(_global_time, b_queue_vector);
            (*it_cv).getTask(cashier_queue, _global_time);
        }


        for(it_bv = b_vector.begin(); it_bv < b_vector.end(); it_bv++){
            
            if(mode == 0) {
                (*it_bv).process_barista(_global_time, b_queue_vector[0] ); 
                (*it_bv).getTask(b_queue_vector[0], _global_time, turnaround );
                           
            }

            else {
                (*it_bv).process_barista(_global_time, b_queue_vector[(*it_bv)._barista_id]);
                (*it_bv).getTask(b_queue_vector[(*it_bv)._barista_id], _global_time, turnaround );
            }
        }


        bool system_free = true;
        for(it_cv = cashier_vector.begin(); it_cv < cashier_vector.end(); it_cv++){
            if( (*it_cv).isBusy() ){

                system_free = false;
                break;
            }
        }


        if(system_free) {
            for(it_bv = b_vector.begin(); it_bv < b_vector.end(); it_bv++){
                if( (*it_bv).isBusy() ){

                    system_free = false;
                    break;
                }
            }
        }


        if(system_free) {
            for(it_bqv = b_queue_vector.begin(); it_bqv < b_queue_vector.end(); it_bqv++){
                if( !(*it_bqv).isEmpty() ){
                    system_free = false;
                    break;
                }
            }
        }

        if(system_free && cashier_queue._size == 0){
            break;
        }
        
        else{
            cashier_queue.lenCashierQueue(_global_time);
            case_id = (temp == 0) ? "Single Queue": "Multiple Queues";

            printf("Global Time: Case: %s - %lf\n", case_id, _global_time );
            _global_time = _global_time + _time_step;
        }



    }



    outfile<<std::fixed << std::setprecision(2)<<_global_time<<std::endl;
    outfile<<cashier_queue._max_length<<std::endl;

    if(mode == 0){
        outfile<<b_queue_vector[0]._max_length<<std::endl;

    }
    else {

        for(it_bqv = b_queue_vector.begin(); it_bqv < b_queue_vector.end(); it_bqv++){
            outfile<<it_bqv->_max_length<<std::endl;
        }

    }

    for(it_cv = cashier_vector.begin(); it_cv < cashier_vector.end(); it_cv++){
        outfile<<std::fixed << std::setprecision(2)<<it_cv->_time_utilization/_global_time<<std::endl;

    }

    for(it_bv = b_vector.begin(); it_bv < b_vector.end(); it_bv++){
        outfile<<std::fixed << std::setprecision(2)<<it_bv->_time_utilization/_global_time<<std::endl;
    }

    if(temp==0) {

        for (int i = 0; i < _number_of_orders; i++) {
            outfile << std::fixed << std::setprecision(2)<<turnaround[i] << std::endl;
        }
    }
    else {
        int i=0;
        for (; i < _number_of_orders - 1; i++) {
            outfile << std::fixed << std::setprecision(2)<<turnaround[i] << std::endl;
        }
        outfile << std::fixed << std::setprecision(2)<<turnaround[i] ;
    }


    if(temp==0){
        outfile<<std::endl;
        temp++;
    }

    outfile.close();
}

Algorithm:: ~Algorithm(){}
