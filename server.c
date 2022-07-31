#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

void print_errono_exit(const char *step)
{
    fprintf(stderr, "ERROR: %s [%s]\n", strerror(errno), step);
    exit(1);
}

void print_errono(const char *step)
{
    fprintf(stderr, "ERROR: %s [%s]\n", strerror(errno), step);
}

int main(void)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        print_errono_exit("Create");
    else
        printf("Success socket connection! %d \n", sock);

    const struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(6969),
        .sin_addr.s_addr = INADDR_ANY,
    };

    int sockbind = bind(sock, (const struct sockaddr *)&addr, sizeof(addr));
    if (sockbind == -1)
        print_errono_exit("Bind");
    else
        printf("Success socket bind connection!\n");

    int listens = listen(sock, 80);
    if (listens == -1)
    {
        print_errono("Listen");
    }
    else
    {
        printf("Listening on port %d\n", addr.sin_port);
        struct sockaddr_in tmp = {0};
        int tmp_size = sizeof(tmp);
        int next = accept(sock, (struct sockaddr*)&tmp, (socklen_t *)&tmp_size);
        if (next == -1)
        {
            print_errono("Accept");
        }
        else
        {
            printf("Client connected! %d\n", tmp.sin_port);
        }
    }

    int shutdown_ret = shutdown(sock, SHUT_RDWR);
    if (shutdown_ret == -1)
        print_errono("Shutdown");
    else
        printf("Success closed socket. %d\n", shutdown_ret);

    close(sock);
}