#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>
#include<stdlib.h>

#define PORT 8000
#define SERVER_IP "127.0.0.1"
#define MAXSZ 100

int main()
{
    int sockfd;

    struct sockaddr_in servaddr;

    int n;
    char msg1[MAXSZ];
    char msg2[MAXSZ];

    sockfd = socket(AF_INET,SOCK_STREAM,0);
    memset(&servaddr,0,sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    servaddr.sin_port = htons(PORT);

    connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

    while(1)
    {
        printf("enter message to send to server : \n");
        fgets(msg1,MAXSZ,stdin);
        if(msg1[0]=='#')
            break;

        n = strlen(msg1)+1;
        send(sockfd,msg1,n,0);

        n = recv(sockfd,msg2,MAXSZ,0);

        printf("receive message from server :: %s\n",msg2);
    }
    return 0;
}