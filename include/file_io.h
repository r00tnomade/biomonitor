#ifndef FILE_IO_H
#define FILE_IO_H

#include "patient.h"

int save_text_report(const char *filename, const Patient *p, float mean, float std_dev);
int save_binary_measurements(const char *filename, const Patient *p);
int load_binary_measurements(const char *filename, Patient *p);

#endif // FILE_IO_H