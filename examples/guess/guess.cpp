// File: guess.cpp
// Purpose: Play a little guessing game.
// Author: CISP1020 Class
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <time.h>

using namespace std;

//constants
const char *SCORE_FILE=".guess.scores";


//data structures
struct Player
{
    string name;  //Player's Name
    int score;    //Player's Score
};


struct Score_Board
{
    Player player[10];  // List of Players
    int count;          // How many players we have
};


//Function Prototypes
int pick_secret();
int get_guess();
void print_response(int num, int guess);
void load_score_board(Score_Board &top10);
void update_score_board(Score_Board &top10, int score);
void print_score_board(const Score_Board &top10);
void save_score_board(Score_Board &top10);

int main()
{
	int num = pick_secret();	//our secret number
	int guess;                  //"human" player's guess
	int score=0;			    //number of guesses
    Score_Board top10;          //top 10 players

    load_score_board(top10);    //load the scoreboard
    cout << num << endl;

	do {
		guess = get_guess();
		print_response(num, guess);
		score++;  		//count the guesses
	} while(num != guess);

	//print the final score
	cout << "You used " << score << " guesses." << endl;

    //handle the score list
    update_score_board(top10, score);
    print_score_board(top10);
    save_score_board(top10);
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


//Load the scoreboard from the file
void load_score_board(Score_Board &top10)
{
    ifstream file;

    //start with an empty score board
    top10.count = 0;

    //open the file for reading
    file.open(SCORE_FILE);
    if(!file) return;

    //read in the count
    file >> top10.count;
    if(top10.count > 10) {
        top10.count = 10;
    }

    //read in the scores 
    for(int i=0; i < top10.count; i++) {
        //read in player
        file >> top10.player[i].score 
             >> top10.player[i].name;
    }

    file.close();
}


// Add the user to the scoreboard, if they are in the top 10
void update_score_board(Score_Board &top10, int score)
{
    //find the player position
    int place = -1;
    for(int i=0; i < top10.count; i++) {
        //find a player we beat
        if(score < top10.player[i].score) {
            place = i;
            break;
        }
    }

    //handle beating no one
    if(place == -1) {
        if(top10.count == 10) return;  // Full board!
        place = top10.count;
    }

    //grow the list if needed
    if(top10.count != 10) {
        top10.count++;
    }

    //shift down one position
    for(int i = top10.count - 1; i > place; i--) {
        top10.player[i] = top10.player[i-1];
    }

    //put the player in their slot
    top10.player[place].score = score;
    cout << "Congratulations!  You're a top player!" << endl
         << "Enter your name: ";
    cin >> top10.player[place].name;
}


// Display the scoreboard
void print_score_board(const Score_Board &top10)
{
    cout << "TOP 10 Players" << endl
         << setfill('=') << setw(25) << "" << endl;
    for(int i=0; i < top10.count; i++) {
        cout << setfill('.') 
             << left << setw(20) << top10.player[i].name
             << right << setw(5) << top10.player[i].score
             << setfill(' ') << endl;
    }
}


// Save the scoreboard to the file
void save_score_board(Score_Board &top10)
{
    ofstream file;

    //open the file for writing
    file.open(SCORE_FILE);
    if(!file) {
        cout << "Could not open high score file!" << endl;
        return;
    }

    //write the count
    file << top10.count << endl;

    //write the players
    for(int i=0; i<top10.count; i++) {
        file << top10.player[i].score << endl
             << top10.player[i].name << endl;
    }

    file.close();
}


