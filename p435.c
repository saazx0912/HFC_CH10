#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

void error(char *msg){
    fprintf(stderr ,"%s: %s\n" , msg,strerror(errno));
    exit(1);
}

int main(int argc , char *argv[]){

  
    char *phrase = argv[1];
    char *vars[] = {"http://www.cnn.com/rss/celebs.xml" , NULL};
    FILE *f =fopen("stories.txt","w");
    if(!f){ //如果不能以"寫"模式打開檔案，f = 0
        error("Can't open stories.txt");
    }
    pid_t pid = fork();
    if(pid == -1){
        error("Can't fork process");
    }
    if(!pid){
        if(dup2(fileno(f) , 1) == -1){
            error("Can't refirect Standard Output");
        }
        if(execle ("python3" , "python3", "./rssgossip.py" , phrase , NULL ,vars ) == -1){
            error("Can't run script");
        }
        
    }

    int pid_status;
    if(waitpid(pid ,&pid_status ,0) == -1){
        error("Error waiting for chile process");
    }
    if(WEXITSTATUS(pid_status)){ //如果退出狀態不為0
        puts("Error status non-zero");
    }

    int fd[2];
    if(pipe(fd) == -1){
        printf("Can't create the pipe");
    }


    return 0 ;
}