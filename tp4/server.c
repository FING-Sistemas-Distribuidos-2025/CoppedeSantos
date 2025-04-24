#include <czmq.h>

int main(void) {
    zsock_t *responder = zsock_new(ZMQ_REP);
    if (!responder) {
        printf("Error al crear el socket\n");
        return 1;
    }

    int rc = zsock_bind(responder, "tcp://*:3000");
    if (rc == -1) {
        printf("Error al hacer bind al puerto 3000\n");
        zsock_destroy(&responder);
        return 1;
    }

    printf("Servidor C escuchando en puerto 3000...\n");

    while (1) {
        char *msg = zstr_recv(responder);
        if (!msg)
            break;

        printf("Recibido: %s\n", msg);

        char respuesta[256];
        snprintf(respuesta, sizeof(respuesta), "Respondiendo a %s", msg);
        zstr_send(responder, respuesta);
        printf("Enviado: %s\n", respuesta);

        free(msg);
    }

    zsock_destroy(&responder);
    return 0;
}
