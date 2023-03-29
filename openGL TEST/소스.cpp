#include <iostream>
#include "windows.h"
#include <time.h>
#include <math.h>
#include <gl\gl.h>
#include <GL/glut.h>

//Teapot

int screenWidth = 500;
int screenHeight = 500;

int    fx = 0, fy = 0, fz = 0;
float  sPI = 0.0, sTH = 0.0;//파이와 세타값
float  sside = 0, sdepth = -5;
float  sx = 0, sy = 0;
bool  MouseLeftEvent, MouseCenterEvent, MouseRightEvent;
int   coordinateX, coordinateY;

// Basic Lighting with Ambient, Diffuse, Specular Gl float commands and setting light position.
void myInit()
{
	glColor3f(1.0, 1.0, 1.0);
	glShadeModel(GL_FLAT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, 1.0, 1.0, 100.0);
	gluLookAt(0, 0, -10, 0, 0, 0, 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);

	GLfloat mat_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat mat_diffuse[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_specular[] = { 0.75, 0.75, 0.75, 0.75 };
	GLfloat mat_shininess[] = { 10.0 };
	GLfloat light_position[] = { 0.45, 0.45, -0.35, 0.25 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

}

void myReshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glOrtho(-2, 2, -2, 2, -2, 2);
}

void myKeyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27: //esc의 아스키코드값
		exit(-1);
	}
	glutPostRedisplay();
}

//Display Screen
void myDisplay(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(sside, 0, -sdepth);
	glRotatef(-sTH, 1, 0, 0);
	glRotatef(sPI, 0, 1, 0);
	glTranslatef(sx, 0, -sy);


	glutSolidTeapot(3);
	glutSwapBuffers();
}

// Rotate on x, y, z axes according to cases.
int Theta_x = 0;
int Theta_y = 0;
int Theta_z = 0;

void menu(int value) {
	switch (value) {
	case 1:
		Theta_x = 90, Theta_y = 180, Theta_z = 0;

		break;
	case 2:
		Theta_x = 270, Theta_y = 180, Theta_z = 0;

		break;
	case 3:
		Theta_x = 0, Theta_y = 180, Theta_z = 0;

		break;
	case 4:
		Theta_x = 0, Theta_y = 0, Theta_z = 0;

		break;
	}
	glutPostRedisplay();
}

//Creating menu and submenus.
void menuFunctions(void) {

	int view = glutCreateMenu(menu);
	glutAddMenuEntry("Top", 1);
	glutAddMenuEntry("Bottom", 2);
	glutAddMenuEntry("Right", 3);
	glutAddMenuEntry("Left", 4);

	glutCreateMenu(menu);

	glutAddSubMenu("View", view);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Display View From Menu
void myDisplayWin2(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(Theta_x, 1, 0, 0);
	glRotatef(Theta_y, 0, 1, 0);
	glRotatef(Theta_z, 0, 0, 1);

	glEnable(GL_COLOR_MATERIAL);

	glColor3f(1.0, 1.0, 1.0);

	glutWireTeapot(2);
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

void myInitWin2()
{
	glColor3f(1.0, 1.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, 1.0, 1.0, 100.0);
	gluLookAt(0, 0, -10, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glShadeModel(GL_SMOOTH);
}

void myReshapeWin2(int width, int height)
{
	glViewport(0, 0, width, height);
	glOrtho(-1, 1, -1, 1, -1, 1);
}
/*
 * When there is a mouse event, we use myMouse()
 */
void myMouse(int button, int state, int x, int y)
{
	coordinateX = x; coordinateY = y;
	MouseLeftEvent = ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN));
	MouseCenterEvent = ((button == GLUT_MIDDLE_BUTTON) &&
		(state == GLUT_DOWN));
	MouseRightEvent = ((button == GLUT_RIGHT_BUTTON) &&
		(state == GLUT_DOWN));
	glutPostRedisplay();
}
/*
 *When we moved the mouse in window 1, we use myMouseMove();
 */
void myMouseMove(int x, int y) {

	// Rotating
	if (MouseLeftEvent)
	{
		sPI += (float)(x - coordinateX) / 4.0;
		sTH += (float)(coordinateY - y) / 4.0;

	}

	// Scaling
	if (MouseCenterEvent)
	{
		sPI += (float)(x - coordinateX) / 4.0;
		sTH += (float)(coordinateY - y) / 4.0;
	}

	// Scaling
	if (MouseRightEvent)
	{
		sPI += (float)(x - coordinateX) / 4.0;
		sTH += (float)(coordinateY - y) / 4.0;
	}
	coordinateX = x;
	coordinateY = y;
	glutPostRedisplay();
}

//Here there is my main codes.
int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(150, 150);//y좌표를 같게 해서 두 화면이 나란히 보이게 함
	glutCreateWindow("View From Menu");
	glutReshapeFunc(myReshapeWin2);
	glutDisplayFunc(myDisplayWin2);
	menuFunctions();

	myInitWin2();


	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(750, 150);
	glutCreateWindow("Rotating Teapot with Mouse1, Mouse2, Mouse3 Clicks.");
	glutKeyboardFunc(myKeyboard);
	glutReshapeFunc(myReshape);
	glutDisplayFunc(myDisplay);
	glutMouseFunc(myMouse);
	glutMotionFunc(myMouseMove);
	myInit();

	glutMainLoop();
}
