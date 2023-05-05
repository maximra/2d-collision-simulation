#include "Animation.h"
#include<iostream>
#include <conio.h>
#include <cstdlib>


using namespace std;

WindowGenerator::WindowGenerator(const int& width, const int& height, const float& size)  // Constructor (Responsible for generating the window itself)
{ 
    Red = 1.0f;  //Define colors as white at start.
    Green = 1.0f;
    Blue = 1.0f;
    m_width = width;
    m_height = height;
    m_size = size;
    // Initialize GLFW library
    glfwInit();

    // Create a window
    m_window = glfwCreateWindow(m_width, m_height, "Window Generator", NULL, NULL);

    // Set the window as the current OpenGL context
    glfwMakeContextCurrent(m_window);

    // Set the viewport to the entire window
    glViewport(0, 0, m_width, m_height);

    // Set the clear color to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    x_location = new float[SIZE];  //Allocation of memory for the mini squares that collide 
    y_location = new float[SIZE]; 
    x_speed = new float[SIZE];
    y_speed = new float[SIZE];


    red_data = new bool[SIZE]; //Responsible to indicate when  all the  balls have collided
    for (int i = 0; i < SIZE; i++)
    {
        red_data[i] = true;
    }

    for (int i = 0; i < SIZE; i++) // Generate their start positions
    {
        x_location[i] = +0.25f + 0.f + float(i) / float(25);
        y_location[i] = -0.25f + 0.f + float(i) / float(25);
    }
    define_start_positon();               // Adjust positions to avoid zero time collission 
    for (int i = 0; i < SIZE; i++)   // give speed 
    {
        if (rand() % 2 == 0)
        {
            x_speed[i] = 0.01f;
        }
        else
        {
            x_speed[i] = -0.01f;
        }
        if (rand() % 2 == 0)
        {

            y_speed[i] = 0.01f;
        }
        else
        {
            y_speed[i] = -0.01f;
        }

    }


    /// From here we work on the spinning squares
    angle = 0; // define the starting angle as zero.
    angular_speed = 1; // define the spinning direction as counter clockwise 
    x_direction_1 = new double[FULL_LOOP];       //Allocating memory
    x_direction_2 = new double[FULL_LOOP];
    x_direction_3 = new double[FULL_LOOP];
    x_direction_4 = new double[FULL_LOOP];

    y_direction_1 = new double[FULL_LOOP];
    y_direction_2 = new double[FULL_LOOP];
    y_direction_3 = new double[FULL_LOOP];
    y_direction_4 = new double[FULL_LOOP];


    for (int i = 0; i < FULL_LOOP; i++)         // Pre defining the locations of the square for optimal results 
    {
        x_direction_1[i] = m_size * cos((PI * double(2 * i)) / FULL_LOOP);
        x_direction_2[i] = m_size * cos(((PI * double(2 * i)) / FULL_LOOP)+PI/2);
        x_direction_3[i] = m_size * cos(((PI * double(2 * i)) / FULL_LOOP) + PI );
        x_direction_4[i] = m_size * cos(((PI * double(2 * i)) / FULL_LOOP) + PI*(double(3)/ double(2)));
        y_direction_1[i] = m_size * sin((PI * double(2 * i)) / FULL_LOOP);
        y_direction_2[i] = m_size * sin(((PI * double(2 * i)) / FULL_LOOP) + PI / 2);
        y_direction_3[i] = m_size * sin(((PI * double(2 * i)) / FULL_LOOP) + PI);
        y_direction_4[i] = m_size * sin(((PI * double(2 * i)) / FULL_LOOP) + PI * (double(3) / double(2)));;
    }

}

WindowGenerator::~WindowGenerator() // Destuctor (Responsible for closing the window).
{
    // Destroy the window and terminate GLFW
    glfwDestroyWindow(m_window);
    glfwTerminate(); 
    delete[] x_location;    // Clearing memory from mini squares
    delete[] y_location;
    delete[] x_speed;
    delete[] y_speed;
    delete[] red_data;     // destroying the array of data that indicated collisions 


    delete[] x_direction_1; // Clearing memory for spinning square
    delete[] x_direction_2;
    delete[] x_direction_3;
    delete[] x_direction_4;


    delete[] y_direction_1;
    delete[] y_direction_2;
    delete[] y_direction_3;
    delete[] y_direction_4;
}



bool WindowGenerator::shouldClose()
{
    // Check if the window should close (e.g. user clicked the close button)
    return glfwWindowShouldClose(m_window);
}

void WindowGenerator::processEvents()
{
    // Poll for and process events (e.g. window resize, key presses)
    glfwPollEvents();
}

