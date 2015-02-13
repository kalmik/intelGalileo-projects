#include <stdio.h>
#include <stdlib.h>
#include <libwebsockets.h>
#include "websocket.h"


int main(void)
{
    // server url will be http://localhost:9000
    int port = 9000;
    const char *interface = NULL;
    struct libwebsocket_context *context;
    // we're not using ssl
    const char *cert_path = NULL;
    const char *key_path = NULL;
    // no special options
    int opts = 0;

    // create libwebsocket context representing this server
    context = libwebsocket_create_context(port, interface, protocols,
                                          libwebsocket_internal_extensions,
                                          cert_path, key_path, -1, -1, opts, NULL);

    if (context == NULL)
    {
        fprintf(stderr, "libwebsocket init failed\n");
        return -1;
    }

    printf("starting server...\n");

    // infinite loop, to end this server send SIGTERM. (CTRL+C)
    while (1)
    {
        libwebsocket_service(context, 50);
        // libwebsocket_service will process all waiting events with their
        // callback functions and then wait 50 ms.
        // (this is a single threaded webserver and this will keep our server
        // from generating load while there are not requests to process)
    }

    libwebsocket_context_destroy(context);

    return 0;
}