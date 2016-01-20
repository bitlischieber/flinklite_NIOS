/*
 * main.c
 *
 *  Created on: 20.01.2016
 *      Author: Raphael Lauber
 */

#include <system.h>
#include "flinklite/flinklib.h"
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
 	uint8_t val, totval;
 	uint32_t val32=0;
 	char description[48];
 	int error = 0;

 	flink_dev*    dev;
 	flink_subdev* subdev;
 	flink_subdev* sdPWM;

 	dev = flink_open();

 	subdev = flink_get_subdevice_by_unique_id(dev, 3); // info device

 	error = flink_info_get_description(subdev, description);

 	sdPWM = flink_get_subdevice_by_unique_id(dev, 2);
 	error = flink_pwm_get_baseclock(sdPWM,&val32);
 	error = flink_pwm_set_period(sdPWM,0,1e6);		// 50 MHz / 1 MHz = 50 Hz = 20 msec periode
 	error = flink_pwm_set_hightime(sdPWM,0,100e3);	// 50 MHz / 100 kHz = 500 Hz = 2 msec high time

 	subdev = flink_get_subdevice_by_unique_id(dev, 1); // GPIO device

 	error = flink_dio_set_direction(subdev, 0x02, 0x01);	// LEDR0
 	error = flink_dio_set_direction(subdev, 0x03, 0x01);	// LEDR1

 	while(1) {

  		error = flink_dio_get_value(subdev,0x00,&val);	// SW0 --> LEDR0
 		totval = val;
 		error = flink_dio_set_value(subdev,0x02,val);
 		error = flink_dio_get_value(subdev,0x01,&val);	// SW1 --> LEDR1
 		totval += val<<1;
 		error = flink_dio_set_value(subdev,0x03,val);

  		switch(totval) {
  			case 0:
  			   	error = flink_pwm_set_hightime(sdPWM,0,100e3);	// 2.00 msec high time
  				break;
  			case 1:
  				error = flink_pwm_set_hightime(sdPWM,0,83e3);	// 1.67 msec high time
  				break;
  			case 2:
  				error = flink_pwm_set_hightime(sdPWM,0,67e3);	// 1.34 msec high time
  				break;
  			case 3:
  				error = flink_pwm_set_hightime(sdPWM,0,50e3);	// 1.00 msec high time
  				break;
  			default:
  				break;
  		} // switch

		usleep(50000);

 	} // while(1)

 	return 0;
} // main
