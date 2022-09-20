#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(2, "usage: sleep time\n");
        exit(1);
    }
    int n=atoi(argv[1]);
    int ret=sleep(n);
    if(ret<0){
        fprintf(2, "sleep wrong\n");
    }
    exit(0);
}


