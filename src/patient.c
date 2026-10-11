#include <stdio.h>
#include <string.h>
#include "../include/patient.h"

// Initialize a patient profile safely
void init_patient(Patient *p, int id, const char *name, int age) {
    p->id = id;
    p->age = age;

    // Safely copy the name string into the fixed-size array (preventing buffer overflows)
    strncpy(p->name, name, sizeof(p->name) - 1);
    p->name[sizeof(p->name) - 1] = '\0'; // Ensure null-termination

    // Initialize pointers and counts safely
    p->measurements = NULL;
    p->measurementCount = 0;
}

// Print basic patient information
void print_patient_summary(const Patient *p) {
    printf("\n--- Patient Profile ---\n");
    printf("ID:   %d\n", p->id);
    printf("Name: %s\n", p->name);
    printf("Age:  %d\n", p->age);
    printf("Readings Logged: %d\n", p->measurementCount);
}