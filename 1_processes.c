#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
    pid_t pid;                                      //initializing process id
    int fd[2];                                      //initializing file descriptor - 0 = read; 1 = write;

    if (pipe(fd) == -1) {                           //initializing pipe function 
        printf("Could not create pipe\n");
        return 1;
    }

    pid = fork();                        

    if (pid == -1){                                
        printf("Error creating fork.\n");
        return 2;

    } else if (pid == 0){                          //child process
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        char* argv[] = {"ls", "-la", NULL};               
        int err = execvp(argv[0], argv);
        if (err == -1){
            printf("Unable to execute command.\n");
            return 3;
        }
        close(fd[1]);

    } else {                                        //parent process
        close(fd[1]);
        char buffer[1024];
        printf("\n");
        printf("Parent process.\n\n");
        if(read(fd[0], buffer, sizeof(buffer)) == -1){
            printf("Could not read output from child process.\n");
            return 4;
        }
        printf("%s\n", buffer);
        close(fd[0]); 
    }
    return 0;
}