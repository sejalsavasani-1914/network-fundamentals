#include<stdio.h>
#include<netdb.h>

int main(int arg ,char *argv[])
{
    struct hostent *lh = gethostbyname("127.0.0.1");
    if(lh)
    {
        puts(lh->h_name);
    }
    else
    {
        herror("gethostbyname");
    }
    return 0;
}