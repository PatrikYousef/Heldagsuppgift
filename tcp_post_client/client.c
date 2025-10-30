#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

int connect_to_server(const char *hostname, int port) {
    int sockfd;
    struct hostent *server;
    struct sockaddr_in server_addr;

    server = gethostbyname(hostname);
    if (server == NULL) {
        fprintf(stderr, "Fel: kunde inte hitta värd %s\n", hostname);
        return -1;
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Fel vid skapande av socket");
        return -1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    memcpy(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length);

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Fel vid anslutning");
        close(sockfd);
        return -1;
    }

    return sockfd;
}

int send_post_request(int sockfd, const char *hostname, const char *json_body) {
    char request[512];
    snprintf(request, sizeof(request),
             "POST /post HTTP/1.1\r\n"
             "Host: %s\r\n"
             "Content-Type: application/json\r\n"
             "Content-Length: %zu\r\n"
             "Connection: close\r\n"
             "\r\n"
             "%s",
             hostname, strlen(json_body), json_body);

    ssize_t sent = send(sockfd, request, strlen(request), 0);
    if (sent < 0) {
        perror("Fel vid skickning");
        return -1;
    }

    printf("Skickad förfrågan:\n%s\n", request);
    return 0;
}

void receive_response(int sockfd, response_handler_t handler) {
    char buffer[1024];
    ssize_t bytes;
    while ((bytes = recv(sockfd, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes] = '\0';
        handler(buffer); 
    }
}
