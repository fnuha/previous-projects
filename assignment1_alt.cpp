/***********************************
** Program: assignment1_alt.cpp
** Author: Faaizah Nuha
** Date: 10/9/2022
** Description: A program that allows a user inputted amount of players to play bowling with randomly generated scores, and tracks their scores.
** Input: User inputs name, and then presses enter to roll. User can also restart or quit after each game.
** Output: The pins the user has knocked down, and the score of the user are both printed after every roll.
***********************************/
#include <iostream>
#include <string>
#include <stdlib.h> /* srand, rand functions */
#include <time.h> /* time */
#include <iomanip> /* for setw() */

using namespace std;

/******************************
** Function: roll
** Description: Rolling a random amount of pins knocked down when there is a full set of pins
** Parameters: None
** Pre-conditions: Must be in the first part of a frame
** Post-conditions: The rolled number is returned, so that the next function can determine how many pins are left standing
******************************/
int roll() {
    int roll;
    roll = rand() % 11;
    return roll;
    }

/******************************
** Function: roll2nd
** Description: Rolling a random amount of pins knocked down when there is only a certain amount of pins standing
** Parameters: score, which is the previous amount of pins knocked down
** Pre-conditions: There must be an integer provided that represents the amount of pins knocked down from the first part of the frame
** Post-conditions: The second rolled number is returned, so that the function can determine how many pins are left standing at the end of the frame
******************************/
int roll2nd(int score) {
    int roll;
    roll = rand() % (11 - score);
    return roll;
    }

/******************************
** Function: printFrameScore
** Description: This function prints the calculated score row for each player, using setw to properly align everything
** Parameters: total, which is the current totaled score, must be passed in so that there is something to print out
** Pre-conditions: There must be a calculated score passed in
** Post-conditions: The total is printed out, but nothing is returned
******************************/
void printFrameScore (int total) {//printing the score
    cout << "|";
    cout << setw(5);
    cout << total;
}

/******************************
** Function: calculateTenthFrameScore
** Description: This function checks to see if the tenth frame has been rolled, and if so, calculates the score of the tenth frame, which is also the final score. 
                This final score is passed onto an array called finalScoreArray in order for all the final scores of each player to be printed out later on.
** Parameters:  This function requires the current player's number in the form of the integer player, the array of pins knocked down, which is scoreArray, the total
                score from before the tenth frame, which is the integer total, and finally, the finalScoreArray, which will be where the final scores are storede.
** Pre-conditions: It must be the tenth frame for this function to proceed.
** Post-conditions: The final scores will be calculated and returned, as well as stored in the finalScoreArray.
******************************/
int calculateTenthFrameScore (int player, int *scoreArray[], int total, int finalScoreArray[]) {
    if (scoreArray[player][18] != -1) {
        if ((scoreArray[player][18] + scoreArray[player][19]) >= 10 && scoreArray[player][19] != -1 && scoreArray[player][20] != -1) {//if player rolls strike on first part of frame
             total = total + scoreArray[player][18] + scoreArray[player][19] + scoreArray[player][20];
            printFrameScore(total);
        }    
        else if (scoreArray[player][19] != -1 && (scoreArray[player][18]+scoreArray[player][19]) < 10) {//if player does not roll a strike on either frame
            total = total + scoreArray[player][18] + scoreArray[player][19];
            printFrameScore(total);
        }
    }
    else {
        cout << "|     ";
    }
    if (scoreArray[player][19] != -1) {
        if ((scoreArray[player][18] + scoreArray[player][19] < 10)) {
            finalScoreArray[player] = total;
        }
        else if (scoreArray[player][20] != -1){
            finalScoreArray[player] = total;
        }  
    }
    return total;
}

