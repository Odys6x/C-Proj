#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX_RECORDS 256
#define MAX_LENGTH 256

// Function to open an existing database file or create a new one
void openFile();

// Function to save records to the database file
void saveFile();

// Function to display all records
void showAllRecords();

// Function to insert a new record
void insertRecord();

// Function to query a record
int queryRecord();

// Function to update a record's value
void updateRecord();

// Function to delete a record
void deleteRecord();

int main() {
    char filename[30];
    int cmd;
    char *data[MAX_RECORDS][2];// Initialize data with 0 (NULL)
    int recordCount = 0;
    char key[256];
    char value[256];
    char choice[2];

    printf("Welcome to EzDB!!!\n");
    printf("------------------------\n");
    printf("Please enter a filename: \n");
    scanf("%s", filename);

    openFile(filename, data, &recordCount);
    
    while (1) {
        // printf("Enter a command (0: SHOW ALL, 1: INSERT, 2: QUERY, 3: UPDATE, 4: DELETE, 5: SAVE, 6: EXIT): \n");
        printmenu();
        scanf("%d", &cmd);
        fflush(stdin);
        if (cmd == 0) {
            showAllRecords(data,&recordCount,filename);

        }
        else if (cmd == 1) {
            printf("Enter a key: \n");
            scanf("%s", key); 
            printf("Enter a value: \n");
            scanf("%s", value);
            insertRecord(data, &recordCount, key, value);
            saveFile(filename, data, recordCount);

        }
        else if (cmd == 2) {
            printf("Enter a key: \n");
            scanf("%s", key);
            queryRecord(data,key,recordCount);

        }
        else if (cmd == 3) {
            printf("Enter a key: \n");
            scanf("%s", key);
            printf("Enter the new value: \n");
            scanf("%s", value);
            updateRecord(data, recordCount, key, value);
            // printf("Updated\n");
            //saveFile(filename, data, recordCount);

        }
        else if (cmd ==4){
            printf("Enter the key you want to delete: \n");
            scanf("%s", key);
            int found= queryRecord(data,key,recordCount);
            if (found==1){
                fflush(stdin);
                printf("Are you sure that you want to delete '%s'? (input n for no, and y for yes)\n", key);
                fflush(stdin);
                scanf("%s", choice);
                printf("choice is %s\n", choice);
                if (strcmp(choice,"y")==0){
                    deleteRecord(data,key,&recordCount);
                    printf("Deleted\n");
                    showAllRecords(data,&recordCount,filename);
                    // saveFile(filename, data, recordCount);
                }
            }
        }
        else if (cmd == 5) {
            saveFile(filename, data, recordCount);

        }
        else if (cmd == 6){
            printf("Goodbye!");
            break;

        }
        // Add more cases for other commands as needed
    }
    // for (int i = 0; i < MAX_RECORDS; i++) {
    //     for (int j = 0; j < 2; j++) {
    //         free(data[i][j]);
    //     }
    //     free(data[i]);
    // }

    // Free allocated memory
    for (int i = 0; i < MAX_RECORDS; i++) {
        free(data[i][0]);
        free(data[i][1]);
        free(data[i]);
    }
    free(data);

    return 0;
}
void printmenu(){
    const char *options[] = {
        "0: SHOW ALL",
        "1: INSERT",
        "2: QUERY",
        "3: UPDATE",
        "4: DELETE",
        "5: SAVE",
        "6: EXIT"
    };
    int numOptions = sizeof(options) / sizeof(options[0]);
    int longestOptionLength = 0;

    // Find the length of the longest option
    for (int i = 0; i < numOptions; i++) {
        int length = strlen(options[i]);
        if (length > longestOptionLength) {
            longestOptionLength = length;
        }
    }

    int padding = 4; // You can adjust this padding
    int totalLength = longestOptionLength + padding * 2;

    // Top border
    printf("+");
    for (int i = 0; i < totalLength; i++) {
        printf("-");
    }
    printf("+\n");

    // Options
    for (int i = 0; i < numOptions; i++) {
        printf("|");
        int spaces = (totalLength - strlen(options[i])) / 2;
        for (int j = 0; j < spaces; j++) {
            printf(" ");
        }
        printf("%s", options[i]);
        for (int j = 0; j < spaces; j++) {
            printf(" ");
        }
        // Adjust for odd totalLength
        if ((strlen(options[i]) + 2 * spaces) < totalLength) {
            printf(" ");
        }
        printf("|\n");
    }

    // Bottom border
    printf("+");
    for (int i = 0; i < totalLength; i++) {
        printf("-");
    }
    printf("+\n");

}

void convertToLowercase(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
}

void openFile(char* filename, char *data[MAX_RECORDS][2], int* recordCount) {

    FILE* file;
    file = fopen(filename, "r");
    int i = 0;
    char key[256];
    char value[256];
    
    if (file != NULL) {
        printf("File found. Loading database...\n");
        // fscanf(file, "%s %s"); //key value
        // Read data from the file and update data and recordCount accordingly
        while (fscanf(file, "%s %s", key, value) == 2) {
            (*recordCount)++; //mango lemon apple orange
        }

    }
    else {
        printf("File not found. Creating a new database.\n");
        // Initialize data and recordCount if necessary
        *recordCount = 0;
    }

    // Bring back to first row
    rewind(file);

     while (i <= *recordCount && fscanf(file, "%s %s", key, value) == 2){
        // memory allocation
        data[i][0] = (char *)malloc(sizeof(char) * strlen(key));
        data[i][1] = (char *)malloc(sizeof(char) * strlen(value));

        strcpy(data[i][0], key);
        strcpy(data[i][1], value);
        i++;
    }
    fclose(file);

    // Remember to delete
    // printf("\nDone loading...\n");
    // // Print out data
    // for (int x = 0; x < *recordCount; x++){
    //     printf("key : %s, value : %s\n", data[x][0], data[x][1]);
    // }
    
}

