/*CANDY CRUSH GAME:
    The program takes row and column as input to select the candy.
    It then takes input from the keyboard (W/A/S/D) as cases of a switch statement.
    It swaps candies in the input direction.
    It uses if statements to check if 3 candies are equal or not.
    If they are equal, they are destroyed and candies from above fall down in their place with the top row generating new candies using a loop.
    The program continues for 60 seconds and offers a total of 15 moves, after which the name and score of the player is stored in a file if it is in the top 3.
*/

#include<iostream>      //for input and output
#include<cstdlib>       //for random generation
#include<ctime>         //to link randoms with time
#include<conio.h>       //console inp/out
#include<string>        //to use string functions
#include<fstream>       //file handling
#include<chrono>        //for timer
#include<thread>        //for timer
using namespace std;


const int Easy_board = 8;                   //board sizes
const int Hard_board = 10;
const int timer = 60;
const int total_moves = 15;
int score = 0;
int board_size;
char board[10][10];
const int max_players = 100;


bool func_get_int(int& value)               //helper to safely read an integer, returns false on bad input
{
    cin >> value;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        return false;
    }
    cin.ignore(1000, '\n');
    return true;
}


void func_delayed_cls()                     //helper to pause briefly then clear the screen for quick transitions between game states
{
    this_thread::sleep_for(chrono::milliseconds(700));
    system("cls");
}


void func_wait_cls()                        //helper to wait for a keypress then clear the screen, used for screens the player needs to read
{
    cout << "\nPress any key to continue...";
    _getch();
    system("cls");
}


void scores()
{                             //function to store and display 3 highest scores
    string names[max_players];
    int scores[max_players];

    ifstream in("score_file.txt");          //opening score file
    if (!in.is_open()) {
        cout << "No score file found. Play a game first!" << endl;
        return;                     //return nothing if file cannot open
    }

    int player_count = 0;
    while (player_count < max_players && in >> names[player_count] >> scores[player_count]) {           //end-of-file controlled loop
        player_count++;
    }

    if (player_count == 0) {
        cout << "No scores recorded yet." << endl;
        return;
    }

    for (int i = 0; i < player_count - 1; ++i)          //sorting using bubble sorting tecnique
    {
        for (int j = 0; j < player_count - i - 1; ++j) {
            if (scores[j] < scores[j + 1])
            {
                int temp = scores[j];                   //swapping scores
                scores[j] = scores[j + 1];
                scores[j + 1] = temp;

                string temp1 = names[j];                //swapping names
                names[j] = names[j + 1];
                names[j + 1] = temp1;
            }
        }
    }
    cout << "Top 3 scores are given below with names:" << endl;
    cout << "Names\t\tScores" << endl;
    const int displayCount = 3;
    for (int i = 0; i < displayCount && i < player_count; ++i)
    {
        cout << names[i] << "\t\t" << scores[i] << endl;
    }
}


void func_board_fill_easy()
{                                                        //function to fill the board for easy mode
    srand(time(0));     //random seed

    for (int i = 0; i < board_size; ++i) {
        for (int j = 0; j < board_size; ++j) {
            do {
                board[i][j] = "~@#$%"[rand() % 5];      //five candies for easy mode
            } while (
                (i >= 2 && board[i][j] == board[i - 1][j] && board[i][j] == board[i - 2][j]) ||     //vertically checking
                (j >= 2 && board[i][j] == board[i][j - 1] && board[i][j] == board[i][j - 2]) ||     //horizontally checking
                (i >= 2 && j >= 2 && board[i][j] == board[i - 1][j - 1] && board[i][j] == board[i - 2][j - 2]) || //diagonal checking from top left to right
                (i >= 2 && j < board_size - 2 && board[i][j] == board[i - 1][j + 1] && board[i][j] == board[i - 2][j + 2]) //vice versa
                );      //ending while
        }
    }
}


