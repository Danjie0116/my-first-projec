/*
 * Copyright (c) 2023 Beijing HuaQing YuanJian Education Technology Co., Ltd
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SYS_CONFIG_H
#define SYS_CONFIG_H

#include "cmsis_os2.h"
#include "hal_bsp_structAll.h"


// DeviceSecret fs12345678   fs123456
// 设备ID
#define DEVICE_ID       "667e7f816bc31504f070fd35_mqtt"
// MQTT客户端ID
#define MQTT_CLIENT_ID "667e7f816bc31504f070fd35_mqtt_0_0_2024070317"
// MQTT用户名
#define MQTT_USER_NAME "667e7f816bc31504f070fd35_mqtt"
// MQTT密码
#define MQTT_PASS_WORD "687e42827c268a171cc68f695e7a6dcdf5e592ba95b315df3ab7da3081f885fd"
// 华为云平台的IP地址
#define SERVER_IP_ADDR "117.78.5.125"
// 华为云平台的IP端口号

#define SERVER_IP_PORT 1883
// 订阅 接收控制命令的主题
#define MQTT_TOPIC_SUB_COMMANDS "$oc/devices/%s/sys/commands/#"
// 发布 成功接收到控制命令后的主题
#define MQTT_TOPIC_PUB_COMMANDS_REQ "$oc/devices/%s/sys/commands/response/request_id=%s"
#define MALLOC_MQTT_TOPIC_PUB_COMMANDS_REQ "$oc/devices//sys/commands/response/request_id="
// 发布 设备属性数据的主题
#define MQTT_TOPIC_PUB_PROPERTIES "$oc/devices/%s/sys/properties/report"
#define MALLOC_MQTT_TOPIC_PUB_PROPERTIES "$oc/devices//sys/properties/report"
#define MQTT_PAYLOAD_PUB "{\"services\":[{\"service_id\":\"base\",\"properties\":\
{\"isBody\":\"%s\",\"autoMode\":\"%s\",\"buzzer\":\"%s\"}}]}"

typedef struct {
    int top;  // 上边距
    int left; // 下边距
    int hight; // 高
    int width; // 宽
} margin_t;   // 边距类型

typedef struct message_data {
    unsigned char buzzerStatus; // 状态
    unsigned char fan;    //风扇
    unsigned char is_Body;      // 有人或没人
    unsigned short psData;      // 接近传感器值
    int  temp_val; 
    int  humi_val; 
    hi_nv_save_sensor_threshold nvFlash;
} msg_data_t;
extern msg_data_t sys_msg_data;

#endif
