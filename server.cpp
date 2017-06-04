#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

#include "receive.cpp"
#include "date.time.h"

#define PORT "3500"  // the port users will be connecting to



using namespace std;


int main() {
    struct sockaddr_storage client_addr;
    socklen_t addr_size;
    struct addrinfo hints, *serveraddrinfo, *p;
    int status, sockfd, new_fd, numbBytes;


    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_protocol = 0;

    if ((status = getaddrinfo(NULL, PORT, &hints, &serveraddrinfo)) != 0) {
        cout << "error filling the addrinfo struct" << endl;
        return -1;
    }
    for(p = serveraddrinfo; p != NULL; p = p->ai_next) {

        if ((sockfd = socket(serveraddrinfo->ai_family, serveraddrinfo->ai_socktype, serveraddrinfo->ai_protocol)) <
            0) {
            cout << "Error creating a socket on server: " << strerror(errno) << endl;
            continue;
        }
        if (bind(sockfd, serveraddrinfo->ai_addr, serveraddrinfo->ai_addrlen) < 0) {
            close(sockfd);
            cout << "Error binding a socket to an address: " << strerror(errno) << endl;
            continue;
        }
        break;
    }
    freeaddrinfo(serveraddrinfo); // all done with this structure
    if (p == NULL)  //check binding
    {
        cout << "Failed to bind server" << endl;
        exit(1);
    }

    if (listen(sockfd, 5) < 0)
    {
        cout << "error listening" << endl;
        exit(1);
    }

    cout << "Server: waiting for connections..." << endl;

    while(1){
        addr_size = sizeof(client_addr);
        new_fd = accept(sockfd, (struct sockaddr *)&client_addr, &addr_size); //new socket on which connection will be established

        if (new_fd == -1)
        {
            cout << "Connection failed" << endl;
            continue;
        }
        cout << "Connection established on port " << PORT << endl;
        if (!fork()) {
            char buff[1];
            close(sockfd);
            if ((numbBytes = recv(new_fd, buff, 1, 0)) == -1) {
                cout << "Error receiving" << endl;
                exit(1);
            }

            //cout << "numb of bytes received " <<  numbBytes << endl;

                buff[numbBytes] = '\0';
                switch (buff[0]) {
                    case 'd': {
                        string s(getDate());
                        if (send(new_fd, getDate(), 10, 0) == -1) {
                            cout << "Error sending" << endl;
                        }
                        break;
                    }
                    case 't': {
                        if (send(new_fd, getTime(), 8, 0) == -1) {
                            cout << "Error sending" << endl;
                        }
                        break;
                    }
                    case 'h': {
                        if (send(new_fd, "Warm greetings from THE SERVER", 30, 0) == -1) {
                            cout << "Error sending" << endl;
                        }
                        break;
                    }
                    case 'm': {
                        short buffForLen = 0;
                        short *p = &buffForLen;
                        receiveNBytes(new_fd, p, 2);
                        // cout << "received len of messg: " << buffForLen<<endl;

                        char buffForMsg[buffForLen];
                        char *chrp = &buffForMsg[0];
                        receiveNBytes(new_fd, chrp, buffForLen);
                        string received(buffForMsg);
                        cout << "received messg: " << received << endl;

                        if (send(new_fd, &buffForMsg, buffForLen, 0) == -1) { //send message back
                            cout << "Error sending" << endl;
                        }
                        break;
                    }
                    default:
                        if (send(new_fd, "What do you want from THE SERVER?", 33, 0) == -1) {
                            cout << "Error sending" << endl;
                        }
                }
            close(new_fd);
            exit(0);

        }
        close(new_fd);
    }

    return 0;
}

