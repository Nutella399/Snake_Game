#include "pch.h"
#include <SFML/Graphics.hpp>   //using namespace sf
#include <time.h>

//dimensions for window size and background
int num_vertBox = 30, num_horzBox = 20;
int size = 16; //number of pixels
int w = size * num_horzBox;  //background number of pixels in width
int h = size * num_vertBox;    //background number of pixels in height

//Snake variables to dertermine length and direction
int direction_1 = -1, direction_2 = -1;    //direction the snake is moving 
int snake_1_length = 4; //initial size is 4 
int snake_2_length = 4; //initial size is 4 
float timer = 0.0f, delay = 0.1f;

//Actual Snake in game is an array of x,y coordinates of sprite2
struct Snake1
{
	int x, y;        //each sprite of snake needs an x,y coordinate
}s1[100];

struct Snake2
{
	int x, y;        //each sprite of snake needs an x,y coordinate
}s2[100];

//***NEW*** this is the fruit or food that the snake will eat
struct Fruit
{
	int x, y;    // only need one sprite needed for one food item
}food;

//move snake head based on user input and body by incrementing 
//forward by iterating through arrays previous position
void move_1() {

	

	for (int i = snake_1_length; i > 0; i--)
	{
		s1[i].x = s1[i - 1].x;
		s1[i].y = s1[i - 1].y;
	}
	if (direction_1 == 0)
		s1[0].y -= 1;

	if (direction_1 == 1)
		s1[0].y += 1;

	if (direction_1 == 2)
		s1[0].x -= 1;

	if (direction_1 == 3)
		s1[0].x += 1;


	if (((s1[0].x) == food.x) && ((s1[0].y) == food.y))
	{
		snake_1_length++;
		delay -= 0.001f; 
		food.x = rand() % num_horzBox;
		food.y = rand() % num_vertBox;
	}

	if (s1[0].x > num_horzBox)
		s1[0].x = 0;
	if (s1[0].x < 0)
		s1[0].x = num_horzBox;
	if (s1[0].y > num_vertBox)
		s1[0].y = 0;
	if (s1[0].y < 0)
		s1[0].y = num_vertBox;

	for (int i = 1; i < snake_1_length; i++)
	{
		if (s1[0].x == s1[i].x && s1[0].y == s1[i].y)
			snake_1_length = i;
	}
	
}

void move_2() {
	for (int i = snake_2_length; i > 0; i--)
	{
		s2[i].x = s2[i - 1].x;
		s2[i].y = s2[i - 1].y;
	}
	if (direction_2 == 4)
		s2[0].y -= 1;

	if (direction_2 == 5)
		s2[0].y += 1;

	if (direction_2 == 6)
		s2[0].x -= 1;

	if (direction_2 == 7)
		s2[0].x += 1;


	//***NEW*** If Snake eats food it should grow
	//check if snake head = food location
	if (((s2[0].x) == food.x) && ((s2[0].y) == food.y))
	{
		//increment snake
		snake_2_length++;
		delay -= 0.001f;
		//Randomly place food somewhere else
		food.x = rand() % num_horzBox;
		food.y = rand() % num_vertBox;
	}

	//***NEW*** Boundary Checking snake as is hits screen end
	//loop snake back on other side
	//LEFT and RIGHT
	if (s2[0].x > num_horzBox)
		s2[0].x = 0;
	if (s2[0].x < 0)
		s2[0].x = num_horzBox;
	//TOP and BOTTOM
	if (s2[0].y > num_vertBox)
		s2[0].y = 0;
	if (s2[0].y < 0)
		s2[0].y = num_vertBox;

	//***NEW*** Check if you eat body of snake
	for (int i = 1; i < snake_2_length; i++)
	{
		//Cut Snake body from place eaten
		if (s2[0].x == s2[i].x && s2[0].y == s2[i].y)
			snake_2_length = i;
	}

}

int main()
{
	//Setting pseudorandom time, TODO:discuss true random vs pseudorandom 
	srand(time(0));

	//Window that we can play the game in 
	sf::RenderWindow window(sf::VideoMode(w, h), "Snake Game");

	//Textures load an image into the GPU Memory
	sf::Texture t1, t2, t3,t4;
	t1.loadFromFile("images/white.png");
	t2.loadFromFile("images/red.png");
	t3.loadFromFile("images/apple.png");
	t4.loadFromFile("images/green.png"); 

	//Sprite has physical dimmensions that can be set in 
	//coordinate system, setPosition(x,y), and drawn on screen
	sf::Sprite sprite1(t1);
	sf::Sprite sprite2(t2);
	sf::Sprite sprite3(t3);
	sf::Sprite sprite4(t4); 

	//***NEW*** initially place food somewhere on screen
	food.x = 10;
	food.y = 10;

	sf::Clock clock;
	
	while (window.isOpen())
	{
		//Error in class I placed this before the while loop
		//Should be placed in while loop as shown here to update
		//timer 
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		//Allow us to check when a user does something
		sf::Event e;

		//Check when the window is closed
		while (window.pollEvent(e))
		{
			//If user presses x in the top right, Windows, top left, Mac,  close the window
			if (e.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		//Control for Snake by User
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) direction_1 = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) direction_1 = 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) direction_1 = 2;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) direction_1 = 3;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) direction_2 = 4;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) direction_2 = 5;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) direction_2 = 6;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) direction_2 = 7;

		if (timer > delay)
		{
			timer = 0; //reset timer
			move_1();    //move Snake one sprite forward
			move_2(); 
		}
		/*****************
		//Draw in window
		*****************/
		window.clear();    //clear the window so new frame can be drawn in

		//NOTE: Order matters as we will draw over items listed first. 
		//Hence the background should be the first thing you will always do
		//1st: Draw Background first
		for (int i = 0; i < num_horzBox; i++)
		{
			for (int j = 0; j < num_vertBox; j++)
			{
				//Set position of sprite1 one at a time
				sprite1.setPosition(i*size, j*size);
				//Draw sprite1 but, do not show it on screen. 
				window.draw(sprite1);
			}
		}

		//2nd: Then Draw snake otherwise background will be drawn over snake if order was reversed with background
		for (int i = 0; i < snake_1_length; i++)
		{
			//position sprite2 one at a time
			sprite2.setPosition(s1[i].x*size, s1[i].y*size);
			//Draw sprite2 one at a time by drawing over background
			window.draw(sprite2);
		}

		for (int i = 0; i < snake_2_length; i++)
		{
			//position sprite4 one at a time
			sprite4.setPosition(s2[i].x*size, s2[i].y*size);
			//Draw sprite4 one at a time by drawing over background
			window.draw(sprite4);
		}

		//***NEW*** 3rd: Draw Fruit
		sprite3.setPosition(food.x*size, food.y*size);
		window.draw(sprite3);

		//Show everything we have drawn on the screen
		window.display();
	}
	return 0;
}