void saveFile(const char* filename, char *data[MAX_RECORDS][2], int recordCount) {
    printf("Filename = %s\n", filename);
    FILE* file = fopen(filename, "w");

    if (file != NULL) {

        for (int i = 0; i < recordCount; i++) {
            fprintf(file, "%s %s\n", data[i][0], data[i][1]);
        }

        fclose(file);
        printf("Database saved.\n");
    }
    else {
        printf("Error: Unable to open file for writing.\n");
    }
}

void insertRecord(char *data[MAX_RECORDS][2], int *recordCount, const char* key, const char* value) {
    
    const int count = *recordCount;
    if (*recordCount >= MAX_RECORDS) {
        printf("Error: Maximum record count reached.\n");
        return;
    }

    for (int i = 0; i < (*recordCount) ; i += 1) {

        char dataCpy[strlen(data[i][0]) + 1];
        strncpy(dataCpy, data[i][0], strlen(data[i][0]));
        dataCpy[strlen(data[i][0])] = '\0';
        
        char keyCpy[strlen(key) + 1];
        strncpy(keyCpy, key, strlen(key));
        keyCpy[strlen(key)] = '\0';

        convertToLowercase(dataCpy);
        convertToLowercase(keyCpy);

        if (strcmp(dataCpy, keyCpy) == 0) {
            printf("Cannot enter duplicate keys.\n");
            return;
        }
    }

    // Create space for new data and insert data
    data[count][0] = (char *)malloc(sizeof(char) * (strlen(key)));
    data[count][1] = (char *)malloc(sizeof(char) * (strlen(value)));

    strcpy(data[count][0], key);
    strcpy(data[count][1], value);
    (*recordCount)++;

    printf("A new record of Key=%s, Value=%s is successfully inserted.\n", key, value);
}

int queryRecord(char *data[MAX_RECORDS][2], char* key, int recordCount) {
    int found = 0;
    printf("recordcount=%d\n", recordCount);
    printf("key is %s\n", key);
    printf("strlen(key) is %d\n", strlen(key));
    for(int x=0; x< recordCount; x++){

        char dataCpy[strlen(data[x][0]) + 1];
        strncpy(dataCpy, data[x][0], strlen(data[x][0]));
        dataCpy[strlen(data[x][0])] = '\0';
        
        char keyCpy[strlen(key) + 1];
        strncpy(keyCpy, key, strlen(key));
        keyCpy[strlen(key)] = '\0';

        convertToLowercase(dataCpy);
        convertToLowercase(keyCpy);

        if(strcmp(dataCpy, keyCpy) == 0) {
            found =1;
            printf("Query found!\n");
            printf("Your search result for value of %s is %s\n",key, data[x][1]);

            break;
        }
    }
    if (found==0){
        printf("Your search result of keyword %s is empty.\n",key);
    }
    return found;
}

void showAllRecords(char *data[MAX_RECORDS][2], int *recordCount, char* filename) {

    if (*recordCount == 0) {
        printf("There is nothing here . . . \n", filename);
        return;
    }

    printf("The %s file contains \n", filename);

    for (int i = 0; i < (*recordCount); i += 1) {
        printf("%s %s\n", data[i][0], data[i][1]);
    }
}

void updateRecord(char *data[MAX_RECORDS][2], int recordCount, const char* key, char *value) {
    const int count = recordCount;

    if (recordCount == 0) {
        printf("There is nothing to update !!!\n");
        return;
    }

    int found = 0;
    for (int i = 0; i < recordCount; i++){
        
        char dataCpy[strlen(data[i][0]) + 1];
        strncpy(dataCpy, data[i][0], strlen(data[i][0]));
        dataCpy[strlen(data[i][0])] = '\0';
        
        char keyCpy[strlen(key) + 1];
        strncpy(keyCpy, key, strlen(key));
        keyCpy[strlen(key)] = '\0';

        convertToLowercase(dataCpy);
        convertToLowercase(keyCpy);

        if (strcmp(dataCpy, keyCpy) == 0){
            // Free out space for previous value
            free(data[i][1]);

            // Create space for new value
            data[i][1] = (char *)malloc(sizeof(char) * strlen(value));
            // data[i][1] = value;
            strcpy(data[i][1], value);
            found = 1;
        }
        // else {
        //     printf("There is no record for the key %s", key);
        // }
    }
    if (found == 0){
        printf("There is no record for the key %s.\n", key);
        return;
    }


    printf("Record of Key=%s, Value=%s is successfully updated.\n", key, value);
}

void deleteRecord(char *data[MAX_RECORDS][2], char* key, int *recordCount) { 
    for(int x=0; x< *recordCount; x++){
        char dataCpy[strlen(data[x][0]) + 1];
        strncpy(dataCpy, data[x][0], strlen(data[x][0]));
        dataCpy[strlen(data[x][0])] = '\0';
        char keyCpy[strlen(key) + 1];
        strncpy(keyCpy, key, strlen(key));
        keyCpy[strlen(key)] = '\0';
        convertToLowercase(dataCpy);
        convertToLowercase(keyCpy);
        if (strcmp(dataCpy, keyCpy) == 0) {
            for (int i = x; i < *recordCount - 1; i++) { 
                data[i][0] = data[i + 1][0]; 
                data[i][1] = data[i + 1][1];
            }
            data[*recordCount-1][0]="\0";
            data[*recordCount-1][1]="\0";
            (*recordCount)--; 
            break;
        }
    }
}