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
        char buff[1000],rec[1000];
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

        char *file1="rootdns.txt";


        sendto(newfd,(char *)file1,strlen(file1)+1,0,(struct sockaddr*)&tdsaddr,sizeof(servaddr));
        sendto(newfd,(char *)buff,strlen(buff)+1,0,(struct sockaddr*)&tdsaddr,sizeof(servaddr));

        recvfrom(newfd,(char *)rec,1000,0,NULL,NULL);
        printf("\nRoot DNS Server : %s",rec);
        sendto(sockfd,(char *)rec,strlen(rec)+1,0,(struct sockaddr*)&cliaddr,cl);

        close(newfd);



        int nfd;
        struct sockaddr_in rootaddr;


        nfd=socket(AF_INET,SOCK_DGRAM,0);


        rootaddr.sin_family=AF_INET;
        rootaddr.sin_addr.s_addr=INADDR_ANY;
        rootaddr.sin_port=htons(5000);


        char file[100];

        int j=0,i;


        while(buff[j]!='.'){
            j++;
        }
        j++;

        for(i=0;buff[j]!='.';i++){
            file[i]=buff[j];
            j++;
        }
        file[i]='\0';

        sendto(nfd,(char *)file,strlen(file)+1,0,(struct sockaddr*)&rootaddr,sizeof(servaddr));
        sendto(nfd,(char *)rec,strlen(rec)+1,0,(struct sockaddr*)&rootaddr,sizeof(servaddr));
        bzero(buff,1000);
        recvfrom(nfd,(char *)buff,1000,0,NULL,NULL);
        printf("\nTLD DNS Server : %s",buff);
        sendto(sockfd,(char *)buff,strlen(buff)+1,0,(struct sockaddr*)&cliaddr,cl);

        close(nfd);
        close(sockfd);
        return 0;
}
