// week5_task3_student_management_system.c
// Task 3: Mini-project – Student management system with file persistence
// Week 5 – Files & Modular Programming
// Name: [Your Name]
// Surname: [Your Surname]
// Student ID: [Your Student ID]

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50
#define DATA_FILE "students.txt"

typedef struct {
    char name[NAME_LEN];
    int id;
    float gpa;
} Student;

// Function prototypes
int load_students(Student arr[], int max_size);
void save_students(Student arr[], int count);
void add_student(Student arr[], int *count, int max_size);
void list_students(Student arr[], int count);
int is_valid_id(Student arr[], int count, int id);

// Helper function to safely read a line of input
void safe_gets(char *buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline
    } else {
        buffer[0] = '\0'; // Clear buffer on input error
    }
}

int main(void) {
    Student students[MAX_STUDENTS];
    int count = 0;
    int choice;

    // Load existing data from file
    count = load_students(students, MAX_STUDENTS);
    printf("Loaded %d student(s) from %s.\n", count, DATA_FILE);

    do {
        printf("\n=== Student Management System ===\n");
        printf("1. List students\n");
        printf("2. Add student\n");
        printf("3. Save and Exit\n");
        printf("Select an option (1-3): ");

        // Safely read menu choice
        char input[100];
        safe_gets(input, sizeof(input));
        if (sscanf(input, "%d", &choice) != 1) {
            choice = -1; // Invalid input
        }

        switch (choice) {
            case 1:
                list_students(students, count);
                break;
            case 2:
                add_student(students, &count, MAX_STUDENTS);
                break;
            case 3:
                save_students(students, count);
                printf("Data saved to %s. Goodbye!\n", DATA_FILE);
                break;
            default:
                printf("Invalid option. Please enter 1, 2, or 3.\n");
        }
    } while (choice != 3);

    return 0;
}

// Implement load_students()
// Open DATA_FILE, read records until EOF, return number of records loaded
int load_students(Student arr[], int max_size) {
    FILE *fp = fopen(DATA_FILE, "r");
    int count = 0;

    if (fp == NULL) {
        printf("No existing data file (%s). Starting with empty list.\n", DATA_FILE);
        return 0;
    }

    // Read records until EOF or max_size reached
    while (count < max_size &&
           fscanf(fp, "%49s %d %f", arr[count].name, &arr[count].id, &arr[count].gpa) == 3) {
        count++;
    }

    if (!feof(fp) && count >= max_size) {
        printf("Warning: Student list full. Some records may not have been loaded.\n");
    } else if (!feof(fp)) {
        printf("Warning: Error reading some records from %s.\n", DATA_FILE);
    }

    fclose(fp);
    return count;
}

// Implement save_students()
// Write all students to DATA_FILE
void save_students(Student arr[], int count) {
    FILE *fp = fopen(DATA_FILE, "w");
    if (fp == NULL) {
        printf("Error: Could not open %s for writing.\n", DATA_FILE);
        exit(1);
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s %d %f\n", arr[i].name, arr[i].id, arr[i].gpa);
    }

    fclose(fp);
}

// Implement add_student()
// Read input from user and append to array
void add_student(Student arr[], int *count, int max_size) {
    if (*count >= max_size) {
        printf("Error: Student list is full (max %d students).\n", max_size);
        return;
    }

    Student new_student;
    printf("Enter name (max %d chars): ", NAME_LEN - 1);
    safe_gets(new_student.name, NAME_LEN);

    // Validate name
    if (strlen(new_student.name) == 0) {
        printf("Error: Name cannot be empty.\n");
        return;
    }

    printf("Enter ID (unique): ");
    char input[100];
    safe_gets(input, sizeof(input));
    int id;
    if (sscanf(input, "%d", &id) != 1 || id <= 0) {
        printf("Error: Invalid ID. Must be a positive integer.\n");
        return;
    }

    // Check for duplicate ID
    if (!is_valid_id(arr, *count, id)) {
        printf("Error: ID %d already exists.\n", id);
        return;
    }

    printf("Enter GPA (0.0 to 4.0): ");
    safe_gets(input, sizeof(input));
    float gpa;
    if (sscanf(input, "%f", &gpa) != 1 || gpa < 0.0f || gpa > 4.0f) {
        printf("Error: Invalid GPA. Must be between 0.0 and 4.0.\n");
        return;
    }

    // Add student to array
    strcpy(arr[*count].name, new_student.name);
    arr[*count].id = id;
    arr[*count].gpa = gpa;
    (*count)++;
    printf("Student added successfully!\n");
}

// Implement list_students()
// Print all students in readable format
void list_students(Student arr[], int count) {
    if (count == 0) {
        printf("No students to display.\n");
        return;
    }

    printf("\nStudent List:\n");
    printf("----------------------------------------\n");
    printf("%-20s %-10s %-10s\n", "Name", "ID", "GPA");
    printf("----------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-20s %-10d %-10.2f\n", arr[i].name, arr[i].id, arr[i].gpa);
    }
    printf("----------------------------------------\n");
}

// Helper function to check if an ID is unique
int is_valid_id(Student arr[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (arr[i].id == id) {
            return 0; // ID already exists
        }
    }
    return 1; // ID is unique
}