/*******************************************************************
 *   _________     _____      _____    ____  _____    ___  ____    *
 *  |_   ___  |  |_   _|     |_   _|  |_   \|_   _|  |_  ||_  _|   *
 *    | |_  \_|    | |         | |      |   \ | |      | |_/ /     *
 *    |  _|        | |   _     | |      | |\ \| |      |  __'.     *
 *   _| |_        _| |__/ |   _| |_    _| |_\   |_    _| |  \ \_   *
 *  |_____|      |________|  |_____|  |_____|\____|  |____||____|  *
 *                                                                 *
 *******************************************************************
 *                                                                 *
 *  flink userspace library lite, subdevice function "pwm"         *
 *                                                                 *
 *******************************************************************/
 
/** @file pwm.c
 *  @brief flink userspace library, subdevice function "pwm".
 *
 *  Contains the high-level functions for a flink subdevice
 *  which realizes the function "pwm".
 *
 *  @author Martin Züger
 */

#include "flinklib.h"
#include "types.h"

/**
 * @brief Reads the base clock of a PWM subdevice
 * @param subdev: Subdevice.
 * @param frequency: Contains the base clock in Hz.
 * @return int: 0 on success, -1 in case of failure.
 */
int flink_pwm_get_baseclock(flink_subdev* subdev, uint32_t* frequency) {
	
	uint32_t offset;
	
	offset = HEADER_SIZE + SUBHEADER_SIZE;
	
	if(flink_read(subdev, offset, REGISTER_WITH, frequency) != REGISTER_WITH) {
		return EXIT_ERROR;
	}
	return EXIT_SUCCESS;
}

/**
 * @brief Sets the PWM period
 * @param subdev: Subdevice.
 * @param channel: Channel number.
 * @param period: Period of the PWM signal in multiples of the base clock.
 * @return int: 0 on success, -1 in case of failure.
 */
int flink_pwm_set_period(flink_subdev* subdev, uint32_t channel, uint32_t period) {
	
	uint32_t offset;
	
	offset = HEADER_SIZE + SUBHEADER_SIZE + PWM_FIRSTPWM_OFFSET + REGISTER_WITH * channel;
	
	if(flink_write(subdev, offset, REGISTER_WITH, &period) != REGISTER_WITH) {
		return EXIT_ERROR;
	}
	return EXIT_SUCCESS;
}

/**
 * @brief Sets the PWM hightime
 * @param subdev: Subdevice.
 * @param channel: Channel number.
 * @param hightime: Hightime of the PWM signal in multiples of the base clock.
 * @return int: 0 on success, -1 in case of failure.
 */
int flink_pwm_set_hightime(flink_subdev* subdev, uint32_t channel, uint32_t hightime) {
	
	uint32_t offset;
		
	offset = HEADER_SIZE + SUBHEADER_SIZE + PWM_FIRSTPWM_OFFSET + subdev->nof_channels * REGISTER_WITH + REGISTER_WITH * channel;
	
	if(flink_write(subdev, offset, REGISTER_WITH, &hightime) != REGISTER_WITH) {
		return EXIT_ERROR;
	}
	return EXIT_SUCCESS;
}
