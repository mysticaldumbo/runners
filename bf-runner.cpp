#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 30000

char memory[MEMORY_SIZE] = {0};
char *ptr = memory;

void executeBrainfuck(char *code) {
    while (*code) {
        switch (*code) {
            case '>':
                ++ptr;
                break;
            case '<':
                --ptr;
                break;
            case '+':
                ++(*ptr);
                break;
            case '-':
                --(*ptr);
                break;
            case '[':
                if (!(*ptr)) {
                    int loop = 1;
                    while (loop > 0) {
                        ++code;
                        if (*code == '[')
                            ++loop;
                        else if (*code == ']')
                            --loop;
                    }
                }
                break;
            case ']':
                if (*ptr) {
                    int loop = 1;
                    while (loop > 0) {
                        --code;
                        if (*code == '[')
                            --loop;
                        else if (*code == ']')
                            ++loop;
                    }
                }
                break;
            case '.':
                putchar(*ptr);
                break;
            case ',':
                *ptr = getchar();
                break;
            default:
                // Ignore characters that are not Brainfuck commands
                break;
        }
        ++code;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <brainfuck_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char *code = malloc(length + 1);
    if (!code) {
        perror("Error allocating memory");
        fclose(file);
        return 1;
    }

    fread(code, 1, length, file);
    fclose(file);
    code[length] = '\0';

    executeBrainfuck(code);

    free(code);

    // Pause before exiting
    printf("\nPress Enter to exit...");
    while (getchar() != '\n');

    return 0;
}
