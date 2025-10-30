#include "client.h"
#include "handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char **argv) {

    const char *hostname = "httpbin.org";
    const char *device_uuid = "123e4567-e89b-12d3-a456-426614174000";

    char time_str[64];
    time_t now = time(NULL);
    strftime(time_str, sizeof(time_str), "%Y-%m-%dT%H:%M:%S", localtime(&now));
    double temperature = 22.7;

    // Bygg JSON-delen
    char json_body[256];
    snprintf(json_body, sizeof(json_body),
             "{\n"
             "    \"device\": \"%s\",\n"
             "    \"time\": \"%s\",\n"
             "    \"temperature\": \"%.1f°C\"\n"
             "}",
             device_uuid, time_str, temperature);

    // Bygg hela POST-förfrågan
    printf("POST / HTTP/1.1\n");
    printf("Host: %s\n", hostname);
    printf("%s\n", json_body);

    return 0;
}
