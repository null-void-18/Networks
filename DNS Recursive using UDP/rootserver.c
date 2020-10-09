//Root DNS code... Sends website extension to TLD and gets the IP address from TLD 

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
        
        //socket creation
        sockfd=socket(AF_INET,SOCK_DGRAM,0);

        //defining the structure of servaddr
        servaddr.sin_family=AF_INET;
        servaddr.sin_addr.s_addr=INADDR_ANY;
        servaddr.sin_port=htons(3000);
        //port number 3000 is used to communicate with client
        
        
        bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

        cl=sizeof(cliaddr);

        bzero(buff,1000);
        recvfrom(sockfd,(char *)buff,1000,0,(struct sockaddr*)&cliaddr,&cl);
        printf("Client : %s",buff);
        int newfd;
        struct sockaddr_in tdsaddr;

        //new socket creation to communicate with TLD server
        newfd=socket(AF_INET,SOCK_DGRAM,0);

        //used port number 4000 to communicate with TLD server
        tdsaddr.sin_family=AF_INET;
        tdsaddr.sin_addr.s_addr=INADDR_ANY;
        tdsaddr.sin_port=htons(4000);
        
        char *file1="com.txt",*file2="edu.txt";

        //send website extension and name to TLD and receive the IP address...
        //after receiving the IP address , send it back to client
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
