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
// ----------------------------------------------------------
// Global Variables
// ----------------------------------------------------------
float co[7][3] = { {0.3,0.8,0 }, { 0,0.5,1 }, { 1,0.8,0 }, { 0.9,0.9,0.9 }, { 1,0.4,0 }, { 0.9,0,0 }, { 0.2,0.2,0.2 } };
float ***v;

int *p;
int f[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 }, theta = 0;
double rotate_y = 0;
double rotate_x = 0;
int n,N;
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
	long double start = 1.0;
	long double intercube_spacing = ( 2 / (N - 1)) / 40;
	long double small_size = (2-( (N-1)*intercube_spacing))/N;
	
	printf("%lf \n", small_size);
	printf("%lf\n", intercube_spacing);
	printf("%d",N / 2);
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
void rotaxis(int **arr, char dir, char axis)
{
	float angle = 5 * 3.1415 / 180;
	for (int i = 0; i < n; i++)
	{
		
		for(int ii=0;ii<N;ii++)
		for (int jj = 0; jj < N; jj++)
		if (i == arr[ii][jj] )//|| i == arr[1] || i == arr[2] || i == arr[3] || i == arr[4] || i == arr[5] || i == arr[6] || i == arr[7] || i == arr[8])
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
void pointswap(int **arr, char dir)
{
	int **temp;
	temp= (int **)malloc(sizeof(int **)*N);
	for (int i = 0; i < N; i++)
		temp[N] = (int *)malloc(sizeof(int*)*N);

	for (int ii = 0; ii < N; ii++)
		for (int jj = 0; jj < N; jj++)
		temp[ii][jj] = p[arr[ii][jj]];
	
	if (dir == 'a')
	{
		int i = 0, j = 0;
		for (int ii = N; ii >0; ii--)
		{

			for (int jj = 0; jj <N; jj++)
			{
				p[arr[i][j]] = temp[ii][jj];
				j++;
			}
			i++;
		}
	}
	else if (dir == 'c')
	{
		int i = 0, j = 0;
		for (int ii = 0; ii < N; ii++)
		{

			for (int jj = N; jj > 0; jj--)
			{
				p[arr[i][j]] = temp[ii][jj];
				j++;
			}
			i++;
		}
	}
	
}
void idle()
{
	int **arr;
	arr = (int **)malloc(sizeof(int **)*N);
	for (int i = 0; i < N; i++)
		arr[N] = (int *)malloc(sizeof(int*)*N);

	if (f[1] == 1)
	{
		int t = 0;
		for (int j = N; j > 0 ;j--)
		
		{
			for (int i = 0; i < N; i++)
			{
				arr[i][j] = t;
				t += 3;
			}
		}
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
		for (int i = 0; i < 10000000; i++);
		glutPostRedisplay();
	}
	if (f[2] == 1)
	{
		int t = n - N;;
		for (int i=0;i<N;i++)

		{
			for (int j=0;j<N;j++)
			{
				arr[i][j] = t;
				t ++;
			}t = t + N;
		}
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
		for (int i = 0; i < 10000000; i++);
		glutPostRedisplay();
	}
	if (f[3] == 1)
	{
		int t = N - 1;
		for (int j = 0; j < N; j++)
		{
			for (int i = 0; i < N; i++)
			{
				arr[i][j] = t;
				t += 3;
			}
		}
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
		for (int i = 0; i < 10000000; i++);
		glutPostRedisplay();
	}
	if (f[4] == 1)
	{
		int t = n - N;;
		for (int i = 0; i < N; i++)

		{
			for (int j = 0; j < N; j++)
			{
				arr[i][j] = t;
				t++;
			}t = t + N;
		}
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
		for (int i = 0; i < 10000000; i++);
		glutPostRedisplay();
	}
	if (f[5] == 1)
	{	
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				arr[i][j] = i + j;
			}
		}
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
		for (int i = 0; i < 10000000; i++);
		glutPostRedisplay();
	}
	if (f[6] == 1)
	{
		int t = 0;
		for (int i = N; i > 0; i--)

		{
			for (int j = 0; j < N; j++)
			{
				arr[i][j] = t;
				t++;
			}t = t + n - N + 1;;
		}
		if (theta < 90)
		{
			rotaxis(arr, 'a', 'y');
		}
		else
		{
			f[6] = 0;
			theta = 0;
			pointswap(arr, 'c');
		}
		for (int i = 0; i < 10000000; i++);
		glutPostRedisplay();
	}
	if (f[7] == 1)
	{
		int t = 0;
		for (int j = N; j > 0; j--)

		{
			for (int i = 0; i < N; i++)
			{
				arr[i][j] = t;
				t += 3;
			}
		}
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
		for (int i = 0; i < 10000000; i++);
		glutPostRedisplay();

	}
	if (f[8] == 1)  //TOP'
	{
		int t =0;
		for (int i = N; i>0; i--)

		{
			for (int j = 0; j < N; j++)
			{
				arr[i][j] = t;
				t++;
			}t = t + n - N + 1;;
		}
		if (theta < 90)
		{
			rotaxis(arr, 'c', 'y');
		}
		else
		{
			f[8] = 0;
			theta = 0;
			pointswap(arr, 'a');
		}
		for (int i = 0; i < 10000000; i++);
		glutPostRedisplay();
	}
	if (f[9] == 1)
	{
		int t = N - 1;
		for (int j = 0; j<N ;j++)
		{
			for (int i = 0; i < N; i++)
			{
				arr[i][j] = t;
				t += 3;
			}
		}
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
		for (int i = 0; i < 10000000; i++);
		glutPostRedisplay();
	}
	if (f[0] == 1) //face-C
	{

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				arr[i][j] = i + j;
			}
		}
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
		for (int i = 0; i < 10000000; i++);
		glutPostRedisplay();
	}
}
void buildcube()
{
	for (int i = 0; i < n; i++)
		drawcube(v[i][0], v[i][1], v[i][2], v[i][3], v[i][4], v[i][5], v[i][6], v[i][7]);
}
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
	printf("Enter the N value for NxN rubik cube:\t");
	scanf_s("%d", &N);
	int n = N * N*N;
	
	v = (float ***)malloc(sizeof(float ***)*n);

	for (int i = 0; i < n; i++)
	{
		v[i] = (float **)malloc(sizeof(float*)*n);
	 	for (int j = 0; j < 8; j++)
		{
			v[i][j] = (float *)malloc(sizeof(float)*3);
	
		}
	
	}
	p = (int *)malloc(sizeof(int *)*n);
	for (int i = 0; i < n; i++)
		p[i] = i;

	
	makepoints();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutSpecialFunc(specialKeys);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	

	return 0;
}