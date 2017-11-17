//
// Created by student on 13.11.2017.
//

#ifndef PROJECT2_BARISTA_H
#define PROJECT2_BARISTA_H


#include "BaristaQueue.h"
#include <vector>

class Barista {
public:
    double  _time_utilization;
    double _deadline;
    int _status;
    int _barista_id;



    Barista();
    Barista(int barista_id);
    Barista(const Barista& other);
    ~Barista();

    bool isBusy();
    bool getTask(BaristaQueue& b_queue, double global_time,  double turnaround[]);
    void process_barista( double global_time, BaristaQueue& b_queue);
};


#endif //PROJECT2_BARISTA_H
