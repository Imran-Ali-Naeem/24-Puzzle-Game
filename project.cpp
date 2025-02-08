#include <iostream>
#include <iomanip>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include<fstream>
#include<string>
#include<Windows.h>
void swap_initial(int display_initial[], int size1);
void swap_goal(int display_goal[], int size2);
void intit(int arry1[], int size3);
void goal(int arry2[], int size4);
bool is_solveable(int int_inversion[], int goal_inversion[], int size5);
void make_move(int init_st[]);
void legal_move(int init_st[]);
bool is_goal(int goal_st[], int init_st[]);
void resume();
void newgame();
void print_path();
using namespace std;
char path[1000];                                            //global char array for print path function
int path_counter = 0, position = 0;
ofstream pathin;                                           //global outputstream handler for storing previous path into file
void swap_initial(int display_initial[], int size1)
{
    for (int i = 0; i < size1; i++)
    {
        int swapR = rand() % 25;                           //random function to generate random index values to shuffle initial stage
        int temp_index;
        temp_index = display_initial[i];
        display_initial[i] = display_initial[swapR];
        display_initial[swapR] = temp_index;
    }
}
void swap_goal(int display_goal[], int size2)
{
    for (int i = 0; i < size2; i++)
    {
        int swapR = rand() % 25;                    //random function to generate random index values to shuffle goal stage
        int temp_index;
        temp_index = display_goal[i];
        display_goal[i] = display_goal[swapR];
        display_goal[swapR] = temp_index;
    }
}

void intit(int arry1[], int size3)
{
    ofstream output;
    output.open("initial.txt");                     //for file handling
    int initial_stage[5][5];
    int count = 0;

    for (int i = 0; i < size3 / 5; i++)
    {
        for (int j = 0; j < size3 / 5; j++)             //converting 1D array into 2D for display only
        {
            initial_stage[i][j] = arry1[count];
            count++;
        }
    }
    if (!output) {
        cout << " initial write File not open" << endl;
    }

    cout << "\n\n" << "\t\t\t\tInitial Stage" << endl;
    cout << "\t\t.........................................." << endl;
    int c = 4;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (i == 0 && j == 0)                                       //for sequence of table
            {
                cout << "\t\t" << "_________________________________________" << endl;
            }
            if (j == 0)
            {
                cout << "\t\t|";
            }
            if (initial_stage[i][j] == 0)
            {                                                           //selected 0 as blankspace
                output << 0 << " ";
                cout << setw(c) << " " << "\t|";
                continue;
            }
            output << initial_stage[i][j] << " ";
            cout << setw(c) << initial_stage[i][j] << "\t|";
        }
        cout << endl << "\t\t" << "|_______|_______|_______|_______|_______|" << endl;
    }
    output.close();
}

void goal(int arry2[], int size4)
{
    ofstream out;
    out.open("goal.txt", ios::out);                                     //file handling
    int goal_stage[5][5];
    int count = 0;
    for (int i = 0; i < size4 / 5; i++)
    {
        for (int j = 0; j < size4 / 5; j++)
        {
            goal_stage[i][j] = arry2[count];                            //1D arry of goal stage into 2D for cout
            count++;
        }
    }
    if (!out)
    {
        cout << " goal write file not open" << endl;
    }

    cout << "\n\n" << "\t\t\t\tGoal Stage" << endl;
    cout << "\t\t.........................................." << endl;
    int c = 4;
    for (int i = 0; i < 5; i++)
    {
        for (int k = 0; k < 5; k++)
        {
            if (i == 0 && k == 0)
            {
                cout << "\t\t" << "_________________________________________" << endl;
            }
            if (k == 0)
            {
                cout << "\t\t|";
            }
            if (goal_stage[i][k] == 0)
            {
                out << 0 << " ";
                cout << setw(c) << " " << "\t|";
                continue;
            }
            out << goal_stage[i][k] << " ";
            cout << setw(c) << goal_stage[i][k] << "\t|";
        }
        cout << endl << "\t\t" << "|_______|_______|_______|_______|_______|" << endl;
    }
    out.close();
}



