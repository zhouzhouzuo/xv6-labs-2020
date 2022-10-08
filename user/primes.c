#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void fun(int[]);

void fun(int fd[]){
    close(fd[1]);
    int p;
    if(read(fd[0],&p,4) == 0)
        exit(0);
    printf("prime %d\n",p);

    int n;

    int f[2];
    pipe(f);

    if(fork() == 0){
        fun(f);
    }
    else{
        close(f[0]);
        while(read(fd[0],&n,4) != 0){
            if(n % p != 0)
                write(f[1],&n,4);    
        }
        close(f[1]);
        wait(0);
        exit(0);
    }
}

int
main()
{
    int f[2];
    pipe(f);
    
    if(fork() == 0){
        fun(f);
    }
    else{
        close(f[0]);
        for(int i = 2 ; i <= 35;i++ ){
            write(f[1],&i,4);
        }
        close(f[1]);
        wait(0);
        exit(0);
    }
    return 0;
}
