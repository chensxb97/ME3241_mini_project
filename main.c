// -----------------------------------------------------------------------------
// C-Skeleton to be used with HAM Library from www.ngine.de
// -----------------------------------------------------------------------------
#include "gba.h"
#include "sprites.h"
#include <stdlib.h>

//Global variables
//Astronaut
int astro = 2;
int x_astro,y_astro;

//Spaceship parts
int part1 = 15;
int part1_x, part1_y; 
int part2 = 16;
int part2_x, part2_y;
int part3 = 17;
int part3_x, part3_y;
int part4 = 18;
int part4_x, part4_y;
int part5 = 19;
int part5_x, part5_y;
int part6 = 20;
int part6_x, part6_y;
int part7 = 21;
int part7_x, part7_y;

//3 Hearts
int remaining;
int label_heart = 9;
int x_heart1= 0;
int y_heart1=0;
int x_heart2=20;
int y_heart2 = 0;
int x_heart3 = 40;
int y_heart3 = 0;

//Meteor
int meteor = 22;
int x_meteor, y_meteor,movementX,movementY;
int movementSpeed;

//Global time
int time;

//Game state variables
int menu, end, gameWon;
int level = 1;

//Handler
void Handler(void)
{
    REG_IME = 0x00; // Stop all other interrupt handling, while we handle this current one
    
	 if ((REG_IF & INT_BUTTON) == INT_BUTTON)
	 {
		 checkbutton(); //Checks for which button is pressed
	 }
	 if ((REG_IF & INT_TIMER0) == INT_TIMER0)
	 {
		 incrementTime(); //Increment global time
	 }
		    
    REG_IF = REG_IF; // Update interrupt table, to confirm we have handled this interrupt
    
    REG_IME = 0x01;  // Re-enable interrupt handling
}
void fillPalette(void)
{
    int  i;
	// Fill the palette in GBA memory
    for (i = 0; i < NCOLS; i++)
        spritePal[i] = palette[i];
}
void drawSprite(int numb, int N, int x, int y)
{
		// Same as CA2, make specific sprite (based on its name/numb) appear on screen, as slide number N (each sprite needs a different, arbitrary, N >= 0)
   	*(unsigned short *)(0x7000000 + 8*N) = y | 0x2000;
    	*(unsigned short *)(0x7000002 + 8*N) = x | 0x4000;
    	*(unsigned short *)(0x7000004 + 8*N) = numb*8;
}

void fillSprites(void)
{
    int i;
	// Load all sprites in GBA memory
    for (i = 0; i < 128*16*16; i++)
        spriteData[i] = (sprites[i*2+1] << 8) + sprites[i*2];

	// draw all sprites on screen, but all of them outside of the screen (starting at position (240,160) the bottom right corner of the GBA screen)
    for(i = 0; i < 128; i++)
        drawSprite(0, i, 240,160);
}

//helper functions

