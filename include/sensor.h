/*
 * sensor.h
 * -----------------------------------------------------------
 * Δηλώσεις δομών και συναρτήσεων για την ανάγνωση και
 * επεξεργασία θερμοκρασιών από sensor log αρχεία.
 * -----------------------------------------------------------
 */

#ifndef SENSOR_H
#define SENSOR_H

#define MAX_READINGS 100000
#define INPUT_BUFFER 256

/* Δομή που κρατά τα στατιστικά αποτελέσματα */
typedef struct {
    int    count;
    double sum;
    double min;
    double max;
    double average;
    double stddev;
} Statistics;

/*
 * Διαβάζει όλες τις έγκυρες θερμοκρασίες από το αρχείο filename
 * στον πίνακα temps[]. Επιστρέφει το πλήθος όσων διαβάστηκαν,
 * ή -1 αν το αρχείο δεν μπόρεσε να ανοιχτεί.
 */
int read_temperatures(const char *filename, double temps[], int max_count);

/*
 * Υπολογίζει μέσο όρο, ελάχιστο, μέγιστο και τυπική απόκλιση
 * από τον πίνακα temps[] με count στοιχεία.
 */
Statistics compute_statistics(double temps[], int count);

/*
 * Γράφει το τελικό report στο αρχείο output_filename και το
 * εμφανίζει ταυτόχρονα και στην οθόνη (stdout).
 */
void write_report(const char *output_filename, Statistics stats, double temps[]);

#endif /* SENSOR_H */
