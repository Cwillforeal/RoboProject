//orientation.h:  Keeps track for all orientation related stuff

#define ASCALE 0x00 //2g

typedef struct{
    int32_t X;
    int32_t Y;
    int32_t Z;
} accel_t;

class Orientation
{
    private:
        I2CDevice * mpu9250;
    public:
        Orientation(void);
        void getAccelData(accel_t* dataOut);
};
