#ifndef CLIENT_H
#define CLIENT_H

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

typedef struct {
    __uint8_t user_id;
} ConnectPacket;

ConnectPacket connect_client(int);

#endif //CLIENT_H