void func_board_fill_hard()
{                                                        //function to fill the board for hard mode
    srand(time(0));     //random seed

    for (int i = 0; i < board_size; ++i) {
        for (int j = 0; j < board_size; ++j) {
            do {
                board[i][j] = "~@#$%&*"[rand() % 7];    //seven candies for hard mode
            } while (
                (i >= 2 && board[i][j] == board[i - 1][j] && board[i][j] == board[i - 2][j]) ||     //vertically checking
                (j >= 2 && board[i][j] == board[i][j - 1] && board[i][j] == board[i][j - 2]) ||     //horizontally checking
                (i >= 2 && j >= 2 && board[i][j] == board[i - 1][j - 1] && board[i][j] == board[i - 2][j - 2]) || //diagonal checking from top left to right
                (i >= 2 && j < board_size - 2 && board[i][j] == board[i - 1][j + 1] && board[i][j] == board[i - 2][j + 2]) //vice versa
                );      //ending while
        }
    }
}


void func_disp_board()
{                                    //function to display game board at start
    cout << "\t\t\t\t\t";            //to display in middle
    if (board_size == 8)
    {
        cout << "    0   1   2   3   4   5   6   7" << endl;                  //column number display for ez mode
    }
    else cout << "    0   1   2   3   4   5   6   7   8   9" << endl;         //column number display for hard mode
    for (int i = 0; i < board_size; ++i) {
        cout << "\t\t\t\t\t";

        cout << " " << i << " ";                                              //row number display

        for (int j = 0; j < board_size; ++j) {
            if (board[i][j] == '*')
            {
                cout << "\033[1;31m" << "|" << board[i][j] << "|" << "\033[0m "; //red colour
            }
            else if (board[i][j] == '@')
            {
                cout << "\033[1;32m" << "|" << board[i][j] << "|" << "\033[0m "; //green colour
            }
            else if (board[i][j] == '#') {
                cout << "\033[1;33m" << "|" << board[i][j] << "|" << "\033[0m "; //yellow colour
            }
            else if (board[i][j] == '$')
            {
                cout << "\033[1;34m" << "|" << board[i][j] << "|" << "\033[0m "; //blue colour
            }
            else if (board[i][j] == '%')
            {
                cout << "\033[1;35m" << "|" << board[i][j] << "|" << "\033[0m "; //magenta colour
            }
            else if (board[i][j] == '&')
            {
                cout << "\033[1;36m" << "|" << board[i][j] << "|" << "\033[0m "; //cyan colour
            }
            else if (board[i][j] == '~')
            {
                cout << "\033[1;37m" << "|" << board[i][j] << "|" << "\033[0m "; //white colour
            }
            else {
                cout << "|" << board[i][j] << "| ";
            }
        }

        cout << endl;
        cout << "\t\t\t\t\t";
        if (board_size == 8) {                              //if ez mode then less lines
            cout << "------------------------------------" << endl;
        }
        else cout << "-------------------------------------------" << endl;
    }
}


void func_welcome()                                         //function for welcome board
{
    system("Color 3");

    cout << endl;
    cout << "\t\t\t\t\t===================================" << endl;
    cout << "         \t\t\t\t\tWelcome to Candy Crush              " << endl;
    cout << "\t\t\t\t\t===================================" << endl;
    cout << "           \t\t\t\t\t   Choose Your Mode        " << endl;
    cout << "\t\t\t\t\t===================================" << endl;
    cout << "  \t\t\t\t\t         1. Play Game                    " << endl;
    cout << "  \t\t\t\t\t         2. Instructions                     " << endl;
    cout << "  \t\t\t\t\t         3. Credits                     " << endl;
    cout << "  \t\t\t\t\t         4. Score                     " << endl;
    cout << "  \t\t\t\t\t         5. Exit                     " << endl;
    cout << "\t\t\t\t\t===================================" << endl;
}


