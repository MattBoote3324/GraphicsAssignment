//Jeff Chastine
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include "loadTGA.h"
#include "TextureLoader.h"


using namespace std;

//--Draws a grid of lines on the floor plane -------------------------------
using namespace std;

//--Globals ---------------------------------------------------------------
int cam_hgt = 40; //Camera height
float angle = 10.0;  //Rotation angle for viewing
float theta = 180;
float zoom = 4;
float cam_x = 0;
bool increasing = false;
float ship_floor_height = 25;
float r2_x_pos = 0;
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

		//glColor3f(0., 0., 1.);
		normal(-100, ship_floor_height, 30, -100, ship_floor_height, -30, -60, ship_floor_height, -10); //Ship Floor Left Base
		glVertex3f(-100, ship_floor_height, 30); glVertex3f(-100, ship_floor_height, -30); glVertex3f(-60, ship_floor_height, -10); glVertex3f(-60, ship_floor_height, 10);
	
		//glColor3f(0., 0., 1.);
		normal(-100, ship_floor_height, 30, -100, ship_floor_height, -30, 60, ship_floor_height, -10); //Ship Floor Right Base
		glVertex3f(100, ship_floor_height, 30); glVertex3f(100, ship_floor_height, -30); glVertex3f(60, ship_floor_height, -10); glVertex3f(60, ship_floor_height, 10);
	
	
		//glColor3f(1., 0., 0.);
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

void drawCP30() {

}
//--Draws a character model constructed using GLUT objects ------------------
void drawR2()
{
	glPushMatrix();
		glBegin(GL_QUAD_STRIP);
		glColor3f(1, 1, 1); //Cylinder Body
		int r2_height = 6;
		for (int i = 0; i <= 359; i++)
		{
			glNormal3d(cos(i), ship_floor_height, sin(i));

			glVertex3f(r2_x_pos + cos(i), ship_floor_height + 2, sin(i));
			glVertex3f(r2_x_pos + cos(i), ship_floor_height + r2_height, sin(i));
			glVertex3f(r2_x_pos + cos(i + 1), ship_floor_height + r2_height, sin(i + 1));
			glVertex3f(r2_x_pos + cos(i + 1), ship_floor_height  + 2, sin(i + 1));
		}
		glEnd();
	glPopMatrix();

	glPushMatrix();
		//glColor3f(0., 0., 1.);
		glTranslatef(r2_x_pos, ship_floor_height + r2_height, 0);
		glutSolidSphere(1, 50,25);

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
	//glDisable(GL_TEXTURE_2D);
}


//--Display: ---------------------------------------------------------------
//--This is the main display module containing function calls for generating
//--the scene.
void display()
{
	float lpos[4] = { 0, 45, 0, 1.0 };  //light's position

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cam_x,cam_hgt, zoom, 0, 4, 0, 0, 1, 0);
	glLightfv(GL_LIGHT0, GL_POSITION, lpos);   //Set light position

	//glRotatef(angle, 0.0, 1.0, 0.0);  //Rotate the scene about the y-axis

	glDisable(GL_LIGHTING);			//Disable lighting when drawing floor.
	//drawFloor();
	
	


	glEnable(GL_LIGHTING);
	draw_skybox(0, 0, 0, 5000, 5000, 5000);
	drawHangar();//Enable lighting when drawing the model
	

	
	drawR2();
	drawCP30();
	
	glFlush();
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
	if (key == GLUT_KEY_LEFT) cam_x-=5;
	else if (key == GLUT_KEY_RIGHT) cam_x+=5;
	else if (key == GLUT_KEY_UP) cam_hgt+=5;
	else if (key == GLUT_KEY_DOWN) cam_hgt-=5;
	else if (key == GLUT_KEY_F1) zoom-=5;
	else if (key == GLUT_KEY_F2) zoom+=5;
	else if (key == GLUT_KEY_F8) angle-=5;
	else if (key == GLUT_KEY_F9) angle+=5;
	glutPostRedisplay();
}

void myTimer(int value)
{
	

	if (increasing) {
		theta++;
	}
	else { theta--; }

	if (theta >= 20) {
		increasing = false;
	}
	else if (theta <= -20) {
		increasing = true;
	}
	//theta++;
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

