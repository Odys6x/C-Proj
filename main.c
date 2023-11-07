#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_RECORDS 256
#define MAX_LENGTH 256

// Function to open an existing database file or create a new one
void openFile();

// Function to save records to the database file
void saveFile();

// Function to display all records


// Function to insert a new record
void insertRecord();

// Function to query a record
void query();

// Function to update a record's value


// Function to delete a record


int main() {
    char filename[30];
    int cmd;
    char data[256][256] = { {0} };
    char append[256] = {0};// Initialize data with 0 (NULL)
    int recordCount = 0;
    char key[256];
    char value[256];

    printf("Please enter a filename: \n");
    scanf("%s", filename);

    openFile(filename, data, &recordCount);

    while (1) {
        printf("Enter a command (0: SHOW ALL ,1: INSERT ,2: QUERY ,3: UPDATE ,4: DELETE ,5: SAVE ,6: EXIT): \n");
        scanf("%d", &cmd);

        if (cmd == 1) {
                printf("Enter a key: \n");
                scanf("%s", key); 
                printf("Enter a value: \n");
                scanf("%s", value);
                insertRecord(append, &recordCount, key, value,data);
                saveFile(filename, append, recordCount);
           
        }
        else if (cmd == 2) {
            printf("Enter a key: \n");
            scanf("%s", key);
            query(data,key,recordCount);

        }
        // Add more cases for other commands as needed
    }
    for (int i = 0; i < MAX_RECORDS; i++) {
        for (int j = 0; j < 2; j++) {
            free(data[i][j]);
        }
        free(data[i]);
    }
    free(data);

    return 0;
}

void openFile(char* filename, char(*data)[2][MAX_RECORDS], int* recordCount) {
    FILE* file;
    file = fopen(filename, "r");

    if (file != NULL) {
        printf("File found. Loading database...\n");
        // Read data from the file and update data and recordCount accordingly
        while (fscanf(file, "%s %s", data[*recordCount][0], data[*recordCount][1]) == 2) {
            (*recordCount)++;
        }
        fclose(file);
    }
    else {
        printf("File not found. Creating a new database.\n");
        // Initialize data and recordCount if necessary
        *recordCount = 0;
    }
}

void saveFile(const char* filename, char(*append)[256], int recordCount) {
    FILE* file = fopen(filename, "a");

    if (file != NULL) {
        fprintf(file, "%s %s\n", append[0], append[1]);
        fclose(file);
        printf("Database saved.\n");
    }
    else {
        printf("Error: Unable to open file for writing.\n");
    }
}


void insertRecord(char(*append)[256], int* recordCount, const char* key, const char* value, char data[256][256]) {
    if (*recordCount >= MAX_RECORDS) {
        printf("Error: Maximum record count reached.\n");
        return;
    }


    for (int i = 0; i < *recordCount; i++) {
        if (strcmp(data[i][0], key[i]) == 0) {
            printf("The record with Key=%s already exists in the database.\n", key);
            return;
        }
    }

    strcpy(append[0], key);
    strcpy(append[1], value);

    (*recordCount)++;
    printf("A new record of Key=%s, Value=%s is successfully inserted.\n", key, value);
}
void query(const char data[2][MAX_RECORDS], char keyword, int recordCount){
    int found = 0;
    for(int x=0; x< recordCount; x++){
        if(strcmp(data[x][0],keyword)==0){
            found =1;
            printf("Query found!\n");
            printf("Your search result of keyword: %s is %s\n",keyword, data[x][1]);

            break;
        }
    }
    if (found==0){
        printf("Query not found, your search result of keyword %s is empty.\n",keyword);
    }
}