bool func_check_match()                                     //function checks 3 same candies and puts them = ' '
{
    bool matchFound = false;

    // Check for upper-left L matches
    for (int i = 2; i < board_size; ++i) {
        for (int j = 2; j < board_size; ++j)
        {
            if (board[i][j] != ' ' && board[i][j] == board[i - 1][j] && board[i][j] == board[i - 2][j] && board[i][j] == board[i][j - 1] && board[i][j] == board[i][j - 2])
            {
                board[i][j] = ' ';
                board[i - 1][j] = ' ';
                board[i - 2][j] = ' ';
                board[i][j - 1] = ' ';
                board[i][j - 2] = ' ';
                matchFound = true;
                score = score + 25;
            }
        }
    }

    // Check for upper-right L matches
    for (int i = 2; i < board_size; ++i) {
        for (int j = 0; j < board_size - 2; ++j)
        {
            if (board[i][j] != ' ' && board[i][j] == board[i - 1][j] && board[i][j] == board[i - 2][j] && board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2])
            {
                board[i][j] = ' ';
                board[i - 1][j] = ' ';
                board[i - 2][j] = ' ';
                board[i][j + 1] = ' ';
                board[i][j + 2] = ' ';
                matchFound = true;
                score = score + 25;
            }
        }
    }

    // Check for lower-left L matches
    for (int i = 0; i < board_size - 2; ++i) {
        for (int j = 2; j < board_size; ++j)
        {
            if (board[i][j] != ' ' && board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j] && board[i][j] == board[i][j - 1] && board[i][j] == board[i][j - 2])
            {
                board[i][j] = ' ';
                board[i + 1][j] = ' ';
                board[i + 2][j] = ' ';
                board[i][j - 1] = ' ';
                board[i][j - 2] = ' ';
                matchFound = true;
                score = score + 25;
            }
        }
    }

    // Check for lower-right L matches
    for (int i = 0; i < board_size - 2; ++i) {
        for (int j = 0; j < board_size - 2; ++j)
        {
            if (board[i][j] != ' ' && board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j] && board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2])
            {
                board[i][j] = ' ';
                board[i + 1][j] = ' ';
                board[i + 2][j] = ' ';
                board[i][j + 1] = ' ';
                board[i][j + 2] = ' ';
                matchFound = true;
                score = score + 25;
            }
        }
    }

    // Check for horizontal matches
    for (int i = 0; i < board_size; ++i) {
        for (int j = 0; j < board_size - 2; ++j)
        {
            if (board[i][j] != ' ' && board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2])
            {
                board[i][j] = ' ';
                board[i][j + 1] = ' ';
                board[i][j + 2] = ' ';
                matchFound = true;
                score = score + 10;
            }
        }
    }

    // Check for vertical matches
    for (int j = 0; j < board_size; ++j)
    {
        for (int i = 0; i < board_size - 2; ++i)
        {
            if (board[i][j] != ' ' && board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j])
            {

                board[i][j] = ' ';
                board[i + 1][j] = ' ';
                board[i + 2][j] = ' ';
                matchFound = true;
                score = score + 10;

            }
        }
    }
    // Check diagonal from  top left to bottom right
    for (int i = 0; i < board_size - 2; i++)
    {
        for (int j = 0; j < board_size - 2; j++)
        {
            if (board[i][j] != ' ' && board[i][j] == board[i + 1][j + 1] && board[i][j] == board[i + 2][j + 2])
            {

                board[i][j] = ' ';
                board[i + 1][j + 1] = ' ';
                board[i + 2][j + 2] = ' ';
                matchFound = true;
                score = score + 20;
            }
        }
    }
    // Check diagonal from top right to bottom left
    for (int i = 0; i < board_size - 2; ++i) {
        for (int j = board_size - 1; j > 1; --j)
        {
            if (board[i][j] != ' ' && board[i][j] == board[i + 1][j - 1] && board[i][j] == board[i + 2][j - 2])
            {
                board[i][j] = ' ';
                board[i + 1][j - 1] = ' ';
                board[i + 2][j - 2] = ' ';
                matchFound = true;
                score = score + 20;
            }
        }
    }
    return matchFound;
}


