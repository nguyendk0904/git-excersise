#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int createRandomNum() {
	return rand() % 100 + 1;
}

int getPlayerGuess() {
	while (true) {
		int guess;
		cout<< endl << "Enter your guess (from 1 to 100): ";
		cin >> guess;
		
		if (guess < 1 || guess > 100) {
			cin.clear();
			cin.ignore();
			cout << "Nah. How about a number between 1 and 100?" << endl;
		}
		else {
			return guess;
		}
	}
}

void printAns (int guess, int secret) {
	if (guess > secret) {
		cout << "Oh no it's too big! Try a smaller one!";
	}
	
	else if (guess < secret) {
		cout << "Nah i'm not that small! I'm bigger!";
	}
	
	else {
		cout << "Bingo! You guessed it right!!" << endl;
	}
	cout << endl;	
}

void gamePlay() {
    char playAgain;
    
    do {
        int secretNum = createRandomNum();
        int guess;
        int score = 10;

        cout << "Welcome to Guess It!" << endl;
        
        do {
            guess = getPlayerGuess();
            if (guess != secretNum) {
            	score--;
			}
            printAns(guess, secretNum);
        } while (guess != secretNum);
		
		cout << "Your final score is: " << score << endl;
        cout << endl << endl << "Wanna play again? (y/n): ";
        cin >> playAgain;

        cin.ignore();

    } while (playAgain == 'y' || playAgain == 'Y');

    cout << endl << "Thanks for playing! Goodbye!";
}
int main() {
	srand(time(0));
	gamePlay();
	return 0;
}
