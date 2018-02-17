#ifndef _PID_SOURCE_
#define _PID_SOURCE_

#include <iostream>
#include <cmath>
#include "pid.h"

using namespace std;

class PIDImpl
{
    public:
        PIDImpl( double dt, double max, double min, double Kp, double Kd, double Ki );
        ~PIDImpl();
        double calculate( double setpoint, double pv );
        double _Kp;
        double _Kd;
        double _Ki;
        double _dt;
        double _max;
        double _min;

    private:
        double _pre_error;
        double _integral;
};


PID::PID( double dt, double max, double min, double Kp, double Kd, double Ki )
{
    pimpl = new PIDImpl(dt,max,min,Kp,Kd,Ki);
}
double PID::calculate( double setpoint, double pv )
{
    return pimpl->calculate(setpoint,pv);
}
void PID::update_values(double Kp, double Kd, double Ki){
    this->pimpl->_Kp = Kp;
    this->pimpl->_Kd = Kd;
    this->pimpl->_Ki = Ki;}

void PID::print_values(void){
    cout << "KP: " << this->pimpl->_Kp<<endl;
    cout << "Kd: " << this->pimpl->_Kd<<endl;
    cout << "Ki: " << this->pimpl->_Ki<<endl;}

PID::~PID() 
{
    delete pimpl;
}


/**
 * Implementation
 */
PIDImpl::PIDImpl( double dt, double max, double min, double Kp, double Kd, double Ki ) :
    _dt(dt),
    _max(max),
    _min(min),
    _Kp(Kp),
    _Kd(Kd),
    _Ki(Ki),
    _pre_error(0),
    _integral(0)
{
}

double PIDImpl::calculate( double setpoint, double pv )
{
    
    // Calculate error
    double error = setpoint - pv;
    //cout <<"Error: "<<error<<endl;

    // Proportional term
    double Pout = _Kp * error;

    // Integral term
    _integral += error * _dt;
    //cout <<"Integral: "<<_integral<<endl;

    double Iout = _Ki * _integral;

    // Derivative term
    double derivative = (error - _pre_error) / _dt;
    //cout <<"Derivative: "<<derivative<<endl;
    double Dout = _Kd * derivative;

    // Calculate total output
    double output = Pout + Iout + Dout;

    // Restrict to max/min
    if( output > _max )
        output = _max;
    else if( output < _min )
        output = _min;

    // Save error to previous error
    _pre_error = error;

    return output;
}

PIDImpl::~PIDImpl()
{
}

#endif
