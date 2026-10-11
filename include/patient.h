#ifndef PATIENT_H
#define PATIENT_H

typedef enum {
    STATUS_OK = 0,
    STATUS_WARNING,
    STATUS_CRITICAL
} SensorStatus;

typedef enum {
    TEMP = 1,
    HEART_RATE,
    ECG
} MeasurementType;

typedef union {
    float temperature; // For TEMP
    int heartRate;     // For HEART_RATE or ECG
} SensorValue;

typedef struct {
    int id;
    char name[50];
    int age;
    MeasurementType currentType; // Tracks whether this is TEMP, HEART_RATE, or ECG
    SensorValue *measurements;
    int measurementCount;
} Patient;

void init_patient(Patient *p, int id, const char *name, int age);
void print_patient_summary(const Patient *p);

#endif // PATIENT_H