// week5_task1_file_io.c
// Task 1: Read and write data from text files
// Week 5 – Files & Modular Programming
// Name: [Your Name]
// Surname: [Your Surname]
// Student ID: [Your Student ID]

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *fp;
    char filename[100];
    char line[256];
    int line_count = 0;

    // BONUS: Ask user for filename
    printf("Enter filename (default: data.txt): ");
    if (fgets(filename, sizeof(filename), stdin) == NULL) {
        printf("Error reading filename input.\n");
        return 1;
    }
    // Remove newline character from filename
    for (int i = 0; filename[i]; i++) {
        if (filename[i] == '\n') {
            filename[i] = '\0';
            break;
        }
    }
    // If user entered nothing, use default
    if (filename[0] == '\0') {
        snprintf(filename, sizeof(filename), "data.txt");
    }

    // 1. Open file for writing (mode = "w")
    fp = fopen(filename, "w");
    
    // 2. Check if file opened successfully
    if (fp == NULL) {
        printf("Error: Could not open file %s for writing.\n", filename);
        return 1;
    }

    // 3. Write 2–3 lines of text to the file using fprintf()
    printf("Writing lines to %s...\n", filename);
    fprintf(fp, "Hello, file I/O in C!\n");
    fprintf(fp, "This is another line.\n");
    fprintf(fp, "Learning file handling is fun!\n");

    // 4. Close the file
    fclose(fp);
    printf("File %s written successfully.\n", filename);

    // 5. Open file again for reading (mode = "r")
    fp = fopen(filename, "r");
    
    // 6. Check if file opened successfully
    if (fp == NULL) {
        printf("Error: Could not open file %s for reading.\n", filename);
        return 1;
    }

    // 7. Use fgets() in a loop to read and print each line to the console
    printf("Reading contents:\n");
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line); // Print each line
        line_count++;       // BONUS: Count lines
    }

    // 8. Close the file
    fclose(fp);

    // BONUS: Display number of lines read
    printf("Total lines read: %d\n", line_count);

    return 0;
}