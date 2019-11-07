#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <time.h>
#include <GL/glut.h>

static float rotx = 0;
static float worldX = 15;
static float worldY = 0;
static float scaleFactor = 0.6;
static bool mover = false;
static float primeiro = 1;
static float segundo = 1;

extern int globalW, globalH;

struct ponto
{
	float x;
	float y;
	float z;
};



bool one = false;
int globalW, globalH;
ponto estrelas[500];

using namespace std;

void texto(const char *str, float size)
{
	glPushMatrix();
	glScalef(size, size, size);

	for (unsigned int i = 0; i<strlen(str); i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	glPopMatrix();
}

void cordenadasAleatorias(ponto *estrelas)
{
	int menor = -1000, maior = 1000;
	int range = (maior - menor) + 1;
	estrelas->x = menor + int(range*rand() / (RAND_MAX + 1.0));
	estrelas->y = menor + int(range*rand() / (RAND_MAX + 1.0));
	estrelas->z = menor + int(range*rand() / (RAND_MAX + 1.0));
}

void DesenharEstrelas()
{
	GLUquadricObj *quadric;
	quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluDeleteQuadric(quadric);
	for ( int i = 0; i < 500; i ++ ) {
		glPushMatrix();
		glTranslatef(estrelas[i].x, estrelas[i].y, estrelas[i].z);
		glColor3f(1, 1, 1);
		gluSphere(quadric, 1, 36, 18);
		glPopMatrix();
	}
}

void sai(int valor)	{
	switch(valor) {
		case 27:
			exit(0);
			break;
		default:
			break;
	}
}

void menu()
{
	int menu1, menu2, menu3, menu4;

    menu1 = glutCreateMenu(sai);
	glutAddMenuEntry("1427652", 0);

    menu2 = glutCreateMenu(sai);
    glutAddMenuEntry("1489160", 0);

	menu3 = glutCreateMenu(sai);
	glutAddMenuEntry("1820850", 0);

    menu4 = glutCreateMenu(sai);
    glutAddSubMenu("Renan",menu1);
    glutAddSubMenu("Andressa",menu2);
	glutAddSubMenu("Helyederson", menu3);
	glutAddMenuEntry("Sair", 27);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void Luz()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	glRotatef(worldX, 1, 0, 0);
	glRotatef(worldY, 0, 1, 0);

	glDisable(GL_LIGHTING);
}

void Desenhar()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0, 0, -100);

	if (!mover) { //texto
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glColor3f(1, 1, 1);
		glTranslatef(-18, 50, 0.0);
		texto("Mini Sistema Solar", 0.03f);
		glPopMatrix();
	}

	Luz();

	GLUquadricObj *quadric;
	quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluDeleteQuadric(quadric);
	glScalef(scaleFactor, scaleFactor, scaleFactor);

	glPushMatrix();

	glColor3f(0.8, 0.5, 0.2);
	gluSphere(quadric, 15, 36, 18);
	glColor3f(1, 1, 0);
	glEnable(GL_BLEND);
	glBlendFunc(primeiro, segundo);
	gluSphere(quadric, 20, 36, 18);//sol
	glDisable(GL_BLEND);
	glPopMatrix();

	glEnable(GL_LIGHTING);
	GLfloat light_position[] = { 0.0, 0.0, 0.0,1 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	GLfloat light_diff[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diff);
	GLfloat light_amb[] = { 0.0, 0.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb);

	glPushMatrix(); //marte
	glRotatef(rotx, 0, 1, 0);
	glTranslatef(40, 0, -10.0);
	glRotatef(rotx, 1, 0, 0);
	glColor3f(1, 0, 0);
	gluSphere(quadric, 5, 36, 18);
	glPopMatrix();

	glPushMatrix();//plutão
	glRotatef(rotx, 0, 1, 0);
	glTranslatef(-20, 0.0, -70);
	glRotatef(rotx, 0, 0, 1);
	glColor3f(0, 1, 0);
	gluSphere(quadric, 10, 36, 18);
	glPopMatrix();

	glPushMatrix();//saturno
	glRotatef(rotx, 0, 1, 0);
	glTranslatef(-60, 0, 0.0);
	glRotatef(rotx, 1, 0, 0);
	glColor3f(0, 0, 1);
	gluSphere(quadric, 17, 36, 18);

	glEnable(GL_BLEND); //anel
	glColor4f(0.3, 0.3, 0.4, 0.9);
	gluCylinder(quadric , 18, 30, 1, 40, 10);

	glDisable(GL_BLEND);
	glPopMatrix();

	glPushMatrix();//terra
	glRotatef(rotx, 0, 1, 0);
	glTranslatef(40, 0, 44.0);
	glRotatef(rotx, 1, 0, 0);
	glColor3f(0, 1, 1);
	gluSphere(quadric, 11, 36, 18);

	glRotatef(rotx, 0, 1, 0); //lua
	glTranslatef(15, 0, 15.0);
	glRotatef(rotx, 1, 0, 0);
	glColor3f(1, 1, 1);
	gluSphere(quadric, 2, 36, 18);

	glPopMatrix();

	DesenharEstrelas();

	glutSwapBuffers();
}

void Resize(int w, int h)
{
	if (h == 0) h = 1;
	glViewport(0, 0, w, h);
	globalH = h;
	globalW = w;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, (float)w / (float)h, 1.0, 1000.0);
}

void Idle()
{
	if (mover)
		rotx += 1.1;

	glutPostRedisplay();
}

void teclado(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w': if (mover) worldX -= 1.0f;
		break;
	case 's': if (mover) worldX += 1.0f;
		break;
	case 'a': if (mover) worldY -= 1.0f;
		break;
	case 'd': if (mover)  worldY += 1.0f;
		break;
	case ' ': mover = !mover;;
		break;
    default: break;
	}
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	if (button == 3) {
		if (scaleFactor <= 2) {
			scaleFactor += 0.01;
			glutPostRedisplay();
		}
    }
	if (button == 4) {
        if (scaleFactor > 0.08) {
            scaleFactor -= 0.01;
            glutPostRedisplay();
        }
    }
    glutPostRedisplay();
}

void Inicializa()
{
	for (int i = 0; i < 500; i++) //coordenada para estrelas
		cordenadasAleatorias(&estrelas[i]);
	srand(time(0));

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Mini Sistema Solar");
	Inicializa();
	glutDisplayFunc(Desenhar);
	glutReshapeFunc(Resize);
	glutIdleFunc(Idle);
	glutKeyboardFunc(teclado);
    glutMouseFunc(mouse);
    menu();
	glClearColor(0.0,0.0,0.0,0.0);

	glutMainLoop();
	return 0;
}
