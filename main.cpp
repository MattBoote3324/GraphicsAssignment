//Jeff Chastine

//#include <GL\glew.h>
//#include <GL\freeglut.h>
#include <iostream>
#include "loadTGA.h"
#include "TextureLoader.h"
#include <cmath>
//# define M_PI           3.14159265358979323846  /* pi */
using namespace std;

//--Draws a grid of lines on the floor plane -------------------------------
using namespace std;

//--Globals ---------------------------------------------------------------
float  theta = 0;
float degreeRatio = M_PI / 180;
float robots_rotation = 0  ;

bool increasing = false;
float ship_floor_height = 25;

int viewNo = 1;
bool locked_view =false;    
bool running = false;                        //Look angle
int step = 0;	
float r2_x_pos = 80, r2_z_pos = 5;
float cp30_x_pos = 80, cp30_z_pos = -5;
float storm_x_pos = -70, storm_z_pos = 0;
float cp30_leg_angle = 10;
float eye_x = 0, eye_y = ship_floor_height + 20, eye_z = 10;
float look_x = 0, look_y = 0, look_z = 0;
bool cp30_angle_inc = false;
float destination = -40;
float start = 80;
float bullet_x_pos = 80;
//--Draws a grid of lines on the floor plane -------------------------------
void c3poColor()
{
	glColor3f(0.941, 0.902, 0.549);
}


