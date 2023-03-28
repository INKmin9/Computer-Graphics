#include <gl/glut.h>

//���� �迭
/*
GLfloat MyVertices[8][3] = {
        { -0.25, -0.25, 0.25 },
    { -0.25, 0.25, 0.25 },
    { 0.25, 0.25, 0.25 },
    { 0.25, -0.25, 0.25 },
    { -0.25, -0.25, -0.25 },
    { -0.25, 0.25, -0.25 },
    { 0.25, 0.25, -0.25 },
    { 0.25, -0.25, -0.25 }
};
GLfloat MyColors[8][3] = {
    { 0.2, 0.2, 0.2 },
    { 1.0, 0.0, 0.0 },
    { 1.0, 1.0, 0.0 },
    { 0.0, 1.0, 0.0 },
    { 0.0, 0.0, 1.0 },
    { 1.0, 0.0, 1.0 },
    { 1.0, 1.0, 1.0 },
    { 0.0, 1.0, 1.0 }

};
GLubyte MyVertexList[24] = {
    0, 3, 2, 1, 2, 3, 7, 6, 0, 4, 7, 3, 1, 2, 6, 5, 4, 5, 6, 7, 0, 1, 5, 4
};//�ش� ������ �� �ִ� ���� �ε���

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, MyColors);
    glVertexPointer(3, GL_FLOAT, 0, MyVertices);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(30.0, 1.0, 1.0, 1.0);
    for (GLint i = 0; i < 6; i++) {
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);
    }//�鿡 ���� �� ����
    glFlush();
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL Drawing Example");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    //���� ��Ŀ� ���� ����� ���Ѵ�, viewport���� �� �Ͼ �� �ִ� �ְ������� ���µ� ��밡��
    glutDisplayFunc(MyDisplay);
    glutMainLoop();
    return 0;
}
*/

//���÷��� ����Ʈ

int MyListID;

void MyCreateList() {
    MyListID = glGenLists(1);
    glNewList(MyListID, GL_COMPILE);
    //�������� �ʰ� ������ �Ϸ�� ������ �����, ���� �Ҹ��ٸ� ���� �迭���ٴ� ����Ʈ������ ȿ����
    glBegin(GL_POLYGON);
        glColor3f(0.5, 0.5, 0.5);
        glVertex3f(-0.5, -0.5, 0.0);
        glVertex3f(0.5, -0.5, 0.0);
        glVertex3f(0.5, 0.5, 0.0);
        glVertex3f(-0.5, 0.5, 0.0);//glNewList, glEndList���ο� ����
        glEnd();
        glEndList();
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, 300, 300);
    glCallList(MyListID);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("OpenGL Example Drawing");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glutDisplayFunc(MyDisplay);
    MyCreateList();
    glutMainLoop();
    return 0;
}