bool is_solveable(int int_inversion[], int goal_inversion[], int size5)
{
    int inversion1 = 0, inversion2 = 0;
    for (int k = 0; k < size5; k++)
    {
        for (int c = k + 1; c < size5; c++)             //c=k+1 so it doesnot compare with same or previous index value
        {
            if (int_inversion[k] > int_inversion[c])
            {
                if (int_inversion[k] != 0 && int_inversion[c] != 0)
                {
                    inversion1++;
                }

            }
        }
    }
    for (int k = 0; k < size5; k++)
    {
        for (int c = k + 1; c < size5; c++)
        {
            if (goal_inversion[k] > goal_inversion[c])
            {
                if ((goal_inversion[k] != 0) && (goal_inversion[c] != 0))
                {
                    inversion2++;
                }
            }
        }
    }
    if (inversion1 % 2 == 0 && inversion2 % 2 == 0)
    {
        return true;
    }
    else if (inversion1 % 2 != 0 && inversion2 % 2 != 0)
    {
        return true;
    }
    else
        return false;
}

void search(int init_st[], int size)
{
    for (int i = 0; i < 25; i++)
    {                                                                   //to get the position of blankspace
        if (init_st[i] == 0)
        {
            position = i;
        }
    }
}


void make_move(int init_st[])
{
    cout << endl;
    cout << "\t\t\t\tLets Play";
    cout << endl << "\t\t.........................................." << endl;
    cout << endl << "\t\tYou can Press 0 to pause the game: ";
    cout << endl << "\t\t OR";
    legal_move(init_st);
    cout << endl << "\t\tUse arrow keys to move the tiltes : ";
    int temp = 0;
    char move = 0;
    while (1)
    {
        bool flage = false;
        move = _getch();                                                  //to get arrow keys
        if (move == '0') {
            exit(0);
        }
        if (move == 72 || move == 75 || move == 77 || move == 80)
        {
            if (flage == false)
            {
                switch (move)
                {

                case 72:                                                 // performing UP  move
                    if (position + 5 >= 25)
                    {
                        cout << endl << "\n\t\t\t\t\t\t-------illegal move------  ";
                        Sleep(2000);
                        break;
                    }
                    temp = init_st[position];
                    init_st[position] = init_st[position + 5];
                    init_st[position + 5] = temp;
                    move = 'U';
                    pathin << move;
                    path[path_counter] = move;
                    path_counter++;
                    break;

                case 75:                                                // performing left  move
                    if (position % 5 == 4)
                    {
                        cout << endl << "\n\t\t\t\t\t\t-------illegal move-------";
                        Sleep(2000);
                        break;
                    }
                    temp = init_st[position];
                    init_st[position] = init_st[position + 1];
                    init_st[position + 1] = temp;
                    move = 'L';
                    pathin << move;
                    path[path_counter] = move;
                    path_counter++;
                    break;

                case 77:                                               // performing Right  move
                    if (position % 5 == 0)
                    {
                        cout << endl << "\n\t\t\t\t\t\t--------illegal move--------";
                        Sleep(2000);
                        break;
                    }
                    temp = init_st[position];
                    init_st[position] = init_st[position - 1];
                    init_st[position - 1] = temp;
                    move = 'R';
                    pathin << move;
                    path[path_counter] = move;
                    path_counter++;
                    break;

                case 80:                                            // performing Down  move
                    if (position - 5 <= -1)
                    {
                        cout << endl << "\n\t\t\t\t\t\t--------illegal move--------";
                        Sleep(2000);
                        break;
                    }
                    temp = init_st[position];
                    init_st[position] = init_st[position - 5];
                    init_st[position - 5] = temp;
                    move = 'D';
                    pathin << move;
                    path[path_counter] = move;
                    path_counter++;
                    break;
                }

            }
            break;
        }
    }
}


void legal_move(int init_st[])
{
    int last_r_f_i = 20, last_r_l_i = 24;
    int first_r_f_i = 0, first_r_l_i = 4;
    int All_is_well = 0;
    int  ch = 1;
    cout << "\t\t\t\t\tPossible Movments: ";
    switch (ch)
    {
    case 1:
        if (position + 5 > last_r_l_i)                                                      // For last row 
        {
            if (position == last_r_f_i)
            {
                cout << " Down ";
                cout << " Left ";
                All_is_well = 1;
                break;
            }
            else if (position == last_r_l_i)
            {
                cout << " Down ";
                cout << " Right ";
                All_is_well = 1;
                break;
            }
            cout << " Down ";
            cout << " left ";
            cout << " Right ";
            All_is_well = 1;
        }
    case 2:                                                                               // For first row
        if (position - 5 < first_r_f_i)
        {
            if (position == first_r_f_i)
            {
                cout << " Up ";
                cout << " Left ";
                All_is_well = 1;
                break;
            }
            else if (position == first_r_l_i)
            {
                cout << " Up ";
                cout << " Right ";
                All_is_well = 1;
                break;
            }
            cout << " UP ";
            cout << " left ";
            cout << " Right ";
            All_is_well = 1;
        }
    case 3:                                                                             // for last column
        if (position % 5 == 4)
        {
            cout << " Down ";
            cout << " UP ";
            cout << " Right ";
            All_is_well = 1;
        }
    case 4:                                                                            // fir first column
        if (position % 5 == 0)
        {
            cout << " Down ";
            cout << " left ";
            cout << " UP ";
            All_is_well = 1;
        }
    }
    if (All_is_well == 0)
    {
        cout << " UP ";
        cout << " left ";
        cout << " Right ";
        cout << " Down ";
    }
}

