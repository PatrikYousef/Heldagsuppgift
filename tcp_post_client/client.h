#ifndef CLIENT_H
#define CLIENT_H

#include <stddef.h>


typedef void (*response_handler_t)(const char *data);


int connect_to_server(const char *hostname, int port);
int send_post_request(int sockfd, const char *hostname, const char *json_body);
void receive_response(int sockfd, response_handler_t handler);

#endif
