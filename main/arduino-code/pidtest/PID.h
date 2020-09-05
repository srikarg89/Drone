#ifndef PID_h
#define PID_h

#include "Arduino.h"

class PID{
    public:
        // Gains: [P, I, D]
        PID();
        void begin(double gains1[], double gains2[], double bounds[3], double filters[3]);
        void update(double x, double y, double z, double *changes);
        double runPID(double gains[], double prevError, double error, double dt, double total_error, double bound);
    private:
        double _gains1[3], _gains2[3], _pid_bounds[3], _error_bounds[3], _filters[3];
        double prevError1, prevError2;
        unsigned long last_time;
        double total_error1, total_error2;
};

#endif
