#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "client.h"

ConnectPacket connect_client(int port)
{
    const struct sockaddr_in server = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr.s_addr = INADDR_ANY,
    };

    int client = TRY(socket(AF_INET, SOCK_STREAM, 0), "Create", "Success create", true);
    int client_sock = TRY(connect(client, (struct sockaddr *)&server, sizeof(server)), "Connect", "Success connect", true);

    const char *handshake = "Hi Server";
    int send_bytes = TRY(send(client, handshake, strlen(handshake), 0), "Send", "Success Send", false);

    char buf[1028] = {0};

    int read_bytes = TRY(read(client, &buf, 1028), "Read", "Success read", false);
    
    printf("Read %d of bytes with: %s\n", read_bytes, buf);
    
    close(client);

    return (ConnectPacket){0};
}