void normal(float x1, float y1, float z1,
	float x2, float y2, float z2,
	float x3, float y3, float z3)
{
	float nx, ny, nz;
	nx = y1*(z2 - z3) + y2*(z3 - z1) + y3*(z1 - z2);
	ny = z1*(x2 - x3) + z2*(x3 - x1) + z3*(x1 - x2);
	nz = x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2);

	glNormal3f(nx, ny, nz);
}
void drawHangar()
{
	glPushMatrix();
		glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, texId[8]);
			glBegin(GL_QUADS);
				
				glNormal3f(0., 0., 1.0); //Front Side +z
				glTexCoord2f(0, 0); glVertex3f(-100, 0., 30);
				glTexCoord2f(1, 0); glVertex3f(100, 0., 30);
				glTexCoord2f(1,1); glVertex3f(100, 50, 30);
				glTexCoord2f(0, 1); glVertex3f(-100, 50, 30);

				glNormal3f(0., 0., -1.0); //Back Side -z
				glTexCoord2f(0, 0); glVertex3f(-100, 0., -30);
				glTexCoord2f(0, 0); glVertex3f(100, 0., -30);
				glTexCoord2f(0, 0); glVertex3f(100, 50, -30);
				glTexCoord2f(0, 0); glVertex3f(-100, 50, -30);

				

			glEnd();
			glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, texId[7]);  /*Building the circular hallway*/
			glBegin(GL_QUADS);
				glNormal3f(0., 1, 0.);  //ship room roof
				glTexCoord2f(0, 0); glVertex3f(-100, 50, 30);
				glTexCoord2f(0,1); glVertex3f(-100, 50, -30);
				glTexCoord2f(1,1); glVertex3f(100, 50, -30);
				glTexCoord2f(1,0); glVertex3f(100, 50, 30);

				normal(-60, ship_floor_height, -10, -60, ship_floor_height + 5, -15, 60, ship_floor_height + 5, -15);
				glTexCoord2f(0, 0); glVertex3f(-60, ship_floor_height, -10); //bottom Left quad
				glTexCoord2f(0, 1); glVertex3f(-60, ship_floor_height + 5, -15);
				glTexCoord2f(1, 1); glVertex3f(60, ship_floor_height + 5,-15);
				glTexCoord2f(1, 0); glVertex3f(60, ship_floor_height, -10);
				
				normal(-60, ship_floor_height, 10, -60, ship_floor_height + 5, 15, 60, ship_floor_height + 5, 15);
				glTexCoord2f(0, 0); glVertex3f(-60, ship_floor_height, 10);
				glTexCoord2f(0, 1); glVertex3f(-60, ship_floor_height + 5, 15);  //bottom right
				glTexCoord2f(1, 1); glVertex3f(60, ship_floor_height + 5, 15);
				glTexCoord2f(1, 0); glVertex3f(60, ship_floor_height, 10);

				glTexCoord2f(0, 0); glVertex3f(-60, 50, 10);
				glTexCoord2f(0, 1); glVertex3f(-60, 50 - 5, 15);	//top right
				glTexCoord2f(1, 1); glVertex3f(60, 50 - 5, 15);
				glTexCoord2f(1, 0); glVertex3f(60, 50, 10);

				glTexCoord2f(0, 0); glVertex3f(-60, 50, -10);
				glTexCoord2f(0, 1); glVertex3f(-60, 50 - 5, -15);
				glTexCoord2f(1, 1); glVertex3f(60, 50 - 5, -15);//top left
				glTexCoord2f(1, 0); glVertex3f(60, 50, -10);

				glTexCoord2f(0, 0); glVertex3f(-60, ship_floor_height + 5, 15);
				glTexCoord2f(0, 1); glVertex3f(-60, 45, 15);
				glTexCoord2f(1, 1); glVertex3f(60, 45, 15); //right middle
				glTexCoord2f(1, 0); glVertex3f(60, ship_floor_height + 5, 15);

				glTexCoord2f(0, 0); glVertex3f(-60, ship_floor_height + 5, -15); //left middle
				glTexCoord2f(0, 1); glVertex3f(-60, 45, -15);
				glTexCoord2f(1, 1); glVertex3f(60, 45, -15);
				glTexCoord2f(1, 0); glVertex3f(60, ship_floor_height + 5, -15);

				
			glEnd();
		glPopMatrix();
		glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, texId[13]);
			glBegin(GL_QUADS);  //door at end of tunnel
				
				glTexCoord2f(0, 0); glVertex3f(-60, ship_floor_height , -15); 
				glTexCoord2f(0, 1); glVertex3f(-60, 50, -15);
				glTexCoord2f(1, 1); glVertex3f(-60, 50, 15);
				glTexCoord2f(1, 0); glVertex3f(-60, ship_floor_height , 15);
			glEnd();
		glPopMatrix();
		glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, texId[6]);
			glBegin(GL_QUADS);
				

				normal(60, ship_floor_height, -10, 60, ship_floor_height, 10, -60, ship_floor_height, 10); //Ship Bridge
				glTexCoord2f(1,0); glVertex3f(60, ship_floor_height, -10);
				glTexCoord2f(1, 1); glVertex3f(60, ship_floor_height, 10);
				glTexCoord2f(0,1); glVertex3f(-60, ship_floor_height, 10);
				glTexCoord2f(0,0); glVertex3f(-60, ship_floor_height, -10);

				
				normal(-100, ship_floor_height, 30, -100, ship_floor_height, -30, -60, ship_floor_height, -10); //Ship Floor Left Base
				glTexCoord2f(1, 1); glVertex3f(-100, ship_floor_height, 30);
				glTexCoord2f(0,1); glVertex3f(-100, ship_floor_height, -30);
				glTexCoord2f(0, 0); glVertex3f(-60, ship_floor_height, -10);
				glTexCoord2f(1, 0); glVertex3f(-60, ship_floor_height, 10);

				
				normal(-100, ship_floor_height, 30, -100, ship_floor_height, -30, 60, ship_floor_height, -10); //Ship Floor Right Base
				glTexCoord2f(1,1); glVertex3f(100, ship_floor_height, 30);
				glTexCoord2f(0,1); glVertex3f(100, ship_floor_height, -30);
				glTexCoord2f(0,0); glVertex3f(60, ship_floor_height, -10);
				glTexCoord2f(1, 0); glVertex3f(60, ship_floor_height, 10);

			glEnd();
		glPopMatrix();
			glPushMatrix();
				glDisable(GL_TEXTURE_2D);
				glBegin(GL_QUADS);
					glColor3f(1.,1.,1.);
					glNormal3f(-1, 0., 0.); //Left Side -x
					glVertex3f(-100, 0, -30);glVertex3f(-100, 0, 30);glVertex3f(-100, 50, 30);glVertex3f(-100, 50, -30);

					glNormal3f(1, 0., 0.); //Right Side +x
					//normal(100, 0., -30, 100, 0., 30, 100, 50, 30);
					glVertex3f(100, 0., -30);glVertex3f(100, 0., 30);glVertex3f(100, 50, 30);glVertex3f(100, 50, -30);

					normal(-100, 50, -30, -50, 70, -20, -50, 70, 20); //Top left Panel
					glVertex3f(-100, 50, -30);glVertex3f(-50, 70, -20);glVertex3f(-50, 70, 20);glVertex3f(-100, 50, 30);

					normal(-100, 50, -30, -50, 70, -20, 50, 70, -20); //Top Middle Back Panel
					glVertex3f(-100, 50, -30);glVertex3f(-50, 70, -20);glVertex3f(50, 70, -20);glVertex3f(100, 50, -30);

					normal(-100, 50, 30, -50, 70, 20, 50, 70, 20); //Top Middle Front Panel
					glVertex3f(-100, 50, 30);glVertex3f(-50, 70, 20);glVertex3f(50, 70, 20);glVertex3f(100, 50, 30);

					normal(100, 50, -30, 50, 70, -20, 50, 70, 20); //Top Right Panel
					glVertex3f(100, 50, -30);glVertex3f(50, 70, -20);glVertex3f(50, 70, 20);glVertex3f(100, 50, 30);

					normal(-50, 70, -20, -50, 70, 20, 50, 70, 20); //Top Top Panel
					glVertex3f(-50, 70, -20);glVertex3f(-50, 70, 20);glVertex3f(50, 70, 20);glVertex3f(50, 70, -20);

					normal(-100, 0, -30, -50, -20, -20, -50, -20, 20); //Bottom left Panel
					glVertex3f(-100, 0, -30);glVertex3f(-50, -20, -20);glVertex3f(-50, -20, 20);glVertex3f(-100, 0, 30);

					normal(-100, 0, -30, -50, -20, -20, 50, -20, -20); //Bottom Middle Back Panel
					glVertex3f(-100, 0, -30);glVertex3f(-50, -20, -20);glVertex3f(50, -20, -20);glVertex3f(100, 0, -30);

					normal(-100, 0, 30, -50, -20, 20, 50, -20, 20); //Bottom Middle Front Panel
					glVertex3f(-100, 0, 30);glVertex3f(-50, -20, 20);glVertex3f(50, -20, 20);glVertex3f(100, 0, 30);

					normal(100, 0, -30, 50, -20, -20, 50, -20, 20); //Bottom Right Panel
					glVertex3f(100, 0, -30);glVertex3f(50, -20, -20);glVertex3f(50, -20, 20);glVertex3f(100, 0, 30);

					normal(-50, -20, -20, -50, -20, 20, 50, -20, 20); //Bottom Bottom Panel
					glVertex3f(-50, -20, -20);glVertex3f(-50, -20, 20);glVertex3f(50, -20, 20);glVertex3f(50, -20, -20);
				glEnd();
	
			glPopMatrix();
		glPopMatrix();
		
		
		
			
		
		
		glPushMatrix();		//Ship Neck
			glColor3f(1.,1.,1.);
			glTranslatef(-201, 25, 0);
			glScalef(8, 2, 2.4);
			glutSolidCube(25);
		glPopMatrix();

		glBegin(GL_TRIANGLES); //Ship front Cone
			glColor3f(1.,1.,1.);
			glVertex3f(-300, 50, 30); glVertex3f(-370, 25, 0); glVertex3f(-300, 0, 30);
			glVertex3f(-300, 50, -30); glVertex3f(-370, 25, 0); glVertex3f(-300, 50, 30);
			glVertex3f(-300, 50, -30); glVertex3f(-370, 25, 0); glVertex3f(-300, 0, -30);
			glVertex3f(-300, 0, 30); glVertex3f(-370, 25, 0); glVertex3f(-300, 0, -30);
		glEnd();
		
		
	//draw lights
	
		glPushMatrix();
			glColor3f(1,1,0);
			glTranslatef(0,ship_floor_height + 25, 0);
			glutSolidCube(2);
		glPopMatrix();
		glPushMatrix();
			glColor3f(1,1,0);
			glTranslatef(-80,ship_floor_height + 25, 0);
			glutSolidCube(2);
		glPopMatrix();
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);

	
}
void drawFeet(int lrc){

		//lrc is left, right or center. 1 = left,2 = right, 3= center
		int z1 =0, z2 = 0;
		switch(lrc){
			case(1):z1 =2;z2 =1;break;
			case(2):z1 = -2;z2 = -1;break;
			//case(3):z1 = 1; z2 = -1;break;
		}
		glPushMatrix();
		glColor3f(1,1,1);
			glBegin(GL_QUADS);//Feet/Wheel things
				
				normal(r2_x_pos- 1, ship_floor_height , r2_z_pos -z1,r2_x_pos, ship_floor_height + 1, r2_z_pos - z1 , r2_x_pos , ship_floor_height + 1, r2_z_pos - z1);
				glVertex3f(r2_x_pos- 1, ship_floor_height , r2_z_pos -z1);glVertex3f(r2_x_pos, ship_floor_height + 1, r2_z_pos - z1);
				glVertex3f(r2_x_pos , ship_floor_height + 1, r2_z_pos - z1);glVertex3f(r2_x_pos + 1, ship_floor_height, r2_z_pos - z1);
				
				normal(r2_x_pos+ 1, ship_floor_height , r2_z_pos -z1,r2_x_pos + 1, ship_floor_height, r2_z_pos -z2,r2_x_pos , ship_floor_height + 1, r2_z_pos -z2 );
				glVertex3f(r2_x_pos+ 1, ship_floor_height , r2_z_pos -z1);glVertex3f(r2_x_pos + 1, ship_floor_height, r2_z_pos -z2);
				glVertex3f(r2_x_pos , ship_floor_height + 1, r2_z_pos -z2);glVertex3f(r2_x_pos , ship_floor_height + 1, r2_z_pos - z1 );
				
				normal(r2_x_pos- 1, ship_floor_height , r2_z_pos -z1,r2_x_pos - 1, ship_floor_height, r2_z_pos -z2,r2_x_pos , ship_floor_height + 1, r2_z_pos-z2 );
				glVertex3f(r2_x_pos- 1, ship_floor_height , r2_z_pos -z1);glVertex3f(r2_x_pos - 1, ship_floor_height, r2_z_pos -z2);
				glVertex3f(r2_x_pos , ship_floor_height + 1, r2_z_pos-z2);glVertex3f(r2_x_pos , ship_floor_height + 1, r2_z_pos - z1 );
				
				normal(r2_x_pos- 1, ship_floor_height , r2_z_pos -z2,r2_x_pos , ship_floor_height + 1, r2_z_pos -z2 ,r2_x_pos, ship_floor_height + 1, r2_z_pos -z2);
				glVertex3f(r2_x_pos- 1, ship_floor_height , r2_z_pos -z2 );glVertex3f(r2_x_pos , ship_floor_height + 1, r2_z_pos -z2);
				glVertex3f(r2_x_pos, ship_floor_height + 1, r2_z_pos -z2 );glVertex3f(r2_x_pos + 1, ship_floor_height, r2_z_pos -z2);
			
				
			glEnd();
		glPopMatrix();
		
}


