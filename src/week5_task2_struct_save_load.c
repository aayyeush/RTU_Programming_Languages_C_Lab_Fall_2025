// week5_task2_struct_save_load.c
// Task 2: Save and load structured records from a file
// Week 5 – Files & Modular Programming
// Name: [Your Name]
// Surname: [Your Surname]
// Student ID: [Your Student ID]

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50

typedef struct {
    char name[MAX_NAME_LEN];
    int age;
    float gpa;
} Student;

// Function prototypes
void save_student(Student s, const char *filename);
Student load_student(const char *filename);

int main(void) {
    Student s1;
    strcpy(s1.name, "Alice");
    s1.age = 21;
    s1.gpa = 3.75f;

    const char *filename = "student.txt";

    // Call save_student() to save student data to file
    printf("Saving student to file...\n");
    save_student(s1, filename);

    // Call load_student() to read data back into a new struct
    printf("Loading student from file...\n");
    Student s2 = load_student(filename);

    // Print loaded data to confirm correctness
    printf("Loaded student: %s, %d, GPA %.2f\n", s2.name, s2.age, s2.gpa);

    return 0;
}

// Implement save_student()
// Open file for writing, check errors, write fields, then close file
void save_student(Student s, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: Could not open file %s for writing.\n", filename);
        exit(1);
    }

    // Write student data in text format: name age gpa
    fprintf(fp, "%s %d %f\n", s.name, s.age, s.gpa);

    // Close the file
    fclose(fp);
}

// Implement load_student()
// Open file for reading, check errors, read fields, then close file
Student load_student(const char *filename) {
    Student s;
    // Initialize to default values in case of read failure
    s.name[0] = '\0';
    s.age = 0;
    s.gpa = 0.0f;

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: Could not open file %s for reading.\n", filename);
        exit(1);
    }

    // Read student data: name (string), age (int), gpa (float)
    if (fscanf(fp, "%49s %d %f", s.name, &s.age, &s.gpa) != 3) {
        printf("Error: Failed to read student data from %s.\n", filename);
        fclose(fp);
        exit(1);
    }

    // Close the file
    fclose(fp);

    return s;
}