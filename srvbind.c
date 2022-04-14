#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>
#include<stdlib.h>

#define PORT 8000
#define MAXSZ 100

int main()
{
    int sockfd;
    int newsockfd;

    struct sockaddr_in servaddr;
    struct sockaddr_in cliaddr;

    int n;
    int opt=1;
    char msg[MAXSZ];
    int cliaddrlength;

    sockfd = socket(AF_INET,SOCK_STREAM,0);
    memset(&servaddr,0,sizeof(servaddr));

    if(setsockopt(sockfd,SOL_SOCKET , SO_REUSEADDR| SO_REUSEPORT, &opt , sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    bind(sockfd,(struct sockaddr *) &servaddr,sizeof(servaddr));

    listen(sockfd,5);

    while(1)
    {
        printf("*********server waiting for new client connection : ***********\n");
        cliaddrlength = sizeof(cliaddr);
        newsockfd = accept(sockfd,(struct sockaddr *)&cliaddr,&cliaddrlength);

        while(1)
        {
            n = recv(newsockfd,msg,MAXSZ,0);
            if(n==0)
            {
                close(newsockfd);
                break;
            }
            msg[n]=0;
            send(newsockfd,msg,n,0);
            printf("received and set : %s\n",msg);
        }
    }
    return 0;
}