#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <conio.h>

using namespace std;

string name[100];
string user_name;
int idx = 0;

void setConsoleColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void write()
{
	setConsoleColor(03);
    cout << "--- Enter The User Name: ---" << endl;
    cout << endl;
    cin >> user_name;
    cout << endl;
}

void store_username()
{
    fstream nfile;
    nfile.open("sign.txt", ios::out);
    nfile << user_name << endl;
    nfile.close();
}

void read()
{
    string word;
    fstream file;
    file.open("sign.txt", ios::in);
   
    while(getline(file, word))
	{  
        name[idx] = word;
        idx++;
    }
    file.close();
}

void display(int ind)
{
	cout << "Sign Up Successfully!" << endl;
}

void hideCursor()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void play()
{
    hideCursor();
    setConsoleColor(11);
    cout << "" << endl;

    const int size = 20;
    bool playfield[size * size] = {};
    int figures[16] = {56, 146, 56, 146, 58, 178, 184, 154, 312, 210, 57, 150, 27, 27, 27, 27};
    
    /* 4 blocks in 4 orientations, encoded as binary 3x3 maps (9 bits)
       So for example L-block is 010 010 110 = 150
       block position (1 row=15) */
    
    int offset = 11;
    bool running = true;
    int time = 0;
    int key_delay = 0;
    int points = 0;
    bool increased_speed = true;
    int direction = 0;
    int figure_number = 0;
    bool collision = false;
    int new_position[2] = {};
    COORD coords = {0, 0};
    
    for(int i = 0; i < size * size; i++)
	{
        playfield[i] = (i % size == 0 || i % size == size - 1 || i >= size * (size - 1));
		  
        /* Draw the edge around playfield */
        
    }

    while(running)
	{ 
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coords);
        cout << "<< Welcome To The Game! >>" << endl;
        cout << endl;
        cout << "<<<<<Points : " << points << ">>>>>" << endl;
        time++;
        offset += size * (time % (2 - 1 * increased_speed) == 0);
        if(key_delay > 0)
		{
            key_delay--;
            
            /* Advance time, move block down, reduce key delay (key_delay) */
            
        }
        
        collision = false;
        for(int i = 0; i < 16; i++)
		{
            collision += playfield[offset + i % 3 + i / 3 * size + size] * ((figures[figure_number * 4 + direction] & 1 << i) > 0);
            playfield[offset + i % 3 + i / 3 * size] += ((figures[figure_number * 4 + direction] & 1 << i) > 0);
            
            /* Collision>0 when there is something below active block, Draw the block */
            
        }
        
        for(int i = 0; i < size * size; i++)
		{
            if(playfield[i])
			{
                cout << '*';
            }
			else
			{
                cout << ' ';
            }
            if(i % size == size - 1)
			{
                cout << endl;
            }
        }

        if(!collision)
		{
            for(int i = 0; i < 9; i++)
			{
                playfield[offset + i % 3 + i / 3 * size] -= ((figures[figure_number * 4 + direction] & 1 << i) > 0);
                
				/* There was no collision? */
				
            }
        }
		else
		{
            /* If so, erase the block, it will be drawn lower in next loop */
            
            if (offset < size)
			{
                running = false;
            }
            offset = 1;
            figure_number = rand() % 4;
            direction = 0;
            increased_speed = false;
            
            /* Collision happened? 
            put the block and create a new one. 
            We are at the top? Game over. */
            
        }

        Sleep(50);
        new_position[0] = offset;
        new_position[1] = direction;
        if((GetKeyState(VK_ESCAPE) & 0x8000))
		{
            running = false;
        }
        if((GetKeyState(VK_RIGHT) & 0x8000) && (offset % size < size - 3))
		{
            offset++;
        }
        if((GetKeyState(VK_LEFT) & 0x8000) && (offset % size > 0))
		{   
            offset--;
        }
        if((GetKeyState(VK_DOWN) & 0x8000))
		{ 
            increased_speed = true;
        }
		else
		{
            increased_speed = false;
        }
        if((GetKeyState(VK_UP) & 0x8000) && key_delay == 0)
		{
            direction = (direction + 1) % 4;
            key_delay = 2;
        }
        
        collision = false;
        for(int i = 0; i < 9; i++)
		{
            if(playfield[offset + i % 3 + i / 3 * size] + ((figures[figure_number * 4 + direction] & 1 << i) > 0) > 1) {
                collision = true;
                
                /* Controls cause the block to collide with something? */
                
            }
        }
        if(collision)
		{   
            offset = new_position[0];
            direction = new_position[1];
        }
        for(int j = 0; j < size - 1; j++)
		{
            collision = true;
            for(int i = 1; i < size - 1; i++)
			{
                if(playfield[j * size + i] == 0)
				{
                    collision = false;
                }
            }
            if(collision)
			{
                for (int i = 1; i < size - 1; i++)
				{
                    playfield[j * size + i] = 0;
                }
                points++;
                for(int j2 = j; j2 > 0; j2--)
				{
                    for(int i = 1; i < size - 1; i++)
					{
                        playfield[j2 * size + i] = playfield[(j2 - 1) * size + i];
                    }
                }
            }
        }
    }
    cout << endl;
    cout << endl;
    setConsoleColor(10);
    cout << "Game Over! <<>> Your Points = " << points;   
}

int main() {
    int option;
    string entered_name;
	
	setConsoleColor(11);
    cout << "<<< Welcome To The Game >>>" << endl;
    cout << endl;
    setConsoleColor(03);
    cout << "1. Sign In" << endl;
    setConsoleColor(03);
    cout << "2. Sign Up" << endl;
    cout << endl;
    setConsoleColor(11);
    cout << "* Enter Any Option: ";
    cin >> option;
    cout << endl;

    if (option == 1)
	{
        read();
        setConsoleColor(03);
        cout << "Enter Your Name: ";
        cin >> entered_name;
        cout << endl;
        
        bool found = false;
        for(int i = 0; i < idx; i++)
		{
            if(entered_name == name[i])
			{
            	display(i);
                found = true;
                system ("cls");
                play();
                break;
            }
        }
        
        if(!found)
		{
			setConsoleColor(02);
            cout << "<<< User Not Found. Please Sign Up. >>>" << endl;
            cout << "<<< Press Any Key To Return To Main Menu. (Then Sign In) >>>" << endl;
            cout << endl;
			getch();
		  	main();
        }
    }
	else if(option == 2)
	{
        write();
        store_username();
        setConsoleColor(02);
		cout << "<<< Sign up successful >>>" << endl;
        cout << "<<< Press Any Key To Return To Main Menu. (Then Sign In) >>>" << endl;
        cout << endl;
		getch();	
        main();
    }
	else
	{
        cout << "Invalid Option!" << endl;
    }
    return 0;
}
