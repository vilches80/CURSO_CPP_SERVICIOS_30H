#include <iostream>
#include <amqp.h>
#include <amqp_tcp_socket.h>

int productor() {
    const char* hostname = "localhost";
    int port = 5672;

    amqp_connection_state_t conn = amqp_new_connection();
    amqp_socket_t* socket = amqp_tcp_socket_new(conn);

    if (!socket) {
        std::cerr << "Error creando socket\n";
        return 1;
    }

    int status = amqp_socket_open(socket, hostname, port);
    if (status != AMQP_STATUS_OK) {
        std::cerr << "Error abriendo socket: " << amqp_error_string2(status) << "\n";
        return 1;
    }

    amqp_rpc_reply_t login = amqp_login(conn, "/", 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, "guest", "guest");
    if (login.reply_type != AMQP_RESPONSE_NORMAL) {
        std::cerr << "Error en login\n";
        return 1;
    }

    amqp_channel_open(conn, 1);
    amqp_rpc_reply_t channel_reply = amqp_get_rpc_reply(conn);
    if (channel_reply.reply_type != AMQP_RESPONSE_NORMAL) {
        std::cerr << "Error abriendo canal\n";
        return 1;
    }

    amqp_bytes_t queue = amqp_cstring_bytes("test_queue");
    amqp_queue_declare(conn, 1, queue, 0, 0, 0, 1, amqp_empty_table);
    amqp_get_rpc_reply(conn);

    amqp_bytes_t message = amqp_cstring_bytes("¡Hola desde C++!");
    amqp_basic_publish(conn, 1, amqp_empty_bytes, queue, 0, 0, nullptr, message);

    std::cout << "Mensaje enviado correctamente\n";

    amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS);
    amqp_connection_close(conn, AMQP_REPLY_SUCCESS);
    amqp_destroy_connection(conn);
}

int consumidor() {
    const char* hostname = "localhost";
    int port = 5672;

    amqp_connection_state_t conn = amqp_new_connection();
    amqp_socket_t* socket = amqp_tcp_socket_new(conn);

    if (!socket) {
        std::cerr << "Error creando socket\n";
        return 1;
    }

    int status = amqp_socket_open(socket, hostname, port);
    if (status != AMQP_STATUS_OK) {
        std::cerr << "Error abriendo socket: " << amqp_error_string2(status) << "\n";
        return 1;
    }

    amqp_rpc_reply_t login = amqp_login(conn, "/", 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, "guest", "guest");
    if (login.reply_type != AMQP_RESPONSE_NORMAL) {
        std::cerr << "Error en login\n";
        return 1;
    }

    amqp_channel_open(conn, 1);
    amqp_rpc_reply_t channel_reply = amqp_get_rpc_reply(conn);
    if (channel_reply.reply_type != AMQP_RESPONSE_NORMAL) {
        std::cerr << "Error abriendo canal\n";
        return 1;
    }

    amqp_bytes_t queue = amqp_cstring_bytes("test_queue");
    amqp_queue_declare(conn, 1, queue, 0, 0, 0, 1, amqp_empty_table);
    amqp_get_rpc_reply(conn);

    amqp_basic_consume(conn, 1, queue, amqp_empty_bytes, 0, 1, 0, amqp_empty_table);
    amqp_get_rpc_reply(conn);

    std::cout << "Esperando mensajes...\n";

    while (true) {
        amqp_envelope_t envelope;
        amqp_maybe_release_buffers(conn);
        amqp_rpc_reply_t res = amqp_consume_message(conn, &envelope, nullptr, 0);

        if (res.reply_type != AMQP_RESPONSE_NORMAL) {
            std::cerr << "Error recibiendo mensaje\n";
            break;
        }

        std::string body(reinterpret_cast<char*>(envelope.message.body.bytes), envelope.message.body.len);
        std::cout << "Mensaje recibido: " << body << "\n";

        amqp_destroy_envelope(&envelope);
    }

    amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS);
    amqp_connection_close(conn, AMQP_REPLY_SUCCESS);
    amqp_destroy_connection(conn);

    return 0;
}

int main(){
    //productor();
    consumidor();
    return 0;
}
