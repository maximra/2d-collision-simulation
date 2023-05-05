#pragma once
#include <GLFW/glfw3.h>
#include<random>
#include<cmath>
#include<string>

#define SIZE 15
#define FULL_LOOP 360

#define PI 3.1415926535

class WindowGenerator {
public:
	WindowGenerator(const int& width, const int& height, const float & size);
	~WindowGenerator();

	bool shouldClose();  //Window related functions.
	void processEvents();
	void refresh();

	void draw_Mini_square();						//Draws the mini squares with color control
	void draw_spinning_square();					// Draws the spinning square 
	void collision_time(const bool& begin);			// Draws the mini squares, colors those that collide, exits the function when all of them collided.
	void define_start_positon();					// Defines start position for all mini squares to avoid collision at time zero. 
	void processInput_color();						// Controls the colors of the squares
	bool check_collision_criteria();				// exits the main loop when the red_counter=SIZE 




private:
	GLFWwindow* m_window; // Window object itself
	int m_width, m_height;  // Window width and height


	//Those arrays are responsible for the mini squares 
	float* x_location;	 //Mini squares horizontal location.
	float* y_location;		// Mini squares vertical location.
	float* x_speed;  // Mini squares horizontal speed.
	float* y_speed;  // Mini squares vertical speed.
	bool* red_data; // Variable that indicates when all of them collides into each other.
	int  red_counter=0; // counts amount of times the squares collided, when this is equal to the SIZE , we exit the functiom


	float Red;  // colors
	float Green;
	float Blue;

	//////////////////////////

	// variables for spinning squares

	float m_size;            // Size of each side of the spinning square.
	double* x_direction_1;   // those variables control the location of the spinning square in the x direction.
	double* x_direction_2;
	double* x_direction_3;
	double* x_direction_4;

	double* y_direction_1;   // those variables control the location of the spinning square in the y direction.
	double* y_direction_2;
	double* y_direction_3;
	double* y_direction_4;

	int angle;   // dictates the current angle of the spinning square
	int angular_speed;  //dictates the angular speed of the square 
};


 int user_input_menu_selection(); //function that is responsible for input