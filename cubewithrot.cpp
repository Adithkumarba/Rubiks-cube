#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <GL/glut.h>
int flagc[5] = { 0,0,0,0,0 };
int flagac[5] = { 0,0,0,0,0 };
void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2, 2, -2, 2, -2, 2);
	glMatrixMode(GL_MODELVIEW);
}
float co[7][3] = { {0.3,0.8,0 }, { 0,0.5,1 }, { 1,0.8,0 }, { 0.9,0.9,0.9 }, { 1,0.4,0 }, { 0.9,0,0 }, { 0.2,0.2,0.2 } };
float v[8][8][3];
int p[8] = { 0,1,2,3,4,5,6,7 };
// ----------------------------------------------------------
// Function Prototypes
// ----------------------------------------------------------
void drawcube(float *a1, float *a2, float *a3, float *a4, float *a5, float *a6, float *a7, float *a8)
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
	for (int i = 0; i < 8; i++)
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
void display(void) {
	//  Clear screen and Z-buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);

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

void idle1()
{
	flagc[1] += 1;
	float theta = 5 * 3.1415 / 180;
	for (int i = 0; i < 8; i++)
	{
		if (i == 0 || i == 1 || i == 4 || i == 5)
		{
			for (int j = 0; j < 8; j++)
			{
				float z = v[p[i]][j][2];
				float x = v[p[i]][j][0];
				v[p[i]][j][2] = z * cos(theta) - x * sin(theta);
				v[p[i]][j][0] = x * cos(theta) + z * sin(theta);
			}
			glutPostRedisplay();
		}
	}
	int temp = p[0];
	p[0] = p[4];
	p[4] = p[5];
	p[5] = p[1];
	p[1] = temp;
	for (int k = 0; k < 9000000; k++);
	printf("%d", p[0]);
	if (flagc[1] == 18)
	{
		glutIdleFunc(NULL);
		flagc[1] = 0;
	}
}
void idle2()
{
	flagc[2] += 1;
	float theta = 5 * 3.1415 / 180;
	for (int i = 0; i < 8; i++)
	{
		if (i == 1 || i == 3 || i == 5 || i == 7)
		{
			for (int j = 0; j < 8; j++)
			{
				float z = v[p[i]][j][2];
				float y = v[p[i]][j][1];
				v[p[i]][j][2] = z * cos(theta) - y * sin(theta);
				v[p[i]][j][1] = y * cos(theta) + z * sin(theta);
			}
			glutPostRedisplay();
		}
	}
	int temp = p[1];
	p[1] = p[3];
	p[3] = p[7];
	p[7] = p[5];
	p[5] = temp;
	for (int k = 0; k < 9000000; k++);

	if (flagc[2] == 18)
	{
		glutIdleFunc(NULL);
		flagc[2] = 0;
	}
}
void idle3()
{
	flagc[3] += 1;
	float theta = 5 * 3.1415 / 180;
	for (int i = 0; i < 8; i++)
	{
		if (i == 0 || i == 1 || i == 4 || i == 5)
		{
			for (int j = 0; j < 8; j++)
			{
				float z = v[p[i]][j][2];
				float x = v[p[i]][j][0];
				v[p[i]][j][2] = z * cos(theta) + x * sin(theta);
				v[p[i]][j][0] = x * cos(theta) - z * sin(theta);

			}
			glutPostRedisplay();
		}
	}
	int temp = p[0];
	p[0] = p[1];
	p[1] = p[5];
	p[5] = p[4];
	p[4] = temp;
	for (int k = 0; k < 9000000; k++);

	if (flagc[3] == 18)
	{
		glutIdleFunc(NULL);
		flagc[3] = 0;
	}
}
void idle4()
{
	flagc[4] += 1;
	float theta = 5 * 3.1415 / 180;

	for (int i = 0; i < 8; i++)
	{
		if (i == 1 || i == 3 || i == 5 || i == 7)
		{
			for (int j = 0; j < 8; j++)
			{
				float z = v[p[i]][j][2];
				float y = v[p[i]][j][1];
				v[p[i]][j][2] = z * cos(theta) + y * sin(theta);
				v[p[i]][j][1] = y * cos(theta) - z * sin(theta);

			}
			glutPostRedisplay();
		}
	}
	int temp = p[1];
	p[1] = p[5];
	p[5] = p[7];
	p[7] = p[3];
	p[3] = temp;
	for (int k = 0; k < 9000000; k++);
	if (flagc[4] == 18)
	{
		glutIdleFunc(NULL);
		flagc[4] = 0;
	}
}
void keyboard(unsigned char key, int x, int y)
{
	if (key == 'q')
	{
		//idle1();
		glutIdleFunc(idle1);
	}

	if (key == 'a')
	{
		//idle2();
		glutIdleFunc(idle2);
	}
	if (key == 'w')
	{	//idle3();
		glutIdleFunc(idle3);
	}
	if (key == 's')
	{	//idle4();
		glutIdleFunc(idle4);
	}
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
	makepoints();
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutSpecialFunc(specialKeys);
	glutKeyboardFunc(keyboard);
	glutMainLoop();


	return 0;

}