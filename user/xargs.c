#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[])
{
    char *cmd = argv[1];
    char rec[MAXARG];
    memset(rec, 0, sizeof(rec));
    int i = 0;
    char ch;
    while (read(0, &ch, sizeof(char)))
    {
        if (ch == '\n')
        {
            char *child_argv[4];
            rec[i] = 0;
            child_argv[0] = cmd;
            child_argv[1] = argv[2];
            child_argv[2] = rec;
            child_argv[3] = 0;
            int pid = fork();
            if (pid == 0)
            {
                exec(child_argv[0], child_argv);
            }
            else
            {
                wait(0);
            }
            i = 0;
        }
        else
        {
            rec[i++] = ch;
        }
    }
    exit(0);
}

// int main(int argc, char *argv[])
// {
//     char *argv_stdin = (char *)malloc(sizeof(char) * MAXARG);
//     read(0, argv_stdin, MAXARG);
//     printf("%s\n", argv_stdin);
//     printf("%d\n", strlen(argv_stdin));
//     char *param[argc + 1];
//     for (int i = 0; i < argc - 1; i++)
//     {
//         param[i] = argv[i + 1];
//     }
//     param[argc - 1] = (char *)malloc(sizeof(char) * MAXARG);
//     param[argc] = 0;
//     char *p = argv_stdin;
//     while (*p != '\0')
//     {
//         int i = 0;
//         while (*p != '\n' && *p != 0)
//         {
//             param[argc - 1][i++] = *p++;
//         }
//         if (*p == '\n')
//         {
//             p++;
//         }
//         param[argc - 1][i] = 0;
//         printf("i=%d\n", i);
//         //查看参数是否正确
//         for (i = 0; i < argc + 1; i++)
//         {
//             printf("%s\t", param[i]);
//         }
//         printf("\n");
//         int pid = fork();
//         int child_status;
//         if (pid > 0)
//         {
//             wait(&child_status);
//         }
//         else if (pid == 0)
//         {
//             exec(param[0], param);
//             exit(0);
//         }
//         else
//         {
//             printf("xargs:fail to create child process\n");
//         }
//     }
//     free(param[argc - 1]);
//     free(argv_stdin);
//     exit(0);
// }

// echo hello too | xargs echo bye
// sh < xargstest.sh