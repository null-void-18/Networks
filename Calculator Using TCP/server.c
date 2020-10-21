#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<fcntl.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<unistd.h>

int main(){
    int sockfd,clifd;
    struct sockaddr_in serv,cli;
    socklen_t len;
    char buff[200];
    char *s="Enter the operation: \n 1.Addition \n 2.Subtraction \n 3.Multiply \n 4.Division \n 5.SQRT \n";
    int choice,op1,op2,result;

    sockfd=socket(AF_INET,SOCK_STREAM,0);

    serv.sin_family=AF_INET;
    serv.sin_addr.s_addr=INADDR_ANY;
    serv.sin_port=htons(4000);

    bind(sockfd,(struct sockaddr*)&serv,sizeof(serv));

    listen(sockfd,5);
    len=sizeof(cli);
    clifd=accept(sockfd,(struct sockaddr*)&cli,&len);
    len=sizeof(cli);

    write(clifd,s,strlen(s)+1);
    read(clifd,&choice,sizeof(int));

    if(choice != 5){
        read(clifd,&op1,sizeof(int));
        read(clifd,&op2,sizeof(int));
    }
    else{
        read(clifd,&op1,sizeof(int));
    }

    switch(choice){

        case 1: result=op1+op2;
        break;

        case 2: result=op1-op2;
        break;

        case 3: result=op1*op2;
        break;

        case 4: result=op1/op2;
        break;

        case 5: result=sqrt(op1);
        break;

        default: printf("Operation does not exist...");
    }

    write(clifd,&result,sizeof(int));

    close(sockfd);
    return 0;
}
