#include <stdio.h>
#include <stdlib.h>
#include "../include/buffer.h"

void allocate_patient_measurements(Patient *p, int count) {
    p->measurementCount = count;

    p->measurements = (SensorValue *)malloc(count * sizeof(SensorValue));

    if (p->measurements == NULL) {
        printf("Error: Memory allocation failed for patient ID %d!\n", p->id);
        exit(1);
    }

    printf("Successfully allocated memory for %d measurements.\n", count);
}

void free_patient_measurements(Patient *p) {
    if (p->measurements != NULL) {
        free(p->measurements);
        p->measurements = NULL;
        printf("Memory successfully freed for patient ID %d.\n", p->id);
    }
}