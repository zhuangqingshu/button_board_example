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

#ifndef __LIGHT_HANDLE_H__
#define __LIGHT_HANDLE_H__

#include "mdf_common.h"
#include "mwifi.h"
#include "mlink.h"
#include "mupgrade.h"

#include "mespnow.h"
#include "mconfig_blufi.h"
#include "mconfig_chain.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief The value of the cid corresponding to each attribute of the button
 */
typedef enum device_cid {
	DEVICE_CID_KEY0 		   = 10,
	DEVICE_CID_KEY1 		   = 11,
	DEVICE_CID_KEY2 		   = 12,
	DEVICE_CID_KEY3 		   = 13,
	DEVICE_CID_KEY4 		   = 14,
	DEVICE_CID_KEY5 		   = 15,
};

/**
 * @brief Show layer of node by light.
 *
 * @param handle_data pointer of mlink_handle_data_t
 *
 * @return
 *     - MDF_OK
 *     - MDF_ERR_INVALID_ARG
 *     - MDF_FAIL
 */
mdf_err_t light_show_layer(mlink_handle_data_t *handle_data);

/**
 * @brief Get the TSF time.
 *
 * @param handle_data pointer of mlink_handle_data_t
 *
 * @return
 *     - MDF_OK
 *     - MDF_ERR_INVALID_ARG
 *     - MDF_FAIL
 */
mdf_err_t light_get_tsf_time(mlink_handle_data_t *handle_data);

/**
 * @brief Set light characteristic
 *
 * @param cid characteristic id
 * @param arg arguments
 *
 * @return
 *     - MDF_OK
 *     - MDF_ERR_INVALID_ARG
 *     - MDF_FAIL
 */
mdf_err_t mlink_set_value(uint16_t cid, void *arg);

/**
 * @brief Get light characteristic
 *
 * @param cid characteristic id
 * @param arg arguments
 *
 * @return
 *     - MDF_OK
 *     - MDF_ERR_INVALID_ARG
 *     - MDF_FAIL
 */
mdf_err_t mlink_get_value(uint16_t cid, void *arg);

#ifdef __cplusplus
}
#endif

#endif /**< __LIGHT_HANDLE_H__ */
