#ifndef BUFFER_H
#define BUFFER_H

#include "patient.h"

void allocate_patient_measurements(Patient *p, int count);

void free_patient_measurements(Patient *p);

#endif // BUFFER_H