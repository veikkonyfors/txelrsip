/*
 * main.c
 *
 *  Created on: Dec 4, 2025
 *      Author: pappa
 */

#include <stdio.h>
#include "sender.h"
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	int opt;
	char *ip = "127.0.0.1";
	int port = 22777;

	while ((opt = getopt(argc, argv, "i:p:")) != -1) {
			switch (opt) {
				case 'i':
					ip = optarg;
					break;
				case 'p':
					port = atoi(optarg);
					break;
				default:
					fprintf(stderr, "Usage: %s [-i IP] [-p port]\n", argv[0]);
					exit(EXIT_FAILURE);
			}
		}

    printf("Call sender on %s:%d\n", ip, port);
    sender(ip, port);

    return 0;
}
