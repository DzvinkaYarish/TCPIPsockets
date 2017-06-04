//
// Created by dzvinka on 03.06.17.
//

#include <iostream>
#include "receive.cpp"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#define PORT "3500" // the port client will be connecting to
#define MAX_DATA_SIZE 100



using namespace std;

void getServerRespond(int lenInBytes, int sockfd)
{
    char buffForMsg[lenInBytes + 1];
    char *chrp = &buffForMsg[0];
    receiveNBytes(sockfd, chrp, lenInBytes);
    buffForMsg[lenInBytes] = '\0';
    string received(buffForMsg);
    cout << "Server: " << received << endl;
}

int main(int argc, char *argv[])
{
    struct addrinfo hints, *clientaddrinfo, *p;
    int status, sockfd, numBytes;
    //char buff[MAX_DATA_SIZE];

    if(argc < 3)
    {
        cout << "Expecting server ip/command" << endl;
        exit(1);

    }

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;


    if ((status = getaddrinfo(argv[1], PORT, &hints, &clientaddrinfo)) != 0) {
        cout << "error filling the addrinfo struct" << endl;
        return -1;
    }
    for(p = clientaddrinfo; p != NULL; p = p->ai_next) {

        if ((sockfd = socket(clientaddrinfo->ai_family, clientaddrinfo->ai_socktype, clientaddrinfo->ai_protocol)) <
            0) {
            cout << "Can't create a socket on client: " << strerror(errno) << endl;
            continue;
        }
        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            cout <<"Can't connect to a server: " << strerror(errno) << endl;
            continue;
        }

        break;
    }

    if (p == NULL)
    {
        cout << "Failed to connect client" << endl;
        exit(1);
    }
    freeaddrinfo(clientaddrinfo);// all done with this structure
    string comnd(argv[2]);
    comnd = comnd[0];
    if (send(sockfd, argv[2], 1, 0) == -1) {
        cout << "Error sending" << endl;
        exit(1);
    }
    if (strcmp("m", comnd.c_str()) == 0)
    {
        string messg (argv[3]);
        short messglen = messg.size();
        //string messglen = "10";
        if (send(sockfd, &messglen, 2, 0) == -1) {
            cout << "Error sending" << endl;
            exit(1);
        }

        if (send(sockfd, argv[3], messglen, 0) == -1) {
            cout << "Error sending" << endl;
            exit(1);
        }
        getServerRespond(messg.size(), sockfd);
        
        
    } else if (strcmp("d", comnd.c_str()) == 0)
    {
        getServerRespond(10, sockfd);
    } else if (strcmp("t", comnd.c_str()) == 0)
    {
        getServerRespond(8, sockfd);
    } else if (strcmp("h", comnd.c_str()) == 0)
    {
        getServerRespond(30, sockfd);
    } else
    {
        getServerRespond(33, sockfd);
    }

    close(sockfd);

}

