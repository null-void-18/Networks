//Server Code

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>

int main(){
    int sockfd,clifd;
    struct sockaddr_in servaddr,cliaddr;
    char buff[100];
    char z[100];
    sockfd=socket(AF_INET,SOCK_STREAM,0);

    //we use port number 4000 to communicate
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=INADDR_ANY;
    servaddr.sin_port=htons(4000);

    bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    socklen_t len;

    listen(sockfd,5);
    len=sizeof(cliaddr);
    clifd=accept(sockfd,(struct sockaddr*)&cliaddr,&len);

    //Receive from client
    //and send acknowledgement for the received packet
    while(1){
        recv(clifd,buff,100,0);
        if(strncmp(buff,"exit",4)==0){
            break;
        }

        printf("\nReceived packet : %s",buff);

        strcpy(z,"ACK for ");
        strncat(z,buff,strlen(buff));
        send(clifd,z,strlen(z)+1,0);
        bzero(z,sizeof(z));
        bzero(buff,sizeof(buff));
    }

    close(clifd);
    close(sockfd);
}

