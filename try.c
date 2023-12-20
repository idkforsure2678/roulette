#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define COIN_INITIAL 100
#define COST_PER_GAME 10


void clearScreen() {
	#ifdef _WIN32
	system("cls");
	#else
	system("clear");
	#endif
}

void shuffleArray(int arr[], int size) {
    int i;
    for (i = size - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

int playRoulette(int *userCoins) {
    int outcomes[] = {1, 1, 1, 2, 2, 3};
    int i, resultCount[3] = {0};

    printf("\nShuffling the roulette...\n");

    for (i = 0; i < 3; ++i) {
    	printf("=============================\n");
        shuffleArray(outcomes, sizeof(outcomes) / sizeof(outcomes[0]));
        printf("Result %d: %d\n", i + 1, outcomes[0]);
        resultCount[outcomes[0] - 1]++;
        printf("=============================\n");
    }

    if (resultCount[0] == 3 || resultCount[1] == 3 || resultCount[2] == 3) {
        int reward = 0;
        if (resultCount[0] == 3) {
        	printf("=============================\n");
            printf("Congratulations! You rolled 3 rocks. You win 50 coins!\n");
            reward = 50;
        } else if (resultCount[1] == 3) {
        	printf("=============================\n");
            printf("Congratulations! You rolled 3 papers. You win 60 coins!\n");
            reward = 60;
        } else if (resultCount[2] == 3) {
        	printf("=============================\n");
            printf("Congratulations! You rolled 3 scissors. You win 70 coins!\n");
            reward = 70;
        }
        *userCoins += reward;
    } else {
        printf("Sorry, no match this time. You lose 10 coins.\n");
        *userCoins -= COST_PER_GAME;
    }

    printf("Your total coins: %d\n", *userCoins);

    printf("Do you want to play again? (1 for Yes, 0 for No): ");
    int playAgain;
    scanf("%d", &playAgain);
    printf("=============================\n");
    clearScreen();

    return playAgain;
}

int main() {
    srand(time(NULL)); 

    int userCoins = COIN_INITIAL;
    int playAgain = 1;

    printf("Welcome to the Roulette Game!\n");

    while (userCoins >= COST_PER_GAME && playAgain) {
    	printf("=============================\n");
        printf("\nCurrent coins: %d\n", userCoins);
        printf("Each game costs %d coins.\n", COST_PER_GAME);
        printf("Press Enter to play...");
        getchar(); 
        getchar(); 

        playAgain = playRoulette(&userCoins);
    }

    printf("Game over. Thanks for playing!\n");

    return 0;
}

