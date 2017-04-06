//Jeff Chastine

//#include <GL\glew.h>
//#include <GL\freeglut.h>
#include <iostream>
#include "loadTGA.h"
#include "TextureLoader.h"
#include <math.h>

using namespace std;

//--Draws a grid of lines on the floor plane -------------------------------
using namespace std;

//--Globals ---------------------------------------------------------------
float  theta = 0;
float degreeRatio = M_PI / 180;
float robots_rotation = 90  ;

bool increasing = false;
float ship_floor_height = 25;

int viewNo = 1;
bool locked_view =false;    
bool running = false;                        //Look angle
int step = 0;	
float r2_x_pos = 80, r2_z_pos = 5;
float cp30_x_pos = 0, cp30_z_pos = -5;
float eye_x = 0, eye_y = ship_floor_height + 20, eye_z = 15;
float look_x = 0, look_y = 0, look_z = 0;

float destination = -80;
float start = 80;
//--Draws a grid of lines on the floor plane -------------------------------

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
	
	glBegin(GL_QUADS);
		glColor3f(1,0.,0.);
		glNormal3f(0., 0., 1.0); //Front Side +z
		glVertex3f(-100, 0., 30);glVertex3f(100, 0., 30);glVertex3f(100, 50, 30); glVertex3f(-100, 50, 30);

		glNormal3f(0., 0., -1.0); //Back Side -z
		glVertex3f(-100, 0., -30);glVertex3f(100, 0., -30);glVertex3f(100, 50, -30);glVertex3f(-100, 50, -30);

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

		glColor3f(0., 0., 1.);
		normal(-100, ship_floor_height, 30, -100, ship_floor_height, -30, -60, ship_floor_height, -10); //Ship Floor Left Base
		glVertex3f(-100, ship_floor_height, 30); glVertex3f(-100, ship_floor_height, -30); glVertex3f(-60, ship_floor_height, -10); glVertex3f(-60, ship_floor_height, 10);
	
		glColor3f(0., 0., 1.);
		normal(-100, ship_floor_height, 30, -100, ship_floor_height, -30, 60, ship_floor_height, -10); //Ship Floor Right Base
		glVertex3f(100, ship_floor_height, 30); glVertex3f(100, ship_floor_height, -30); glVertex3f(60, ship_floor_height, -10); glVertex3f(60, ship_floor_height, 10);
	
	
		glColor3f(1., 0., 0.);
		normal(-100, ship_floor_height, 30, -100, ship_floor_height, -30, 80, ship_floor_height, -20); //Ship Bridge
		glVertex3f(60, ship_floor_height, -10); glVertex3f(60, ship_floor_height, 10); glVertex3f(-60, ship_floor_height, 10); glVertex3f(-60, ship_floor_height, -10);

	glEnd();

	glPushMatrix();		//Ship Neck
		glTranslatef(-200, 25, 0);
		glScalef(8, 2, 2.4);
		glutSolidCube(25);
	glPopMatrix();

	glBegin(GL_TRIANGLES); //Ship front Cone
		glVertex3f(-300, 50, 30); glVertex3f(-370, 25, 0); glVertex3f(-300, 0, 30);
		glVertex3f(-300, 50, -30); glVertex3f(-370, 25, 0); glVertex3f(-300, 50, 30);
		glVertex3f(-300, 50, -30); glVertex3f(-370, 25, 0); glVertex3f(-300, 0, -30);
		glVertex3f(-300, 0, 30); glVertex3f(-370, 25, 0); glVertex3f(-300, 0, -30);
	glEnd();

	
}
void drawFeet(int lrc){

		//lrc is left, right or center. 1 = left,2 = right, 3= center
		int z1 =0, z2 = 0;
		switch(lrc){
			case(1):z1 =2;z2 =1;break;
			case(2):z1 = -2;z2 = -1;break;
			//case(3):z1 = 1; z2 = -1;break;
		}
		glBegin(GL_QUADS);//Feet/Wheel things
			glColor3f(1,1,1);
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
		
}


void animateRobots(){
	
	if(!running){
		if(r2_x_pos > destination){
			r2_x_pos--;
			} //go towards destination
		else if(r2_x_pos == destination)
		{
			robots_rotation += 1;
			
		}
		if (robots_rotation == 270  && r2_x_pos == destination){ //we've turned them around
				r2_x_pos++;
				
				running = true;
		}
		
	}
	else{
		if (r2_x_pos < start)
		{
			r2_x_pos ++;
		}else if(r2_x_pos == start)
		{
			robots_rotation -=1;
			
		}
		if (robots_rotation == 90  && r2_x_pos == start ){ //we've turned them around
			r2_x_pos--;
			running = false; //we are going back towards the bullets
		}
		
	}
	if (viewNo == 2){
		
		eye_x = r2_x_pos;
		theta = robots_rotation * degreeRatio;
		
	}
		
}
void drawCP30() {
	glPushMatrix();
		glColor3f(1,1,0);  //Draw Body
		int cp30_height = 8;
		
		glBegin(GL_QUADS);
			glVertex(
			
		glTranslatef(cp30_x_pos, ship_floor_height + cp30_height, cp30_z_pos);
		glScalef(3,cp30_height,3);
		glutSolidCube(1);
		
	glPopMatrix();
}
//--Draws a character model constructed using GLUT objects ------------------
void drawR2()
{
	glPushMatrix();
		glBegin(GL_QUAD_STRIP);
		float rads;
		glColor3f(1, 1, 1); //Cylinder Body
		int r2_height = 6;
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
	drawFeet(2);
		
	glPushMatrix();
		glColor3f(0,0,1);
		glTranslatef(r2_x_pos, ship_floor_height + 2, r2_z_pos - 1);
		glScalef(1, r2_height, 1);
		glutSolidCube(1);
	glPopMatrix();
	
		

}

void draw_skybox(float x, float y, float z, float width, float height, float length)
{
	
	// Center the Skybox around the given x,y,z position
	x = x - width / 2;
	y = y - height / 2;
	z = z - length / 2;

	glEnable(GL_TEXTURE_2D);
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
	glDisable(GL_TEXTURE_2D);
}



//--Display: ---------------------------------------------------------------
//--This is the main display module containing function calls for generating
//--the scene.
void display()
{
	float lpos[4] = { 0, 0, 0, 1.0 };  //light's position
	
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
	glLightfv(GL_LIGHT0, GL_POSITION, lpos);   //Set light position

	//glRotatef(angle, 0.0, 1.0, 0.0);  //Rotate the scene about the y-axis

			//Disable lighting when drawing floor.
	//drawFloor();
	
	


	glDisable(GL_LIGHTING);
	draw_skybox(eye_x, eye_y, eye_z, 5000, 5000, 5000);
	glEnable(GL_LIGHTING);
	drawHangar();//Enable lighting when drawing the model
	

	
	drawR2();
	drawCP30();
	
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
		eye_x = 0; eye_y = ship_floor_height + 10; eye_z = 15;
		look_x = 0; look_y = 0; look_z = 0;
		locked_view = false;
		theta = 0;
	}
		
		
		
}

//------- Initialize OpenGL parameters -----------------------------------
void initialize()
{
	
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);	//Background colour

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
	
	animateRobots();
	
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

