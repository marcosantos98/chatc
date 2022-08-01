#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define TRY(som, step, msg, _exit) __extension__({                     \
    int result = 0;                                                    \
    do                                                                 \
    {                                                                  \
        result = som;                                                  \
        if (result == -1)                                              \
        {                                                              \
            fprintf(stderr, "ERROR[%s]: %s\n", step, strerror(errno)); \
            if (_exit)                                                 \
                exit(1);                                               \
        }                                                              \
        else                                                           \
            printf("[%s] %s\n", step, msg);                            \
    } while (0);                                                       \
    result;                                                            \
})

void start_server(int socket_port)
{
    int sock = TRY(socket(AF_INET, SOCK_STREAM, 0), "Create", "Socket created.", true);

    const struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(socket_port),
        .sin_addr.s_addr = INADDR_ANY,
    };

    TRY(bind(sock, (const struct sockaddr *)&addr, sizeof(addr)), "Bind", "Socket binded.", true);
    TRY(listen(sock, 80), "Listen", "Listenning...", false);

    printf("Listening on port %d\n", addr.sin_port);

    struct sockaddr_in client_socket = {0};
    int client_socket_sz = sizeof(client_socket);

    int client_sock = TRY(accept(sock, (struct sockaddr *)&client_socket, (socklen_t *)&client_socket_sz), "Client Connect", "Client Connected", false);

    char buf[1028]= {0};

    int read_bytes = TRY(read(client_sock, &buf, 1028), "Read", "Success read", false);
    
    printf("Read %d of bytes with: %s\n", read_bytes, buf);

    const char* handshake = "Hi Client";
    int send_bytes = TRY(send(client_sock, handshake, strlen(handshake), 0), "Send", "Success Send", false);

    printf("Send %d bytes\n", send_bytes);

    TRY(shutdown(sock, SHUT_RDWR), "Shutdown", "Success shutdown.", false);

    close(sock);
}

int main(void)
{

    start_server(6969);
}