//The code for receiving IP address for a website from top level domain server
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
        struct sockaddr_in servaddr;
        char buff[1000];
        //socket creation
        sockfd=socket(AF_INET,SOCK_DGRAM,0);

        //defining the structure of the servaddr
        servaddr.sin_family=AF_INET;
        servaddr.sin_addr.s_addr=INADDR_ANY;
        servaddr.sin_port=htons(3000);
        //port number 3000 is used to communicate between client and server

        bzero(buff,1000);
        fgets(buff,sizeof(buff),stdin);
        
        //send website name to server and receive address from server
        sendto(sockfd,(char *)buff,sizeof(buff),0,(struct sockaddr*)&servaddr,sizeof(servaddr));
        bzero(buff,1000);
        recvfrom(sockfd,(char *)buff,1000,0,NULL,NULL);
        printf("IP address : %s",buff);
        close(sockfd);
        return 0;
}
