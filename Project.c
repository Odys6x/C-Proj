#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure to represent data records
typedef struct {
    char key[256];
    char value[256];
} Record;

// Function to open an existing database file or create a new one
void openDatabase(const char* filename, Record** records, int* recordCount);

// Function to save records to the database file
void saveDatabase(const char* filename, Record* records, int recordCount);

// Function to display all records
void showAllRecords(Record* records, int recordCount);

// Function to insert a new record
void insertRecord(Record** records, int* recordCount, const char* key, const char* value);

// Function to query a record
void queryRecord(Record* records, int recordCount, const char* key);

// Function to update a record's value
void updateRecord(Record* records, int recordCount, const char* key, const char* newValue);

// Function to delete a record
void deleteRecord(Record** records, int* recordCount, const char* key);

int main(void) {
    char filename[256];
    printf("Enter the database filename: ");
    scanf("%s", filename);

    Record* records = NULL;
    int recordCount = 0;

    openDatabase(filename, &records, &recordCount);

    char command[10];
    while (1) {
        printf("Enter a command (SHOW ALL, INSERT, QUERY, UPDATE, DELETE, SAVE, EXIT): ");
        scanf("%s", command);

        if (strcmp(command, "SHOW") == 0 || strcmp(command, "ALL") == 0) {
            showAllRecords(records, recordCount);
        }
        else if (strcmp(command, "INSERT") == 0) {
            char key[256];
            char value[256];
            printf("Enter key and value: ");
            scanf("%s %s", key, value);
            insertRecord(&records, &recordCount, key, value);
        }
        else if (strcmp(command, "QUERY") == 0) {
            char key[256];
            printf("Enter the key to query: ");
            scanf("%s", key);
            queryRecord(records, recordCount, key);
        }
        else if (strcmp(command, "UPDATE") == 0) {
            char key[256];
            char newValue[256];
            printf("Enter key and new value: ");
            scanf("%s %s", key, newValue);
            updateRecord(records, recordCount, key, newValue);
        }
        else if (strcmp(command, "DELETE") == 0) {
            char key[256];
            printf("Enter the key to delete: ");
            scanf("%s", key);
            deleteRecord(&records, &recordCount, key);
        }
        else if (strcmp(command, "SAVE") == 0) {
            saveDatabase(filename, records, recordCount);
        }
        else if (strcmp(command, "EXIT") == 0) {
            break;
        }
        else {
            printf("Invalid command. Please try again.\n");
        }
    }

    free(records); // Release memory before exiting

    return 0;
}

// Function to open an existing database file or create a new one
void openDatabase(const char* filename, Record** records, int* recordCount) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("File not found. Creating a new database.\n");
        *records = (Record*)malloc(0);
        *recordCount = 0;
    }
    else {
        *recordCount = 0;
        while (fscanf(file, "%s %s", (*records)[*recordCount].key, (*records)[*recordCount].value) == 2) {
            (*recordCount)++;
            *records = (Record*)realloc(*records, (*recordCount) * sizeof(Record));
        }
        fclose(file);
    }
}

// Function to save records to the database file
void saveDatabase(const char* filename, Record* records, int recordCount) {
    FILE* file = fopen(filename, "w");
    for (int i = 0; i < recordCount; i++) {
        fprintf(file, "%s %s\n", records[i].key, records[i].value);
    }
    fclose(file);
    printf("Database saved.\n");
}

// Function to display all records
void showAllRecords(Record* records, int recordCount) {
    printf("There are in total %d records found:\n", recordCount);
    for (int i = 0; i < recordCount; i++) {
        printf("%s %s\n", records[i].key, records[i].value);
    }
}

// Function to insert a new record
void insertRecord(Record** records, int* recordCount, const char* key, const char* value) {
    for (int i = 0; i < *recordCount; i++) {
        if (strcmp((*records)[i].key, key) == 0) {
            printf("The record with Key=%s already exists in the database.\n", key);
            return;
        }
    }

    (*recordCount)++;
    *records = (Record*)realloc(*records, (*recordCount) * sizeof(Record));
    strcpy((*records)[*recordCount - 1].key, key);
    strcpy((*records)[*recordCount - 1].value, value);
    printf("A new record of Key=%s, Value=%s is successfully inserted.\n", key, value);
}

// Function to query a record
void queryRecord(Record* records, int recordCount, const char* key) {
    for (int i = 0; i < recordCount; i++) {
        if (strcmp(records[i].key, key) == 0) {
            printf("A record of Key=%s, Value=%s is found in the database.\n", key, records[i].value);
            return;
        }
    }
    printf("There is no record with Key=%s found in the database.\n", key);
}

// Function to update a record's value
void updateRecord(Record* records, int recordCount, const char* key, const char* newValue) {
    for (int i = 0; i < recordCount; i++) {
        if (strcmp(records[i].key, key) == 0) {
            strcpy(records[i].value, newValue);
            printf("The value for the record of Key=%s is successfully updated.\n", key);
            return;
        }
    }
    printf("There is no record with Key=%s found in the database.\n", key);
}

// Function to delete a record
void deleteRecord(Record** records, int* recordCount, const char* key) {
    int found = 0;
    for (int i = 0; i < *recordCount; i++) {
        if (strcmp((*records)[i].key, key) == 0) {
            for (int j = i; j < *recordCount - 1; j++) {
                strcpy((*records)[j].key, (*records)[j + 1].key);
                strcpy((*records)[j].value, (*records)[j + 1].value);
            }
            (*recordCount)--;
            *records = (Record*)realloc(*records, (*recordCount) * sizeof(Record));
            printf("The record of Key=%s is successfully deleted.\n", key);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("There is no record with Key=%s found in the database.\n", key);
    }
}