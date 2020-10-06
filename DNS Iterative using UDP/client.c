//Working code to implement DNS Iterative procedure

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

        sockfd=socket(AF_INET,SOCK_DGRAM,0);


        servaddr.sin_family=AF_INET;
        servaddr.sin_addr.s_addr=INADDR_ANY;
        servaddr.sin_port=htons(3000);


        bzero(buff,1000);
        fgets(buff,sizeof(buff),stdin);

        sendto(sockfd,(char *)buff,strlen(buff)+1,0,(struct sockaddr*)&servaddr,sizeof(servaddr));
        bzero(buff,1000);
        recvfrom(sockfd,(char *)buff,1000,0,NULL,NULL);
        printf("Root DNS IP address : %s",buff);
        bzero(buff,1000);
        recvfrom(sockfd,(char *)buff,1000,0,NULL,NULL);
        printf("\nTLD DNS IP address : %s",buff);
        close(sockfd);
        return 0;
}
