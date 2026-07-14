# sensor_logger

Πρόγραμμα σε C για ανάγνωση, επεξεργασία και αναφορά (report)
θερμοκρασιών που έχουν καταγραφεί από αισθητήρα (sensor).

## Δομή project

```
sensor_logger/
│
├── data/
│     measurements.txt      # Δεδομένα εισόδου (μία θερμοκρασία ανά γραμμή)
│
├── include/
│     sensor.h              # Δηλώσεις δομών / συναρτήσεων
│
├── src/
│     main.c                # Κύριο πρόγραμμα (entry point)
│     sensor.c              # Υλοποίηση ανάγνωσης / στατιστικών / report
│
├── output/
│     report.txt            # Παράγεται/ενημερώνεται αυτόματα
│
├── Makefile
└── README.md
```

## Μεταγλώττιση

Με χρήση του Makefile:

```bash
make
```

Ή χειροκίνητα:

```bash
gcc -Wall -Wextra -Iinclude -o sensor_logger src/main.c src/sensor.c -lm
```

## Εκτέλεση

Με τα default paths (`data/measurements.txt` -> `output/report.txt`):

```bash
./sensor_logger
```

ή:

```bash
make run
```

Με προσαρμοσμένα αρχεία εισόδου/εξόδου:

```bash
./sensor_logger data/measurements.txt output/report.txt
./sensor_logger path/to/other_data.txt path/to/other_report.txt
```

## Μορφή αρχείου εισόδου

Μία θερμοκρασία ανά γραμμή (δεκαδικός αριθμός):

```
23.5
24.1
22.8
19.9
```

Κενές γραμμές αγνοούνται σιωπηλά. Γραμμές που δεν περιέχουν
έγκυρο αριθμό αγνοούνται με προειδοποίηση στο stderr.

## Έξοδος (report)

Το `output/report.txt` περιέχει:

- Πλήθος έγκυρων μετρήσεων
- Μέσο όρο
- Ελάχιστη και μέγιστη τιμή
- Τυπική απόκλιση
- Πλήρη λίστα των μετρήσεων

Το ίδιο περιεχόμενο εμφανίζεται και στην οθόνη κατά την εκτέλεση.

## Καθαρισμός

```bash
make clean
```
