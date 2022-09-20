#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int p1[2], p2[2];
    pipe(p1);
    pipe(p2);
    char str[10];
    int ret = fork();
    if (ret > 0)
    { //父进程接收之后退出 注意同步顺序
        close(p1[0]);
        write(p1[1], "ping", 5);
        close(p1[1]);

        close(p2[1]);
        read(p2[0], str, 5);
        printf("%d: received %s\n", getpid(), str);
        // printf("%s", str);
        close(p2[0]);
    }
    else if (ret == 0)
    {
        close(p1[1]);
        read(p1[0], str, 5);
        printf("%d: received %s\n", getpid(), str);
        // printf("%s", str);
        close(p1[0]);

        close(p2[0]);
        write(p2[1], "pong", 5);
        close(p2[1]);
    }
    else
    {
        fprintf(2, "error in fork\n");
    }

    exit(0);
}