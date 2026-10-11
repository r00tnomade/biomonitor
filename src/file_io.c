#include <stdio.h>
#include <stdlib.h>
#include "../include/file_io.h"
#include "../include/buffer.h"

int save_text_report(const char *filename, const Patient *p, float mean, float std_dev) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening text file for writing");
        return 0;
    }

    // Determine unit and sensor name string
    const char *sensorName;
    const char *unit;
    if (p->currentType == TEMP) {
        sensorName = "Temperature";
        unit = "°C";
    } else if (p->currentType == HEART_RATE) {
        sensorName = "Heart Rate";
        unit = "BPM";
    } else {
        sensorName = "ECG Signal";
        unit = "Units";
    }

    fprintf(file, "========================================\n");
    fprintf(file, "        BIOMONITOR PATIENT REPORT       \n");
    fprintf(file, "========================================\n");
    fprintf(file, "Patient ID:   %d\n", p->id);
    fprintf(file, "Name:         %s\n", p->name);
    fprintf(file, "Age:          %d\n", p->age);
    fprintf(file, "Sensor Type:  %s\n", sensorName);
    fprintf(file, "Readings Count: %d\n", p->measurementCount);
    fprintf(file, "Mean Value:   %.2f %s\n", mean, unit);
    fprintf(file, "Std Dev:      %.2f\n", std_dev);
    fprintf(file, "----------------------------------------\n");
    fprintf(file, "Raw Readings:\n");

    for (int i = 0; i < p->measurementCount; i++) {
        if (p->currentType == TEMP) {
            fprintf(file, "  [%d] %.2f %s\n", i + 1, p->measurements[i].temperature, unit);
        } else {
            fprintf(file, "  [%d] %d %s\n", i + 1, p->measurements[i].heartRate, unit);
        }
    }
    fprintf(file, "========================================\n");

    fclose(file);
    printf("Successfully exported text report to %s\n", filename);
    return 1;
}

int save_binary_measurements(const char *filename, const Patient *p) {
    FILE *file = fopen(filename, "wb"); // 'wb' = write binary
    if (file == NULL) {
        perror("Error opening binary file for writing");
        return 0;
    }

    // Write metadata including currentType enum
    fwrite(&(p->id), sizeof(int), 1, file);
    fwrite(&(p->age), sizeof(int), 1, file);
    fwrite(&(p->currentType), sizeof(MeasurementType), 1, file);
    fwrite(&(p->measurementCount), sizeof(int), 1, file);

    // Write the dynamic measurement union array block directly
    if (p->measurementCount > 0 && p->measurements != NULL) {
        fwrite(p->measurements, sizeof(SensorValue), p->measurementCount, file);
    }

    fclose(file);
    printf("Successfully saved binary telemetry to %s\n", filename);
    return 1;
}

int load_binary_measurements(const char *filename, Patient *p) {
    FILE *file = fopen(filename, "rb"); // 'rb' = read binary
    if (file == NULL) {
        perror("Error opening binary file for reading");
        return 0;
    }

    // Read metadata back in exact matching order
    fread(&(p->id), sizeof(int), 1, file);
    fread(&(p->age), sizeof(int), 1, file);
    fread(&(p->currentType), sizeof(MeasurementType), 1, file);

    int count = 0;
    fread(&count, sizeof(int), 1, file);

    if (count > 0) {
        // Allocate space using your buffer manager
        allocate_patient_measurements(p, count);
        // Read raw array block directly into allocated memory
        fread(p->measurements, sizeof(SensorValue), count, file);
    } else {
        p->measurementCount = 0;
        p->measurements = NULL;
    }

    fclose(file);
    printf("Successfully loaded binary telemetry from %s (%d readings, Type: %d)\n", filename, count, p->currentType);
    return 1;
}