//Main menu
void setup(void)
{
	end = 1;
	menu = 0;
	gameWon = 0;

	//Clear screen
	fillPalette();
	fillSprites();

	drawSprite(32,4,80,70);//LV1
	drawSprite(33,5,96,70);
	drawSprite(32,6,126,70);//LV2
	drawSprite(34,7,142,70);
	
	x_astro = 84;
	y_astro = 80;
	drawSprite(astro,0,x_astro,y_astro);//Astronaut
	menu =1;
}
//Level 1 game state
void setup1(void)
{
	//Clear screen
	fillPalette();
	fillSprites();

	//Starting Astronaut
	x_astro = 220;
	y_astro = 140;

	//Starting Spaceship parts
	part1_x =220;       
	part1_y =100; 
	part2_x = 220;
	part2_y = 20;
	part3_x = 170;
	part3_y = 60;
	part4_x = 130;
	part4_y = 100;
	part5_x = 130;
	part5_y = 20;
	part6_x = 90;
	part6_y = 60;
	part7_x = 40;
	part7_y = 20;

	//Starting Hearts
	remaining = 3;

	//Random meteor
	x_meteor = 70;
	y_meteor = 0; 
	movementX = movementY = 0;
	movementSpeed = 1.5;
	
	//Starting time
	time = 0;

	//astronaut
	drawSprite(astro,0,x_astro,y_astro); 

	//hearts
	drawSprite(label_heart,1,x_heart1,y_heart1); 
	drawSprite(label_heart,2,x_heart2,y_heart2);
	drawSprite(label_heart,3,x_heart3,y_heart3);

	//spaceship parts
	drawSprite(part1,12,part1_x,part1_y); 
	drawSprite(part2,13,part2_x,part2_y);
	drawSprite(part3,14,part3_x,part3_y);
	drawSprite(part4,15,part4_x,part4_y);
	drawSprite(part5,16,part5_x,part5_y);
	drawSprite(part6,17,part6_x,part6_y);
	drawSprite(part7,18,part7_x,part7_y);
	
	//game state
	menu = 0;
	end = 0;
	gameWon = 0;
	
}
//Level 2 game state
void setup2(void)
{
	//Clear screen
	fillPalette();
	fillSprites();

	//Starting Astronaut
	x_astro = 220;
	y_astro = 140;

	//Starting Spaceship parts
	part1_x =220;       
	part1_y =100; 
	part2_x = 220;
	part2_y = 20;
	part3_x = 170;
	part3_y = 60;
	part4_x = 130;
	part4_y = 100;
	part5_x = 130;
	part5_y = 20;
	part6_x = 90;
	part6_y = 60;
	part7_x = 40;
	part7_y = 20;

	//Starting Hearts
	remaining = 3;

	//Random meteor
	x_meteor = 70;
	y_meteor = 0; 
	movementX = movementY = 0;
	movementSpeed = 2.5;
	
	//Starting time
	time = 0;
	
	//astronaut
	drawSprite(astro,0,x_astro,y_astro); 

	//hearts
	drawSprite(label_heart,1,x_heart1,y_heart1); 
	drawSprite(label_heart,2,x_heart2,y_heart2);
	drawSprite(label_heart,3,x_heart3,y_heart3);

	//spaceship parts
	drawSprite(part1,12,part1_x,part1_y); 
	drawSprite(part2,13,part2_x,part2_y);
	drawSprite(part3,14,part3_x,part3_y);
	drawSprite(part4,15,part4_x,part4_y);
	drawSprite(part5,16,part5_x,part5_y);
	drawSprite(part6,17,part6_x,part6_y);
	drawSprite(part7,18,part7_x,part7_y);

	//game state
	menu = 0;
	end = 0;
	gameWon = 0;
}

void gameOver(void)
{
	drawSprite(23,0,80,70); //GAME
	drawSprite(24,1,96,70);
	drawSprite(25,2,116,70);//OVER
	drawSprite(26,3,132,70);
	delay(8000);
}
void playAgain(void)
{
	drawSprite(27,0,80,70);//PLAY
	drawSprite(28,1,96,70);
	drawSprite(29,2,116,70);//AGAI
	drawSprite(30,3,132,70);
	drawSprite(31,4,148,70);//N?
	delay(8000);
}

void delay(int s)
{
	int c, d;
	for (c = 1; c <= s; c++)
       for (d = 1; d <= 100; d++)
       		{}
}
void moveAsteroid(movement)
{
	//Vertical boundary
	if (movementY<200)
	{
		movementY +=movementSpeed;
		drawSprite(meteor,4,x_meteor,movementY); 
		drawSprite(meteor,5,x_meteor+40,movementY);
		drawSprite(meteor,6,x_meteor+80,movementY);
		drawSprite(meteor,7,x_meteor+120,movementY);
		hitByAsteroid();
	}
	else movementY = 0;
	
	//Horizontal boundary
	if (movementX<230)
	{
		movementX+=movementSpeed;
		drawSprite(meteor,8,movementX,y_meteor);
		drawSprite(meteor,9,movementX,y_meteor+40);
		drawSprite(meteor,10,movementX,y_meteor+80);
		drawSprite(meteor,11,movementX,y_meteor+120);
		hitByAsteroid();
	}
	else movementX = 0;
	delay(100); //Slows down the speed of the meteors
}