void animateRobots(){
	
	if(!running){
		if(r2_x_pos > destination){
			r2_x_pos--;
			cp30_x_pos--;
			} //go towards destination
		else if(r2_x_pos == destination)
		{
			robots_rotation += 5;
			
		}
		if (robots_rotation == 180  && r2_x_pos == destination){ //we've turned them around
				r2_x_pos++;
				cp30_x_pos ++;
				running = true;
		}
		
	}
	else{
		if (r2_x_pos < start)
		{
			cp30_x_pos ++;
			r2_x_pos ++;
		}else if(r2_x_pos == start)
		{
			robots_rotation -=5;
			
		}
		if (robots_rotation == 0  && r2_x_pos == start ){ //we've turned them around
			r2_x_pos--;
			cp30_x_pos--;
			running = false; //we are going back towards the bullets
		}
		
	}
	if (viewNo == 2){
		
		eye_x = r2_x_pos;
		theta = (robots_rotation + 90) * degreeRatio;
	}else if(viewNo ==3)
	{
		eye_x = cp30_x_pos;
		theta = (robots_rotation + 90) * degreeRatio;
	}
		
		
}

void animateC3PO() {

	if (cp30_angle_inc) {
		cp30_leg_angle++;
		if (cp30_leg_angle == 10)
		{
			cp30_angle_inc = false;
		}

	}
	else {
		cp30_leg_angle--;
		if (cp30_leg_angle == -10)
		{
			cp30_angle_inc = true;
		}
	}
}
void drawStormTrooper(){
		glPushMatrix();
		
			int storm_height = ship_floor_height + 10;
			//Legs
			glTranslatef(storm_x_pos, storm_height - 2.5, storm_z_pos);
			glRotatef(180, 0, 1,0);
			glTranslatef(-storm_x_pos, -(storm_height - 2.5), -storm_z_pos);
			glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, texId[14]);
				glBegin(GL_QUADS);
					normal(storm_x_pos - 1, storm_height + 3, storm_z_pos - 1,storm_x_pos - 1, storm_height, storm_z_pos - 1,storm_x_pos - 1, storm_height, storm_z_pos + 1);
					glTexCoord2f(0, 0); glVertex3f(storm_x_pos - 1, storm_height + 3, storm_z_pos - 1); //front side of head
					glTexCoord2f(0, 1); glVertex3f(storm_x_pos - 1, storm_height, storm_z_pos - 1);
					glTexCoord2f(1, 1); glVertex3f(storm_x_pos - 1, storm_height, storm_z_pos + 1);
					glTexCoord2f(1, 0); glVertex3f(storm_x_pos - 1, storm_height + 3, storm_z_pos + 1);
				glEnd();
			glPopMatrix();
			
			glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, texId[15]);
				glBegin(GL_QUADS);
					glTexCoord2f(0, 0); glVertex3f(storm_x_pos + 1, storm_height, storm_z_pos - 1); //back side of head
					glTexCoord2f(0, 1); glVertex3f(storm_x_pos + 1, storm_height + 3, storm_z_pos - 1);
					glTexCoord2f(1, 1); glVertex3f(storm_x_pos + 1, storm_height + 3, storm_z_pos + 1);
					glTexCoord2f(1, 0); glVertex3f(storm_x_pos + 1, storm_height , storm_z_pos + 1);


					glTexCoord2f(0, 0); glVertex3f(storm_x_pos + 1, storm_height, storm_z_pos - 1); //right side of head
					glTexCoord2f(0, 1); glVertex3f(storm_x_pos + 1, storm_height + 3, storm_z_pos - 1);
					glTexCoord2f(1, 1); glVertex3f(storm_x_pos - 1, storm_height + 3, storm_z_pos - 1);
					glTexCoord2f(1, 0); glVertex3f(storm_x_pos - 1, storm_height, storm_z_pos - 1);

					glTexCoord2f(0, 0); glVertex3f(storm_x_pos + 1, storm_height, storm_z_pos + 1); //left side of head
					glTexCoord2f(0, 1); glVertex3f(storm_x_pos + 1, storm_height + 3, storm_z_pos + 1);
					glTexCoord2f(1, 1); glVertex3f(storm_x_pos - 1, storm_height + 3, storm_z_pos + 1);
					glTexCoord2f(1, 0); glVertex3f(storm_x_pos - 1, storm_height, storm_z_pos + 1);
				glEnd();
			glPopMatrix();
			
			
		
			
			glPushMatrix();
			glDisable(GL_TEXTURE_2D);
				glColor3f(1.0,1.0,1.0);
				glBegin(GL_QUADS);
					
					normal(storm_x_pos + 1 , storm_height - 5, storm_z_pos - 2,storm_x_pos + 1, storm_height, storm_z_pos - 2,storm_x_pos + 1, storm_height, storm_z_pos + 2);
					glVertex3f(storm_x_pos + 1 , storm_height - 5, storm_z_pos - 2); //front side
					glVertex3f(storm_x_pos + 1, storm_height, storm_z_pos - 2);
					glVertex3f(storm_x_pos + 1, storm_height, storm_z_pos + 2);
					glVertex3f(storm_x_pos + 1, storm_height - 5, storm_z_pos + 2);
				glEnd();
				
				//glBindTexture(GL_TEXTURE_2D, texId[17]);
				glBegin(GL_QUADS);
					
					normal(storm_x_pos - 1, storm_height - 5, storm_z_pos - 2,storm_x_pos - 1, storm_height, storm_z_pos - 2,storm_x_pos - 1, storm_height, storm_z_pos + 2);
					glVertex3f(storm_x_pos - 1, storm_height - 5, storm_z_pos - 2); //back side
					glVertex3f(storm_x_pos - 1, storm_height, storm_z_pos - 2);
					glVertex3f(storm_x_pos - 1, storm_height, storm_z_pos + 2);
					glVertex3f(storm_x_pos - 1, storm_height - 5, storm_z_pos + 2);
				glEnd();

				glBegin(GL_QUADS);
					
					normal(storm_x_pos - 1, storm_height - 5, storm_z_pos - 2,storm_x_pos + 1, storm_height - 5, storm_z_pos - 2,storm_x_pos + 1, storm_height, storm_z_pos - 2);
					glTranslatef(cp30_x_pos, storm_height - 2.5, storm_z_pos);
					glRotatef(robots_rotation, 0, 1,0);
					glVertex3f(storm_x_pos - 1, storm_height - 5, storm_z_pos - 2); 
					glVertex3f(storm_x_pos + 1, storm_height - 5, storm_z_pos - 2);
					glVertex3f(storm_x_pos + 1, storm_height, storm_z_pos - 2);
					glVertex3f(storm_x_pos - 1, storm_height, storm_z_pos - 2);
					glTranslatef(storm_x_pos, storm_height - 2.5, storm_z_pos);
					glRotatef(robots_rotation, 0, 1,0);
					
					normal(storm_x_pos - 1, storm_height - 5, storm_z_pos + 2,storm_x_pos + 1, storm_height - 5, storm_z_pos + 2,storm_x_pos + 1, storm_height, storm_z_pos + 2);
					glVertex3f(storm_x_pos - 1, storm_height - 5, storm_z_pos + 2);
					glVertex3f(storm_x_pos + 1, storm_height - 5, storm_z_pos + 2);
					glVertex3f(storm_x_pos + 1, storm_height, storm_z_pos + 2);
					glVertex3f(storm_x_pos - 1, storm_height, storm_z_pos + 2);
					
					
					normal(storm_x_pos - 1, storm_height , storm_z_pos + 2,storm_x_pos + 1, storm_height , storm_z_pos + 2,storm_x_pos + 1, storm_height, storm_z_pos - 2);
					glVertex3f(storm_x_pos - 1, storm_height , storm_z_pos + 2);
					glVertex3f(storm_x_pos + 1, storm_height , storm_z_pos + 2);
					glVertex3f(storm_x_pos + 1, storm_height, storm_z_pos - 2);
					glVertex3f(storm_x_pos - 1, storm_height, storm_z_pos - 2);

				glEnd();
				
				glBegin(GL_QUADS); //top of head
					
					glVertex3f(storm_x_pos + 1, storm_height + 3, storm_z_pos + 1);
					glVertex3f(storm_x_pos + 1, storm_height + 3, storm_z_pos - 1);
					glVertex3f(storm_x_pos - 1, storm_height + 3, storm_z_pos - 1);
					glVertex3f(storm_x_pos - 1, storm_height + 3, storm_z_pos + 1);
				glEnd();

				 //Left leg
				glPushMatrix();
					
					glTranslatef(storm_x_pos , ship_floor_height + 10, storm_z_pos + 1);
					glRotatef(cp30_leg_angle, 0, 0, 1);
					glTranslatef(-(storm_x_pos), -(ship_floor_height + 8), -(storm_z_pos + 1));
					glTranslatef(storm_x_pos, ship_floor_height, storm_z_pos + 1);
					glScalef(1, 13, 1);
					glutSolidCube(1);
				glPopMatrix();

				glPushMatrix();
					
					glTranslatef(storm_x_pos, ship_floor_height + 10, storm_z_pos - 1);
					glRotatef(-cp30_leg_angle, 0, 0, 1);
					glTranslatef(-(storm_x_pos), -(ship_floor_height + 8), -(storm_z_pos - 1));
					glTranslatef(storm_x_pos, ship_floor_height, storm_z_pos - 1);
					glScalef(1, 13, 1);
					glutSolidCube(1);
				glPopMatrix();
				 
				glPushMatrix();			//gun hand
					
					glTranslatef(storm_x_pos, ship_floor_height + 10, storm_z_pos - 1);
					glRotatef(270, 0, 0, 1);
					glTranslatef(-(storm_x_pos), -(ship_floor_height + 8), -(storm_z_pos - 1));
					glTranslatef(storm_x_pos, ship_floor_height + 6, storm_z_pos - 2);
					glScalef(1, 6, 1);
					glutSolidCube(1);
				glPopMatrix();
				
				glPushMatrix();  //right hand
					
					
					glTranslatef(storm_x_pos, ship_floor_height + 8, storm_z_pos + 2);
					glScalef(1, 6, 1);
					glutSolidCube(1);
				glPopMatrix();
			glPopMatrix();

		
	
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}

	
void drawCP30() {
	glPushMatrix();
		  //Draw Body
		int cp30_height = ship_floor_height + 12;
		glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, texId[10]);
			glTranslatef(cp30_x_pos, cp30_height - 2.5, cp30_z_pos);
			glRotatef(robots_rotation, 0, 1,0);
			glTranslatef(-cp30_x_pos, -(cp30_height - 2.5), -cp30_z_pos);
			glBegin(GL_QUADS);
				glTexCoord2f(0, 0); glVertex3f(cp30_x_pos + 1 , cp30_height - 5, cp30_z_pos - 2); //front side
				glTexCoord2f(0, 1); glVertex3f(cp30_x_pos + 1, cp30_height, cp30_z_pos - 2);
				glTexCoord2f(1, 1); glVertex3f(cp30_x_pos + 1, cp30_height, cp30_z_pos + 2);
				glTexCoord2f(1,0); glVertex3f(cp30_x_pos + 1, cp30_height - 5, cp30_z_pos + 2);
			glEnd();
		
			glBindTexture(GL_TEXTURE_2D, texId[9]);
			glBegin(GL_QUADS);
				glTexCoord2f(0, 0); glVertex3f(cp30_x_pos - 1, cp30_height - 5, cp30_z_pos - 2); //back side
				glTexCoord2f(0, 1); glVertex3f(cp30_x_pos - 1, cp30_height, cp30_z_pos - 2);
				glTexCoord2f(1, 1); glVertex3f(cp30_x_pos - 1, cp30_height, cp30_z_pos + 2);
				glTexCoord2f(1, 0); glVertex3f(cp30_x_pos - 1, cp30_height - 5, cp30_z_pos + 2);
			glEnd();
		
			
		
	
		
		
			glBindTexture(GL_TEXTURE_2D, texId[11]);
			glBegin(GL_QUADS);
				
				glTexCoord2f(0, 0); glVertex3f(cp30_x_pos - 1, cp30_height + 3, cp30_z_pos - 1); //front side of head
				glTexCoord2f(0, 1); glVertex3f(cp30_x_pos - 1, cp30_height, cp30_z_pos - 1);
				glTexCoord2f(1, 1); glVertex3f(cp30_x_pos - 1, cp30_height, cp30_z_pos + 1);
				glTexCoord2f(1, 0); glVertex3f(cp30_x_pos - 1, cp30_height + 3, cp30_z_pos + 1);
			glEnd();
		
			glBindTexture(GL_TEXTURE_2D, texId[12]);
			glBegin(GL_QUADS);
				glTexCoord2f(0, 0); glVertex3f(cp30_x_pos + 1, cp30_height, cp30_z_pos - 1); //back side of head
				glTexCoord2f(0, 1); glVertex3f(cp30_x_pos + 1, cp30_height + 3, cp30_z_pos - 1);
				glTexCoord2f(1, 1); glVertex3f(cp30_x_pos + 1, cp30_height + 3, cp30_z_pos + 1);
				glTexCoord2f(1, 0); glVertex3f(cp30_x_pos + 1, cp30_height , cp30_z_pos + 1);

				glTexCoord2f(0, 0); glVertex3f(cp30_x_pos + 1, cp30_height, cp30_z_pos + 1); //left side of head
				glTexCoord2f(0, 1); glVertex3f(cp30_x_pos + 1, cp30_height + 3, cp30_z_pos + 1);
				glTexCoord2f(1, 1); glVertex3f(cp30_x_pos - 1, cp30_height + 3, cp30_z_pos + 1);
				glTexCoord2f(1, 0); glVertex3f(cp30_x_pos -1, cp30_height , cp30_z_pos  + 1);

				glTexCoord2f(0, 0); glVertex3f(cp30_x_pos + 1, cp30_height, cp30_z_pos - 1); //right side of head
				glTexCoord2f(0, 1); glVertex3f(cp30_x_pos + 1, cp30_height + 3, cp30_z_pos - 1);
				glTexCoord2f(1, 1); glVertex3f(cp30_x_pos - 1, cp30_height + 3, cp30_z_pos - 1);
				glTexCoord2f(1, 0); glVertex3f(cp30_x_pos - 1, cp30_height, cp30_z_pos - 1);

				glTexCoord2f(0, 0); glVertex3f(cp30_x_pos + 1, cp30_height, cp30_z_pos + 1); //left side of head
				glTexCoord2f(0, 1); glVertex3f(cp30_x_pos + 1, cp30_height + 3, cp30_z_pos + 1);
				glTexCoord2f(1, 1); glVertex3f(cp30_x_pos - 1, cp30_height + 3, cp30_z_pos + 1);
				glTexCoord2f(1, 0); glVertex3f(cp30_x_pos - 1, cp30_height, cp30_z_pos + 1);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glBegin(GL_QUADS);
				c3poColor();
				glNormal3f(0, 0, -1);
				glTranslatef(cp30_x_pos, cp30_height - 2.5, cp30_z_pos);
				glRotatef(robots_rotation, 0, 1,0);
				glVertex3f(cp30_x_pos - 1, cp30_height - 5, cp30_z_pos - 2); 
				glVertex3f(cp30_x_pos + 1, cp30_height - 5, cp30_z_pos - 2);
				glVertex3f(cp30_x_pos + 1, cp30_height, cp30_z_pos - 2);
				glVertex3f(cp30_x_pos - 1, cp30_height, cp30_z_pos - 2);
				glTranslatef(cp30_x_pos, cp30_height - 2.5, cp30_z_pos);
				glRotatef(robots_rotation, 0, 1,0);
				glNormal3f(0, 0, 1);
				glVertex3f(cp30_x_pos - 1, cp30_height - 5, cp30_z_pos + 2);glVertex3f(cp30_x_pos + 1, cp30_height - 5, cp30_z_pos + 2);glVertex3f(cp30_x_pos + 1, cp30_height, cp30_z_pos + 2);
				glVertex3f(cp30_x_pos - 1, cp30_height, cp30_z_pos + 2);
				
				
				glNormal3f(0, 1, 0);
				glVertex3f(cp30_x_pos - 1, cp30_height , cp30_z_pos + 2);
				glVertex3f(cp30_x_pos + 1, cp30_height , cp30_z_pos + 2);
				glVertex3f(cp30_x_pos + 1, cp30_height, cp30_z_pos - 2);
				glVertex3f(cp30_x_pos - 1, cp30_height, cp30_z_pos - 2);

			glEnd();
		

			glBegin(GL_QUADS); //top of head
			glVertex3f(cp30_x_pos + 1, cp30_height + 3, cp30_z_pos + 1);
			glVertex3f(cp30_x_pos + 1, cp30_height + 3, cp30_z_pos - 1);
			glVertex3f(cp30_x_pos - 1, cp30_height + 3, cp30_z_pos - 1);
			glVertex3f(cp30_x_pos - 1, cp30_height + 3, cp30_z_pos + 1);
			glEnd();

		 //Left leg
			glPushMatrix();
				glTranslatef(cp30_x_pos , ship_floor_height + 10, cp30_z_pos + 1);
				glRotatef(cp30_leg_angle, 0, 0, 1);
				glTranslatef(-(cp30_x_pos), -(ship_floor_height + 10), -(cp30_z_pos + 1));
				glTranslatef(cp30_x_pos, ship_floor_height, cp30_z_pos + 1);
				glScalef(1, 15, 1);
				glutSolidCube(1);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(cp30_x_pos, ship_floor_height + 10, cp30_z_pos - 1);
				glRotatef(-cp30_leg_angle, 0, 0, 1);
				glTranslatef(-(cp30_x_pos), -(ship_floor_height + 10), -(cp30_z_pos - 1));
				glTranslatef(cp30_x_pos, ship_floor_height, cp30_z_pos - 1);
				glScalef(1, 15, 1);
				glutSolidCube(1);
			glPopMatrix();
			
			glPushMatrix();  //right hand
				glTranslatef(cp30_x_pos, cp30_height - 3, cp30_z_pos + 2.5);
				glScalef(1, 6, 1);
				glutSolidCube(1);
			glPopMatrix();
			
			glPushMatrix();  //right hand
				glTranslatef(cp30_x_pos, cp30_height - 3, cp30_z_pos - 2.5);
				glScalef(1, 6, 1);
				glutSolidCube(1);
			glPopMatrix();
		glPopMatrix();

		

	glPopMatrix();
	
}
//--Draws a character model constructed using GLUT objects ------------------
void drawR2()
{
	int r2_height = 6;
	glPushMatrix();
		glTranslatef(r2_x_pos, ship_floor_height + r2_height, r2_z_pos);
		glRotatef(robots_rotation, 0, 1,0);
		glTranslatef(-r2_x_pos, -(ship_floor_height + r2_height), -r2_z_pos);
		glPushMatrix();
			
			glBegin(GL_QUAD_STRIP);
				float rads;
				glColor3f(1, 1, 1); //Cylinder Body
				
				glVertex3f(r2_x_pos + cos(0), ship_floor_height + r2_height, r2_z_pos + sin(0));
				glVertex3f(r2_x_pos + cos(0), ship_floor_height , r2_z_pos +sin(0));
				for (int i = 0; i <= 359 ; i++ )
				{	
					rads = i * degreeRatio;
					normal(r2_x_pos + cos(rads), ship_floor_height, r2_z_pos + sin(rads),r2_x_pos + cos(rads), ship_floor_height + r2_height, r2_z_pos +sin(rads),
							r2_x_pos + cos(rads + 1* degreeRatio), ship_floor_height + r2_height, r2_z_pos +sin(rads + 1 * degreeRatio));
					glVertex3f(r2_x_pos + cos(rads + 1* degreeRatio), ship_floor_height + r2_height, r2_z_pos +sin(rads + 1 * degreeRatio));
					glVertex3f(r2_x_pos + cos(rads + 1* degreeRatio), ship_floor_height, r2_z_pos + sin(rads + 1* degreeRatio));
				}
				glVertex3f(r2_x_pos + cos(0), ship_floor_height , r2_z_pos +sin(1* degreeRatio));
				glVertex3f(r2_x_pos + cos(0), ship_floor_height + r2_height, r2_z_pos + sin(1* degreeRatio));
			glEnd();
		glPopMatrix();


		glPushMatrix();    //Draw R2 Head
			glColor3f(0., 0., 1.);
			glTranslatef(r2_x_pos, ship_floor_height + r2_height, r2_z_pos );
			glRotatef(robots_rotation, 0., 0., 1.);
			glutSolidSphere(1, 50,25);
		glPopMatrix();
		
		
		
		// Draw leg 1
		
		glPushMatrix();
			glColor3f(0,0,1);
			glTranslatef(r2_x_pos, ship_floor_height + 2, r2_z_pos + 1);
			glScalef(1, r2_height, 1);
			glutSolidCube(1);
		glPopMatrix();
		
		drawFeet(1);
		
			//Draw Leg 2
		glPushMatrix();
			glColor3f(0,0,1);
			glTranslatef(r2_x_pos, ship_floor_height + 2, r2_z_pos - 1);
			glScalef(1, r2_height, 1);
			glutSolidCube(1);
		glPopMatrix();
		drawFeet(2);
	glPopMatrix();

		

	
		

}

