// sync_subscribe.cpp
//
// This is a Paho MQTT C++ client, sample application.
//
// This application is an MQTT subscriber using the C++ synchronous client
// interface, but employs callbacks to receive messages.
//
// The sample demonstrates:
//  - Connecting to an MQTT server/broker.
//  - Subscribing to a topic
//  - Receiving messages through the callback API
//  - Automatic reconnects.
//  - Using a persistent (non-clean) session
//

/*******************************************************************************
 * Copyright (c) 2017 Frank Pagliughi <fpagliughi@mindspring.com>
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Frank Pagliughi - initial implementation and documentation
 *******************************************************************************/

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cctype>
#include <thread>
#include <chrono>
#include "mqtt/client.h"

const std::string SERVER_ADDRESS("eu.thethings.network:1883");
const std::string CLIENT_ID("sync_subcribe_cpp");
const std::string TOPIC("es_sensor_network/devices/es_rasp_sn/events/down/scheduled");
const std::string USERNAME("es_sensor_network");
const std::string PASSWORD("ttn-account-v2.NC7lBuZ1_ztXF1cSXrJnswIX4kDSCBJjQTWF_xIjce4");

const int QOS = 1;

/////////////////////////////////////////////////////////////////////////////

/**
 * Local callback & listener class for use with the client connection.
 * This is primarily intended to receive messages, but it will also monitor
 * the connection to the broker. If the connection is lost, it will attempt
 * to restore the connection and re-subscribe to the topic.
 */
class callback : public virtual mqtt::callback
{
	mqtt::client& cli_;

	void connected(const std::string& cause) override {
		std::cout << "\nConnected: " << cause << std::endl;
		//std::cout << "Subscribing to : " << TOPIC << std::endl;
		//cli_.subscribe(TOPIC, QOS);
		//std::cout << "Subscribe ok" << std::endl;
		//std::cout << std::endl;
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

/////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	mqtt::connect_options connOpts;
	connOpts.set_keep_alive_interval(20);
	connOpts.set_clean_session(false);
	connOpts.set_automatic_reconnect(true);
	connOpts.set_user_name(USERNAME);
	connOpts.set_password(PASSWORD);


	mqtt::client cli(SERVER_ADDRESS, CLIENT_ID);

	callback cb(cli);
	cli.set_callback(cb);

	// Start the connection.

	try {
		std::cout << "Connecting to the MQTT server..." << std::flush;
		cli.connect(connOpts);
		std::cout << "Subsribing to topic : " << TOPIC << std::endl;
		cli.subscribe(TOPIC, QOS);
		std::cout << "OK" << std::endl;
	}
	catch (const mqtt::exception& exc) {
		std::cerr << "\nERROR: Unable to connect to MQTT server: '"
			<< SERVER_ADDRESS << "'" << std::endl;
		return 1;
	}

	// Just block till user tells us to quit.

	while (std::tolower(std::cin.get()) != 'q')
		;

	// Disconnect

	try {
		std::cout << "\nDisconnecting from the MQTT server..." << std::flush;
		cli.disconnect();
		std::cout << "OK" << std::endl;
	}
	catch (const mqtt::exception& exc) {
		std::cerr << exc.what() << std::endl;
		return 1;
	}

 	return 0;
}
