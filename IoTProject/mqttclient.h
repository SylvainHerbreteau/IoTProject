#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include "callback.h"



class mqttclient
{
private :
    mqtt::connect_options connOpts;
    mqtt::client cli;
    callback cb;

    std::string SERVER_ADDRESS; //("eu.thethings.network:1883");
    std::string CLIENT_ID;      //("sync_subcribe_cpp");
    std::string TOPIC;          //("es_sensor_network/devices/es_rasp_sn/events/up");
    std::string USERNAME;       //("es_sensor_network");
    std::string PASSWORD;       //("ttn-account-v2.NC7lBuZ1_ztXF1cSXrJnswIX4kDSCBJjQTWF_xIjce4");
    const int QOS = 1;

public:
    mqttclient(std::string server_addr, std::string client_id, std::string topic, std::string username, std::string passwd);
    void connect();
    void disconnect();
};

#endif // MQTTCLIENT_H
