#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    // Construct command to pipe output into clip.exe
    char cmd[] = "clip.exe";

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Open a pipe to clip.exe
    FILE *pipe = popen(cmd, "w");
    if (!pipe) {
        perror("Error opening pipe");
        fclose(fp);
        return EXIT_FAILURE;
    }

    // Read from file and write into the pipe
    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        fputc(ch, pipe);
    }

   // Close the file and the pipe
   fclose(fp);
   if (pclose(pipe) == -1) {
       fprintf(stderr, "Error occurred while closing the pipe\n");
       return EXIT_FAILURE;
   }

   printf("File content copied to clipboard.\n");

   return 0;
}

