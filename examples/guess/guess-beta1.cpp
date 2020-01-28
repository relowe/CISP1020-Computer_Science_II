// File: guess.cpp
// Purpose: Play a little guessing game.
// Author: CISP1020 Class
#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

//Function Prototypes
int get_guess();
void print_response(int num, int guess);

int main()
{
	int num;	// Our secret number
	int guess;

	// seed the random number generator PRNG
	srand(time(0));

	//Generate a Secret Number (between 1 and 100)
	num = rand() % 100 + 1;

	do {
		guess = get_guess();
		print_response(num, guess);
	} while(num != guess);
}


// get the user's guess
int get_guess()
{
	int guess;

	//Get a guess from the user
	cout << "Guess a number between 1 and 100> ";
	cin >> guess;

	return guess;
}


// Print the response to a guess
void print_response(int num, int guess)
{
	//print our response
	if(guess > num) {
		cout << "Too High" << endl;
	} else if(guess < num) {
		cout << "Too Low" << endl;
	} else {
		cout << "Correct" << endl;
	}
}
