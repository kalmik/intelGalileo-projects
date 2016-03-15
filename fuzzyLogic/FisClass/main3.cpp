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
#include "fis.h"

using namespace std;

#define MSG_SIZE 30

//The library automatically reconnects to broker

string hst = "192.168.0.2";
const char *host = hst.c_str();
int port = 1883;
string vhost = "yourvhost";
string usn = "username";
string vhusn = vhost + ":" + usn;
const char *username = vhusn.c_str();
string pwd = "password";
const char *password = pwd.c_str();

string tpcTX = "test/fuzzytx";
const char *topicTX = tpcTX.c_str();
string tpcRX = "test/fuzzyrx";
const char *topicRX = tpcRX.c_str();

int keepalive = 60;
bool clean_session = true;
struct mosquitto *mosq = NULL;
char payload[MSG_SIZE];

pthread_t THREADS[2];

/**
 * This method is the callback on connecting broker. 
 * @It is event-driven. You don't call it in your code.
 * @It subscribes the specific topic.
 * @There're other callback functions provided by this library.
 */
void onConnect(struct mosquitto *mosq, void *userdata, int result) {
    if (!result) {
        try {
            mosquitto_subscribe(mosq, NULL, topicRX, 1); 
        } catch (exception& e) {
            printf("Error: Failed to subscribe\n%s\n", e.what());
        }
    } else {
        printf("Error: Failed to connect\n");
    }
}

/**
 * This method is the callback on receiving messages. 
 * @It is event-driven. You don't call it in your code.
 * @It prints the message topic and payload on console.
 * @There're other callback functions provided by this library.
 */
void onMessage(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message) {
    if(message->payloadlen) {
        printf("Topic: %s, Message: %s\n", (char*)message->topic, (char*)message->payload);
    } else {
        printf("Topic: %s, Message: (null)\n", message->topic);
    }
    fflush(stdout);
}

void *listenner(void *param)
{
	mosquitto_connect_callback_set(mosq, onConnect);
    mosquitto_message_callback_set(mosq, onMessage);
  	while(!mosquitto_loop_forever(mosq, 0, 1));
}

void sendPayload(){
	mosquitto_publish(mosq, NULL, topicTX, MSG_SIZE, payload, 1, false);
}

void *fuzzy(void *param) {
	Fis* f = new Fis("b7matlab.fis");

	double* fuzzyOutput = (double*)malloc(sizeof(double)*f->numOutputs);
	double* in = (double*)malloc(sizeof(double)*f->numInputs);

	

	in[0] = 0.5;
	in[1] = 0.5;

	fuzzyOutput = f->Evalfis(in);

	while(1) {
		fuzzyOutput = f->Evalfis(in);

		sprintf(payload, "{\"a\": %f}\0", fuzzyOutput[0]);
		printf("%s\n", payload);
        
        sendPayload();

        sleep(1);
	}
}

int main(){

    //create producer and connect to broker
    mosquitto_lib_init();
    mosq = mosquitto_new(NULL, clean_session, NULL);
    mosquitto_username_pw_set(mosq, username, password);
    if(mosquitto_connect(mosq, host, port, keepalive)) {
        printf("Error: Failed to connect\n");
        return 1;
    }
    //usually start loop right after connecting
    mosquitto_loop_start(mosq);

    printf("Creating Trheads...\n");
	pthread_create(&(THREADS[0]), NULL, fuzzy, NULL);
	pthread_create(&(THREADS[1]), NULL, listenner, NULL);

	printf("Joing Threads\n");
	pthread_join(THREADS[0], NULL);
	pthread_join(THREADS[1], NULL);

	return 0;
}

