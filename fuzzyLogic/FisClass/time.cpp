#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <mosquitto.h>
#include <exception>
#include <iostream>
#include <pthread.h>
#include <mraa.h>
#include "timer.h"
#include "fis.h"

using namespace std;

#define MSG_SIZE 200

//The library automatically reconnects to broker

string hst = "10.13.100.18";
const char *host = hst.c_str();
int port = 1883;
string vhost = "yourvhost";
string usn = "username";
string vhusn = vhost + ":" + usn;
const char *username = vhusn.c_str();
string pwd = "password";
const char *password = pwd.c_str();
string tpc_tx = "fuzzy/tx";
const char *topic_tx = tpc_tx.c_str();
string tpc_rx = "fuzzy/rx";
const char *topic_rx = tpc_rx.c_str();



/**
 * This method is the callback on connecting broker.
 * @It is event-driven. You don't call it in your code.
 * @It subscribes the specific topic.
 * @There're other callback functions provided by this library.
 */
 void onConnect(struct mosquitto *mosq, void *userdata, int result) {

}

/**
 * This method is the callback on receiving messages.
 * @It is event-driven. You don't call it in your code.
 * @It prints the message topic and payload on console.
 * @There're other callback functions provided by this library.
 */
 void onMessage(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message) {

}


int main(int argc, char* argv[]){

    int keepalive = 60;
    bool clean_session = true;
    struct mosquitto *mosq = NULL;

    if(argc < 4) {
        printf("Usage %s <fis file> <host> <n itter>\n", argv[0]);
        return -1;

    }

    hst = argv[2];
    host = hst.c_str();


    //create producer and connect to broker
    mosquitto_lib_init();
    mosq = mosquitto_new(NULL, clean_session, NULL);
    mosquitto_username_pw_set(mosq, username, password);
    mosquitto_connect_callback_set(mosq, onConnect);
    mosquitto_message_callback_set(mosq, onMessage);
    if(mosquitto_connect(mosq, host, port, keepalive)) {
        printf("Error: Failed to connect\n");
        return 1;
    }
    //usually start loop right after connecting
    mosquitto_loop_start(mosq);



    Fis* f = new Fis(argv[1]);


    double* out = (double*)malloc(sizeof(double)*f->numOutputs);
    double* in = (double*)malloc(sizeof(double)*f->numInputs);

    char payload[MSG_SIZE];

    srand(time(NULL));

    int ledState = 1;
    mraa_gpio_context gpio;
    gpio = mraa_gpio_init(7);
    mraa_gpio_dir(gpio, MRAA_GPIO_OUT);

    mraa_gpio_write(gpio, ledState);

    double start, finish, elapsed;

    printf("t = [\n");

    int iter = 0;
    int maxIter = atoi(argv[3]);

    while(iter++ < maxIter) {
        GET_TIME(start);
        in[0] = (rand()%1001/500.0) - 1;
        in[1] = (rand()%1001/500.0) - 1;
        out = f->Evalfis(in);

        sprintf(payload, "{\"input1\": %f, \"input2\": %f, \"output\": %f}\0", in[0], in[1], out[0]);

        #ifdef PUBLISH
        try {
            mosquitto_publish(mosq, NULL, topic_tx, MSG_SIZE, payload, 0, false);
        } catch(exception& e) {
            printf("Error: Failed to publish message\n%s\n", e.what());
            return 1;
        }
        #endif
        GET_TIME(finish);
        elapsed = finish - start;
        printf("%f \n", elapsed);

    }
    printf("];\n");

    return 0;
}

