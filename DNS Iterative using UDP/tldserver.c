#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>


int main(){
        int sockfd,flag=0;
        struct sockaddr_in servaddr,cliaddr;
        char buff[1000],file1[100],file2[100],ftoken[100],ip[100];
        socklen_t cl;

        sockfd=socket(AF_INET,SOCK_DGRAM,0);


        servaddr.sin_family=AF_INET;
        servaddr.sin_addr.s_addr=INADDR_ANY;
        servaddr.sin_port=htons(5000);

        bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

        cl=sizeof(cliaddr);

        bzero(buff,1000);
        char* file="tld.txt";
        recvfrom(sockfd,(char *)file1,100,0,(struct sockaddr*)&cliaddr,&cl);
        recvfrom(sockfd,(char *)buff,1000,0,(struct sockaddr*)&cliaddr,&cl);
        int i=0,index;

            FILE *fptr;
            fptr = fopen(file, "r");

            char *il=".txt";

            while (fgets(ftoken, 100, fptr) != NULL)
            {
                int l=0;
                bzero(ip,100);
                char web[100];
                index = 0;
                i = 0;
                for (; ftoken[i] != ','; i++)
                {
                    l++;
                    web[index++]=ftoken[i];
                }
                web[index]='\0';
                i++;
                index = 0;
                for (; ftoken[i] != '\n'; i++)
                {
                    ip[index++] = ftoken[i];
                }
                ip[index] = '\0';
                l=strlen(buff);
                if(!strncmp(web,buff,l)){
                    strcat(ip,il);
                    flag=1;
                    break;
                }

            }

            if(flag==1){
                fptr = fopen(ip, "r");
                index=0;
                i=0;
            while (fgets(ftoken, 100, fptr) != NULL)
                {
                    int l=0;
                bzero(file2,100);
                char web[100];
                index = 0;
                i = 0;
                for (; ftoken[i] != ','; i++)
                {
                    l++;
                    web[index++]=ftoken[i];
                }
                web[index]='\0';
                i++;
                index = 0;
                for (; ftoken[i] != '\n'; i++)
                {
                    file2[index++] = ftoken[i];
                }
                file2[index] = '\0';

                if(!strncmp(web,file1,l)){
                    break;
                }

                }
            }
            if(flag==1)
            printf("IP address : %s",file2);
            else
                strcpy(ip,"Error.. URL does not exist.");
            sendto(sockfd,(char *)file2,strlen(file2)+1,0,(struct sockaddr*)&cliaddr,cl);

            close(sockfd);
        return 0;
}
