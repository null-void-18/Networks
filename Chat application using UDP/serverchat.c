//Server code

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>


int main(){
        int sockfd;
        struct sockaddr_in servaddr,cliaddr;
        char buff[1000];
        socklen_t cl;

        sockfd=socket(AF_INET,SOCK_DGRAM,0);


        servaddr.sin_family=AF_INET;
        servaddr.sin_addr.s_addr=INADDR_ANY;
        servaddr.sin_port=htons(3000);

        bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

        cl=sizeof(cliaddr);
        while(1){
                bzero(buff,1000);
                recvfrom(sockfd,(char *)buff,1000,0,(struct sockaddr*)&cliaddr,&cl);
                //printing the message received from server
                printf("Client : %s",buff);
                bzero(buff,1000);
                fgets(buff,1000,stdin);
                sendto(sockfd,(char *)buff,1000,0,(struct sockaddr*)&cliaddr,cl);
        }
        close(sockfd);
        return 0;
}
