// File: guess.cpp
// Purpose: Play a little guessing game.
// Author: CISP1020 Class
#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

int main()
{
	int num;	// Our secret number

	// seed the random number generator PRNG
	srand(time(0));

	//Generate a Secret Number (between 1 and 100)
	num = rand() % 100 + 1;

	do {
		//Get a guess from the user
		int guess;
		cout << "Guess a number between 1 and 100> ";
		cin >> guess;

		//print our response
		if(guess > num) {
			cout << "Too High" << endl;
		} else if(guess < num) {
			cout << "Too Low" << endl;
		} else {
			cout << "Correct" << endl;
		}
	} while(num != guess);
}
