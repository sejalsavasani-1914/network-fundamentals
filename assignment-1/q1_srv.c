/* Write a udp client server program,client writing messages to server program and server
return back the same toggled msg to client */

#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>
#include<stdlib.h>

int main()
{
    int sockfd,n,retval;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;
    char buff[10000];

    sockfd = socket(AF_INET, SOCK_DGRAM,0);
    if(sockfd < 0)
    {
        perror("sock:");
        exit(1);
    }
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(8000);

    retval = bind(sockfd,(struct sockaddr *) &servaddr,sizeof(servaddr));
    if(retval < 0)
    {
        perror("bind:");
        exit(2);
    }
    printf("socket bound to port 8000\n");
    clilen = sizeof(struct sockaddr_in);
    while(1)
    {
        printf("before recvfrom\n");
        n = recvfrom(sockfd,buff,10000,0,(struct sockaddr *) &cliaddr, &clilen);
        printf("recv'd %d bytes\n",n);
        printf("message from client = %s\n",buff);
    }
    return 0;
}
