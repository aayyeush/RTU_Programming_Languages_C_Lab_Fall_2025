/*
 * week4_2_struct_student.c
  * Author: Ayush
 * Student ID: 241ADB040
 * Description:
 *   Demonstrates defining and using a struct in C.
 *   Students should define a 'Student' struct with fields like name, id, and grade.
 *   Then create a few instances and print them.
 */

#include <stdio.h>
#include <string.h>


// Define struct Student with fields: name (char[]), id (int), grade (float)
struct Student {
    char name[50];
    int id;
    float grade;
};

int main(void) {

    // Declare and assign values to Student variables
    struct Student s1 = {"Alice", 1001, 8.5f};
    struct Student s2 = {"Bob", 1002, 7.9f};

    // Print struct contents using printf
    printf("Student 1: Name: %s, ID: %d, Grade: %.2f\n", s1.name, s1.id, s1.grade);
    printf("Student 2: Name: %s, ID: %d, Grade: %.2f\n", s2.name, s2.id, s2.grade);

    return 0;
}
