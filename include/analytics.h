#ifndef ANALYTICS_H
#define ANALYTICS_H

#include "patient.h"

float calculate_mean(const Patient *p);

float calculate_std_dev(const Patient *p, float mean);

#endif // ANALYTICS_H