/******************************
** Function: ifStrike
** Description: This function branches off from the calculateFinalFrameScore function, and is specifically for figuring out what the total score is
                if there is a strike.
** Parameters: The array scoreArray keeps track of the pins knocked down, which is used in order to calculate the score of the strike. The integer
                player tracks which player this function is focusing on. The integer i is tracking which frame the strike occured in. The integer
                total is tracking the current running total for this player.
** Pre-conditions: There must be a strike in order for this function to be called.
** Post-conditions: The score from the strike is calculated if all necessary frames have been rolled.
******************************/
int ifStrike (int *scoreArray[], int player, int i, int total) {
    if (scoreArray[player][(i*2)+2] != 10 && scoreArray[player][(i*2)+2] != -1 && scoreArray[player][(i*2)+3] != -1) {
        total = total + scoreArray[player][i*2] + scoreArray[player][(i*2)+2] + scoreArray[player][(i*2)+3];
        printFrameScore(total);
    }
    else if (scoreArray[player][(i*2)+2] == 10 && scoreArray[player][(i*2)+4] != 10 && scoreArray[player][(i*2)+4] != -1){
        total = total + scoreArray[player][i*2] + scoreArray[player][(i*2)+2] + scoreArray[player][(i*2)+4];
        printFrameScore(total);
    }
    else if (scoreArray[player][(i*2)+2] == 10 && scoreArray[player][(i*2)+4] == 10) {
        total = total + 30;
        printFrameScore(total);
    }
    else {
        cout << "|     ";
    }
    return total;
            
    
}

/******************************
** Function: calculateFinalFrameScore
** Description: This function prints out the scores row, making sure to wait if a score can't be printed out yet (like a strike or spare)
** Parameters: The player integer tracks which player's scores this function is focusing on, pointArray holds information about how many pins
                have been knocked down, scoreArray holds information about which frames are open and closed, and finalScoreArray will store
                the final scores when the tenth frame is reached.
** Pre-conditions: The arrays must be initialized and the game must be underway
** Post-conditions: The scores are printed out and the current total is returned as an integer
******************************/
int calculateFinalFrameScore (int player, int *pointArray[], int *scoreArray[], int finalScoreArray[]) {
    cout << "           ";
    int total = 0;
    for (int i = 0; i < 9; i++) {
        if (pointArray[player][i] == 0) {
            cout << "|     ";
        }
        else if (pointArray[player][i] == 1) {
                total = total + scoreArray[player][i*2] + scoreArray[player][(i*2)+1];
                printFrameScore(total);
        }
        else if (pointArray[player][i] == 2) {
            if (scoreArray[player][(i*2)+1] != -1) {
                total = total + scoreArray[player][i*2] + scoreArray[player][(i*2)+1] + scoreArray[player][(i*2)+2];
                printFrameScore(total);
            }
        }
        else if (pointArray[player][i] == 3) {
            total = ifStrike(scoreArray, player, i, total);
        }
    }
    total = calculateTenthFrameScore(player, scoreArray, total, finalScoreArray);
    return total;
}

/******************************
** Function: checkPrintScore
** Description: This function checks whether a frame is unfinished, open, spare, or strike, and assigns a value to it in the pointArray accordingly
** Parameters: player tracks which player is being focused on, scoreArray tracks which pins are knocked down so that strikes and spares can be checked
                for, and pointArray is the array that will hold the information about whether each frame is unfinished, open, spare, or strike
** Pre-conditions: Arrays must be initalized and the game must be underway
** Post-conditions: The condition of each frame will be recorded
******************************/
void checkPrintScore (int player, int *scoreArray[], int *pointArray[]){
    for (int i = 0; i < 18; i++) {
        if (scoreArray[player][i] != -1 && scoreArray[player][i+1] != -1) {
            if (scoreArray[player][i] + scoreArray[player][i+1] == 10) {
                pointArray[player][(i/2)] = 2; 
            }
            else {
                pointArray[player][(i/2)] = 1; 
            }
        }
        else if (scoreArray[player][i] == 10) {
            pointArray[player][(i/2)] = 3; 
        }
        else {
            pointArray[player][(i/2)] = 0; 
        }
        i++;
    }
}

