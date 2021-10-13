// Copyright 2017 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef __MDF_BUZZER_DRIVER_H__
#define __MDF_BUZZER_DRIVER_H__

#include "mdf_common.h"

#ifdef  __cplusplus
extern "C" {
#endif


/**
 * @brief  Light initialize
 *
 * @param  config [description]
 *
 * @return
 *      - MDF_OK
 *      - MDF_ERR_INVALID_ARG
 */
mdf_err_t buzzer_driver_init();

/**
 * @brief  Light deinitialize
 *
 * @return
 *      - MDF_OK
 *      - MDF_ERR_INVALID_ARG
 */
mdf_err_t buzzer_driver_deinit();

/**
 * @brief Set the color of the light
 *
 * @param  red   Red led brightness, the range is: 0 ~ 255
 * @param  green Green led brightness, the range is: 0 ~ 255
 * @param  blue  Blue led brightness, the range is: 0 ~ 255
 *
 * @return
 *     - MDF_OK
 *     - MDF_FAIL
 */
mdf_err_t buzzer_driver_set_onoff(uint8_t onoff);

/**
 * [buzzer_driver_blink_start description]
 *
 * @param  red   Red led brightness, the range is: 0 ~ 255
 * @param  green Green led brightness, the range is: 0 ~ 255
 * @param  blue  Blue led brightness, the range is: 0 ~ 255
 * @param  period_ms breath period (uint: ms)
 *
 * @return
 *     - MDF_OK
 *     - MDF_FAIL
 */
mdf_err_t buzzer_driver_start(uint8_t count, uint32_t period_ms);

/**
 * @brief Stop the blink of led
 *
 * @return
 *     - MDF_OK
 *     - MDF_FAIL
 */
mdf_err_t buzzer_driver_stop();


/**@}*/

#ifdef __cplusplus
}
#endif

#endif/**< __MDF_BUZZER_DRIVER_H__ */
