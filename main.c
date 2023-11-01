#include <stdio.h>
#include <stdlib.h>

// Function to open an existing database file or create a new one
void openFile();

// Function to save records to the database file
void saveFile();

// Function to display all records


// Function to insert a new record


// Function to query a record


// Function to update a record's value


// Function to delete a record


int main() {
    char filename[30];
    int cmd;
    char data[256][256];
    int recordCount = 0;

    printf("Please enter a filename: \n");
    scanf("%s", filename);

    openFile(filename, data, &recordCount);
    saveFile(filename, data, &recordCount);

    while (1)
    {
        printf("Enter a command (0: SHOW ALL ,1: INSERT ,2: QUERY ,3: UPDATE ,4: DELETE ,5: SAVE ,6: EXIT): \n");
        scanf("%d", &cmd);

        if (cmd == 0) {
            // Code for showing all records goes here
        }
        // Add more cases for other commands as needed
    }

    return 0;
}

void openFile(char* filename, char data[][256], int* recordCount) {
	FILE* file;
	file = fopen(filename, "r");

	if (file != NULL) {
		printf("File found. Loading database...\n");
		// Read data from the file and update data and recordCount accordingly
		fclose(file);
	}
	else {
		printf("File not found. Creating a new database.\n");
		// Initialize data and recordCount if necessary
		*recordCount = 0;
	}
}

void saveFile(const char* filename, char data[][256], int recordCount) {
    FILE* file = fopen(filename, "w");

    if (file != NULL) {
        for (int i = 0; i < recordCount; i++) {
            fprintf(file, "%s\n", data[i]);
        }
        fclose(file);
        printf("Database saved.\n");
    }
    else {
        printf("Error: Unable to open file for writing.\n");
    }
}