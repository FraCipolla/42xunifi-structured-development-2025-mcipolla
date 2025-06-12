#ifndef CRITICAL_WINDOWS_H
#define CRITICAL_WINDOWS_H

#define MAX(i, t) i > t ? t : i

int count_critical_windows(const int *readings, int size);

#endif