#include <ctype.h>
#include <stdio.h>
#include <string.h>


int searchPattern(char* text, char* pattern, int sensitive) {
    int textLength = strlen(text); //length of text
    int patternLength = strlen(pattern); //length of pattern you wanna find

    for (int i = 0; i < textLength; i++) { //a for loop from index 0 to end of index of text
        int match = 1; // this will help us to determine if matches or not (1 being true and 0 being false)
        for (int j = 0; j < patternLength; j++) { //a for loop from index 0 to end of index of pattern
            if (pattern[j] == '.') //checks if the pattern at index j is a .
                continue; // if it is a . , it will continue to the next iteration of the loop
            if (pattern[j] == '_') { //checks if the pattern at index j has an underscore
                if (!isspace(text[i + j])) { //checks if the text at index i + j is not a space
                    //if j = 1 (pattern only got 2 characters in total), then it will check 2 character in text one at a time)
                    match = 0; // change match to 0 meaning to say it does not match
                    break; // break because if text has no space while pattern has underscore just break the loop no point looping
                }
            }
            else { // if there is no underscore or . performs normal search pattern
                if (sensitive) { //checks if user wants it to be Case sensitive
                    if (text[i + j] != pattern[j]) { //checks if the text at index i + j is not the same as pattern at index j
                        match = 0; // change match to 0 meaning to say it does not match
                        break; //break because pattern does not match in text even in the case of ("Cat" and "cat")
                    }
                }
                else { // if user wants it to be Case insensitive
                    if (tolower(text[i + j]) != tolower(pattern[j])) { //make everything in lowercase since user only wants to find letters without case sensitive
                        match = 0; // change match to 0 meaning to say it does not match
                        break; //break because pattern does not match in text
                    }
                }
            }
        }
        if (match) //after going through check process if there are no issues from the checks above then pattern matches in text
            return i; // return the 1st index occurance when pattern is found
    }

    return -1; // pattern not found
}

int main() { //your main function always put it below your functions else it cannot detect functions below it
    char text[255]; //limit text to 255 characters
    char pattern[255]; //limit pattern to 255 characters
    int sensitive; // declare a variable to handle if user wants it to be case sensitive or not

    // Get input from the user
    printf("Enter a line of text (up to 255 characters):\n");
    fgets(text, sizeof(text), stdin); //gets input from user and stores it in text, restricting size of text by sizeof(text) (stdin --> standard input)
    printf("Enter a pattern (up to 255 characters):\n");
    fgets(pattern, sizeof(pattern), stdin); //gets input from user and stores it in pattern
    printf("Case sensitivity (0 for insensitive, 1 for sensitive): ");
    scanf("%d", &sensitive); //gets input from user and stores it in sensitive

    // Remove the newline character at the end of the strings
    text[strcspn(text, "\n")] = '\0';
    pattern[strcspn(pattern, "\n")] = '\0';

    int index; // declare variable
    index = searchPattern(text, pattern, sensitive); //input the text, pattern, and sensitive
    //returns the index of the first occurance of the pattern in the text or -1 if not found


    // Output results
    if (index != -1) { // if pattern is found in text
        printf("Matches at position %d.\n", index); //pring out the index of the first occurance of the pattern in the text
    }
    else { // if pattern is not found in text
        printf("No match.\n"); //print out no match
    }

    return 0;
}