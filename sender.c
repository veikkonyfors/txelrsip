/*
 * sender.c
 *
 *  Created on: Dec 4, 2025
 *      Author: pappa
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "crsf.h"

#define BUF_SIZE 64

int sender(char *ip, int port) {
    int send_sock;
    struct sockaddr_in serv_addr;

    send_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (send_sock == -1) {
        perror("socket() virhe");
        exit(EXIT_FAILURE);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    serv_addr.sin_port = htons(port);

    crsf_frame_union_t tx_frame;
    crsf_channels_t default_channels = CRSF_CHANNELS_DEFAULT;
    crsf_channels_t channels;

    printf("UDP-sender. up to 5 ints 0-2047 (stop with Ctrl+D):\n");

    char line[128];
    while (fgets(line, sizeof(line), stdin) != NULL) {
    	memcpy(&channels, &default_channels, sizeof(channels));
		sscanf(line, "%hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu",
		&channels.ch1, &channels.ch2, &channels.ch3, &channels.ch4, // Roll, Pitch, Throttle, Yaw
		&channels.ch5, &channels.ch6, &channels.ch7, &channels.ch8, // Disarm, Flight Mode, Buzzer, Blackbox log activation
		&channels.ch9, &channels.ch10, &channels.ch11, &channels.ch12, // VTX Control, Pan, OSD Menu Navigation, RTH activation
		&channels.ch13, &channels.ch14, &channels.ch15, &channels.ch16); // LED Strip Control, Script Control, Trainer Mode, Custom / Reserved

        crsf_create_rc_frame(&tx_frame, &channels);

        sendto(send_sock, &tx_frame, sizeof(tx_frame), 0, // message
               (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    }

    close(send_sock);
    return 0;
}


