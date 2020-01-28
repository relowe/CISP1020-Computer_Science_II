// File: guess.cpp
// Purpose: Play a little guessing game.
// Author: CISP1020 Class
#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

//Function Prototypes
int pick_secret();
int get_guess();
void print_response(int num, int guess);

int main()
{
	int num = pick_secret();	//our secret number
	int guess;			//"human" player's guess
	int score=0;			//number of guesses

	do {
		guess = get_guess();
		print_response(num, guess);
		score++;  		//count the guesses
	} while(num != guess);

	//print the final score
	cout << "You used " << score << " guesses." << endl;
}


// get the user's guess
int get_guess()
{
	int guess;
	bool valid;  //is the input valid?

	//Get a guess from the user
	do {
		cout << "Guess a number between 1 and 100> ";
		cin >> guess;

		//detect and handle errors
		valid = cin;
		if(!valid) {
			cout << "Invalid entry. Please try again." << endl;
			cin.clear(); 		  //clear the error flag
			while(cin.get() != '\n'); //consume the rest of the line
		}
	} while(!valid);

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


// Select our secret number
int pick_secret()
{	
	// seed the random number generator PRNG
	srand(time(0));

	//Generate a Secret Number (between 1 and 100)
	return rand() % 100 + 1;
}
