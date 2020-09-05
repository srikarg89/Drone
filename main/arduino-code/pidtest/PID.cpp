#include "PID.h"

PID::PID(){}

void PID::begin(double gains1[3], double gains2[3], double error_bounds[3], double pid_bounds[3], double filters[3]){
    for(int i = 0; i < 3; i++){
        _gains1[i] = gains1[i];
        _gains2[i] = gains2[i];
        _error_bounds[i] = error_bounds[i];
        _pid_bounds[i] = pid_bounds[i];
        _filters[i] = filters[i];
    }
    prevError1 = 0;
    prevError2 = 0;
    last_time = millis();
    total_error1 = 0;
    total_error2 = 0;
}

void bound(double val, double lower, double upper){
    if(val < lower){
        return lower;
    }
    if(val > upper){
        return upper;
    }
    return val;
}

void PID::update(double x, double y, double z, double *changes){
    // Let's ignore z for now: x is direction 1, y is direction 2
    double dt = (double)(millis() - last_time) / 1000.0;
    last_time = millis();
    total_error1 += y;
    total_error2 += z;
    total_error1 = bound(total_error1, -_error_bounds[0], _error_bounds[0]);
    total_error2 = bound(total_error2, -_error_bounds[1], _error_bounds[1]);
    double change1 = runPID(_gains1, prevError1, y, dt, total_error1, _pid_bounds[0], _filters[0]);
    double change2 = runPID(_gains2, prevError2, z, dt, total_error2, _pid_bounds[1], _filters[1]);
    prevError1 = y;
    prevError2 = z;
    changes[0] = change1;
    changes[1] = change2;
    // changes[1] = 0.0;
}

double myabs(double val){
    if(val < 0){
        return -val;
    }
    return val;
}

double PID::runPID(double gains[], double prevError, double error, double dt, double total_error, double bound, double N){
    /*
    double P = gains[0] * error;
    double D = ((error - prevError) / dt) * gains[2];
    total_error += (dt * error);
    double I = gains[1] * (total_error);
//    return P + I + D;
    return P + D;
    */
    double minbound = -bound;
    double P = gains[0] * error;
    double D = ((error - prevError) * gains[2]) / dt;
    // Filter: N is the filter coeficcient
    // D = (D * N) / (D + N);
    // if(myabs(error) > myabs(prevError)){
    //     D = 0;
    // }
    double I = gains[1] * total_error * dt;
    double total = P + I + D;
    total = bound(total, minbound, bound);
    Serial.print("P: ");
    Serial.println(P);
    Serial.print("I: ");
    Serial.println(I);
    Serial.print("D: ");
    Serial.println(D);
    Serial.print("Total: ");
    Serial.println(total);
    // Not using I rn, so gains[1] is just 0
    return total;
}

