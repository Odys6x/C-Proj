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
void showAll();

// Function to insert a new record
void insertRecord();

// Function to query a record
void query();

// Function to update a record's value
void update();

// Function to delete a record


int main() {
    char filename[30];
    int cmd;
    char data[256][256] = {0};// Initialize data with 0 (NULL)
    int recordCount = 0;
    char key[256];
    char value[256];

    printf("Please enter a filename: \n");
    scanf("%s", filename);

    openFile(filename, data, &recordCount);

    while (1) {
        printf("Enter a command (0: SHOW ALL ,1: INSERT ,2: QUERY ,3: UPDATE ,4: DELETE ,5: SAVE ,6: EXIT): \n");
        scanf("%d", &cmd);


        if (cmd == 0) {
            
            showAll(data,&recordCount,filename);

        }

        else if (cmd == 1) {
                printf("Enter a key: \n");
                scanf("%s", key); 
                printf("Enter a value: \n");
                scanf("%s", value);
                insertRecord(data, &recordCount, key, value,data);
                saveFile(filename, data, recordCount);

        }
        else if (cmd == 2) {
            printf("Enter a key: \n");
            scanf("%s", key);
            query(data,key,recordCount);

        }

        else if (cmd == 3) {
            printf("Enter a key: \n");
            scanf("%s", key);
            update(data, recordCount, key, value);
            saveFile(filename, data, recordCount);

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

void openFile(char* filename, char(*data)[MAX_RECORDS][MAX_LENGTH], int* recordCount) {
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

void saveFile(const char* filename, char data[MAX_RECORDS][MAX_LENGTH], int recordCount) {
    FILE* file = fopen(filename, "w");

    if (file != NULL) {

        for (int i = 0; i <= recordCount*2; i+=2) {
            fprintf(file, "%s %s\n", data[i], data[i + 1]);
        }

        fclose(file);
        printf("Database saved.\n");
    }
    else {
        printf("Error: Unable to open file for writing.\n");
    }
}

void insertRecord(char data[MAX_RECORDS][MAX_LENGTH], int *recordCount, const char* key, const char* value) {
    const int count = *recordCount;
    if (*recordCount >= MAX_RECORDS) {
        printf("Error: Maximum record count reached.\n");
        return;
    }

    for (int i = 0; i < (*recordCount) * 2; i += 2) {
        if (strcmp(data[i], key) == 0) {
            printf("Cannot enter duplicate keys.\n");
            return;
        }
    }

    strcpy(data[count * 2], key);
    strcpy(data[count *2 + 1], value);
    (*recordCount)++;

    printf("A new record of Key=%s, Value=%s is successfully inserted.\n", key, value);
}

void query(char data[MAX_RECORDS][MAX_LENGTH], char* keyword, int recordCount) {
    int found = 0;
    for(int x=0; x< recordCount*2; x+=2){
        if(strcmp(data[x],keyword) == 0) {
            found =1;
            printf("Query found!\n");
            printf("Your search result of keyword: %s is %s\n",keyword, data[x]);

            break;
        }
    }
    if (found==0){
        printf("Query not found, your search result of keyword %s is empty.\n",keyword);
    }
}

void showAll(char data[MAX_RECORDS][MAX_LENGTH], int* recordCount, char* filename) {

    if (*recordCount == 0) {
        printf("There is nothing here . . . \n", filename);
        return;
    }

    printf("The %s file contains \n", filename);

    for (int i = 0; i <= *recordCount * 2; i += 2) {
        printf("%s %s\n", data[i], data[i + 1]);
    }
}

void update(char data[MAX_RECORDS][MAX_LENGTH], int recordCount, const char* key, const char* value) {
    const int count = recordCount;

    if (recordCount == 0) {
        printf("There is nothing to update !!!\n");
        return;
    }

    for (int i = 0; i < (recordCount) * 2; i += 2) {
        if (strcmp(data[i], key) == 0) {
            printf("Enter a value: \n");
            scanf("%s", value);
            strcpy(data[i+ 1], value);
            return;
        }
    }


    printf("Record of Key=%s, Value=%s is successfully updated.\n", key, value);
}