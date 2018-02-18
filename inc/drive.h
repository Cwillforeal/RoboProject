//drive.h
#include "main.h"
#include <string>
#include <fstream>

#define DRIVE_PERIOD 1000

#define DRIVE_SPEED_PERCENT(x)      DRIVE_PERIOD*(x/100)

class Drive{
    private:
        string pwm_path;
        ofstream left_wheel;
        ofstream right_wheel;
        ofstream gpio_left;
        ofstream gpio_right;
    public:
        Drive(void);
        ~Drive(void);
        void reverse_left(void);
        void reverse_right(void);
        void forward_left(void);
        void forward_right(void);
        void set_speed_left(int speed);
        void set_speed_right(int speed);
};
