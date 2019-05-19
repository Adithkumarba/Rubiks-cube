#include <stdio.h>
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
float v[27][8][3];
int p[27] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26 };
int f[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 }, theta = 0;
double rotate_y = 20;
double rotate_x = 15;


void drawcube(float *a1, float *a2, float *a3, float *a4, float *a5, float *a6, float *a7, float *a8)
{
	glBegin(GL_POLYGON);
	glColor3fv(co[0]);
	glVertex3fv(a1);
	glVertex3fv(a2);
	glVertex3fv(a3);
	glVertex3fv(a4);
	glEnd();

	
	glBegin(GL_POLYGON);
	glColor3fv(co[1]);
	glVertex3fv(a5);
	glVertex3fv(a6);
	glVertex3fv(a7);
	glVertex3fv(a8);
	glEnd();

	
	glBegin(GL_POLYGON);
	glColor3fv(co[2]);
	glVertex3fv(a2);
	glVertex3fv(a6);
	glVertex3fv(a7);
	glVertex3fv(a3);
	glEnd();

	
	glBegin(GL_POLYGON);
	glColor3fv(co[3]);
	glVertex3fv(a1);
	glVertex3fv(a5);
	glVertex3fv(a8);
	glVertex3fv(a4);
	glEnd();

	
	glBegin(GL_POLYGON);
	glColor3fv(co[4]);
	glVertex3fv(a1);
	glVertex3fv(a2);
	glVertex3fv(a6);
	glVertex3fv(a5);
	glEnd();

	
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
	double small_size = 0.65;
	double intercube_spacing = 0.025;
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
void rotaxis(int *arr, char dir, char axis)
{
	float angle = 5 * 3.1415 / 180;
	for (int i = 0; i < 27; i++)
	{
		if (i == arr[0] || i == arr[1] || i == arr[2] || i == arr[3] || i == arr[4] || i == arr[5] || i == arr[6] || i == arr[7] || i == arr[8])
		{
			for (int j = 0; j < 8; j++)
			{
				if (dir == 'c'&& axis == 'x')
				{
					float z = v[p[i]][j][2];
					float y = v[p[i]][j][1];
					v[p[i]][j][2] = z * cos(angle) + y * sin(angle);
					v[p[i]][j][1] = y * cos(angle) - z * sin(angle);
				}
				else if (dir == 'a'&& axis == 'x')
				{
					float z = v[p[i]][j][2];
					float y = v[p[i]][j][1];
					v[p[i]][j][2] = z * cos(angle) - y * sin(angle);
					v[p[i]][j][1] = y * cos(angle) + z * sin(angle);
				}

				else if (dir == 'a'&& axis == 'y')
				{
					float z = v[p[i]][j][2];
					float x = v[p[i]][j][0];
					v[p[i]][j][2] = z * cos(angle) - x * sin(angle);
					v[p[i]][j][0] = x * cos(angle) + z * sin(angle);
				}
				else if (dir == 'c'&& axis == 'y')
				{
					float z = v[p[i]][j][2];
					float x = v[p[i]][j][0];
					v[p[i]][j][2] = z * cos(angle) + x * sin(angle);
					v[p[i]][j][0] = x * cos(angle) - z * sin(angle);
				}
				else if (dir == 'c'&& axis == 'z')
				{
					float y = v[p[i]][j][1];
					float x = v[p[i]][j][0];
					v[p[i]][j][0] = x * cos(angle) + y * sin(angle);
					v[p[i]][j][1] = y * cos(angle) - x * sin(angle);
				}
				else if (dir == 'a'&& axis == 'z')
				{
					float y = v[p[i]][j][1];
					float x = v[p[i]][j][0];
					v[p[i]][j][0] = x * cos(angle) - y * sin(angle);
					v[p[i]][j][1] = y * cos(angle) + x * sin(angle);
				}
			}
		}
	}
	theta += 5;
}
void pointswap(int *arr, char dir)
{
	int temp[27] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	for (int m = 0; m < 9; m++)
		temp[m] = p[arr[m]];
	if (dir == 'a')
	{
		p[arr[0]] = temp[2];
		p[arr[1]] = temp[5];
		p[arr[2]] = temp[8];
		p[arr[3]] = temp[1];
		p[arr[4]] = temp[4];
		p[arr[5]] = temp[7];
		p[arr[6]] = temp[0];
		p[arr[7]] = temp[3];
		p[arr[8]] = temp[6];
	}
	else if (dir == 'c')
	{
		p[arr[0]] = temp[6];
		p[arr[1]] = temp[3];
		p[arr[2]] = temp[0];
		p[arr[3]] = temp[7];
		p[arr[4]] = temp[4];
		p[arr[5]] = temp[1];
		p[arr[6]] = temp[8];
		p[arr[7]] = temp[5];
		p[arr[8]] = temp[2];
	}
	
}
void idle()
{
	if (f[1] == 1)
	{
		int arr[9] = { 18,9,0,21,12,3,24,15,6 };
		if (theta < 90)
		{
			rotaxis(arr, 'a', 'x');
		}
		else
		{
			f[1] = 0;
			theta = 0;
			pointswap(arr, 'a');
		}
		for (int i = 0; i < 8000000; i++);
		glutPostRedisplay();
	}
	if (f[2] == 1)
	{
		int arr[9] = { 6,7,8,15,16,17,24,25,26 };
		if (theta < 90)
		{
			rotaxis(arr, 'a', 'y');
		}
		else
		{
			f[2] = 0;
			theta = 0;
			pointswap(arr, 'c');
		}
		for (int i = 0; i < 8000000; i++);
		glutPostRedisplay();
	}
	if (f[3] == 1)
	{
		int arr[9] = { 2,11,20,5,14,23,8,17,26 };
		if (theta < 90)
		{
			rotaxis(arr, 'a', 'x');
		}
		else
		{
			f[3] = 0;
			theta = 0;
			pointswap(arr, 'c');
		}
		for (int i = 0; i < 8000000; i++);
		glutPostRedisplay();
	}
	if (f[4] == 1)
	{
		int arr[9] = { 6,7,8,15,16,17,24,25,26 };
		if (theta < 90)
		{
			rotaxis(arr, 'c', 'y');
		}
		else
		{
			f[4] = 0;
			theta = 0;
			pointswap(arr, 'a');
		}
		for (int i = 0; i < 8000000; i++);
		glutPostRedisplay();
	}
	if (f[5] == 1)
	{
		int arr[9] = { 0,1,2,3,4,5,6,7,8 };
		if (theta < 90)
		{
			rotaxis(arr, 'a', 'z');
		}
		else
		{
			f[5] = 0;
			theta = 0;
			pointswap(arr, 'a');
		}
		for (int i = 0; i < 8000000; i++);
		glutPostRedisplay();
	}
	if (f[6] == 1)
	{
		int arr[9] = { 18,19,20,9,10,11,0,1,2 };
		if (theta < 90)
		{
			rotaxis(arr, 'a', 'y');
		}
		else
		{
			f[6] = 0;
			theta = 0;
			pointswap(arr, 'a');
		}
		for (int i = 0; i < 8000000; i++);
		glutPostRedisplay();
	}
	if (f[7] == 1)
	{
		int arr[9] = { 18,9,0,21,12,3,24,15,6 };
		if (theta < 90)
		{
			rotaxis(arr, 'c', 'x');
		}
		else
		{
			f[7] = 0;
			theta = 0;
			pointswap(arr, 'c');
		}
		for (int i = 0; i < 8000000; i++);
		glutPostRedisplay();

	} 
	if (f[8] == 1)  //TOP'
	{
		int arr[9] = { 18,19,20,9,10,11,0,1,2 };
		if (theta < 90)
		{
			rotaxis(arr, 'c', 'y');
		}
		else
		{
			f[8] = 0;
			theta = 0;
			pointswap(arr, 'c');
		}
		for (int i = 0; i < 8000000; i++);
		glutPostRedisplay();
	}
	if (f[9] == 1)
	{
		int arr[9] = { 2,11,20,5,14,23,8,17,26 };
		if (theta < 90)
		{
			rotaxis(arr, 'c', 'x');
		}
		else
		{
			f[9] = 0;
			theta = 0;
			pointswap(arr, 'a');
		}
		for (int i = 0; i < 8000000; i++);
		glutPostRedisplay();
	}
	if (f[0] == 1) 
	{
		int arr[9] = { 0,1,2,3,4,5,6,7,8 };
		if (theta < 90)
		{
			rotaxis(arr, 'c', 'z');
		}
		else
		{
			f[0] = 0;
			theta = 0;
			pointswap(arr, 'c');
		}
		for (int i = 0; i < 8000000; i++);
		glutPostRedisplay();
	}
	if (f[10] == 1)
	{
		int arr[9] = { 18,19,20,21,22,23,24,25,26 };
		if (theta < 90)
		{
			rotaxis(arr, 'c', 'z');
		}
		else
		{
			f[10] = 0;
			theta = 0;
			pointswap(arr, 'c');
		}
		for (int i = 0; i < 8000000; i++);
		glutPostRedisplay();
	}
	if (f[11] == 1)
	{
		int arr[9] = { 18,19,20,21,22,23,24,25,26 };
		if (theta < 90)
		{
			rotaxis(arr, 'a', 'z');
		}
		else
		{
			f[11] = 0;
			theta = 0;
			pointswap(arr, 'a');
		}
		for (int i = 0; i < 8000000; i++);
		glutPostRedisplay();
	}
}
void buildcube()
{
	for (int i = 0; i < 27; i++)
		drawcube(v[i][0], v[i][1], v[i][2], v[i][3], v[i][4], v[i][5], v[i][6], v[i][7]);
}


void display(void) {
	
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);

	buildcube();

	glutSwapBuffers();

}
 

