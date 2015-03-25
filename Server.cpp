/*************************************************Server*************************************/
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;

    char sendBuff[1025];
    time_t ticks;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);  //creates an socket in kernel and returns integer socketID
                                                //SOCK_STREAM:the transport layer protocol should have acknowledge techniques i.e TCP
                                                //"0" to let the kernel decide the default protocol to use for this connection - TCP
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));

    serv_addr.sin_family = AF_INET;         //AF_INET:Internet family of IPv4 address
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);       //set port

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); //assign the above server information to the created socket

    listen(listenfd, 10);  //"10" maximum # clients could be queued for this listen socket

    while(1)
    {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);

        ticks = time(NULL);
        snprintf(sendBuff, sizeof(sendBuff), "connected%.24s\r\n", ctime(&ticks)); //assign the current time information to sendBuffer
        write(connfd, sendBuff, strlen(sendBuff)); //send buffer to the connected client
        close(connfd);
        sleep(1);
     }
}
