#include <stdio.h>
#include <math.h>
#include "../include/analytics.h"

// Generic mean calculation supporting both floats and ints via union
float calculate_mean(const Patient *p) {
    if (p->measurementCount <= 0 || p->measurements == NULL) {
        return 0.0f;
    }

    float sum = 0.0f;
    for (int i = 0; i < p->measurementCount; i++) {
        if (p->currentType == TEMP) {
            sum += p->measurements[i].temperature;
        } else {
            // HEART_RATE or ECG are stored as integers
            sum += (float)p->measurements[i].heartRate;
        }
    }

    return sum / p->measurementCount;
}

// Standard deviation calculation supporting both types
float calculate_std_dev(const Patient *p, float mean) {
    if (p->measurementCount <= 1 || p->measurements == NULL) {
        return 0.0f;
    }

    float variance_sum = 0.0f;
    for (int i = 0; i < p->measurementCount; i++) {
        float val = (p->currentType == TEMP) ?
                    p->measurements[i].temperature :
                    (float)p->measurements[i].heartRate;

        float diff = val - mean;
        variance_sum += (diff * diff); // Efficient squaring
    }

    float variance = variance_sum / p->measurementCount;
    return sqrt(variance);
}