void WindowGenerator::refresh()
{
    // Swap the front and back buffers (double buffering)
    glfwSwapBuffers(m_window);
}


void WindowGenerator::draw_Mini_square()
{
    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Set the colors
    glColor3f(Red, Green, Blue);

    // Draw a hollow square
    for (int i = 0; i < SIZE; i++)
    {

        glBegin(GL_LINE_LOOP);
        glVertex2f(-0.01f + x_location[i], -0.01f + y_location[i]);
        glVertex2f(-0.01f + x_location[i], +0.01f + y_location[i]);
        glVertex2f(+0.01f + x_location[i], +0.01f + y_location[i]);
        glVertex2f(+0.01f + x_location[i], -0.01f + y_location[i]);
        glEnd();
    }
    // Draw a hollow square
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.8f, -0.8f);
    glVertex2f(-0.8f, 0.8f);
    glVertex2f(0.8f, 0.8f);
    glVertex2f(0.8f, -0.8f);
    glEnd();

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (j != i and (abs(x_location[i] - x_location[j]) <= 0.06) and (abs(y_location[i] - y_location[j]) <= 0.06))
            {
                if (x_speed[i] == x_speed[j])
                {
                    y_speed[i] = -y_speed[i];
                    y_speed[j] = -y_speed[j];
                }
                else if (y_speed[i] == y_speed[j])
                {
                    x_speed[i] = -x_speed[i];
                    x_speed[j] = -x_speed[j];
                }
                else
                {
                    y_speed[i] = -y_speed[i];
                    y_speed[j] = -y_speed[j];
                    x_speed[i] = -x_speed[i];
                    x_speed[j] = -x_speed[j];
                }
            }
        }
    }
    for (int i = 0; i < SIZE; i++)
    {
        x_location[i] += x_speed[i];
        y_location[i] += y_speed[i];
    }
    for (int i = 0; i < SIZE; i++)
    {
        if (x_location[i] >= 0.78f or x_location[i] <= -0.78f)
        {
            x_speed[i] = -x_speed[i];
            if (x_location[i] > 0.78f or x_location[i] < -0.78f)
            {
                x_location[i] = x_location[i] + x_speed[i];
            }
        }

        if (y_location[i] >= 0.78f or y_location[i] <= -0.78f)
        {
            y_speed[i] = -y_speed[i];
            if (y_location[i] > 0.78f or y_location[i] < -0.78f)
            {
                y_location[i] = y_location[i] + y_speed[i];
            }
        }
    }


}

void WindowGenerator::draw_spinning_square()
{
    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Set the colors
    glColor3f(1.0f, 1.0f, 1.0f);

    // Draw spinning square
    glBegin(GL_LINE_LOOP); 
    glVertex2f(x_direction_1[angle], y_direction_1[angle]);
    glVertex2f(x_direction_2[angle], y_direction_2[angle]);
    glVertex2f(x_direction_3[angle], y_direction_3[angle]);
    glVertex2f(x_direction_4[angle], y_direction_4[angle]);
    glEnd();


    angle += angular_speed;
    if (angle >= FULL_LOOP)
    {
        angle -= FULL_LOOP;
    }


    glColor3f(1.0f, 1.0f, 1.0f);
    // Draw a hollow square
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.8f, -0.8f);
    glVertex2f(-0.8f, 0.8f);
    glVertex2f(0.8f, 0.8f);
    glVertex2f(0.8f, -0.8f);
    glEnd();
}

