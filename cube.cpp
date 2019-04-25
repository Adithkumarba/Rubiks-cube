#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <GL/glut.h>

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2, 2, -2, 2, -2, 2);
	glMatrixMode(GL_MODELVIEW);
}
float co[7][3] = { {0.3,0.8,0 }, { 0,0.5,1 }, { 1,0.8,0 }, { 0.9,0.9,0.9 }, { 1,0.4,0 }, { 0.9,0,0 }, { 0.2,0.2,0.2 } };
float v[8][8][3];
// ----------------------------------------------------------
// Function Prototypes
// ----------------------------------------------------------
void drawcube(float *a1,float *a2,float *a3 , float *a4 , float *a5,float *a6 , float *a7, float *a8)
{
	glBegin(GL_POLYGON);
	glColor3fv(co[0]);
	glVertex3fv(a1);
	glVertex3fv(a2);
	glVertex3fv(a3);
	glVertex3fv(a4);

	glEnd();

	// White side - BACK
	glBegin(GL_POLYGON);
	glColor3fv(co[1]);
	glVertex3fv(a5);
	glVertex3fv(a6);
	glVertex3fv(a7);
	glVertex3fv(a8);
	glEnd();

	// Purple side - RIGHT
	glBegin(GL_POLYGON);
	glColor3fv(co[2]);
	glVertex3fv(a2);
	glVertex3fv(a6);
	glVertex3fv(a7);
	glVertex3fv(a3);
	glEnd();

	// Green side - LEFT
	glBegin(GL_POLYGON);
	glColor3fv(co[3]);
	glVertex3fv(a1);
	glVertex3fv(a5);
	glVertex3fv(a8);
	glVertex3fv(a4);
	glEnd();

	// Blue side - TOP
	glBegin(GL_POLYGON);
	glColor3fv(co[4]);
	glVertex3fv(a1);
	glVertex3fv(a2);
	glVertex3fv(a6);
	glVertex3fv(a5);
	glEnd();

	// Red side - BOTTOM
	glBegin(GL_POLYGON);
	glColor3fv(co[5]);
	glVertex3fv(a4);
	glVertex3fv(a3);
	glVertex3fv(a7);
	glVertex3fv(a8);
	glEnd();
	//glFlush();
	
}

void makepoints()
{
	double start = 1.0;
	double small_size = 0.975;
	double intercube_spacing = 0.05;
	int i = 0;

	for (double z = start; z > -start; z -= small_size + intercube_spacing) {
		for (double y = start; y > -start; y -= small_size + intercube_spacing) {
			for (double x = -start; x < start; x += small_size + intercube_spacing) {

				float a[8][3] = {
					{ x , y, z },
					{ x + small_size, y, z },
					{ x + small_size, y - small_size, z },
					{ x , y - small_size, z },
					{ x , y, z - small_size },
					{ x + small_size, y, z - small_size },
					{ x + small_size, y - small_size, z - small_size },
					{ x , y - small_size, z - small_size }
				};
				for (int j = 0; j < 8; j++)
					for (int k = 0; k < 3; k++)
						v[i][j][k] = a[j][k];
				i += 1;
			}
		}
	}
}


void buildcube()
{
	for(int i=0;i<8;i++)
		drawcube(v[i][0], v[i][1], v[i][2], v[i][3], v[i][4], v[i][5], v[i][6], v[i][7]);			
}

void display();
void specialKeys();

// ----------------------------------------------------------
// Global Variables
// ----------------------------------------------------------
double rotate_y = 0;
double rotate_x = 0;

// ----------------------------------------------------------
// display() Callback function
// ----------------------------------------------------------
void display() {
	//  Clear screen and Z-buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);
	makepoints();
	buildcube();
	
	glutSwapBuffers();

}

// ----------------------------------------------------------
// specialKeys() Callback Function
// ----------------------------------------------------------
void specialKeys(int key, int x, int y) {
	
	//  Right arrow - increase rotation by 5 degree
	if (key == GLUT_KEY_RIGHT)
	{
		rotate_y += 5;
	} 
	//  Left arrow - decrease rotation by 5 degree
	else if (key == GLUT_KEY_LEFT)
	{
		rotate_y -= 5;
	}

	else if (key == GLUT_KEY_UP)
	{
		rotate_x += 5;
	}

	else if (key == GLUT_KEY_DOWN)
	{
		rotate_x -= 5;
	}

	//  Request display update
	glutPostRedisplay();

}

// ----------------------------------------------------------
// main() function
// ----------------------------------------------------------
int main(int argc, char* argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	
	glutCreateWindow("dumb box");

	glEnable(GL_DEPTH_TEST);
	init();

	glutDisplayFunc(display);
	glutSpecialFunc(specialKeys);
	glutMainLoop();


	return 0;

}