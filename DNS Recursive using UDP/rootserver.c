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

        bzero(buff,1000);
        recvfrom(sockfd,(char *)buff,1000,0,(struct sockaddr*)&cliaddr,&cl);
        printf("Client : %s",buff);
        int newfd;
        struct sockaddr_in tdsaddr;


        newfd=socket(AF_INET,SOCK_DGRAM,0);


        tdsaddr.sin_family=AF_INET;
        tdsaddr.sin_addr.s_addr=INADDR_ANY;
        tdsaddr.sin_port=htons(4000);

        char *file1="com.txt",*file2="edu.txt";





        sendto(newfd,(char *)file1,sizeof(file1),0,(struct sockaddr*)&tdsaddr,sizeof(servaddr));
        sendto(newfd,(char *)file2,sizeof(file2),0,(struct sockaddr*)&tdsaddr,sizeof(servaddr));
        sendto(newfd,(char *)buff,1000,0,(struct sockaddr*)&tdsaddr,sizeof(servaddr));
        bzero(buff,1000);
        recvfrom(newfd,(char *)buff,1000,0,NULL,NULL);
        printf("TD Server : %s",buff);
        sendto(sockfd,(char *)buff,1000,0,(struct sockaddr*)&cliaddr,cl);

        close(newfd);
        close(sockfd);
        return 0;
}
