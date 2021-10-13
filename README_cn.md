[[EN]](./README.md)

# ESP32-Button-Board-Example

## 概述

ESP32-Button-Board-Example 是用于测试 ESP32-Button 面板的测试程序，此程序可用于测试硬件的完整性。

此程序适用于：6键面板

主要功能为按下触摸按键蜂鸣器提示，对应按键的LED灯亮起。

## 硬件说明

ESP32-Button-Board-Example 有 6 路触摸按键，1 个物理按键，1 个霍尔传感器，1 个蜂鸣器，7个LED。

1. 6键面板-引脚定义

| 符号 | 状态 | 描述 |
|:---:|:---:|:---|
| GND | P| 接地脚|
| CHIP_PU| I| 芯片使能（高电平有效），模块内部有上拉，为外部使能备用|
| GIPO32| I/O|RTC 32K_XP（32.768 kHz 晶振输入），功能扩展备用脚 |
| GPIO33| I/O|RTC 32K_XN（32.768 kHz 晶振输入），功能扩展备用脚 |
|GIPO0| I/O|IC 内部上拉，功能扩展备用脚。 |
| VDD3.3V|P | 模块供电脚，3V3|
| GPIO36 |I | 触摸按键 0 |
| GPIO39 |I|触摸按键 1|
| GPIO34 |I|触摸按键 2|
| GPIO35 |I|触摸按键 3|
| GPIO4 |I/O|触摸按键 4|
| GPIO5 |I/O|触摸按键 5|
| GPIO23 |I/O |物理按键 0，霍尔传感器输出 |
| GPIO32 |I/O |LED 0 |
| GPIO33 | I/O|LED 1 |
| GPIO25 | I/O |LED 2 |
| GPIO26 | I/O |LED 3 |
| GPIO27 | I/O |LED 4 |
| GPIO14 | I/O |LED 5 |
| GPIO2 | I/O |Backlight |
| GPIO15 | I/O |蜂鸣器 |
| UORXD| I/O|UART 调试和软件烧录接口接收脚 |
| UOTXD| I/O|UART 调试和软件烧录接口发送脚|
| ANT| I/O| 外置天线输出脚 |
| GND | P| RF 接地|

## 工程介绍

### 简介

ESP32-Button-Board-Example 基于 ESP-MDF 构建，主要用到了ESP32 的GPIO，PWM输出功能。

**在使用本工程前，需要先搭建好ESP32开发环境，相关步骤可参考官方说明**：[快速入门 — ESP-MDF 编程指南 v1.0-147-g0b59603 文档 (espressif.com)](https://docs.espressif.com/projects/esp-mdf/zh_CN/latest/get-started/index.html#id4) 

编译&烧写命令

```
cd button_board_example
idf.py -p /dev/ttyUSB0 flash monitor
```

### 代码分析

为了更好地理解工程的实现，本节将对工程中代码的详细分析。

#### 工程结构

```
switch_examples/
├── CMakeLists.txt /* Cmake compiling parameters for the demo */
├── components /* Contains the components used by the demo */
│   └── light_driver /* light driver component */
│   └── light_handle /* light status handle component */
│   └── mesh_utils /* mesh utils component */
├── main /* Stores the main `.c` and `.h` application code files for this demo */
│   ├── Kconfig.projbuild /* Demo configuration file */
│   └── button.c /* main application codes, more info below */
├── Makefile /* Make compiling parameters for the demo */
├── partitions.csv /* Partition table file */
├── README_cn.md /* Quick start guide */
├── README.md /* Quick start guide */
├── sdkconfig /* Current parameters of `make menuconfig` */
├── sdkconfig.defaults /* Default parameters of `make menuconfig` */
└── sdkconfig.old /* Previously saved parameters of `make menuconfig` */
```

#### 源码分析

ESP32 系统初始化完成后，将调用 `app_main`。下面的代码块展示了 `app_main` 函数的主要实现。

```
void app_main()
{
    ……
    ……
    ……
	/**
	 * @brief Light driver initialization
	 */
	MDF_ERROR_ASSERT(light_driver_led_init());
	/**
	 * @brief Buzzer driver initialization
	 */
	MDF_ERROR_ASSERT(buzzer_driver_init());
	/**
	 * @brief Button driver initialization
	 */
	MDF_ERROR_ASSERT(button_driver_init());
    ……
	MDF_ERROR_ASSERT(mdf_event_loop_init(event_loop_cb));
}
```

包含以下代码：

 - `mdf_event_loop_init(event_loop_cb)`：事件处理回调函数初始化，所有的事件都将发送到这个函数中
 - light_driver_led_init() : LED IO 初始化
 - buzzer_driver_init() : 蜂鸣器 IO初始化
 - button_driver_init() : 按键 IO 初始化

按键按下、按键释放、按键长按释放的事件处理代码：

任意按键按下，蜂鸣器“滴”一声

```
static mdf_err_t event_loop_cb(mdf_event_loop_t event, void *ctx)
{
    ……
    ……
    ……
		case MDF_EVENT_BUTTON_KEY_PUSH:{
			bool bTriggerHandle = false;
			int key_index = (int)ctx;
			MDF_LOGI("EVENT: %d push\r\n", key_index);
			buzzer_driver_start(1,100);
			bTriggerHandle = true;
			if(bTriggerHandle) {
				/**
				 * @brief Trigger handler
				 */
				ret = mlink_trigger_handle(MLINK_COMMUNICATE_MESH);
				MDF_ERROR_BREAK(ret != MDF_OK, "<%s> mlink_trigger_handle", mdf_err_to_name(ret));
			}
			s_button_key_push_flag = true;
		}
		break;
		
		case MDF_EVENT_BUTTON_KEY_RELEASE:
			s_button_key_push_flag = false;
		break;

		case MDF_EVENT_BUTTON_KEY_LONG_PRESS_PUSH:{
			int key_index = (int)ctx;
			MDF_LOGI("EVENT: %d long press\r\n", key_index);
			buzzer_driver_start(1,100);
			switch(key_index){
				case BUTTON_E_KEY_SET:
				case BUTTON_E_KEY_SET2:
					// blink led				
					light_driver_led_blink_start(0, 0, 255, 2000); 
				break;
			
				default:
					break;
			}
		}
		break;
		
		case MDF_EVENT_BUTTON_KEY_LONG_PRESS_RELEASE: {
			int key_index = (int)ctx;
			MDF_LOGI("EVENT: %d long release\r\n", key_index);
			switch(key_index){
				case BUTTON_E_KEY_SET:
				case BUTTON_E_KEY_SET2:
					// stop blink led
					light_driver_led_blink_stop();
					// send reset system event
					mdf_event_loop_send(MDF_EVENT_MLINK_SYSTEM_RESET, (void *)NULL);
				break;
			
				default:
					break;
			}
		}
		break;
    ……
    ……
    ……	
}
```

* buzzer_driver_start(1,100) ：蜂鸣器“滴”一声
