//drive.h
#include "main.h"
#include <string>
#include <fstream>

#define WHEEL_PERIOD 1000000000

class Drive{
    private:
        string pwm_path;
        ofstream left_wheel;
        ofstream right_wheel;
        ofstream gpio_left;
        ofstream gpio_right;
    public:
        Drive(void);
        void reverse_left(void);
        void reverse_right(void);
        void forward_left(void);
        void forward_right(void);
        void set_speed_left(int speed);
        void set_speed_right(int speed);
};
