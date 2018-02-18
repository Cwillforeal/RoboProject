
#include "test.h"
#include <fstream>
#include <dirent.h>


TestOutput::TestOutput(void){

    /* Debug pin setup P9_41 GPIO 20. */
    test_GPIO.open("/sys/class/gpio/export");
    test_GPIO << "20";
    test_GPIO.close();

    /* Confirm init worked!. */
    if(!opendir("/sys/class/gpio/gpio20"))
    {
        cout << "Failed to open gpio 20." << endl;
    }

    /* Set direction and initial value. */
    test_GPIO.open("/sys/class/gpio/gpio20/direction");
    test_GPIO << "out";
    test_GPIO.close();
    test_GPIO.open("/sys/class/gpio/gpio20/value");
    test_GPIO << "0";
}

void TestOutput::On(){
    test_GPIO.open("/sys/class/gpio/gpio20/value");
    test_GPIO << "1";
    test_GPIO.close();
}

void TestOutput::Off(){
    test_GPIO.open("/sys/class/gpio/gpio20/value");
    test_GPIO << "0";
    test_GPIO.close();
}