#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>



int main(){
        int sockfd,connfd;
        struct sockaddr_in servaddr,cliaddr;
        char buff[1000];
        socklen_t cli;
        if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0){
               printf("ERROR");
        }



        servaddr.sin_family=AF_INET;
        servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
        servaddr.sin_port=htons(3500);
        if(bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0){
                printf("Error");
        }

        listen(sockfd,5);

        cli=sizeof(cliaddr);
        connfd=accept(sockfd,(struct sockaddr*)&cliaddr,&cli);


        while(1){
                bzero(buff,sizeof(buff));
                read(connfd,buff,sizeof(buff));
                if(!strncmp("Exit",buff,4)){
                                break;
                                }
                printf("%s",buff);
                bzero(buff,sizeof(buff));
                strcpy(buff,"We have received your message");
                write(connfd,buff,sizeof(buff));
        }

        close(sockfd);

        return 0;
}
