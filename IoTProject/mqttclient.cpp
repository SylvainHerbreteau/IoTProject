#include "mqttclient.h"

mqttclient::mqttclient(std::string server_addr, std::string client_id, std::string topic, std::string username, std::string passwd) : cli(server_addr, client_id), cb(cli)
{
    SERVER_ADDRESS = server_addr;
    CLIENT_ID = client_id;
    TOPIC = topic;
    USERNAME = username;
    PASSWORD = passwd;
    connOpts.set_keep_alive_interval(20);
    connOpts.set_clean_session(false);
    connOpts.set_automatic_reconnect(true);
    connOpts.set_user_name(USERNAME);
    connOpts.set_password(PASSWORD);

    cli.set_callback(cb);

    std::cout << "MQTT client created " << std::endl;

}

void mqttclient::connect(){
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
    }
}

void mqttclient::disconnect(){
    try {
        std::cout << "\nDisconnecting from the MQTT server..." << std::flush;
        cli.disconnect();
        std::cout << "OK" << std::endl;
    }
    catch (const mqtt::exception& exc) {
        std::cerr << exc.what() << std::endl;
    }
}
