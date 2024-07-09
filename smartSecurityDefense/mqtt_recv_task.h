#ifndef MQTT_RECV_TASK_H
#define MQTT_RECV_TASK_H

#include "cmsis_os2.h"

int8_t mqttClient_sub_callback(unsigned char *topic, unsigned char *payload);
void mqtt_recv_task(void);

#endif
