//drive.h
#include "main.h"
#include <string>
#include <fstream>

class Drive{
    private:
        string pwm_path;
        ofstream pwmchip;
    public:
        Drive(void);
};
