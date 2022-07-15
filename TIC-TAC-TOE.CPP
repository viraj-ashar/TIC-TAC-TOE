#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <ctime>

// HANDLE is a class which controls some of the functions related to console screen
// Like text color, bold.....
HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);

using namespace std;

int i, j;
char history_ch;
fstream file;

// class common in which both the  function related to multiplayer game and computer  game are same
class common
{
public:
    char ox, pos, ttt[3][3], level;
    int turn = 1, rand_value;
    time_t now;
    string player1, player2;
    common()
    {
        for (i = 0; i < 3; i++)
            for (j = 0; j < 3; j++)
                ttt[i][j] = ' ';
        turn = 1;
        player1.clear();
        player2.clear();
    }
    void color_change(int, int);
    void display();
    bool valid();
    bool winner();
};

// multiplayer class inhertis the common class
class multiplayer : public common
{
public:
    void start_multiplayer_game();
};

// computer class inhertis the common class
class computer : public common
{
public:
    void start_computer_game();
    void computer_choice();
    bool easy_strategy();
    bool hard_strategy();
    bool is_winning(char);
    void any_address();
    bool random();
};
void history();

int main()
{
    system("CLS");

    // function which always generate a random value
    srand(time(0));

    char choice;

    // SetConsoleTextAttribute will change the color of the text in the console screen
    SetConsoleTextAttribute(color, 1);
    cout << setw(104) << "Welcome to TIC-TAC-TOE.";
    for (int i = 0; i < 6; i++)
    {
        // Sleep(900);
        cout << ".";
    }
    SetConsoleTextAttribute(color, 7);
    cout << "\n";
    while (1)
    {
        cout << "\n\n"
             << setw(106) << "What would you like to play?\n";
        cout << setw(93) << "1. Multi-player.\n";
        cout << setw(89) << "2. Computer.\n";
        cout << setw(112) << "3. See history of the played games.\n";
        cout << setw(98) << "4. Clear the history.\n";
        cout << setw(86) << "5. Exit.\n\n";
        //<< setw(100);
    x:
        cout << setw(107) << "Enter your choice from above : ";
        choice = getche();
        switch (choice)
        {
        case '1':
        {
            multiplayer game;
            game.start_multiplayer_game();
            break;
        }
        case '2':
        {
            computer game;
            game.start_computer_game();
            break;
        }
        case '3':
        {
            history();
            break;
        }
        case '4':
        {
            file.open("history.dat", ios::out);
            system("CLS");
            cout << "\n"
                 << setw(114) << "History Deleted\n";
            file.close();
            break;
        }
        case '5':
            return 0;
        default:
            SetConsoleTextAttribute(color, 4);
            cout << endl
                 << setw(102) << "Enter a valid choice\n";
            SetConsoleTextAttribute(color, 7);
            goto x;
        }
        cout << endl
             << setw(120) << "Press any key to continue....";
        getch();
        system("CLS");
        SetConsoleTextAttribute(color, 1);
        cout << setw(104) << "Welcome to TIC-TAC-TOE.";
        SetConsoleTextAttribute(color, 7);
        cout << "\n";
    }
    return 0;
}

void multiplayer::start_multiplayer_game()
{
    system("CLS");

    cout << setw(110) << "Here starts your Multiplayer game.\n\n";
    if (player1.empty())
    {
        fflush(stdin);
        cout << setw(100) << "Enter the name of player 1 : ";
        getline(cin, player1);
        cout << setw(100) << "Enter the name of player 2 : ";
        getline(cin, player2);
    }
    fflush(stdin);
    system("CLS");

    cout << setw(101 - (player1.size() + player2.size()) / 2) << "Welcome " << player1 << " and " << player2 << " to TIC-TAC-TOE\n";
    display();

    do
    {
        if (turn == 10)
        {
            file.open("history.dat", ios::in | ios::app);
            file << player1 << " vs " << player2;
            for (i = 0; i < (54 - (player1.length() + player2.length())); i++)
                file << " ";
            file << "Draw!";
            for (i = 0; i < 25; i++)
                file << " ";
            file << asctime(localtime(&now));
            SetConsoleTextAttribute(color, 2);
            cout << "\n\n"
                 << setw(111) << "Draw.\n";
            SetConsoleTextAttribute(color, 7);
            file.close();
            break;
        }
        if (turn % 2 == 1)
        {
            do
            {
                cout << "\n\n"
                     << setw(103 + (player1.size() / 2)) << player1 << "'s turn : ";
                pos = getche();
            } while (!valid());
        }
        else
        {
            do
            {
                cout << "\n\n"
                     << setw(103 + (player2.size() / 2)) << player2 << "'s turn : ";
                pos = getche();
            } while (!valid());
        }
        system("CLS");
        cout << setw(101 - (player1.size() + player2.size()) / 2) << "Welcome " << player1 << " and " << player2 << " to TIC-TAC-TOE\n";
        display();
        turn++;
    } while (!winner());
}

