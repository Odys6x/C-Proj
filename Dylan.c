#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 256

void update(int recordcount, FILE* ptr, char *data[recordcount][2]);
void open(const char *filename, FILE** ptr, int *recordcount);
void save(const char *filename, int recordcount, FILE** ptr, char *data[recordcount][2]);

int main() {
    
    char filename[MAX];
    FILE* ptr;
    int recordcount = 0;
    char *data[recordcount][2];


    printf("Please enter the filename with .txt : ");
    scanf("%s", filename);
    //printf("0\n");
    open(filename, &ptr, &recordcount);
    //printf("1\n");
    //Update
    update(recordcount, ptr, data);
    //printf("2\n");

    // Save
    save(filename, recordcount, &ptr, data);
    //printf("3\n");

return 0;
}
void open(const char *filename, FILE** ptr, int *recordcount){

    char key[MAX], value[MAX];

    printf("%s", filename);

    *ptr = fopen(filename, "r");

    if (ptr == NULL){
        printf("\nFile can't be opened.\n");
    }

    // Get recordcount to determine the size of the array
    while (fscanf(*ptr, "%s %s", key, value) == 2){
        (*recordcount)++;
    }
    
    printf("%d\n", *recordcount);
    
    // Rewind to the beginnig
    rewind(*ptr);

}

void update(int recordcount, FILE* ptr, char *data[recordcount][2]){

    char key[MAX], value[MAX];
    int i = 0;

    
    
    while (i <= recordcount && fscanf(ptr, "%s %s", key, value) == 2){
       
        // memory allocation
        data[i][0] = (char *)malloc(sizeof(char) * strlen(key));
        data[i][1] = (char *)malloc(sizeof(char) * strlen(value));

        strcpy(data[i][0], key);
        strcpy(data[i][1], value);
        i++;
    }


    printf("\nPlease enter the key : "); fscanf(stdin, "%s", key);
    printf("\nPlease key in the new value : "), fscanf(stdin, "%s", value);


    for (int i = 0; i < recordcount; i++){
        if (strcmp(data[i][0], key) == 0){
            // Free out space for previous value
            free(data[i][1]);

            // Create space for new value
            data[i][1] = (char *)malloc(sizeof(char) * strlen(value));
            data[i][1] = value;
            printf("\nNew value has been updated...\n");
        }
    }

     // Print out data
    for (int i = 0; i < recordcount; i++){
        printf("key : %s, value : %s\n", data[i][0], data[i][1]);
    }

    // // Close for previous file
    fclose(ptr);
    printf("\nClosed\n");
}

void save(const char* filename, int recordcount, FILE** ptr, char *data[recordcount][2]){
    
    
   *ptr = fopen(filename, "w");

    if (*ptr != NULL) {
        for (int i = 0; i < recordcount; i++) {
            printf("Hello\n");
            fprintf(*ptr, "%s %s\n", data[i][0], data[i][1]);
        }
        fclose(*ptr);
    }

    printf("Data saved\n");

    // Free allocated memory
    for (int i = 0; i < recordcount; i++) {
        free(data[i][0]);
        free(data[i][1]);
        free(data[i]);
    }
    
}
