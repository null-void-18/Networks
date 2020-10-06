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
        char buff[1000],file1[100],ftoken[100],ip[100],w[100];
        socklen_t cl;

        sockfd=socket(AF_INET,SOCK_DGRAM,0);


        servaddr.sin_family=AF_INET;
        servaddr.sin_addr.s_addr=INADDR_ANY;
        servaddr.sin_port=htons(4000);

        bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

        cl=sizeof(cliaddr);

        bzero(buff,1000);

        recvfrom(sockfd,(char *)file1,100,0,(struct sockaddr*)&cliaddr,&cl);

        recvfrom(sockfd,(char *)buff,1000,0,(struct sockaddr*)&cliaddr,&cl);
        int i=0,j=0,k=0,index;

            FILE *fptr;
            fptr = fopen(file1, "r");

            while(buff[j]!='.'){
                j++;
            }
            j++;
            while(buff[j]!='.'){
                j++;
            }

            while(buff[j]!='\0'){
                w[k]=buff[j];
                k++;
                j++;
            }

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
                web[i]='\0';
                i++;
                index = 0;
                for (; ftoken[i] != '\n'; i++)
                {
                    ip[index++] = ftoken[i];
                }
                ip[index] = '\0';

                if(strncmp(web,w,4)==0){
                    flag=1;
                    break;
                }

            }




            if(flag==1)
            printf("IP address : %s",ip);
            else
                strcpy(ip,"Error.. URL does not exist.");
            sendto(sockfd,(char *)ip,100,0,(struct sockaddr*)&cliaddr,cl);

            close(sockfd);
        return 0;
}