void computer::start_computer_game()
{
    system("CLS");
    cout << setw(120) << "Here starts your game with computer. I hope you enjoy.\n\n";
    if (player1.empty())
    {
        fflush(stdin);
        cout << endl
             << setw(90) << "Enter your name : ";
        getline(cin, player1);
        player2 = "Computer";
    }
    cout << setw(112) << "Which level would you like to play.\n";
    cout << setw(90) << "1. Easy.\n";
    cout << setw(90) << "2. Hard.\n"
         << setw(90);
    level = getche();
    fflush(stdin);
    system("CLS");

    cout << setw(96 + (player1.size() / 2)) << "Welcome " << player1 << " to TIC-TAC-TOE.\n";
    display();

    do
    {
        if (turn == 10)
        {
            file.open("history.dat", ios::in | ios::app);
            file << player1 << " vs " << player2;
            for (i = 0; i < (54 - (player1.length() + player2.length())); i++)
                file << " ";
            file << "Draw!";
            for (i = 0; i < 25; i++)
                file << " ";
            file << asctime(localtime(&now));

            SetConsoleTextAttribute(color, 2);
            cout << "\n\n"
                 << setw(111) << "Game Draw.\n";
            SetConsoleTextAttribute(color, 7);
            file.close();
            break;
        }
        if (turn % 2 == 1)
        {
            do
            {
                cout << "\n\n level is " << level << " \n\n";
                cout << "\n\n"
                     << setw(103 + (player1.size() / 2)) << player1 << "'s turn : ";
                pos = getche();
            } while (!valid());
        }
        else
        {
            computer_choice();
        }
        system("CLS");
        cout << setw(96 + (player1.size() / 2)) << "Welcome " << player1 << " to TIC-TAC-TOE.\n";
        display();
        turn++;
    } while (!winner());
}

void common::color_change(int i, int j)
{
    if (ttt[i][j] == 'X')
        SetConsoleTextAttribute(color, 4);
    else
        SetConsoleTextAttribute(color, 1);
}

void common::display()
{
    SetConsoleTextAttribute(color, 2);
    cout << setw(120) << "       |       |       \n";
    cout << setw(99) << "   ";
    SetConsoleTextAttribute(color, 13);
    cout << "1   ";
    SetConsoleTextAttribute(color, 2);
    cout << "|   ";
    SetConsoleTextAttribute(color, 13);
    cout << "2   ";
    SetConsoleTextAttribute(color, 2);
    cout << "|   ";
    SetConsoleTextAttribute(color, 13);
    cout << "3   \n";
    SetConsoleTextAttribute(color, 2);
    cout << setw(120) << "_______|_______|_______\n";
    cout << setw(120) << "       |       |       \n";
    SetConsoleTextAttribute(color, 13);
    cout << setw(103) << "4   ";
    SetConsoleTextAttribute(color, 2);
    cout << "|   ";
    SetConsoleTextAttribute(color, 13);
    cout << "5   ";
    SetConsoleTextAttribute(color, 2);
    cout << "|   ";
    SetConsoleTextAttribute(color, 13);
    cout << "6   \n";
    SetConsoleTextAttribute(color, 2);
    cout << setw(120) << "_______|_______|_______\n";
    cout << setw(120) << "       |       |       \n";
    SetConsoleTextAttribute(color, 13);
    cout << setw(103) << "7   ";
    SetConsoleTextAttribute(color, 2);
    cout << "|   ";
    SetConsoleTextAttribute(color, 13);
    cout << "8   ";
    SetConsoleTextAttribute(color, 2);
    cout << "|   ";
    SetConsoleTextAttribute(color, 13);
    cout << "9   \n\n\n";

    SetConsoleTextAttribute(color, 2);
    cout << setw(120) << "       |       |       \n";

    color_change(0, 0);
    cout << setw(99) << "   " << ttt[0][0];
    SetConsoleTextAttribute(color, 2);
    cout << "   |   ";
    color_change(0, 1);
    cout << ttt[0][1];
    SetConsoleTextAttribute(color, 2);
    cout << "   |   ";
    color_change(0, 2);
    cout << ttt[0][2] << endl;

    SetConsoleTextAttribute(color, 2);
    cout << setw(120) << "_______|_______|_______\n";
    cout << setw(120) << "       |       |       \n";

    color_change(1, 0);
    cout << setw(99) << "   " << ttt[1][0];
    SetConsoleTextAttribute(color, 2);
    cout << "   |   ";
    color_change(1, 1);
    cout << ttt[1][1];
    SetConsoleTextAttribute(color, 2);
    cout << "   |   ";
    color_change(1, 2);
    cout << ttt[1][2] << endl;

    SetConsoleTextAttribute(color, 2);
    cout << setw(120) << "_______|_______|_______\n";

    cout << setw(120) << "       |       |       \n";

    color_change(2, 0);
    cout << setw(99) << "   " << ttt[2][0];
    SetConsoleTextAttribute(color, 2);
    cout << "   |   ";
    color_change(2, 1);
    cout << ttt[2][1];
    SetConsoleTextAttribute(color, 2);
    cout << "   |   ";
    color_change(2, 2);
    cout << ttt[2][2] << endl;

    SetConsoleTextAttribute(color, 2);
    cout << setw(120) << "       |       |       \n";

    SetConsoleTextAttribute(color, 7);
}

