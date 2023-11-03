#include <stdio.h>

int test() {
    int secretNumber, guess, remainingGuesses = 10;

    // Step 1: Player 1 inputs a number within range
    do {
        printf("Player 1, enter a number between 1 and 1000: ");
        scanf_s("%d", &secretNumber);
        if (secretNumber < 1 || secretNumber > 1000) {
            printf("That number is out of range.\n");
        }
    } while (secretNumber < 1 || secretNumber > 1000);

    // Game loop for Player 2
    for (int round = 1; round <= 10; round++) {
        printf("Player 2, you have %d guesses remaining.\n", remainingGuesses);
        printf("Enter your guess: ");
        scanf_s("%d", &guess);

        // Step 3: Check Player 2's guess
        if (guess < 1 || guess > 1000) {
            printf("That number is out of range.\n");
            continue;
        }
        else if (guess < secretNumber) {
            printf("Too low.\n");
        }
        else if (guess > secretNumber) {
            printf("Too high.\n");
        }
        else {
            printf("Player 2 wins.\n");
            return 0; // Exit the program
        }

        remainingGuesses--;
    }

    // Step 4: Player 1 wins if Player 2 hasn't guessed the number in 10 rounds
    printf("Player 1 wins.\n");

    return 0;
}