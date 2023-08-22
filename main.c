#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 1024

void run_command(char *command);

int main() {
    char input[MAX_INPUT_SIZE];

    while (1) {
        printf("SuprShell> ");
        fgets(input, sizeof(input), stdin);

        // Remove the newline character from the input
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            printf("Exiting shell...\n");
            break;
        }

        run_command(input);
    }

    return 0;
}

void run_command(char *command) {
    char *cmd = strtok(command, " ");
    if (cmd == NULL)
        return;

    if (strcmp(cmd, "echo") == 0) {
        char *arg = strtok(NULL, "");
        if (arg != NULL)
            printf("%s\n", arg);
    }
    else if (strcmp(cmd, "cat") == 0) {
        char *arg = strtok(NULL, "");
        if (arg != NULL) {
            FILE *file = fopen(arg, "r");
            if (file) {
                char buffer[MAX_INPUT_SIZE];
                while (fgets(buffer, sizeof(buffer), file)) {
                    printf("%s", buffer);
                }
                fclose(file);
            } else {
                printf("Error: Unable to open the file.\n");
            }
        }
    }
    else if (strcmp(cmd, "touch") == 0) {
        char *arg = strtok(NULL, "");
        if (arg != NULL) {
            FILE *file = fopen(arg, "w");
            if (file) {
                fclose(file);
            } else {
                printf("Error: Unable to create the file.\n");
            }
        }
    }
    else if (strcmp(cmd, "ls") == 0) {
        char *arg = strtok(NULL, "");
        if (arg == NULL) {
            struct dirent *entry;
            DIR *dir = opendir(".");
            if (dir) {
                while ((entry = readdir(dir)) != NULL) {
                    printf("%s\n", entry->d_name);
                }
                closedir(dir);
            } else {
                printf("Error: Unable to open directory.\n");
            }
        } else {
            printf("Usage: ls [directory]\n");
        }
    }
    else if (strcmp(cmd, "mkdir") == 0) {
        char *arg = strtok(NULL, "");
        if (arg != NULL) {
            if (mkdir(arg, 0777) == 0) {
                printf("Directory created: %s\n", arg);
            } else {
                printf("Error: Unable to create directory.\n");
            }
        }
    }
    else if (strcmp(cmd, "rm") == 0) {
        char *arg = strtok(NULL, "");
        if (arg != NULL) {
            if (remove(arg) == 0) {
                printf("File removed: %s\n", arg);
            } else {
                printf("Error: Unable to remove file.\n");
            }
        }
    }
    else if (strcmp(cmd, "cd") == 0) {
        char *arg = strtok(NULL, "");
        if (arg != NULL) {
            if (chdir(arg) == 0) {
                printf("Changed directory to: %s\n", arg);
            } else {
                printf("Error: Unable to change directory.\n");
            }
        }
    }
    else if (strcmp(cmd, "pwd") == 0) {
        char cwd[MAX_INPUT_SIZE];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("Current working directory: %s\n", cwd);
        } else {
            printf("Error: Unable to get current working directory.\n");
        }
    }
    else {
        printf("Unknown command: %s\n", cmd);
    }
}
