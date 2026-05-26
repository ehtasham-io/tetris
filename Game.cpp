#include <iostream>
#include <windows.h> // Needed for setting text cursor position and Sleep
using namespace std;

void setConsoleColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Get the console handle
    SetConsoleTextAttribute(hConsole, color);         // Set the color
}

void hideCursor()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = false; // Set the cursor visibility to false
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}

int main()
{
	hideCursor(); // Hide the cursor
    setConsoleColor(11); // Light Aqua
    cout<<""<<endl;

    const int size = 25;
    bool playfield[size * size] = {};   // Playfield is 25x25
    int figures[16] = {56, 146, 56, 146, 58, 178, 184, 154, 312, 210, 57, 150, 27, 27, 27, 27};
    
    /* 4 blocks in 4 orientations, encoded as binary 3x3 maps (9 bits)
       So for example L-block is 010 010 110 = 150
       block position (1 row=15) */
    
    int offset = 11;
    bool running = true;   // Flag: game is running?
    int time = 0;
    int key_delay = 0;
    int points = 0;
    bool increased_speed = true;   // Increased block speed flag
    int direction = 0;   // Block orientation
    int figure_number = 0;   // Block type
    bool collision = false;
    int new_position[2] = {};   // New position after applying controls, to test if input will cause a collision
    COORD coords = {0, 0};   // For setting console pos. to beginning
    
    for(int i = 0; i < size * size; i++)
	{
        playfield[i] = (i % size == 0 || i % size == size - 1 || i >= size * (size - 1));   // Draw the edge around playfield
    }

    while (running)   // Main loop
    { 
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coords);
        cout<<"<< Welcome To The Game! >>"<<endl;
        cout<<endl;
        cout<<"<<<<<<<<Points: "<<points<<">>>>>>>>"<<"\n";   // Set to 0,0 , output points
        time++;
        offset += size * (time % (2 - 1 * increased_speed) == 0);
        if (key_delay > 0)
		{
            key_delay--;   // Advance time, move block down, reduce key delay (key_delay)
        }
        
        collision = false;   // No collision?
        for (int i = 0; i < 9; i++) {
            collision += playfield[offset + i % 3 + i / 3 * size + size] * ((figures[figure_number * 4 + direction] & 1 << i) > 0);
            playfield[offset + i % 3 + i / 3 * size] += ((figures[figure_number * 4 + direction] & 1 << i) > 0);
			/* Collision>0 when there is something below active block, Draw the block */
        }
        for (int i = 0; i < size * size; i++) {
            if (playfield[i])
			{
                cout<<'*'; // Filled block
            }
//			else if (i % size== 0 || i % size == size - 1 || i >= size * (size - 1))
//			{
//                cout << '|'; // Border
//            }
			else
			{
                cout << ' '; // Empty space
            }
            if (i % size == size - 1) cout << endl;
        }
        if (!collision)
		{
            for (int i = 0; i < 9; i++)
			{
                playfield[offset + i % 3 + i / 3 * size] -= ((figures[figure_number * 4 + direction] & 1 << i) > 0);   // There was no collision?
            }
        }
		else
		{ // If so, erase the block, it will be drawn lower in next loop
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

        Sleep(50);   // Bad way of regulating speed
        new_position[0] = offset;
        new_position[1] = direction;   // Save the position and angle of the block
        if ((GetKeyState(VK_ESCAPE) & 0x8000))
		{
            running = false;
        }
        if ((GetKeyState(VK_RIGHT) & 0x8000) && (offset % size < size - 3))
		{
            offset++;
        }
        if ((GetKeyState(VK_LEFT) & 0x8000) && (offset % size > 0))
		{   
            offset--;
        }
        if ((GetKeyState(VK_DOWN) & 0x8000))
		{ 
            increased_speed = true;
        }
		else
		{
            increased_speed = false;
        }
        if ((GetKeyState(VK_UP) & 0x8000) && key_delay == 0)
		{
            direction = (direction + 1) % 4;
            key_delay = 2;
        }
        collision = false;
        for (int i = 0; i < 9; i++) {
            if (playfield[offset + i % 3 + i / 3 * size] + ((figures[figure_number * 4 + direction] & 1 << i) > 0) > 1)
			{
                collision = true;   // Controls cause the block to collide with something?
            }
        }
        if (collision)
		{   
            offset = new_position[0]; // Collision happened - reset position and angle (e.g. move was impossible)
            direction = new_position[1];
        }
        for (int j = 0; j < size - 1; j++)
		{   // Go through field rows
            collision = true;
            for (int i = 1; i < size - 1; i++)
			{
                if (playfield[j * size + i] == 0)
				{
                    collision = false;   // Test if we have a whole line
                }
            }
            if (collision)
			{  // Whole line? Remove blocks, add points...
                for (int i = 1; i < size - 1; i++)
				{
                    playfield[j * size + i] = 0;
                }
                points++;
                for (int j2 = j; j2 > 0; j2--)
				{
                    for (int i = 1; i < size - 1; i++)
					{   // Move everything above line one block down
                        playfield[j2 * size + i] = playfield[(j2 - 1) * size + i];
                    }
                }
            }
        }
    }
    cout<<endl;
    cout<<endl;
    setConsoleColor(10);
    cout<<"Game Over! <<>> Your Points = "<<points;
    return 0;
}
