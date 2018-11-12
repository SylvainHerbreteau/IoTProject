#include "mqtt.h"
//#include <iostream>

#define CLIENT_ID "SE_THLJ"
#define BROKER_ADDRESS "eu.thethings.network:1883"
#define MQTT_PORT 1883;
#define MQTT_TOPIC "es_sensor_network/devices/es_rasp_sn/up" //ajouter bon topic


int main(int argc, char *argv[])
{
    class mqtt_client *iot_client;
    int rc;

    char client_id[] = CLIENT_ID;
    char host[] = BROKER_ADDRESS;
    int port = MQTT_PORT;

    mosqpp::lib_init();



    if (argc > 1)
        strcpy (host, argv[1]);

    iot_client = new mqtt_client(client_id, host, port);


    while(1)
    {
        rc = iot_client->loop();
        if (rc)
        {
          std::cout << "je suis la" << std::endl;
            iot_client->reconnect();
        }
        else{
            std::cout << "subscribing" << std::endl;
            iot_client->subscribe(NULL, MQTT_TOPIC);
          }
    }

    mosqpp::lib_cleanup();

    return 0;
}
