#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 100

void prompt() {
    char command[MAX_COMMAND_LENGTH];
    
    while (1) {
        printf("$ ");
        
        if (fgets(command, sizeof(command), stdin) == NULL) {
            break;
   }
        command[strcspn(command, "\n")] = '\0';
        
        execute_command(command);
    }
}

void execute_command(const char* command) {
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        execlp(command, command, NULL);
        printf("Command not found: %s\n", command);
        exit(EXIT_FAILURE);
    } else{
        wait(NULL);
    }
}

int main() {
    prompt();
    
    return 0;
}