void specialKeys(int key, int x, int y) {

	
	if (key == GLUT_KEY_RIGHT)
	{
		rotate_y += 5;
	}
	
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

	
	glutPostRedisplay();

}
void keyboard(unsigned char key, int x, int y)
{
	if (key == '1')
	{
		f[1] = 1;
	}
	if (key == '2')
	{
		f[2] = 1;
	}
	if (key == '3')
	{
		f[3] = 1;
	}
	if (key == '4')
	{
		f[4] = 1;
	}
	if (key == '6')
	{
		f[6] = 1;
	}
	if (key == '7')
	{
		f[7] = 1;
	}
	if (key == '8')
	{
		f[8] = 1;
	}
	if (key == '9')
	{
		f[9] = 1;
	}
	if (key == '0')
	{
		f[0] = 1;
	}
	if (key == '5')
	{
		f[5] = 1;
	}
	if (key == 'b')
	{
		f[10] = 1;
	}
	if (key == 'n')
	{
		f[11] = 1;
	}
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
	{
		glOrtho(-2, 2, -2 * (GLfloat)h / (GLfloat)w, 2 * (GLfloat)h / (GLfloat)w, -2, 2);
	}
	else
	{
		glOrtho(-2 * (GLfloat)w / (GLfloat)h, 2 * (GLfloat)w / (GLfloat)h, -2, 2, -2, 2);
	}
	glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char* argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);

	glutCreateWindow("dumb box");

	glEnable(GL_DEPTH_TEST);
	init();
	makepoints();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutSpecialFunc(specialKeys);
	glutKeyboardFunc(keyboard);
	glutMainLoop();


	return 0;
}