void func_swap_candies(int inp_row, int inp_col, int row2, int col2)              //function to swap selected candies
{
    char temp = board[inp_row][inp_col];
    board[inp_row][inp_col] = board[row2][col2];
    board[row2][col2] = temp;
}


void func_destroyed_easy()                                      //function to move down candies and generate random ones at top row for easy mode
{
    for (int j = 0; j < board_size; ++j) {                     //processing each column independently
        bool found = true;
        while (found) {                                         //repeating until no spaces remain in the column
            found = false;
            for (int i = board_size - 1; i >= 0; --i) {        //scanning from bottom to top
                if (board[i][j] == ' ')
                {
                    found = true;
                    for (int k = i; k > 0; --k) {
                        board[k][j] = board[k - 1][j];         //moves down candies
                    }
                    board[0][j] = "~@#$%"[rand() % 5];         //fills top with new candy
                }
            }
        }
    }
}


void func_destroyed_hard()                                       //function to move down candies and generate random ones at top row for hard mode
{
    for (int j = 0; j < board_size; ++j) {                     //processing each column independently
        bool found = true;
        while (found) {                                         //repeating until no spaces remain in the column
            found = false;
            for (int i = board_size - 1; i >= 0; --i) {        //scanning from bottom to top
                if (board[i][j] == ' ')
                {
                    found = true;
                    for (int k = i; k > 0; --k) {
                        board[k][j] = board[k - 1][j];         //moves down candies
                    }
                    board[0][j] = "~@#$%&*"[rand() % 7];       //fills top with new candy
                }
            }
        }
    }
}


void testing()
{
    cout << "Hello World";
}


void instruction();         //body at last
void credits();