// check in this
bool common::valid()
{
    if (turn % 2 == 1)
        ox = 'X';
    else
        ox = 'O';
    if (pos == '1' && ttt[0][0] == ' ')
        ttt[0][0] = ox;
    else if (pos == '2' && ttt[0][1] == ' ')
        ttt[0][1] = ox;
    else if (pos == '3' && ttt[0][2] == ' ')
        ttt[0][2] = ox;
    else if (pos == '4' && ttt[1][0] == ' ')
        ttt[1][0] = ox;
    else if (pos == '5' && ttt[1][1] == ' ')
        ttt[1][1] = ox;
    else if (pos == '6' && ttt[1][2] == ' ')
        ttt[1][2] = ox;
    else if (pos == '7' && ttt[2][0] == ' ')
        ttt[2][0] = ox;
    else if (pos == '8' && ttt[2][1] == ' ')
        ttt[2][1] = ox;
    else if (pos == '9' && ttt[2][2] == ' ')
        ttt[2][2] = ox;
    else
    {
        cout << endl
             << setw(121) << "Enter a valid position.\n";
        return false;
    }
    return true;
}

bool common::winner()
{
    if ((ttt[0][0] == ttt[0][1] && ttt[0][1] == ttt[0][2] && ttt[0][0] != ' ') ||
        (ttt[1][0] == ttt[1][1] && ttt[1][1] == ttt[1][2] && ttt[1][1] != ' ') ||
        (ttt[2][0] == ttt[2][1] && ttt[2][1] == ttt[2][2] && ttt[2][2] != ' ') ||
        (ttt[0][0] == ttt[1][0] && ttt[1][0] == ttt[2][0] && ttt[0][0] != ' ') ||
        (ttt[0][1] == ttt[1][1] && ttt[1][1] == ttt[2][1] && ttt[1][1] != ' ') ||
        (ttt[0][2] == ttt[1][2] && ttt[1][2] == ttt[2][2] && ttt[2][2] != ' ') ||
        (ttt[0][0] == ttt[1][1] && ttt[1][1] == ttt[2][2] && ttt[1][1] != ' ') ||
        (ttt[2][0] == ttt[1][1] && ttt[1][1] == ttt[0][2] && ttt[1][1] != ' '))
    {
        file.open("history.dat", ios::in | ios::app);
        if (turn % 2 == 0)
        {
            time(&now);
            SetConsoleTextAttribute(color, 4);
            cout << "\n"
                 << setw(100 + (player1.size() / 2)) << player1 << " wins the game.\n";
            file << player1 << " vs " << player2;
            for (i = 0; i < (54 - (player1.length() + player2.length())); i++)
                file << " ";
            file << player1;
            for (i = 0; i < (30 - player1.length()); i++)
                file << " ";
            file << asctime(localtime(&now));
            SetConsoleTextAttribute(color, 7);
        }
        else
        {
            SetConsoleTextAttribute(color, 1);
            cout << "\n"
                 << setw(100 + (player2.size() / 2)) << player2 << " wins the game.\n";
            file << player1 << " vs " << player2;
            for (i = 0; i < (54 - (player1.length() + player2.length())); i++)
                file << " ";
            file << player2;
            for (i = 0; i < (30 - player2.length()); i++)
                file << " ";
            file << asctime(localtime(&now));
            SetConsoleTextAttribute(color, 7);
        }
        file.close();
        return true;
    }
    return false;
}

