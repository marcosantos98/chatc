#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
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
        printf("Success socket created! %d \n", sock);

    const struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(6969),
        .sin_addr.s_addr = INADDR_ANY,
    };

    int conn = connect(sock, (const struct sockaddr *)&addr, sizeof(addr));
    if (conn == -1)
        print_errono_exit("Connect");
    else
        printf("Success socket connection!\n");
}