/******************************
** Function: whatToPrint
** Description: This function prints out either symbols or numbers for pins knocked down. If there is a strike, X is printed, if there is a spare, / is printed,
                and if there is a gutter ball, - is printed
** Parameters:  i and j track which position of the scores array is being focused on, and scores is tracking how many pins are knocked down at a specific frame
** Pre-conditions: Game must be underway
** Post-conditions: Nothing is returned, but the number of pins knocked down is printed out
******************************/
void whatToPrint (int i, int j, int *scores[]) {
     if (i % 2 == 0) {
                cout << "| ";
            }
            if (scores[j][i] == -1) {
                cout << "  ";
            }
            else if (scores[j][i] == 10 && i % 2 == 0) {
                cout << "X ";
            }
            else if ((scores[j][i] == 10) || ((scores[j][i] + scores[j][i-1]) == 10 && i % 2 == 1 && scores[j][i-1] != 10)) {
                cout << "/ ";
            }
            else if (scores[j][i] == 0) {
                cout << "- ";
            }
            else {
                cout << scores[j][i] << " ";
            }
}

/******************************
** Function: printScores
** Description: This function prints the grid and names for the score sheet, and calls other functions to print the pins knocked down and scores
** Parameters: The different arrays hold information about different aspects of the score sheet, such as the names from nameArray, pins knocked down
                in scores, the condition of each frame in pointArray, and the final scores in finalScoreArray
** Pre-conditions: The game must be underway
** Post-conditions: Nothing is returned, but the score sheet is printed out
******************************/
void printScores(int *scores[], int playerCount, string nameArray[], int *pointArray[], int finalScoreArray[]) {
    int total{0};
    cout << "   Name    |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |   10    |Total\n---------------------------------------------------------------------------------\n";
    for (int j = 0; j < playerCount; j++) {
        total = 0;
        if (nameArray[j].length() > 11) {
        for (int k = 0; k < 10; k++) {
            cout << nameArray[j].at(k);
        }
        cout << " ";
        }
        else {
            cout << nameArray[j];
            for (int f = 0; f < (11 - nameArray[j].length()); f++) {
                cout << " ";
                }
            }
        for (int i = 0; i < 21; i++) {

            whatToPrint(i, j, scores);
        }
        cout <<"\n---------------------------------------------------------------------------------\n";
        checkPrintScore(j, scores, pointArray);
        total = calculateFinalFrameScore(j, pointArray, scores, finalScoreArray);
        cout << "|    " << total << "\n---------------------------------------------------------------------------------\n";
        }
    cout << "Press enter to proceed!\n";
}

/******************************
** Function: askName
** Description: This function asks for the name of each player
** Parameters: The name array is passed in through array[], and the amount of players is passed in through playerCount
** Pre-conditions: The name array should be initialized and the user should have inputted the amount of players playing already
** Post-conditions: Every player name is recorded in the nameArray
******************************/
void askName(string array[], int playerCount) {
    cin.ignore();
    for (int i = 0; i < playerCount; i++) {
    cout << "Enter name of player " << (i + 1) << ".\n";
    getline(cin, array[i]);
    cout << "\nHello, " << array[i] << "!\n";
    }
}

/******************************
** Function: createScoreArray
** Description: This creates the array where the number of pins knocked down per frame will be recorded
** Parameters: playerCount stores how many players are playing so that an appropriate sized array can be made
** Pre-conditions: The user should have inputted how many players are playing
** Post-conditions: A dynamic array will have been created
******************************/
int **createScoreArray(int playerCount) {
    int **array;
    array = new int*[playerCount];
    for (int i = 0; i<playerCount; i++) {
        array[i] = new int[20];
    }
    return array;
}

/******************************
** Function: askPlayerCount
** Description: Asking for amount of players, and checking to make sure the input is a valid integer using a do while loop
** Parameters: None
** Pre-conditions: None
** Post-conditions: Amount of players will be returned 
******************************/
int askPlayerCount() {
    string playerCount;
    bool validInput = true;
    do {
        validInput = true;
        cout << "Enter number of players.\n";
        cin >> playerCount;

        for (int i = 0; i < playerCount.length(); i++) {
            if (!isdigit(playerCount[i])){
                cout << "Please enter a number greater than zero.\n";
                validInput = false;
                break;
            }
            else if (stoi(playerCount) == 0) {
                cout << "Please enter a number greater than zero.\n";
                validInput = false;
                break;
            }
        }

    } while (validInput == false);

    return stoi(playerCount);

}

