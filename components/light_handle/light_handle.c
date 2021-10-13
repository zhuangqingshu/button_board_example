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

#include "mdf_common.h"
#include "mlink.h"

#include "light_handle.h"
static const char *TAG = "light_handle";


mdf_err_t light_show_layer(mlink_handle_data_t *handle_data)
{
    switch (esp_mesh_get_layer()) {
        default:
            break;
    }

    return MDF_OK;
}

mdf_err_t light_get_tsf_time(mlink_handle_data_t *handle_data)
{
    char tsf_time_str[16] = {0x0};

    sprintf(tsf_time_str, "%lld", esp_mesh_get_tsf_time());
    mlink_json_pack(&handle_data->resp_data, "tsf_time", tsf_time_str);

    handle_data->resp_size = strlen(handle_data->resp_data);

    return MDF_OK;
}
mdf_err_t mlink_set_value(uint16_t cid, void *arg)
{
    int value = *((int *)arg);

    switch (cid) {
        default:
            MDF_LOGE("No support cid: %d", cid);
            return MDF_FAIL;
    }

    MDF_LOGD("cid: %d, value: %d", cid, value);

    return MDF_OK;
}

mdf_err_t mlink_get_value(uint16_t cid, void *arg)
{
    int *value = (int *)arg;

    switch (cid) {

        default:
            MDF_LOGE("No support cid: %d", cid);
            return MDF_FAIL;
    }

    MDF_LOGV("cid: %d, value: %d", cid, *value);

    return MDF_OK;
}
