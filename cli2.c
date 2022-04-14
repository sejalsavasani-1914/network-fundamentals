#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>
#include<stdlib.h>

main()
{
    char buff[200];
    int n;
    char *serv_ip = "127.0.0.1";
    int sockfd,ret_val;
    struct sockaddr_in servaddr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8000);
    inet_pton(AF_INET, serv_ip, &servaddr.sin_addr);

    ret_val = connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    if(ret_val < 0)
    {
        perror("connect:");
        exit(1);
    }
    printf("enter the data that you want to send to the server\n");
    gets(buff);
    write(sockfd,buff,strlen(buff));
    n = read(sockfd,buff,200);
    buff[n]='\0';
    printf("rec'd %s from server\n",buff);
    getchar();
    close(sockfd);
}