#include <GLFW/glfw3.h>
#include<iostream>
#include"Animation.h"
#include <conio.h>
#include <cstdlib>
#include<string>
#include <crtdbg.h>
#include<time.h>
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW

#define FRAME_RATE   1.0f/60.0f   // Controls the frame rate of the animation
#define TIME_BEFORE_WE_COUNT 5.0f  // giving some time for the balls to mix together
const int Width = 800; // Window width.
const int Height = 600; // Window height.

using namespace std;

int main() {
    {
        srand(time(NULL));
        int input;
        double current_time = 0, previous_time = 0;
        bool begin = false;
        input=user_input_menu_selection();
        if (input == 0)
        {
            cout << "Standard Mini square simulation" << endl;
            cout << "You can control the mini squares colors" << endl;
            cout << "Press any key to start simulation" << endl;
            _getch();
            system("CLS");
            WindowGenerator window_0(Width, Height,0.1f);  // Create a 800x600 window
            while (!window_0.shouldClose()) {
                current_time = glfwGetTime();
                if (current_time - previous_time >= FRAME_RATE)
                {
                    previous_time = current_time;
                    window_0.draw_Mini_square();
                    window_0.refresh();
                    window_0.processEvents();  // Process events (if any)
                    window_0.processInput_color();
                }

            }

        }
        else if (input == 1)
        {
            cout << "The following simulation gives 5 seconds for all the sqaures to move around before we start counting the total collision time" << endl;
            cout << "Press any key to start simulation" << endl;
            _getch();
            system("CLS");
            WindowGenerator window_1(Width, Height, 0.1f);  // Create a 800x600 window
            while (!window_1.shouldClose()){
                current_time = glfwGetTime();
                if (current_time >= TIME_BEFORE_WE_COUNT)
                {
                    begin = true;
                }
                if (current_time - previous_time >= FRAME_RATE)
                {
                    previous_time = current_time;
                    window_1.collision_time(begin);
                    window_1.refresh();
                    window_1.processEvents();  // Process events (if any)
                }
                if (window_1.check_collision_criteria() == true) //all mini squares collided, we can exit the animation.
                {
                    break;
                }
            }
            cout << "The time it took all the balls to collide is:  " << current_time - TIME_BEFORE_WE_COUNT << " seconds" << endl;
        }
        else if (input == 2)
        {
            cout << "Press any key to start simulation" << endl;
            _getch();
            system("CLS");
            WindowGenerator window_2(Width, Height, 0.25f);  // Create a 800x600 window
            while (!window_2.shouldClose()) {
                current_time = glfwGetTime();
                if (current_time - previous_time >= FRAME_RATE)
                {
                    previous_time = current_time;
                    window_2.draw_spinning_square();
                    window_2.refresh();
                    window_2.processEvents();  // Process events (if any)
                }

            }

        }


    }
    cout << endl;
    cout << "Leaks: " << _CrtDumpMemoryLeaks() << endl;
    return 0;
}