int main()
{
    string Name;
    cout << "Enter your name: ";
    cin >> Name;
    cin.ignore(1000, '\n');             //clearing leftover newline after name input

    func_delayed_cls();                 //clean transition into the main menu

    while (true)
    {
        func_welcome();                     //displaying welcome board

        char ch;
        cout << "Enter your choice: ";
        cin >> ch;                          //getting choice from welcome board
        cin.ignore(1000, '\n');             //clearing buffer after menu choice

        if (ch == '1')
        {
            score = 0;                                               //resetting score for new game

            char ch2;
            cout << "Choose game mode (1 for Easy, 2 for Hard): ";
            cin >> ch2;                                             //getting choice for easy or hard
            cin.ignore(1000, '\n');                                 //clearing buffer after mode choice

            if (ch2 == '1')
            {
                board_size = Easy_board;                     //iniatializing it with const integer
            }
            else if (ch2 == '2')
            {
                board_size = Hard_board;
            }
            else {
                cout << "Invalid choice. Returning to menu." << endl;
                func_delayed_cls();                          //brief pause then clear before returning to menu
                continue;
            }

            if (ch2 == '1') {
                func_board_fill_easy();
            }
            else func_board_fill_hard();

            func_delayed_cls();                              //clean transition into the game board
            cout << "Initial Board" << endl;                 //displaying initial board
            func_disp_board();

            auto startTime = chrono::system_clock::now();    //timer started
            chrono::seconds duration(timer);

            int moves = total_moves;
            bool outOfBounds = false;                        //flag to skip match logic when move was out of bounds

            while (chrono::system_clock::now() - startTime < duration && moves > 0) {
                auto remainingTime = chrono::duration_cast<chrono::seconds>(duration - (chrono::system_clock::now() - startTime));
                cout << "Time remaining: " << remainingTime.count() << " seconds" << endl;
                cout << "Score: " << score << endl;                             //displaying current score during gameplay

                int inp_row, inp_col;

                if (board_size == 8)
                {
                    cout << "Enter the row of the candy to select (0-7): ";             //for ez mode
                }
                else
                {
                    cout << "Enter the row of the candy to select (0-9): ";             //for hard mode
                }

                if (!func_get_int(inp_row)) {                                           //checking if row input is a valid integer
                    cout << "Invalid input! Please enter numbers only." << endl;
                    func_delayed_cls();                                                  //brief pause then clear, then redisplay board
                    func_disp_board();
                    continue;
                }
                if (inp_row < 0 || inp_row >= board_size) {                            //checking if row is within board bounds
                    cout << "Row out of range! Please enter a value between 0 and " << board_size - 1 << "." << endl;
                    func_delayed_cls();                                                  //brief pause then clear, then redisplay board
                    func_disp_board();
                    continue;
                }

                if (board_size == 8)
                {
                    cout << "Enter the column of the candy to select (0-7): ";          //for ez mode
                }
                else
                {
                    cout << "Enter the column of the candy to select (0-9): ";          //for hard mode
                }

                if (!func_get_int(inp_col)) {                                           //checking if column input is a valid integer
                    cout << "Invalid input! Please enter numbers only." << endl;
                    func_delayed_cls();                                                  //brief pause then clear, then redisplay board
                    func_disp_board();
                    continue;
                }
                if (inp_col < 0 || inp_col >= board_size) {                            //checking if column is within board bounds
                    cout << "Column out of range! Please enter a value between 0 and " << board_size - 1 << "." << endl;
                    func_delayed_cls();                                                  //brief pause then clear, then redisplay board
                    func_disp_board();
                    continue;
                }

                char direction;
                cout << "Enter the direction to move the candy by using (W/A/S/D): ";
                cin >> direction;                                       //getting direction for the candy
                cin.ignore(1000, '\n');                                 //clearing buffer after direction input

                outOfBounds = false;                                    //resetting flag each turn

                switch (direction) {                                    //checking which key was pressed for direction
                case 'W':
                case 'w':
                    if (!(inp_row == 0)) {
                        func_swap_candies(inp_row, inp_col, inp_row - 1, inp_col);
                    }
                    else {
                        cout << "Cannot move out of bounds! Move not counted." << endl;
                        func_delayed_cls();                                              //brief pause then clear, then redisplay board
                        func_disp_board();
                        outOfBounds = true;                                              //flagging so match logic is skipped
                    }
                    break;
                case 'S':
                case 's':
                    if (!(inp_row == board_size - 1)) {
                        func_swap_candies(inp_row, inp_col, inp_row + 1, inp_col);
                    }
                    else {
                        cout << "Cannot move out of bounds! Move not counted." << endl;
                        func_delayed_cls();                                              //brief pause then clear, then redisplay board
                        func_disp_board();
                        outOfBounds = true;                                              //flagging so match logic is skipped
                    }
                    break;
                case 'A':                                                               //if conditions to restrict invalid movements
                case 'a':
                    if (!(inp_col == 0)) {
                        func_swap_candies(inp_row, inp_col, inp_row, inp_col - 1);
                    }
                    else {
                        cout << "Cannot move out of bounds! Move not counted." << endl;
                        func_delayed_cls();                                              //brief pause then clear, then redisplay board
                        func_disp_board();
                        outOfBounds = true;                                              //flagging so match logic is skipped
                    }
                    break;
                case 'D':
                case 'd':
                    if (!(inp_col == board_size - 1)) {
                        func_swap_candies(inp_row, inp_col, inp_row, inp_col + 1);
                    }
                    else {
                        cout << "Cannot move out of bounds! Move not counted." << endl;
                        func_delayed_cls();                                              //brief pause then clear, then redisplay board
                        func_disp_board();
                        outOfBounds = true;                                              //flagging so match logic is skipped
                    }
                    break;
                default:
                    cout << "Invalid direction! Please use W, A, S or D only.\n";
                    func_delayed_cls();                                                  //brief pause then clear, then redisplay board
                    func_disp_board();
                    continue;
                }

                if (outOfBounds) continue;                              //skipping match logic entirely if move was out of bounds

                func_delayed_cls();                                                      //brief pause then clear before showing board after move
                cout << "Board after the move" << endl;                                  //board after move
                func_disp_board();

                bool anyMatch = func_check_match();                     //checking if match function returned true or not?
                if (!anyMatch) {
                    func_swap_candies(inp_row, inp_col,                 //swapping back if no match found to undo invalid move
                        (direction == 'W' || direction == 'w') ? inp_row - 1 :
                        (direction == 'S' || direction == 's') ? inp_row + 1 : inp_row,
                        (direction == 'A' || direction == 'a') ? inp_col - 1 :
                        (direction == 'D' || direction == 'd') ? inp_col + 1 : inp_col);
                    cout << "No match found! Move reversed." << endl;
                    func_delayed_cls();                                 //brief pause then clear before showing restored board
                    func_disp_board();
                    moves++;                                             //move not counted if no match
                }

                while (anyMatch) {                                      //looping while matches keep being found
                    cout << "SWEET" << endl;                            //sweet if YES

                    func_delayed_cls();                                     //brief pause then clear before showing board with destroyed candies
                    cout << "Board after destroying candies:\n";
                    func_disp_board();                                      //board after destroying

                    if (ch2 == '1') {
                        func_destroyed_easy();                              //calling function to generate candies at destoryed places
                    }
                    else func_destroyed_hard();

                    func_delayed_cls();                                     //brief pause then clear before showing board with new candies
                    cout << "Board after generating new candies:\n";        //updated board display
                    func_disp_board();

                    anyMatch = func_check_match();                          //checking again after new candies fall
                }
                moves--;
                cout << "Moves Left = " << moves << endl;                   //display moves
            }

            func_delayed_cls();                                          //clean transition to game over screen
            if (!(chrono::system_clock::now() - startTime < duration)) {    //timer ended
                cout << "Game over! Time's up" << endl;
            }
            else if (moves == 0) {                                          //no moves left
                cout << "Game over! No Moves left!" << endl;
            }
            cout << "Your final score is: " << score << endl;

            ofstream name1;
            name1.open("score_file.txt", name1.app);         //using append to keep prevous data
            if (name1.is_open()) {                           //checking file opened successfully before writing
                name1 << Name << " " << score << endl;
                name1.close();
            }
            else {
                cout << "Warning: Could not save score to file." << endl;
            }

            func_wait_cls();                                 //wait for keypress so player can read their final score before returning to menu
        }
        else if (ch == '2')                                                 //choice to get instructions  
        {
            func_delayed_cls();
            instruction();
            func_wait_cls();                                 //wait for keypress so player can finish reading instructions
        }

        else if (ch == '3')                                                     //choice to check credits                                                          
        {
            func_delayed_cls();
            credits();
            func_wait_cls();                                 //wait for keypress so player can finish reading credits
        }
        else if (ch == '4')                                                     //choice to check score
        {
            func_delayed_cls();
            scores();
            func_wait_cls();                                 //wait for keypress so player can finish reading scores
        }
        else if (ch == '5')
        {
            func_delayed_cls();
            cout << "Quitting the game. Goodbye " << Name << "!" << endl;      //choice to exit
            break;
        }
        else
        {
            cout << "Invalid choice. Try again" << endl;
            func_delayed_cls();                              //brief pause then clear before redisplaying menu
        }
    }


    system("pause");
    return 0;
}


void instruction()              //function for instruction
{
    cout << "Instructions:" << endl;

    cout << "Match three candies of the same type in a row, column, diagonal or L shape to score points.\n";
    cout << "You have 60 seconds to make moves. The game ends when the time runs out or moves left are 0.\n";
    cout << "If a swap results in no match, it will be automatically reversed and the move will not be counted.\n";
    cout << "Horizontal and Vertical matches grant 10 points.\n";
    cout << "Diagonal matches grant 20 points. \n";
    cout << "L shape matchees grant 25 points. \n";
}


void credits()                  //function for credits
{
    cout << "Credits:" << endl;
    cout << "Game developed by Bilal Mohsin (23F-0646) and Ali Meekal (23F-0574) as their Programming Fundamentals project." << endl;
    cout << "Special credit goes to Sir Usman and Sir Muiz for teaching us all this and making us able to complete our project.";
}