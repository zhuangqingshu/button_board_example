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
#include "buzzer_driver.h"
#include "mdf_info_store.h"
#include "iot_light.h"
#include "freertos/timers.h"

#define BUZZER_NUM                     (1)
#define BUZZER_GPIO_0                  CONFIG_BUZZER_GPIO_0

#define BUZZER_TIMER_BIT               (LEDC_TIMER_12_BIT)
#define BUZZER_FULL_DUTY               ((1 << BUZZER_TIMER_BIT) - 1)

/**
 * @brief The id of the channel corresponding to the led light
 */
enum buzzer_channel {
    CHANNEL_ID_BUZZER_0   = 0,
};


static const char *TAG                    = "buzzer_driver";
static light_handle_t g_buzzer_handle = NULL;
static bool g_buzzer_blink_flag       = false;

static TimerHandle_t xTimerBuzzer;
static int32_t lExpireCounters =  0 ;


static void vTimerBuzzerCallback( TimerHandle_t pxTimer )
{
	// Optionally do something if the pxTimer parameter is NULL.
	configASSERT( pxTimer );

	if(lExpireCounters > 0) {
		if(lExpireCounters % 2 == 0) {
			buzzer_driver_set_onoff(1);
		}else {
			buzzer_driver_set_onoff(0);
		}
		lExpireCounters--;
	} 
	if(lExpireCounters == 0) {
		g_buzzer_blink_flag = false;
		xTimerStop( pxTimer, 0 );
	}
}

mdf_err_t buzzer_driver_set_onoff(uint8_t onoff)
{
    mdf_err_t ret = MDF_OK;

    ret = iot_light_fade_with_time(g_buzzer_handle, CHANNEL_ID_BUZZER_0, onoff ? BUZZER_FULL_DUTY / 2 : BUZZER_FULL_DUTY, 0);
    MDF_ERROR_CHECK(ret < 0, ret, "iot_light_fade_with_time, ret: %d", ret);

    return MDF_OK;
}

mdf_err_t buzzer_driver_start(uint8_t count, uint32_t period_ms)
{
    mdf_err_t ret      = MDF_OK;

    if (g_buzzer_blink_flag) {
        buzzer_driver_stop();
    }

	lExpireCounters = count * 2;
	
	xTimerChangePeriod( xTimerBuzzer, period_ms / portTICK_PERIOD_MS, 0 );
	xTimerStart( xTimerBuzzer, 0 );

    g_buzzer_blink_flag = true;
    return MDF_OK;
}

mdf_err_t buzzer_driver_stop()
{
    mdf_err_t ret = MDF_OK;

    if (g_buzzer_blink_flag == false) {
        return MDF_OK;
    }

    xTimerStop( xTimerBuzzer, 0 );

	buzzer_driver_set_onoff(0);
		
	g_buzzer_blink_flag = false;

    return MDF_OK;
}

mdf_err_t buzzer_driver_init()
{
    mdf_err_t ret = MDF_OK;
/*	
	// unuse gpio init to inpul no pull
	gpio_config_t unuse_io_conf;
	//disable interrupt
	unuse_io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
	//set as output mode
	unuse_io_conf.mode = GPIO_MODE_INPUT;
	//bit mask of the pins that you want to set,e.g.GPIO18/19
	unuse_io_conf.pin_bit_mask = BIT64(BUZZER_GPIO_0);
	//disable pull-down mode
	unuse_io_conf.pull_down_en = 0;
	//disable pull-up mode
	unuse_io_conf.pull_up_en = 1;
	//configure GPIO with the given settings
	gpio_config(&unuse_io_conf);
*/
    /**
     * @brief led
     */
    g_buzzer_handle = iot_light_create(LEDC_TIMER_1, LEDC_HIGH_SPEED_MODE, 1000, BUZZER_NUM, BUZZER_TIMER_BIT);
    iot_light_channel_regist(g_buzzer_handle, CHANNEL_ID_BUZZER_0, BUZZER_GPIO_0, LEDC_CHANNEL_3);
	buzzer_driver_set_onoff(0);


	xTimerBuzzer = xTimerCreate(	  "TimerBuzzer",		 // Just a text name, not used by the kernel.
								  100 / portTICK_PERIOD_MS,	 // The timer period in ticks.
								  pdTRUE,		 // The timers will auto-reload themselves when they expire.
								  ( void * ) 0,  // Assign each timer a unique id equal to its array index.
								  vTimerBuzzerCallback // Each timer calls the same callback when it expires.
							  );

    return MDF_OK;
}

mdf_err_t buzzer_driver_deinit()
{
    return MDF_OK;
}