/******************************
** Function: rollMessage
** Description: Checks whether a player has rolled a gutter ball or strike, and outputs a roll message appropriately then prints the scoreboard
** Parameters: The different arrays are used to call the scoreboard printing function, and j and i are used to track which part of the frame is being rolled
** Pre-conditions: The game must be underway
** Post-conditions: Nothing is returned, but a message is printed out
******************************/
void rollMessage (string nameArray[], int j, int i, int *scoreArray[], int playerCount, int *pointArray[], int finalScoreArray[]) {
    if (scoreArray[j][i] == 0) {
        cout << nameArray[j] << " rolled a gutter ball!\n";
    }
    else if (scoreArray[j][i] == 10) {
        cout << nameArray[j] << " rolled a strike!\n";
    }
    else {
        cout << nameArray[j] << " rolled a " << scoreArray[j][i] <<"!\n";
    }
    printScores(scoreArray, playerCount, nameArray, pointArray, finalScoreArray);
    cin.ignore();
}

/******************************
** Function: rollAlgo
** Description: This checks to see if the game is on the first or second part of a frame and then rolls accordingly, before printing out a roll message using
                a function
** Parameters: The different parameters for the rollMessage function are passed in, along with playerCount in order to determine how many loops this should go through
** Pre-conditions: The game should be underway, the amount of players should have been declared
** Post-conditions: The scores rolled will be printed out
******************************/
void rollAlgo(int playerCount, int *scoreArray[], string nameArray[], int *pointArray[], int finalScoreArray[]) {
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < playerCount; j++) {
            scoreArray[j][i] = roll();
            rollMessage(nameArray, j, i, scoreArray, playerCount, pointArray, finalScoreArray);
            
            if (scoreArray[j][i] != 10) {
                scoreArray[j][i+1] = roll2nd(scoreArray[j][i]);
                rollMessage(nameArray, j, (i+1), scoreArray, playerCount, pointArray, finalScoreArray);
            }
        }
i++;
}
}

/******************************
** Function: frameTenAlgo
** Description: This focuses on rolling and printing out rolls for the tenth frame specifically
** Parameters: The different parameters for rollMessage are passed in. scoreArray is called so that rolls can be assigned to their proper frame
** Pre-conditions: The game should be on the tenth frame
** Post-conditions: The game ends with all the rolls having been made
******************************/
void frameTenAlgo(int playerCount, int *scoreArray[], string nameArray[], int *pointArray[], int finalScoreArray[]) {
    for (int j = 0; j < playerCount; j++) {
    scoreArray[j][18] = roll();
    rollMessage(nameArray, j, 18, scoreArray, playerCount, pointArray, finalScoreArray);
    if (scoreArray[j][18] == 10) {
        scoreArray[j][19] = roll();
        rollMessage(nameArray, j, 19, scoreArray, playerCount, pointArray, finalScoreArray);
    }
    else if (scoreArray[j][18] != 10){
        scoreArray[j][19] = roll2nd(scoreArray[j][18]);
        rollMessage(nameArray, j, 19, scoreArray, playerCount, pointArray, finalScoreArray);
    }
    if (scoreArray[j][18] + scoreArray[j][19] == 10 || scoreArray[j][18] == 10 || scoreArray[j][19] == 10) {
        scoreArray[j][20] = roll();
        rollMessage(nameArray, j, 20, scoreArray, playerCount, pointArray, finalScoreArray);
    }
}
}

/******************************
** Function: initializeScoreArray
** Description: Initializing the scoreArray with -1s in order to avoid errors
** Parameters: playerCount tells the function how many times to loop, scoreArray is the array being initialized
** Pre-conditions: ScoreArray should have been created
** Post-conditions: The array is initialized
******************************/
void initializeScoreArray (int playerCount, int *scoreArray[]) {
    for (int i = 0; i < playerCount; i++) {
    for (int j = 0; j < 21; j++) {
        scoreArray[i][j] = -1;
    }
}
cin.ignore();
}