void computer::computer_choice()
{
    // check whether player wins
    if (is_winning('O'))
        return;
    else if (is_winning('X'))
        return;
    // create a strategy
    else if (level == '1' || level == 'E' || level == 'e')
    {
        // if (easy_strategy())
        any_address();
        return;
    }
    else if (level == '2' || level == 'H' || level == 'h')
    {
        if (hard_strategy())
            return;
        else
            any_address();
    }
    else
        any_address();
    // else random
}

bool computer::easy_strategy()
{
    // horizontal  strategy
    if ((ttt[0][0] == 'O' && ttt[0][1] == 'O') || (ttt[0][1] == 'O' && ttt[0][2] == 'O') || (ttt[0][0] == 'O' && ttt[0][2] == 'O'))
        while (1)
        {
            rand_value = (rand() % 6) + 3;
            if (random())
                return true;
        }
    else if ((ttt[1][0] == 'O' && ttt[1][1] == 'O') || (ttt[1][1] == 'O' && ttt[1][2] == 'O') || (ttt[1][0] == 'O' && ttt[1][2] == 'O'))
        while (1)
        {
            while (1)
            {
                rand_value = rand() % 9;
                if (rand_value != 3 && rand_value != 4 && rand_value != 5)
                    break;
            }
            if (random())
                return true;
        }
    else if ((ttt[2][0] == 'O' && ttt[2][1] == 'O') || (ttt[2][1] == 'O' && ttt[2][2] == 'O') || (ttt[2][0] == 'O' && ttt[2][2] == 'O'))
        while (1)
        {
            rand_value = rand() % 6;
            if (random())
                return true;
        }

    // vertical strategy
    else if ((ttt[0][0] == 'O' && ttt[1][0] == 'O') || (ttt[1][0] == 'O' && ttt[2][0] == 'O') || (ttt[0][0] == 'O' && ttt[2][0] == 'O'))
        while (1)
        {
            while (1)
            {
                rand_value = rand() % 9;
                if (rand_value != 0 && rand_value != 3 && rand_value != 6)
                    break;
            }
            if (random())
                return true;
        }
    else if ((ttt[0][1] == 'O' && ttt[1][1] == 'O') || (ttt[1][1] == 'O' && ttt[2][1] == 'O') || (ttt[0][1] == 'O' && ttt[2][1] == 'O'))
        while (1)
        {
            while (1)
            {
                rand_value = rand() % 9;
                if (rand_value != 1 && rand_value != 4 && rand_value != 7)
                    break;
            }
            if (random())
                return true;
        }
    else if ((ttt[0][2] == 'O' && ttt[1][2] == 'O') || (ttt[1][2] == 'O' && ttt[2][2] == 'O') || (ttt[0][2] == 'O' && ttt[2][2] == 'O'))
        while (1)
        {
            while (1)
            {
                rand_value = rand() % 9;
                if (rand_value != 2 && rand_value != 5 && rand_value != 8)
                    break;
            }
            if (random())
                return true;
        }

    // diagonal strategy
    else if ((ttt[0][0] == '0' && ttt[1][1] == 'O') || (ttt[1][1] == 'O' && ttt[2][2] == 'O') || (ttt[0][0] == 'O' && ttt[2][2] == 'O'))
        while (1)
        {
            while (1)
            {
                rand_value = rand() % 9;
                if (rand_value != 0 && rand_value != 4 && rand_value != 8)
                    break;
            }
            if (random())
                return true;
        }
    else if ((ttt[2][0] == '0' && ttt[1][1] == 'O') || (ttt[1][1] == 'O' && ttt[0][2] == 'O') || (ttt[2][0] == 'O' && ttt[0][2] == 'O'))
        while (1)
        {
            while (1)
            {
                rand_value = rand() % 9;
                if (rand_value != 2 && rand_value != 4 && rand_value != 6)
                    break;
            }
            if (random())
                return true;
        }
    return false;
}

