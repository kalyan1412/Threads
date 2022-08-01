#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main() {
    // let's have two pipes.
    // first pipe is used to send the input string from parent.
    // second pipe is used to send the concatenate string from child.
    int fd1[2], fd2[2];
    pid_t p;
    
    const char *fixed_str = "@oracle.com";
    char input_str[100];
    scanf("%s", input_str);
    if (pipe(fd1) == -1) {
        fprintf(stderr, "Pipe Failed");
        return 1;
    }
    
    if (pipe(fd2) == -1) {
        fprintf(stderr, "Pipe Failed");
        return 1;
    }
    
    p = fork();
    if (p < 0) {
        fprintf(stderr, "fork failed");
        return 1;
    } else if (p > 0) { // parent execute
        char concat_str[100];
        close (fd1[0]); // close read end of first pipe
        write (fd1[1], input_str, strlen(input_str) + 1);
        close (fd1[1]); // close write end of first pipe
        wait(NULL); // wait for child to send the concatenate string.
        close (fd2[1]);
        read (fd2[0], concat_str, 100);
        printf("%s\n", concat_str);
        close (fd2[0]);
    } else { // child execution
        char concat_str[100];
        close (fd1[1]); // close write end of first pipe.
        read (fd1[0], concat_str, 100);
        close (fd1[0]);
        int k = strlen(concat_str);
        for (int i = 0; i < strlen(fixed_str); i++) {
            concat_str[k++] = fixed_str[i];
        }
        concat_str[k] = '\0';
        close(fd2[0]); // close the read end of second pipe
        write(fd2[1], concat_str, strlen(concat_str) +1);
        close (fd2[1]);
        exit(0);
    }
    return 0;
}