void checkbutton(void)
{
	//Gift function, check which button is pressed
    u16 buttons = INPUT;
    
    if ((buttons & KEY_DOWN) == KEY_DOWN && menu ==0 && end ==0)
    {
		 if (menu ==0 && end ==0)
       {
			 if (y_astro<=140)
					y_astro = y_astro+2; //Moves down
		  	 drawSprite(astro,0,x_astro,y_astro-1);
		 }
				
    }
	 if ((buttons & KEY_UP) == KEY_UP && menu ==0 && end ==0)
	 {
		 if (menu==0 && end ==0) 
		 {
		 	 if (y_astro>=5)
			 	y_astro = y_astro-2; //Moves up
		 	drawSprite(astro,0,x_astro,y_astro);
		 }
	 }
	 if ((buttons& KEY_RIGHT) == KEY_RIGHT)
	 {
		if (menu ==0 && end ==0)
		{
			if (x_astro<=225)
				x_astro = x_astro+2; //Moves right
			astro = 0; //right facing
			drawSprite(astro,0,x_astro,y_astro);
		}
		else if (menu ==1)
		{
			astro = 0; //right facing
			x_astro=130; //Moves right
			y_astro =80;
			drawSprite(astro,0, x_astro,y_astro);
		}
	 }
	 if ((buttons & KEY_LEFT) == KEY_LEFT)
	 {
		 if (menu ==0 && end ==0)
		{	
			if (x_astro>=1)
				x_astro = x_astro-2; //Moves left
		 	astro = 2; //left facing
		 	drawSprite(astro,0,x_astro,y_astro);
		}
		else if (menu ==1)
		{
			astro = 2; //left facing
			x_astro= 84; //Moves left
			y_astro = 80;
			drawSprite(astro,0, x_astro,y_astro);
		}
	 }
	 hitByAsteroid();
	 if ((buttons & KEY_A) == KEY_A && end ==0 && menu ==0)
	 {
		  pickup(); //Collect spaceship part
	 }
	 if ((buttons & KEY_B) == KEY_B && end ==0 && menu ==0)
	 {
		  takeoff(); //Fly spaceship and win the game
	 }
	 if ((buttons & KEY_START) == KEY_START)
	 {
		  restartGame(); //Restart game
	 }
	 if ((buttons & KEY_SELECT) == KEY_SELECT && (end == 0 && menu ==0))
	 {
		  endGame(); //End game
	 }
		
}
void pickup(void)
{
	//When astronaut presses A and he is located on a part, part is drawn on the bottom left
		if (abs(part1_x-x_astro)<8 && abs(part1_y-y_astro)<8)
		{  
			part1_x =20;       
			part1_y =140; 
			drawSprite(part1,12,part1_x,part1_y);
		}
		else if (abs(part2_x-x_astro)<8 && abs(part2_y-y_astro)<8)
		{
			part2_x =20;       
			part2_y =130; 
			drawSprite(part2,13,part2_x,part2_y);
		}
		else if (abs(part3_x-x_astro)<8 && abs(part3_y-y_astro)<8)
		{	
			part3_x =20;       
			part3_y =120; 
			drawSprite(part3,14,part3_x,part3_y);
		}
		else if (abs(part4_x-x_astro)<8 && abs(part4_y-y_astro)<8)
		{
			part4_x =20;       
			part4_y =110; 
			drawSprite(part4,15,part4_x,part4_y);
		}
		else if (abs(part5_x-x_astro)<8 && abs(part5_y-y_astro)<8)
		{
			part5_x =20;       
			part5_y =100; 
			drawSprite(part5,16,part5_x,part5_y);
		}
		else if (abs(part6_x-x_astro)<8 && abs(part6_y-y_astro)<8)
		{
			part6_x =20;       
			part6_y =90; 
			drawSprite(part6,17,part6_x,part6_y);
		}
		else if (abs(part7_x-x_astro)<8 && abs(part7_y-y_astro)<8)
		{
			part7_x =20;       
			part7_y =80; 
			drawSprite(part7,18,part7_x,part7_y);
		}	
}
void takeoff(void)
{
	//When astronaut presses B and he is located at the base of the fully assembled spaceship, 
	//the ship takes off and wins game.
	if (part1_x ==20 && part2_x ==20 && part3_x ==20 && part4_x ==20 && part5_x ==20 && part6_x ==20 
		&& part7_x ==20 && (abs(x_astro-part1_x)<15 && y_astro<=part1_y && y_astro>=part7_y))
	{
		x_astro = part1_x;
		y_astro = part1_y;
		drawSprite(astro,0,x_astro,y_astro);
		fly();
	}
}
void fly(void)
{
	while(part1_y >-20) //flying the spaceship
	{
		part1_y = part1_y - 1;
		part2_y = part2_y - 1;
		part3_y = part3_y - 1;
		part4_y = part4_y - 1;
		part5_y = part5_y - 1;
		part6_y = part6_y - 1;
		part7_y = part7_y - 1;
		y_astro = y_astro -1;
		drawSprite(astro,0,x_astro,y_astro);
		drawSprite(part1,12,part1_x,part1_y);
		drawSprite(part2,13,part2_x,part2_y);
		drawSprite(part3,14,part3_x,part3_y);
		drawSprite(part4,15,part4_x,part4_y);
		drawSprite(part5,16,part5_x,part5_y);
		drawSprite(part6,17,part6_x,part6_y);
		drawSprite(part7,18,part7_x,part7_y);
		delay(100);
	}
	gameWon = 1;
	if (level==1) //prepare for level 2
	{
		level = level+1;
		setup2();
	}
	else
	{
		level =1;
		endGame(); //game ends when level 2 is finished
	}

}
void hitByAsteroid(void)
{
		//astronaut loses one heart when hit by asteroid, and respawns at the base
		if ((abs(x_astro-movementX)<8 && abs(y_astro-y_meteor)<8)
		|| (abs(x_astro-movementX)<8 && abs(y_astro-y_meteor-40)<8)
		|| (abs(x_astro-movementX)<8 && abs(y_astro-y_meteor-80)<8)
		||	(abs(x_astro-movementX)<8 && abs(y_astro-y_meteor-120)<8)
		|| (abs(x_astro-x_meteor)<8 && abs(y_astro-movementY)<8)
		|| (abs(x_astro-x_meteor-40)<8 && abs(y_astro-movementY)<8)
		|| (abs(x_astro-x_meteor-80)<8 && abs(y_astro-movementY)<8)
		|| (abs(x_astro-x_meteor-120)<8 && abs(y_astro-movementY)<8))
		{
			x_astro = 220;
			y_astro = 140;		
			drawSprite(astro,0,x_astro,y_astro);
			decrementHeart();
		}
	
}
void incrementTime(void)
{	
	//increments time during a timer interrupt
	if (end==1)
		return;
	time = time +1;
	time_damage();
}
void time_damage(void)
{	
	//astronaut loses one heart every 15 seconds
	//Heart blinks for 3 times before the 15 second mark
	if ((time+6)%15 ==0)
	{
		decrementHeart();
	}
	if ((time+5)%15 ==0)
	{
		incrementHeart();
	}
	if ((time+4)%15==0)
	{
		decrementHeart();
	}
	if ((time+3)%15 ==0)
	{
		incrementHeart();
	}
	if ((time+2)%15 ==0)
	{
		decrementHeart();
	}
	if ((time+1)%15 ==0)
	{
		incrementHeart();
	}
	if (time%15 ==0)
		decrementHeart();
}
void decrementHeart(void)
{
	 //heart turns grey when lost
	 if (remaining ==3)
	 {
		drawSprite(10,remaining,x_heart3,y_heart3);
	 }
	 else if (remaining == 2)
	 {
		drawSprite(10,remaining,x_heart2,y_heart2);
	 }
	 else
	 {
		drawSprite(10,remaining,x_heart1,y_heart1);
	 }
	 remaining= remaining -1;
	 if (remaining <0)
	 {
	 	endGame(); //astronaut loses the game when out of hearts
	 }
}
void incrementHeart(void)
{
	 //Used alongside decrementHeart to achieve a blinking heart effect
	 remaining = remaining +1;
	 if (remaining ==3)
	 {
		drawSprite(9,remaining,x_heart3,y_heart3);
	 }
	 else if (remaining == 2)
	 {
		drawSprite(9,remaining,x_heart2,y_heart2);
	 }
	 else if (remaining == 1)
	 {
		drawSprite(9,remaining,x_heart1,y_heart1);
	 }
}
void restartGame(void)
{
	//main menu control
	if (menu ==1)
	{
		if (x_astro ==84)
		{
			level = 1;
			setup1();
		}
		else
		{
			level = 2;
			setup2();
		}
	}//in-game control
	else if (end == 0 && menu ==0)
	{
		if (level ==1)
			setup1();
		else
			setup2();
	}
}
void endGame(void)
{
	//game ends
	end = 1;
	menu = 0;
	fillPalette();
	fillSprites();
	delay(10000);
	if (gameWon ==0)
		gameOver(); //prints game over when game is lost
	playAgain();
	setup(); //returns to main menu
}

// -----------------------------------------------------------------------------
// Project Entry Points
// -----------------------------------------------------------------------------
int main(void)
{
    // Set Mode 2
	 *(unsigned short *) 0x4000000 = 0x40 | 0x2 | 0x1000;
		
 	 //Setup default level
	 setup();
	 
    // Set Handler Function for interrupts and enable selected interrupts
    REG_INT = (int)&Handler;
	 REG_IE |= INT_TIMER0; // Timer Interrupt
	 REG_IE |= INT_BUTTON; // Button Interrupt
    REG_IME = 0x1;		// Enable interrupt handling
	 
	 // Set Button Interrupt
	 REG_P1CNT |= KEY_MASK;
	 REG_P1CNT |= (1 << 14);
	
	 // Set Timer Mode
    REG_TM0D =	49152; //Time taken from this base value to overflow is 1 second
    REG_TM0CNT |= TIMER_FREQUENCY_1024|TIMER_ENABLE|TIMER_INTERRUPTS; 

    while(1)
	 {		
			if (end==0)
			{
 				//Automating the movement of asteroids during game
			   moveAsteroid();	
			}
	 };

	return 0;
}