void WindowGenerator::collision_time(const bool & begin)
{
    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);



    // Draw a hollow square
    for (int i = 0; i < SIZE; i++)
    {
        // Set the colors
        if (red_data[i] == true)  //The ball didn't collide yet.
        {
            glColor3f(0.0f, 1.0f, 0.0f);
        }
        else                      // Collission occured
        {
            glColor3f(1.0f, 0.0f, 0.0f);
        }
        glBegin(GL_LINE_LOOP);
        glVertex2f(-0.01f + x_location[i], -0.01f + y_location[i]);
        glVertex2f(-0.01f + x_location[i], +0.01f + y_location[i]);
        glVertex2f(+0.01f + x_location[i], +0.01f + y_location[i]);
        glVertex2f(+0.01f + x_location[i], -0.01f + y_location[i]);
        glEnd();
    }
    // Draw a hollow square
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.9f, -0.9f);
    glVertex2f(-0.9f, 0.9f);
    glVertex2f(0.9f, 0.9f);
    glVertex2f(0.9f, -0.9f);
    glEnd();

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (j != i and (abs(x_location[i] - x_location[j]) <= 0.06) and (abs(y_location[i] - y_location[j]) <= 0.06))
            {
                if (begin == true)
                {
                    if (red_data[i] == true)
                    {
                        red_data[i] = false;
                        red_counter++;
                    }
                    if (red_data[j] == true)
                    {
                        red_data[j] = false;
                        red_counter++;
                    }
                }
                if (x_speed[i] == x_speed[j])
                {
                    y_speed[i] = -y_speed[i];
                    y_speed[j] = -y_speed[j];
                }
                else if (y_speed[i] == y_speed[j])
                {
                    x_speed[i] = -x_speed[i];
                    x_speed[j] = -x_speed[j];
                }
                else
                {
                    y_speed[i] = -y_speed[i];
                    y_speed[j] = -y_speed[j];
                    x_speed[i] = -x_speed[i];
                    x_speed[j] = -x_speed[j];
                }
            }
        }
    }
    for (int i = 0; i < SIZE; i++)
    {
        x_location[i] += x_speed[i];
        y_location[i] += y_speed[i];
    }
    for (int i = 0; i < SIZE; i++)
    {
        if (x_location[i] >= 0.88f or x_location[i] <= -0.88f)
        {
            x_speed[i] = -x_speed[i];
            if (x_location[i] > 0.88f or x_location[i] < -0.88f)
            {
                x_location[i] = x_location[i] + x_speed[i];
            }
        }

        if (y_location[i] >= 0.88f or y_location[i] <= -0.88f)
        {
            y_speed[i] = -y_speed[i];
            if (y_location[i] > 0.88f or y_location[i] < -0.88f)
            {
                y_location[i] = y_location[i] + y_speed[i];
            }
        }
    }

}

void WindowGenerator::define_start_positon()  // This function makes sure that the positions at time zero dont collide 
{
    float current_rand;
    for (int i = 0; i < SIZE; i++)
    {
        current_rand = float(rand() % 1000) / float(2000);
        x_location[i] = 0.f + current_rand;
        current_rand = float(rand() % 1000) / float(2000);
        y_location[i] = 0.f + current_rand;
    }


    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (j != i and (abs(x_location[i] - x_location[j]) <= 0.2) and (abs(y_location[i] - y_location[j]) <= 0.2))
            {

                while ((abs(x_location[i] - x_location[j]) <= 0.2) and (abs(y_location[i] - y_location[j]) <= 0.2))
                {
                    current_rand = float(rand() % 1000) / float(2000);
                    x_location[j] = 0.f + current_rand;
                    current_rand = float(rand() % 1000) / float(2000);
                    y_location[j] = 0.f + current_rand;
                }
                j = 0;
            }
        }
    }
    cout << "done with function" << endl;
}

void WindowGenerator::processInput_color()  //controls the colors of animation 
{
    if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        if (Red >= 0.f)
            Red -= 0.01f;
    }
    else if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        if (Red <= 1.f)
            Red += 0.01f;
    }
    else if (glfwGetKey(m_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        if (Green >= 0.f)
            Green -= 0.01f;
    }
    else if (glfwGetKey(m_window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        if (Green <= 1.f)
            Green += 0.01f;
    }
    else if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
    {
        if (Blue >= 0.f)
            Blue -= 0.01f;
    }
    else if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
    {
        if (Blue <= 1.f)
            Blue += 0.01f;
    }

}

bool WindowGenerator::check_collision_criteria()
{
    if (red_counter != SIZE)  //criteria not reached yet.
        return false;
    else         //criteria reached.
        return true;
}








int user_input_menu_selection()
{
        int number;

    while (true) {

        cout << "Menu list:" << endl;
        cout << endl;
        cout << "Option 0: Activates the standard simulation" << endl;
        cout << "Option 1: Activates the collision simulation" << endl;
        cout << "Option 2: Activates the spinning simulation" << endl;
        cout << "Enter an integer: ";
        std::cin >> number;
        system("CLS");
        if (std::cin.fail()) {
            system("CLS");
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Press any key to continue." << endl;
            _getch();
            system("CLS");
            continue;
        }

        switch (number) {
        case 0:
            system("CLS");
            cout << "You entered zero. Generating standard mini square animation." << std::endl;
            return 0;
        case 1:
            system("CLS");
            cout << "You entered one. Entering collision simulation." << std::endl;
            return 1;
        case 2:
            system("CLS");
            cout << "You entered two. Entering spinning square simulation" << std::endl;
            return 2;
        default:
            system("CLS");
            cout << "You entered a number other than zero, one, or two." << std::endl;
            continue;
        }

    }
}
