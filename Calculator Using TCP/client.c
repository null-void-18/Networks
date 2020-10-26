//Server is the calculator and asks for the operation to be performed
//Client sends the operands and server does the calculation
//And then server returns the result

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<fcntl.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main(){
    
    int sockfd,choice,op1,op2;
    struct sockaddr_in serv;
    char buff[200];
    
    //since we have square root fucntion we declare the value of result as float
    float result;
    
    sockfd=socket(AF_INET,SOCK_STREAM,0);

    serv.sin_family=AF_INET;
    serv.sin_addr.s_addr=INADDR_ANY;
    serv.sin_port=htons(4000);

    connect(sockfd,(struct sockaddr*)&serv,sizeof(serv));

    //send the choice and operands to the server
    //receive the result from the server
    read(sockfd,buff,sizeof(buff));
    printf("\n%s\n",buff);
    bzero(buff,200);
    scanf("%d",&choice);
    write(sockfd,&choice,sizeof(int));
    printf("Enter the values of operand(s) : ");
    if(choice != 5){
        scanf("%d%d",&op1,&op2);
        write(sockfd,&op1,sizeof(int));
        write(sockfd,&op2,sizeof(int));
    }
    else{
        scanf("%d",&op1);
        write(sockfd,&op1,sizeof(int));
    }

    read(sockfd,&result,sizeof(float));

    printf("\nResult is %f\n",result);

    close(sockfd);
    return 0;
}
