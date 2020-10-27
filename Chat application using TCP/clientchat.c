//This is a simple chat application between client and server 
//Client sends message to server and server reponds back

#include<stdio.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>


int main(){
        int sockfd;
        struct sockaddr_in servaddr;
        char buff[1000];
        sockfd=socket(AF_INET,SOCK_STREAM,0);

        //we use port number 3500 to connect with server
        servaddr.sin_family=AF_INET;
        servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
        servaddr.sin_port=htons(3500);

        connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

        //Enter "Exit" to exit the communication
        while(1){
                bzero(buff,sizeof(buff));
                fgets(buff,1000,stdin);
                write(sockfd,buff,sizeof(buff));
                if(!strncmp(buff,"Exit",4)){
                        break;
                }
                bzero(buff,sizeof(buff));
                read(sockfd,buff,sizeof(buff));
                printf("%s",buff);
        }

        close(sockfd);
        return 0;
}