/******************************
** Function: createPointArray
** Description: The array for storing the condition of each frame is created here
** Parameters: playerCount determines how many rows of the array should be made
** Pre-conditions: The amount of players should have been determined already
** Post-conditions: pointArray has been created
******************************/
int **createPointArray(int playerCount) {
    int **array;
    array = new int*[playerCount];
    for (int i = 0; i<playerCount; i++) {
        array[i] = new int[9];
    }
    return array;
}

/******************************
** Function: initializePointArray
** Description: The array that stores the condition of each frame is initialized
** Parameters: The array is passed in, along with playerCount to determine how many loops are made
** Pre-conditions: The array needs to have been made
** Post-conditions: The array is initialized
******************************/
void initializePointArray (int playerCount, int *pointArray[]) {//initializing the pointArray with -1s
    for (int i = 0; i < playerCount; i++) {
    for (int j = 0; j < 10; j++) {
        pointArray[i][j] = -1;
    }
}
}

/******************************
** Function: deleteMemory
** Description: This deletes the 2D dynamic arrays in this program, freeing up memory and preventing memory leaks
** Parameters: arraySize tells the function how many columns there are in the function, *array[] is the pointer of the array
** Pre-conditions: The game should be finished and the memory should no longer be needed
** Post-conditions: All memory is freed and there are no memory leaks
******************************/
void deleteMemory (int arraySize, int *array[]) {
    for (int i = 0; i < arraySize; i++) {
        delete[] array [i];
        array[i] = NULL;
    }
    delete[] array;
    array = NULL;
}

/******************************
** Function: announceFinalScores
** Description: This function prints out the final score of each player
** Parameters: nameArray tracks the name of each player, playerCount tracks how many players there are, finalScoreArray tracks the actual final scores of each player
** Pre-conditions: The game should have ended before this is called
** Post-conditions: Nothing is returned, but the final score of each player is printed out
******************************/
void announceFinalScores (string nameArray[], int playerCount, int finalScoreArray[]) {
    for (int i = 0; i < playerCount; i++) {
        cout << "Final score for " << nameArray[i] << ": " << finalScoreArray[i] << endl; 
    }
}

/******************************
** Function: gameLoop
** Description: This function groups many other functions in together to create one loop of the game, in order to make a looping game possible
** Parameters: The different arrays and integers required by the other functions are passed into this function
** Pre-conditions: All the arrays and integers must be initialized
** Post-conditions: Nothing is returned, return to the main function
******************************/
void gameLoop (string nameArray[], int playerCount, int *scoreArray[], int *pointArray[], int finalScoreArray[]) {
    askName(nameArray, playerCount);
    initializeScoreArray (playerCount, scoreArray);
    initializePointArray (playerCount, pointArray);
    rollAlgo(playerCount, scoreArray, nameArray, pointArray, finalScoreArray);
    frameTenAlgo(playerCount, scoreArray, nameArray, pointArray, finalScoreArray);
    announceFinalScores(nameArray, playerCount, finalScoreArray);
    deleteMemory(playerCount, scoreArray);
    deleteMemory(playerCount, pointArray);
}

main() {
cout << "Welcome to bowling!\n";
srand(time(NULL));
bool play = true;
string input;
/*This entire do-while loop above makes it so that the player can restart the game if they wish, checking for valid yes or no inputs.*/
do {
    /* The below code is creating each dynamic array along with 1-D arrays for storing different data. */
    play = true;
    int playerCount = askPlayerCount();
    int **scoreArray;
    scoreArray = createScoreArray(playerCount);
    int **pointArray;
    pointArray = createPointArray(playerCount);
    string nameArray[playerCount];
    int finalScoreArray[playerCount];

    gameLoop(nameArray, playerCount, scoreArray, pointArray, finalScoreArray);
    cout << "Play again?\n";
        do {
        cout << "Please type Y or N.\n";
        getline(cin, input);
    } while (input.length() != 1 || input[0] != 'y' && input[0] != 'Y' && input[0] != 'n' && input[0] != 'N');

    if (input[0] == 'N' || input[0] == 'n') {
        play = false;
        break;
    } 

} while (play != false);
}


