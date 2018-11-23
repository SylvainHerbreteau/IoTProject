#ifndef CALLBACK_H
#define CALLBACK_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cctype>
#include <thread>
#include <chrono>
#include "mqtt/client.h"


class callback : public virtual mqtt::callback
{
    mqtt::client& cli_;

    void connected(const std::string& cause) override {
        std::cout << "\nConnected: " << cause << std::endl;
    }

    // Callback for when the connection is lost.
    // This will initiate the attempt to manually reconnect.
    void connection_lost(const std::string& cause) override {
        std::cout << "\nConnection lost";
        if (!cause.empty())
            std::cout << ": " << cause << std::endl;
        std::cout << std::endl;
    }

    // Callback for when a message arrives.
    void message_arrived(mqtt::const_message_ptr msg) override {
        std::cout << msg->get_topic() << ": " << msg->get_payload_str() << std::endl;
    }

    void delivery_complete(mqtt::delivery_token_ptr token) override {}

public:
    callback(mqtt::client& cli) : cli_(cli) {}
};
#endif // CALLBACK_H
