/*
 * Command line arguments ¿¹Á¦
 */


 #include <stdio.h>

int main(int argc, char **argv) {
    printf("The number of command line arguments: %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }
    return 0;
}