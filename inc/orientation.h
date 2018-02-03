//orientation.h:  Keeps track for all orientation related stuff

#define ASCALE 0x00 //2g
#define G_CONVERT 32768

typedef struct{
    int16_t X;
    int16_t Y;
    int16_t Z;
} accel_t;

class Orientation
{
    private:
        I2CDevice * mpu9250;
    public:
        Orientation(void);
        void readAccelData(accel_t &dataOut);
        void convertAccelData(accel_t &data);
        void printAccelData(accel_t data);
};
