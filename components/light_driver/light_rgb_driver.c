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
#include "light_driver.h"
#include "mdf_info_store.h"
#include "iot_light.h"

#define LIGHT_LED_NUM                     (3)
#define LIGHT_GPIO_LED_RED                GPIO_NUM_27
#define LIGHT_GPIO_LED_GREEN              GPIO_NUM_26
#define LIGHT_GPIO_LED_BLUE               GPIO_NUM_14

#define LIGHT_LED_TIMER_BIT               (LEDC_TIMER_12_BIT)
#define LIGHT_LED_FULL_DUTY               ((1 << LIGHT_LED_TIMER_BIT) - 1)

/**
 * @brief The id of the channel corresponding to the led light
 */
enum light_channel {
    CHANNEL_ID_RED   = 0,
    CHANNEL_ID_GREEN = 1,
    CHANNEL_ID_BLUE  = 2,
};

static const char *TAG                    = "light_driver";
static light_handle_t g_light_led_handle = NULL;
static bool g_light_led_blink_flag       = false;


mdf_err_t light_driver_led_set_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
    mdf_err_t ret = MDF_OK;

    /**< NOTE: repair the pwd output unbalance */
    red = red / 2 * 180 / 255;
    green = green * 180 / 255;
    blue = blue * 180 / 255;

    if (g_light_led_blink_flag) {
        light_driver_led_blink_stop();
    }

    ret = iot_light_fade_with_time(g_light_led_handle, CHANNEL_ID_RED, red * LIGHT_LED_FULL_DUTY / 255, 0);
    MDF_ERROR_CHECK(ret < 0, ret, "iot_light_fade_with_time, ret: %d", ret);

    ret = iot_light_fade_with_time(g_light_led_handle, CHANNEL_ID_GREEN, green * LIGHT_LED_FULL_DUTY / 255, 0);
    MDF_ERROR_CHECK(ret < 0, ret, "iot_light_fade_with_time, ret: %d", ret);

    ret = iot_light_fade_with_time(g_light_led_handle, CHANNEL_ID_BLUE, blue * LIGHT_LED_FULL_DUTY / 255, 0);
    MDF_ERROR_CHECK(ret < 0, ret, "iot_light_fade_with_time, ret: %d", ret);

    return MDF_OK;
}

mdf_err_t light_driver_led_blink_start(uint8_t red, uint8_t green, uint8_t blue, uint32_t period_ms)
{
    mdf_err_t ret      = MDF_OK;

    /**< NOTE: repair the pwd output unbalance */
    red   = red / 2 * 128 / 255;
    green = green * 128 / 255;
    blue  = blue * 128 / 255;

    if (g_light_led_blink_flag) {
        light_driver_led_blink_stop();
    }

    ret = iot_light_breath_config(g_light_led_handle, CHANNEL_ID_RED,
                                  red * LIGHT_LED_FULL_DUTY / 255, period_ms);
    MDF_ERROR_CHECK(ret < 0, ESP_FAIL, "iot_light_breath_config, ret: %d", ret);
    ret = iot_light_breath_config(g_light_led_handle, CHANNEL_ID_GREEN,
                                  green * LIGHT_LED_FULL_DUTY / 255, period_ms);
    MDF_ERROR_CHECK(ret < 0, ESP_FAIL, "iot_light_breath_config, ret: %d", ret);
    ret = iot_light_breath_config(g_light_led_handle, CHANNEL_ID_BLUE,
                                  blue * LIGHT_LED_FULL_DUTY / 255, period_ms);
    MDF_ERROR_CHECK(ret < 0, ESP_FAIL, "iot_light_breath_config, ret: %d", ret);

    ret = iot_light_operate_start(g_light_led_handle, CHANNEL_ID_RED);
    MDF_ERROR_CHECK(ret < 0, ESP_FAIL, "iot_light_operate_start, ret: %d", ret);
    ret = iot_light_operate_start(g_light_led_handle, CHANNEL_ID_GREEN);
    MDF_ERROR_CHECK(ret < 0, ESP_FAIL, "iot_light_operate_start, ret: %d", ret);
    ret = iot_light_operate_start(g_light_led_handle, CHANNEL_ID_BLUE);
    MDF_ERROR_CHECK(ret < 0, ESP_FAIL, "iot_light_operate_start, ret: %d", ret);

    g_light_led_blink_flag = true;
    return MDF_OK;
}

mdf_err_t light_driver_led_blink_stop()
{
    mdf_err_t ret = MDF_OK;

    if (g_light_led_blink_flag == false) {
        return MDF_OK;
    }

    ret = iot_light_operate_stop(g_light_led_handle, CHANNEL_ID_RED);
    MDF_ERROR_CHECK(ret < 0, ESP_FAIL, "iot_light_operate_stop, ret: %d", ret);

    ret = iot_light_operate_stop(g_light_led_handle, CHANNEL_ID_GREEN);
    MDF_ERROR_CHECK(ret < 0, ESP_FAIL, "iot_light_operate_stop, ret: %d", ret);

    ret = iot_light_operate_stop(g_light_led_handle, CHANNEL_ID_BLUE);
    MDF_ERROR_CHECK(ret < 0, ESP_FAIL, "iot_light_operate_stop, ret: %d", ret);

    return MDF_OK;
}

mdf_err_t light_driver_led_init()
{
    mdf_err_t ret = MDF_OK;

    /**
     * @brief led
     */
    for (int i = 0; i < LIGHT_LED_NUM; ++i) {
        g_light_led_handle = iot_light_create(LEDC_TIMER_0, LEDC_HIGH_SPEED_MODE, 2000, 3, LIGHT_LED_TIMER_BIT);
        iot_light_channel_regist(g_light_led_handle, CHANNEL_ID_RED, LIGHT_GPIO_LED_RED, LEDC_CHANNEL_0);
        iot_light_channel_regist(g_light_led_handle, CHANNEL_ID_GREEN, LIGHT_GPIO_LED_GREEN, LEDC_CHANNEL_1);
        iot_light_channel_regist(g_light_led_handle, CHANNEL_ID_BLUE, LIGHT_GPIO_LED_BLUE, LEDC_CHANNEL_2);
    }

    return MDF_OK;
}

mdf_err_t light_driver_led_deinit()
{
    return MDF_OK;
}