bool computer::hard_strategy()
{
    bool placed = false;
    if (turn == 2)
    {
        if (ttt[1][1] == ' ')
        {
            ttt[1][1] = 'O';
            return true;
        }
        while (true)
        {
            // placing at place 1, 3, 7 or 9
            srand(time(0));
            rand_value = rand() % 4;
            if (rand_value == 0 && ttt[0][0] == ' ')
            {
                ttt[0][0] = 'O';
                return true;
            }
            else if (rand_value == 1 && ttt[0][2] == ' ')
            {
                ttt[0][2] = 'O';
                return true;
            }
            else if (rand_value == 2 && ttt[2][0] == ' ')
            {
                ttt[2][0] = 'O';
                return true;
            }
            else if (rand_value == 3 && ttt[2][2] == ' ')
            {
                ttt[2][2] = 'O';
                return true;
            }
        }
    }

    else if (turn == 4)
    {
        if (ttt[1][1] == 'X')
        {
            if (ttt[0][0] == ' ' && ttt[2][2] == ' ')
            {
                rand_value = rand() % 2;
                if (rand_value == 0)
                {
                    ttt[0][0] = 'O';
                    return true;
                }
                else
                {
                    ttt[2][2] = 'O';
                    return true;
                }
            }
            else
            {
                rand_value = rand() % 2;
                if (rand_value == 0)
                {
                    ttt[0][2] = 'O';
                    return true;
                }
                else
                {
                    ttt[2][0] = 'O';
                    return true;
                }
            }
        }

        else
        {
            // Placing at 2, 4, 6 or 8
            // case 1(turn == 4)
            if ((ttt[0][0] == 'X' && ttt[2][2] == 'X') || (ttt[0][2] == 'X' && ttt[2][0] == 'X'))
            {
                rand_value = rand() % 4;
                if (rand_value == 0)
                {
                    ttt[0][1] = 'O';
                    return true;
                }
                else if (rand_value == 1)
                {
                    ttt[1][0] = 'O';
                    return true;
                }
                else if (rand_value == 2)
                {
                    ttt[1][2] = 'O';
                    return true;
                }
                else if (rand_value == 3)
                {
                    ttt[2][1] = 'O';
                    return true;
                }
            }

            // Placing at
            // case 2(turn == 4)
            //_X_   X__     __X     _X_     _X_
            //$_$   $_$     $_$     $_$     $_$
            //_X_   _X_     _X_     X__     __X
            else if ((ttt[0][1] == 'X' && ttt[2][1] == 'X') || (ttt[0][0] == 'X' && ttt[2][1] == 'X') || (ttt[0][2] == 'X' && ttt[2][1] == 'X') ||
                     (ttt[0][1] == 'X' && ttt[2][0] == 'X') || (ttt[0][1] == 'X' && ttt[2][2] == 'X'))
            {
                rand_value = rand() % 2;
                if (rand_value == 0)
                {
                    ttt[1][0] = 'O';
                    return true;
                }
                else
                {
                    ttt[1][2] = 'O';
                    return true;
                }
            }
            else if ((ttt[1][0] == 'X' && ttt[1][2] == 'X') || (ttt[2][0] == 'X' && ttt[1][2] == 'X') || (ttt[0][0] == 'X' && ttt[1][2] == 'X') ||
                     (ttt[1][0] == 'X' && ttt[2][2] == 'X') || (ttt[1][0] == 'X' && ttt[0][2] == 'X'))
            {
                rand_value = rand() % 2;
                if (rand_value == 0)
                {
                    ttt[0][1] = 'O';
                    return true;
                }
                else
                {
                    ttt[2][1] = 'O';
                    return true;
                }
            }

            // case 4 all 4 conditions
            // possibility where a player can win the game which is ___%
            else if ((ttt[0][1] == 'X' && ttt[1][2] == 'X') || (ttt[0][1] == 'X' && ttt[1][0] == 'X') ||
                     (ttt[1][0] == 'X' && ttt[2][1] == 'X') || (ttt[2][1] == 'X' && ttt[1][2] == 'X'))
            {
                rand_value = rand() % 4;
                if (rand_value == 0)
                {
                    ttt[0][0] = 'O';
                    return true;
                }
                else if (rand_value == 1)
                {
                    ttt[0][2] = 'O';
                    return true;
                }
                else if (rand_value == 2)
                {
                    ttt[2][0] = 'O';
                    return true;
                }
                else if (rand_value == 3)
                {
                    ttt[2][2] = 'O';
                    return true;
                }
            }
        }
    }

    return false;
}

