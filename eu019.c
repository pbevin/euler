#include "euler.h"

/*
 * Jan 1, 1900 was a Monday
 * Find Sundays on the first of the month from
 * Jan 1, 1901 to
 * Dec 31, 2000
 *
 * We use Sun => 0, Mon => 1, ..., Sat => 7.
 */
int countsun(int *days_in_month, int day, int *newday) {
  // Return the number of Sundays in the year, and
  // modify newday to be the day of the week on Jan 1
  // of the next year.
  int count = 0;
  for (int i = 0; i < 12; i++) {
    if (day == 0) count++;
    day += days_in_month[i];
    day %= 7;
  }
  *newday = day;
  return count;
}

void eu019(char *ans) {
  int day;
  int count;
  int days[]   = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
  int daysly[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

  /* 1900 was NOT a leap year, but 2000 was. */
  countsun(days, 1, &day);
  count = 0; /* Not counting 1900 */
  for (int yr = 1901; yr <= 2000; yr++) {
    if (yr % 4 == 0) {
      count += countsun(daysly, day, &day);
    } else {
      count += countsun(days, day, &day);
    }
  }

  sprintf(ans, "%d", count);
}
