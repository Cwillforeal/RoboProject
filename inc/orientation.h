//orientation.h:  Keeps track for all orientation related stuff

#define ASCALE 0x00 //2g
#define GSCALE 0x00 //250 DPS
#define G_CONVERT 32768

typedef struct{
    int16_t X;
    int16_t Y;
    int16_t Z;
} accel_t;


class Data
{
public:
	float x,y,z;
	Data(void);	
	void display(void);
};

class Orientation
{
    private:
        I2CDevice * mpu9250;
    public:
        Orientation(void);
        void readAccelData(accel_t &dataOut);
        void readGyroData(accel_t &dataOut);
        Data *convertAccelData(accel_t &data);
        Data *convertGyroData(accel_t &data);
        void printAccelData(accel_t data);
};
