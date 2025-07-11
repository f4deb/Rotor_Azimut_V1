//Structure for Accelerometer, Gyrometer, Magnetometer
#ifndef SENSOR_H
#define SENSOR_H

#define SENSOR_TASK_STACK_SIZE   3072

typedef struct _accel_data{
    short x;
    short y;
    short z;
} accel_data;

typedef struct _magneto_data{
    short x;
    short y;
    short z;
} magneto_data;


/*
 @brief initialize gy511 using default settings. To use accelerometer or magnetometer, need gy511_accel_init or gy511_magneto_init.
*/
void gy511_init();

/*
@brief initialize gy511 to use magnetometer
*/
void gy511_magneto_init();

/*
@brief initialize gy511 to use accelerometer
*/
void gy511_accel_init();

/*
@brief get accelerometer data. Need gy511_accel_init.
*/
accel_data gy511_get_accel();

/*
@brief get magnetometer data. Need gy511_magneto_init.
*/
magneto_data gy511_get_magneto();



void setSensorRefresh(int value);


void initSensor(void);

void sensor_task(void *arg);

#endif