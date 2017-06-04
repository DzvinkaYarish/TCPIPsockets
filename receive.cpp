//
// Created by dzvinka on 04.06.17.
//

#include "receive.h"

void receiveNBytes(int sockfd, void *msgp, int lenInBytes)
{
    //char buffForMsg[buffForLen];
    //char *chrp = &buff[0];
    int numbBytesF = 0, numbBytes = 0;
    while(numbBytesF != lenInBytes) {
        if ((numbBytes = recv(sockfd, msgp, lenInBytes, 0)) == -1) { //recv len of a message
            std::cout << "Error receiving" << std::endl;
            break;
        }
        numbBytesF += numbBytes;
        msgp += numbBytes;
    }
    std::cout << lenInBytes << " bytes received" << std::endl;
    //return buff;
}



