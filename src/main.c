/*
 * main.c
 * -----------------------------------------------------------
 * Κύριο πρόγραμμα του sensor_logger.
 * Διαβάζει θερμοκρασίες από αρχείο (default: data/measurements.txt),
 * τις επεξεργάζεται και παράγει report στο output/report.txt.
 *
 * Χρήση:
 *   ./sensor_logger [input_file] [output_file]
 *
 * Αν δεν δοθούν ορίσματα, χρησιμοποιούνται τα default paths:
 *   data/measurements.txt  ->  output/report.txt
 * -----------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sensor.h"

#define DEFAULT_INPUT  "data/measurements.txt"
#define DEFAULT_OUTPUT "output/report.txt"

int main(int argc, char *argv[]) {
    const char *input_file  = (argc >= 2) ? argv[1] : DEFAULT_INPUT;
    const char *output_file = (argc >= 3) ? argv[2] : DEFAULT_OUTPUT;

    /* Δυναμική δέσμευση μνήμης για τις μετρήσεις */
    double *temps = malloc(MAX_READINGS * sizeof(double));
    if (temps == NULL) {
        fprintf(stderr, "Error: memory allocation failure.\n");
        return EXIT_FAILURE;
    }

    printf("Reading temperatures from: %s\n", input_file);

    int count = read_temperatures(input_file, temps, MAX_READINGS);
    if (count < 0) {
        free(temps);
        return EXIT_FAILURE;
    }

    Statistics stats = compute_statistics(temps, count);
    write_report(output_file, stats, temps);

    free(temps);
    return EXIT_SUCCESS;
}