bool computer::is_winning(char temp)
{
    // horizontal
    for (i = 0; i < 3; i++)
    {
        if (ttt[i][0] == ' ' && ttt[i][1] == temp && ttt[i][2] == temp)
        {
            ttt[i][0] = 'O';
            return true;
        }
        if (ttt[i][0] == temp && ttt[i][1] == ' ' && ttt[i][2] == temp)
        {
            ttt[i][1] = 'O';
            return true;
        }

        if (ttt[i][0] == temp && ttt[i][1] == temp && ttt[i][2] == ' ')
        {
            ttt[i][2] = 'O';
            return true;
        }

        // vertical
        if (ttt[0][i] == ' ' && ttt[1][i] == temp && ttt[2][i] == temp)
        {
            ttt[0][i] = 'O';
            return true;
        }

        if (ttt[0][i] == temp && ttt[1][i] == ' ' && ttt[2][i] == temp)
        {
            ttt[1][i] = 'O';
            return true;
        }

        if (ttt[0][i] == temp && ttt[1][i] == temp && ttt[2][i] == ' ')
        {
            ttt[2][i] = 'O';
            return true;
        }
    }
    // diagonal1
    if (ttt[0][0] == ' ' && ttt[1][1] == temp && ttt[2][2] == temp)
    {
        ttt[0][0] = 'O';
        return true;
    }
    if (ttt[0][0] == temp && ttt[1][1] == ' ' && ttt[2][2] == temp)
    {
        ttt[1][1] = 'O';
        return true;
    }
    if (ttt[0][0] == temp && ttt[1][1] == temp && ttt[2][2] == ' ')
    {
        ttt[2][2] = 'O';
        return true;
    }

    // diagonal2
    if (ttt[2][0] == ' ' && ttt[1][1] == temp && ttt[0][2] == temp)
    {
        ttt[2][0] = 'O';
        return true;
    }
    if (ttt[2][0] == temp && ttt[1][1] == ' ' && ttt[0][2] == temp)
    {
        ttt[1][1] = 'O';
        return true;
    }
    if (ttt[2][0] == temp && ttt[1][1] == temp && ttt[0][2] == ' ')
    {
        ttt[0][2] = 'O';
        return true;
    }

    return false;
}

void computer::any_address()
{
    while (1)
    {
        rand_value = rand() % 9;
        if (random())
            return;
    }
}

void history()
{
    int color_change_number = 1;
    system("CLS");
    file.open("history.dat", ios::in | ios::app);
    if (file.eof())
    {
        cout << setw(103) << "There are no records.\n";
        file.close();
        return;
    }
    cout << setw(50);
    while (!file.eof())
    {
        if (color_change_number % 2 == 0)
            SetConsoleTextAttribute(color, 4);
        else
            SetConsoleTextAttribute(color, 1);
        history_ch = file.get();
        cout << history_ch;
        if (history_ch == '\n')
        {
            cout << setw(50);
            color_change_number++;
        }
    }
    file.close();
    SetConsoleTextAttribute(color, 7);
}

bool computer::random()
{
    if (rand_value == 0 && ttt[0][0] == ' ')
    {
        ttt[0][0] = 'O';
        return true;
    }
    else if (rand_value == 1 && ttt[0][1] == ' ')
    {
        ttt[0][1] = 'O';
        return true;
    }
    else if (rand_value == 2 && ttt[0][2] == ' ')
    {
        ttt[0][2] = 'O';
        return true;
    }
    else if (rand_value == 3 && ttt[1][0] == ' ')
    {
        ttt[1][0] = 'O';
        return true;
    }
    else if (rand_value == 4 && ttt[1][1] == ' ')
    {
        ttt[1][1] = 'O';
        return true;
    }
    else if (rand_value == 5 && ttt[1][2] == ' ')
    {
        ttt[1][2] = 'O';
        return true;
    }
    else if (rand_value == 6 && ttt[2][0] == ' ')
    {
        ttt[2][0] = 'O';
        return true;
    }
    else if (rand_value == 7 && ttt[2][1] == ' ')
    {
        ttt[2][1] = 'O';
        return true;
    }
    else if (rand_value == 8 && ttt[2][2] == ' ')
    {
        ttt[2][2] = 'O';
        return true;
    }
    return false;
}
