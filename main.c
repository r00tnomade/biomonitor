#include <stdio.h>
#include <stdlib.h>
#include "include/patient.h"
#include "include/buffer.h"
#include "include/analytics.h"
#include "include/file_io.h"

int main(int argc, char *argv[]) {
    Patient currentPatient;
    currentPatient.id = 0;
    currentPatient.measurements = NULL;
    currentPatient.measurementCount = 0;

    // Check if a binary file path was passed via command-line arguments
    if (argc > 1) {
        printf("Startup config: Loading patient data from '%s'...\n", argv[1]);
        load_binary_measurements(argv[1], &currentPatient);
    }

    int choice;
    int running = 1;

    while (running) {
        printf("\n=============================\n");
        printf("     BIOMONITOR MAIN MENU    \n");
        printf("=============================\n");
        printf("1. Set Patient Info\n");
        printf("2. Enter Temperature Readings\n");
        printf("3. Display Analytics & Alerts\n");
        printf("4. Export Text Report\n");
        printf("5. Save to Binary File\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a valid number.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
            // Inside case 1 of your main menu:
            case 1: {
                int id, age;
                char name[50];

                printf("Enter Patient ID: ");
                scanf("%d", &id);
                printf("Enter Age: ");
                scanf("%d", &age);
                printf("Enter Name: ");
                scanf("%49s", name);

                // Call function from src/patient.c
                init_patient(&currentPatient, id, name, age);
                printf("Patient profile updated successfully!\n");
                break;
            }
            case 2: {
                int typeChoice, count;
                printf("\nSelect Measurement Type:\n");
                printf("1. Temperature (°C)\n");
                printf("2. Heart Rate (BPM)\n");
                printf("3. ECG Signal\n");
                printf("Enter choice (1-3): ");
                scanf("%d", &typeChoice);

                if (typeChoice < 1 || typeChoice > 3) {
                    printf("Invalid measurement type selection.\n");
                    break;
                }

                currentPatient.currentType = (MeasurementType)typeChoice;

                printf("How many readings to record? ");
                scanf("%d", &count);

                if (count <= 0) {
                    printf("Error: Reading count must be greater than zero.\n");
                    break;
                }

                allocate_patient_measurements(&currentPatient, count);

                for (int i = 0; i < count; i++) {
                    if (currentPatient.currentType == TEMP) {
                        printf("Enter Temperature reading %d (°C): ", i + 1);
                        scanf("%f", &currentPatient.measurements[i].temperature);
                    } else {
                        char *label = (currentPatient.currentType == HEART_RATE) ? "Heart Rate (BPM)" : "ECG";
                        printf("Enter %s reading %d: ", label, i + 1);
                        scanf("%d", &currentPatient.measurements[i].heartRate);
                    }
                }
                printf("Sensor telemetry logged successfully!\n");
                break;
            }

            case 3: {
                if (currentPatient.measurementCount == 0 || currentPatient.measurements == NULL) {
                    printf("Warning: No measurements found. Please record telemetry first.\n");
                    break;
                }

                float mean = calculate_mean(&currentPatient);
                float std_dev = calculate_std_dev(&currentPatient, mean);

                printf("\n--- Analytics Report for Patient %d ---\n", currentPatient.id);
                printf("Name: %s | Age: %d\n", currentPatient.name, currentPatient.age);

                if (currentPatient.currentType == TEMP) {
                    printf("Sensor Type: Temperature\n");
                    printf("Mean: %.2f °C | Std Dev: %.2f\n", mean, std_dev);

                    if (mean > 38.0f) {
                        printf("[ALERT] CRITICAL: High fever detected!\n");
                    } else {
                        printf("[STATUS] OK: Temperature is normal.\n");
                    }
                } else {
                    char *typeName = (currentPatient.currentType == HEART_RATE) ? "Heart Rate" : "ECG Signal";
                    printf("Sensor Type: %s\n", typeName);
                    printf("Mean: %.2f | Std Dev: %.2f\n", mean, std_dev);

                    if (currentPatient.currentType == HEART_RATE) {
                        if (mean > 100.0f) {
                            printf("[ALERT] WARNING: Tachycardia detected (High Heart Rate)!\n");
                        } else if (mean < 60.0f) {
                            printf("[ALERT] WARNING: Bradycardia detected (Low Heart Rate)!\n");
                        } else {
                            printf("[STATUS] OK: Heart rate is within normal limits.\n");
                        }
                    }
                }
                break;
            }
            case 4: {
                if (currentPatient.measurementCount == 0) {
                    printf("No data to export.\n");
                    break;
                }
                float mean = calculate_mean(&currentPatient);
                float std_dev = calculate_std_dev(&currentPatient, mean);
                save_text_report("patient_report.txt", &currentPatient, mean, std_dev);
                break;
            }

            case 5:
                if (currentPatient.measurementCount == 0) {
                    printf("No data to save.\n");
                    break;
                }
                save_binary_measurements("patient_data.bin", &currentPatient);
                break;

            case 6:
                printf("Shutting down BioMonitor and freeing memory...\n");
                free_patient_measurements(&currentPatient);
                running = 0;
                break;

            default:
                printf("Invalid choice! Please choose an option between 1 and 6.\n");
        }
    }

    return 0;
}