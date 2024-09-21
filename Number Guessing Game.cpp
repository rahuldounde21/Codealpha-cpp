#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(time(0)); 

    int secretNumber = rand() % 100 + 1; 
    int guess;
    int attempts = 0;

    cout << "Let's play a number guessing game!\n";
    cout << "I've chosen a number between 1 and 100. Can you guess it?\n";

    while (true) {
        cout << "Enter your guess: ";
        cin >> guess;

        attempts++;

        if (guess == secretNumber) {
            cout << "Congratulations! You guessed the number in " << attempts << " attempts.\n";
            break;
        } else if (guess < secretNumber) {
            cout << "Too low! Try again.\n";
        } else {
            cout << "Too high! Try again.\n";
        }
    }

    return 0;
}