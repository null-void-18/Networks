#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
int main(){
    int sockfd,rtt,t=0,ud=0,i,p=0;
    struct sockaddr_in servaddr;
    char buff[100],rec[100];
    sockfd=socket(AF_INET,SOCK_STREAM,0);

    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=INADDR_ANY;
    servaddr.sin_port=htons(4000);
    printf("Enter the string : ");
    fgets(buff,100,stdin);
    printf("Enter the RTT : ");
    scanf("%d",&rtt);
     printf("Enter the Delay : ");
    scanf("%d",&ud);
    connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));


    char buf1[100];
    p++;
    strncpy(buf1,buff,1);

    send(sockfd,buf1,strlen(buff)+1,0);
    bzero(buf1,sizeof(buf1));

    recv(sockfd,rec,sizeof(rec),0);
    printf("%s\n",rec);
    bzero(rec,sizeof(rec));

    t+=rtt;
    for(i=p;i<strlen(buff) && (i<(floor(rtt/ud)+p-1));i++){
        strncat(buf1,buff+i,1);
    }
    p+=floor(rtt/ud)-1;
    while(p<strlen(buff)){
        send(sockfd,buf1,strlen(buff)+1,0);
        bzero(buf1,sizeof(buf1));

        recv(sockfd,rec,sizeof(rec),0);
        printf("%s\n",rec);
        bzero(rec,sizeof(rec));

        t+=rtt;
        for(i=p;i<strlen(buff) && (i<(floor(rtt/ud)+p));i++){
            strncat(buf1,buff+i,1);
        }

        p+=floor(rtt/ud);

    }

    if(strlen(buf1)!=0){
        t+=rtt;
        send(sockfd,buf1,sizeof(buf1),0);
        recv(sockfd,rec,sizeof(rec),0);
        printf("%s\n",rec);
    }
    printf("Total transmission time : %d",t);
    send(sockfd,"exit",4,0);
    recv(sockfd,rec,sizeof(rec),0);

    close(sockfd);
}