bool is_goal(int initial_goal_1D[], int initial_1D[])
{
    for (int i = 0; i < 25; i++)
    {                                                 //to check initial stage matched with goal stage or not
        if (initial_goal_1D[i] != initial_1D[i])
        {
            return false;
        }
    }
    return true;
}

void resume()
{
    ifstream in;
    ifstream in2;
    int  size = 0, resume_int[50], resume_goal[50];
    string initial_str, goal_str;
    in.open("initial.txt", ios::in);
    if (!in)
    {
        cout << " initial read file not open" << endl;
    }
    else
        while (!in.eof())
        {
            in >> initial_str;
            resume_int[size] = stoi(initial_str);
            size++;                                     //reading data from file
        }
    in.close();
    size = 0;
    in2.open("goal.txt", ios::in);
    if (!in2)
    {
        cout << "goal read file not open" << endl;
    }
    else
        while (!in2.eof())
        {
            in2 >> goal_str;
            resume_goal[size] = stoi(goal_str);      //storing file data ino an 1D array
            size++;
        }
    in2.close();
    size = size - 1;                               //because it read last value 2 time
    goal(resume_goal, size);
    intit(resume_int, size);

    int i = 0;
    ifstream pathout;
    pathout.open("path.txt", ios::in);
    if (!pathout)
    {
        cout << "Path read file not open" << endl;
    }
    while (!pathout.eof())
    {
        pathout >> path[path_counter];
        path_counter++;
    }
    path_counter = path_counter - 1;              //because it read last value 2 time
    pathout.close();
    while (1)
    {
        if (is_goal(resume_goal, resume_int))
        {
            break;
        }
        search(resume_int, size);
        make_move(resume_int);
        system("cls");


        goal(resume_goal, size);
        intit(resume_int, size);
        i++;
    }
    print_path();
}

void newgame()
{
    srand((unsigned int)time(0));
    int goal_1D[25] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,0 },
        initial_1D[25] = { 24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0 };
    swap_initial(initial_1D, 25);
    swap_goal(goal_1D, 25);
    while (!is_solveable(initial_1D, goal_1D, 25))
    {
        swap_initial(initial_1D, 25);
    }
    goal(goal_1D, 25);
    intit(initial_1D, 25);

    int i = 0;
    pathin.open("path.txt", ios::out);
    if (!pathin)
    {
        cout << "Path write file not open" << endl;
    }
    while (1)
    {
        if (is_goal(goal_1D, initial_1D))
        {
            break;
        }
        search(initial_1D, 25);
        make_move(initial_1D);
        system("cls");
        goal(goal_1D, 25);
        intit(initial_1D, 25);
        i++;
    }
    pathin.close();
    print_path();

}

void print_path()
{
    cout << "PATH" << endl;
    for (int i = 0; i < path_counter; i++)
    {
        if (i == path_counter - 1)
        {
            cout << path[i];
        }
        else
            cout << path[i] << " --> ";
    }
    cout << endl;
}


int main()
{

    int choice;
    cout << endl << "\t\tYou can Pause the game in between : " << endl << endl;
    cout << "\t\t.........................................." << endl << endl;
    cout << "\t\tPress ____Any key____ to play new game: " << endl << endl;
    cout << "\t\t.........................................." << endl << endl;
    cout << "\t\tPress 1 to Resume from previous : ";
    cin >> choice;
    if (choice == 1)
    {
        resume();
    }
    else
    {
        newgame();
    }
    cout << endl;
    system("pause");
    return 0;
}
