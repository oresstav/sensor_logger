/*
 * sensor.c
 * -----------------------------------------------------------
 * Υλοποίηση των συναρτήσεων ανάγνωσης, επεξεργασίας και
 * αναφοράς (report) θερμοκρασιών.
 * -----------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "sensor.h"

int read_temperatures(const char *filename, double temps[], int max_count) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Σφάλμα: δεν ήταν δυνατό το άνοιγμα του αρχείου '%s'\n", filename);
        return -1;
    }

    char line[INPUT_BUFFER];
    int  count = 0;
    int  line_number = 0;
    int  skipped = 0;

    while (fgets(line, sizeof(line), fp) != NULL) {
        line_number++;

        /* Αφαίρεση χαρακτήρα νέας γραμμής */
        line[strcspn(line, "\r\n")] = '\0';

        /* Αγνόησε εντελώς κενές γραμμές */
        if (strlen(line) == 0) {
            continue;
        }

        char *endptr;
        double value = strtod(line, &endptr);

        /* Αν δεν μετατράπηκε τίποτα, η γραμμή δεν περιέχει αριθμό */
        if (endptr == line) {
            fprintf(stderr, "Προειδοποίηση: μη έγκυρη γραμμή %d αγνοήθηκε: \"%s\"\n",
                    line_number, line);
            skipped++;
            continue;
        }

        if (count >= max_count) {
            fprintf(stderr, "Προειδοποίηση: υπερβήκατε το μέγιστο πλήθος μετρήσεων (%d)\n", max_count);
            break;
        }

        temps[count++] = value;
    }

    fclose(fp);

    if (skipped > 0) {
        printf("Σύνολο γραμμών που αγνοήθηκαν λόγω μη έγκυρων δεδομένων: %d\n", skipped);
    }

    return count;
}

Statistics compute_statistics(double temps[], int count) {
    Statistics stats;
    memset(&stats, 0, sizeof(stats));

    if (count == 0) {
        return stats;
    }

    stats.count = count;
    stats.min = temps[0];
    stats.max = temps[0];

    for (int i = 0; i < count; i++) {
        stats.sum += temps[i];
        if (temps[i] < stats.min) stats.min = temps[i];
        if (temps[i] > stats.max) stats.max = temps[i];
    }

    stats.average = stats.sum / count;

    /* Τυπική απόκλιση (πληθυσμιακή) */
    double sq_diff_sum = 0.0;
    for (int i = 0; i < count; i++) {
        double diff = temps[i] - stats.average;
        sq_diff_sum += diff * diff;
    }
    stats.stddev = sqrt(sq_diff_sum / count);

    return stats;
}

void write_report(const char *output_filename, Statistics stats, double temps[]) {
    FILE *out = fopen(output_filename, "w");
    if (out == NULL) {
        fprintf(stderr, "Error: The report file could not be created '%s'\n", output_filename);
        return;
    }

    FILE *targets[2] = { out, stdout };

    for (int t = 0; t < 2; t++) {
        FILE *f = targets[t];
        fprintf(f, "==============================================\n");
        fprintf(f, "        REPORT ON RECORDED TEMPERATURES\n");
        fprintf(f, "==============================================\n\n");

        if (stats.count == 0) {
            fprintf(f, "No valid temperature readings were found.\n");
        } else {
            fprintf(f, "Number of measurements : %d\n", stats.count);
            fprintf(f, "Average                : %.2f °C\n", stats.average);
            fprintf(f, "Minimum value          : %.2f °C\n", stats.min);
            fprintf(f, "Maximum value          : %.2f °C\n", stats.max);
            fprintf(f, "Standard deviation     : %.2f °C\n", stats.stddev);
            fprintf(f, "\n----------------------------------------------\n");
            fprintf(f, "All measurements:\n");
            for (int i = 0; i < stats.count; i++) {
                fprintf(f, "  [%3d] %.2f °C\n", i + 1, temps[i]);
            }
        }
        fprintf(f, "\n==============================================\n");
    }

    fclose(out);
    printf("\nThe report was saved to the file: %s\n", output_filename);
}