void draw_skybox(float x, float y, float z, float width, float height, float length)
{
	
	// Center the Skybox around the given x,y,z position
	x = x - width / 2;
	y = y - height / 2;
	z = z - length / 2;

	
	// Draw Front side
	glBindTexture(GL_TEXTURE_2D, texId[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glEnd();

	// Draw Back side
	glBindTexture(GL_TEXTURE_2D, texId[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glEnd();

	// Draw Left side
	glBindTexture(GL_TEXTURE_2D, texId[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glEnd();

	// Draw Right side
	glBindTexture(GL_TEXTURE_2D, texId[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glEnd();

	// Draw Up side
	glBindTexture(GL_TEXTURE_2D, texId[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glEnd();

	// Draw Down side
	glBindTexture(GL_TEXTURE_2D, texId[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z);
	glEnd();
	
}
void fireBullet(){
	
	glPushMatrix();
		glColor3f(1,0,0);
		glTranslatef(storm_x_pos + 6, ship_floor_height + 6, storm_z_pos);
		glScalef(3,1,1);
		glutSolidCube(1);
	glPopMatrix();
		
}
void animateClone(){
	
	
	if (!running){
		if(r2_x_pos <= -27.5 && r2_x_pos > destination){
		storm_x_pos++;
		}
	
	}else if(running == true){
		
		if (storm_x_pos > -70 && r2_x_pos > 37.5){
			storm_x_pos--;
		}
		if(robots_rotation == 180  && r2_x_pos > destination){ //turned round
			//fireBullet();
			
		}
			
		if(running && r2_x_pos < start){
			bullet_x_pos += 5;
		}
		if(r2_x_pos == start){
		
			bullet_x_pos = storm_x_pos + 6;
		//set bullet position to hand position
		};
	}
}
	
	
		


//--Display: ---------------------------------------------------------------
//--This is the main display module containing function calls for generating
//--the scene.
void display()
{
		
	float lgt_pos[4]={0,ship_floor_height + 25, 0, 1.};
	
	float lgt_pos2[4]={-80,ship_floor_height + 50, 0, 1.};
	float dir_x = -sin(theta), dir_y = 0,  dir_z = -cos(theta);


	eye_x = eye_x + 1.1* dir_x * step;
	eye_z = eye_z + 1.1* dir_z * step;
	
	look_x = eye_x + 2*dir_x;
	look_y = eye_y + 2*dir_y;
	look_z = eye_z + 2*dir_z;
	step = 0;
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);								
	glLoadIdentity();
	
	gluLookAt(eye_x, eye_y, eye_z,  look_x, look_y, look_z,   0, 1, 0);	
	
	glLightfv(GL_LIGHT0, GL_POSITION, lgt_pos);
	glLightfv(GL_LIGHT0, GL_POSITION, lgt_pos2);
	
	
	glEnable(GL_TEXTURE_2D);

	glDisable(GL_LIGHTING);
	draw_skybox(eye_x, eye_y, eye_z, 5000, 5000, 5000);

	glDisable(GL_TEXTURE_2D);
	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	drawHangar();//Enable lighting when drawing the model
	glDisable(GL_TEXTURE_2D);


	
	drawR2();
	glEnable(GL_TEXTURE_2D);
	drawStormTrooper();
	drawCP30();
	
	glDisable(GL_TEXTURE_2D);
	glFlush();
}

void changeView()
{
	if (viewNo == 1)
	{
		viewNo ++;
		eye_x = r2_x_pos;  eye_y = ship_floor_height + 6; eye_z = r2_z_pos;
		look_x = - 100; look_y = ship_floor_height + 6; look_z = 0;
		    //Camera View 2, R2D2
		locked_view = true;    //"Look-at" point along -z direction
		theta = robots_rotation;
	}
	else if(viewNo == 2)
	{ 
		viewNo ++;  //View 3, cp30;
		eye_x = cp30_x_pos;eye_y = ship_floor_height + 10, eye_z = cp30_z_pos;
		look_x = - 100; look_y = ship_floor_height + 10; look_z = 0;
		locked_view = true;
		theta = robots_rotation;
	}
	else if (viewNo == 3)
	{
		viewNo ++; //view 4- The outside of ship.
		eye_x = -200;eye_y = ship_floor_height + 100; eye_z = -400;
		look_x = -200;look_y= 0; look_z = 0;
		locked_view = false;
		theta = 179.4;
		
	}
	else{
		viewNo = 1;  //default view. Just above 
		eye_x = 0; eye_y = ship_floor_height + 10; eye_z = 10;
		look_x = 0; look_y = 0; look_z = 0;
		locked_view = false;
		theta = 0;
	}
		
		
		
}

//------- Initialize OpenGL parameters -----------------------------------
void initialize()
{
	
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);	//Background colour

	float lgt_amb[4] = {0.2, 0.2, 0.2, 1.0};
	float lgt_dif[4] = {1.0, 1.0, 1.0, 1.0};
	float lgt_spe[4] = {1.0, 1.0, 1.0, 1.0};
	float mat_amb[4] = {0.0, 0.0, 1.0, 1.0};
	float mat_dif[4] = {0.0, 0.0, 1.0, 1.0};
	float mat_spe[4] = {1.0, 1.0, 1.0, 1.0};

	 glLightfv(GL_LIGHT0, GL_AMBIENT, lgt_amb);
	 glLightfv(GL_LIGHT0, GL_DIFFUSE, lgt_dif);
	 glLightfv(GL_LIGHT0, GL_SPECULAR, lgt_spe);
	 glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
	 glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dif);
	 glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spe);
	 glMaterialf(GL_FRONT, GL_SHININESS, 50); 
	
	glEnable(GL_LIGHTING);					//Enable OpenGL states
	glEnable(GL_LIGHT0);
 	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 20000.0);   //Camera Frustum
	loadTextures();
	
}

//------------ Special key event callback ---------------------------------
// To enable the use of left and right arrow keys to rotate the scene
void special(int key, int x, int y)
{
	if(key == GLUT_KEY_F1) changeView();
	if (!locked_view){
		step = 0;
		if(key == GLUT_KEY_LEFT) theta += 0.1;   //in radians
		else if(key == GLUT_KEY_RIGHT) theta -= 0.1;
		else if(key == GLUT_KEY_DOWN) step = -1;
		else if(key == GLUT_KEY_UP) step = 1;
	
	}
	//glutPostRedisplay();
}

void myTimer(int value)
{
	animateClone();
	animateRobots();
	
	animateC3PO();
	glutPostRedisplay();
	glutTimerFunc(50, myTimer, 0);

}


//  ------- Main: Initialize glut window and register call backs -----------
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("A Robots World");
	initialize();

	glutDisplayFunc(display);
	glutSpecialFunc(special);
	glutTimerFunc(50, myTimer, 0);
	glutMainLoop();
	return 0;
}

