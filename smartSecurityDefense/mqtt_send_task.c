#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "sys_config.h"
#include "cJSON.h"
#include "cmsis_os2.h"
#include "hal_bsp_mqtt.h"
#include "oled_show_log.h"
#include "mqtt_send_task.h"

void publish_sensor_data(msg_data_t *msg);
#define MQTT_TOPIC_MAX 128
char publish_topic[MQTT_TOPIC_MAX] = {0};

/**
 * @brief MQTT  发布消息任务
 */
void mqtt_send_task(void)
{
    while (1) {
        // 发布消息
        publish_sensor_data(&sys_msg_data);
        sleep(1); // 1s
    }
}

/**
 * @brief  发布传感器的信息
 * @note
 * @param  msg:
 * @retval None
 */
void publish_sensor_data(msg_data_t *msg)
{
    // 拼接Topic
    memset_s(publish_topic, MQTT_TOPIC_MAX, 0, MQTT_TOPIC_MAX);
    if (sprintf_s(publish_topic, MQTT_TOPIC_MAX, MQTT_TOPIC_PUB_PROPERTIES, DEVICE_ID) > 0) {
        // 组装JSON数据
        cJSON *json_root = cJSON_CreateObject();
        cJSON *json_services = cJSON_CreateArray();
        cJSON *json_services_root = cJSON_CreateObject();
        cJSON *json_properties = cJSON_CreateObject();

        cJSON_AddItemToObject(json_root, "services", json_services);
        cJSON_AddItemToArray(json_services, json_services_root);
        cJSON_AddStringToObject(json_services_root, "service_id", "base");
        cJSON_AddItemToObject(json_services_root, "properties", json_properties);
        cJSON_AddStringToObject(json_properties, "isBody", (msg->is_Body) ? "ON" : "OFF");
        cJSON_AddStringToObject(json_properties, "autoMode", (msg->nvFlash.smartControl_flag) ? "ON" : "OFF");
        cJSON_AddStringToObject(json_properties, "buzzer", (msg->buzzerStatus) ? "ON" : "OFF");
        cJSON_AddStringToObject(json_properties, "fan", (msg->fan) ? "ON" : "OFF");
        cJSON_AddNumberToObject(json_properties, "humi_val", msg->humi_val);
        cJSON_AddNumberToObject(json_properties, "temp_val", msg->temp_val);
        char *payload = cJSON_PrintUnformatted(json_root);
        // 发布消息
        MQTTClient_pub(publish_topic, payload, strlen((char *)payload));
        cJSON_Delete(json_root);
        json_root = json_services = json_services_root = json_properties = NULL;
    }
}
