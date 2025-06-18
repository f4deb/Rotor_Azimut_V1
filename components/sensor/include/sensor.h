//Structure for Accelerometer, Gyrometer, Magnetometer
#ifndef SENSOR_H
#define SENSOR_H

#define SENSOR_TASK_STACK_SIZE   3072

struct sensorAGM
{
  int	acc_x;
  int	acc_y;
  int	acc_z;
  int	gyr_x;
  int	gyr_y;
  int	gyr_z;
  int	mag_x;
  int	mag_y;
  int	mag_z;
};

void setSensorRefresh(int value);


void initSensor(void);

void sensor_task(void *arg);

#endif