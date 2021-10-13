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

#ifndef __MDF_BUTTON_DRIVER_H__
#define __MDF_BUTTON_DRIVER_H__

#include "iot_button.h"
#include "mdf_common.h"

#ifdef  __cplusplus
extern "C" {
#endif


typedef enum {
	BUTTON_E_KEY_0 = 0,
	BUTTON_E_KEY_1,
	BUTTON_E_KEY_2,
	BUTTON_E_KEY_3,
	BUTTON_E_KEY_4,
	BUTTON_E_KEY_5,
	BUTTON_E_KEY_SET,
	BUTTON_E_KEY_SET2
};


#define MDF_EVENT_BUTTON_KEY_NONE               (MDF_EVENT_CUSTOM_BASE + 0x01)
#define MDF_EVENT_BUTTON_KEY_PUSH               (MDF_EVENT_CUSTOM_BASE + 0x02)
#define MDF_EVENT_BUTTON_KEY_RELEASE            (MDF_EVENT_CUSTOM_BASE + 0x03)
#define MDF_EVENT_BUTTON_KEY_SHORT_PRESS        (MDF_EVENT_CUSTOM_BASE + 0x04)
#define MDF_EVENT_BUTTON_KEY_LONG_PRESS_PUSH    (MDF_EVENT_CUSTOM_BASE + 0x05)
#define MDF_EVENT_BUTTON_KEY_LONG_PRESS_RELEASE (MDF_EVENT_CUSTOM_BASE + 0x06)
/**
 * @brief  Button initialize
 *
 * @return
 *      - MDF_OK
 *      - MDF_ERR_INVALID_ARG
 */
mdf_err_t button_driver_init();

/**
 * @brief  Button deinitialize
 *
 * @return
 *      - MDF_OK
 *      - MDF_ERR_INVALID_ARG
 */
mdf_err_t button_driver_deinit();

#ifdef __cplusplus
}
#endif

#endif/**< __MDF_BUTTON_DRIVER_H__ */
