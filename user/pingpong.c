#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main()
{
    int p[2];
    int q[2];
    pipe(p);
    pipe(q);
    char buf[100];
    char buff[100];

    if(fork() == 0){
        close(p[1]);
        read(p[0], buf,sizeof(buf));
        close(p[0]);
        printf("%d: received %s\n",getpid(),buf);
       
        close(q[0]);
        write(q[1],"pong",4);
        close(q[1]);

        exit(0);
    }else{
        close(p[0]);
        write(p[1],"ping",4);
        close(p[1]);

        close(q[1]);
        read(q[0],buff,sizeof(buff));
        close(q[0]);
        printf("%d: received %s\n",getpid(),buff);


        wait(0);
        exit(0);
    }
}