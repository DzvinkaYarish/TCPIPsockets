//
// Created by dzvinka on 04.06.17.
//

#ifndef SOCKETS_RECEIVE_H_H
#define SOCKETS_RECEIVE_H_H

#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
#include <string.h>

void receiveNBytes(int sockfd, void *msgp, int lenInBytes);



#endif //SOCKETS_RECEIVE_H_H
