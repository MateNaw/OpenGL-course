#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <math.h>
#include <cstdlib>

typedef float point3[3];

static int xMousePosition = 0;
static int delta_x = 0;
static int yMousePosition = 0;
static int delta_y = 0;
static int status = 0;
static GLfloat thetaU = 1.0;
static GLfloat thetaV = 1.0;
static GLfloat xAngleInPixels;
static GLfloat yAngleInPixels;
static GLfloat R = 15.0;
static GLfloat R_current = 0.0;
static GLfloat delta_R = 0.0;
float aspectRatio;
const int N = 20;
float var = 1.0f / N;
float Pi = 3.14f;
static GLfloat viever[] = { 0.0, 0.0, 15.0 };

struct eggPoints {
	float x;
	float y;
	float z;
	float xColor;
	float yColor;
	float zColor;
};

eggPoints TableOfPoint[N][N];

void Axes(void)
{

	point3  x_min = { -5.0, 0.0, 0.0 };
	point3  x_max = { 5.0, 0.0, 0.0 };
	// pocz?tek i koniec obrazu osi x

	point3  y_min = { 0.0, -5.0, 0.0 };
	point3  y_max = { 0.0,  5.0, 0.0 };
	// pocz?tek i koniec obrazu osi y

	point3  z_min = { 0.0, 0.0, -5.0 };
	point3  z_max = { 0.0, 0.0,  5.0 };
	//  pocz?tek i koniec obrazu osi y

	glColor3f(1.0f, 0.0f, 0.0f);  // kolor rysowania osi - czerwony
	glBegin(GL_LINES); // rysowanie osi x

	glVertex3fv(x_min);
	glVertex3fv(x_max);

	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);  // kolor rysowania - zielony
	glBegin(GL_LINES);  // rysowanie osi y

	glVertex3fv(y_min);
	glVertex3fv(y_max);

	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);  // kolor rysowania - niebieski
	glBegin(GL_LINES);			  // rysowanie osi z

	glVertex3fv(z_min);
	glVertex3fv(z_max);

	glEnd();

}

void MakeTableOfPoints() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			float u = i * var;
			float v = j * var;
			float hel = Pi * v;
			TableOfPoint[i][j].x = ((-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * pow(u, 2) - 45 * u) * cos(hel));
			TableOfPoint[i][j].y = (160 * pow(u, 4) - 320 * pow(u, 3) + 160 * pow(u, 2));
			TableOfPoint[i][j].z = ((-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * pow(u, 2) - 45 * u) * sin(hel));
			TableOfPoint[i][j].xColor = ((float)rand() / (RAND_MAX));
			TableOfPoint[i][j].yColor = ((float)rand() / (RAND_MAX));
			TableOfPoint[i][j].zColor = ((float)rand() / (RAND_MAX));
		}
	}
}

void MouseButtonState(int btn, int state, int x, int y)
{

	// Zmiana stanu zmiennej okreslającej naciśnięcie guzika
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		// Aktualizacja pozycji kursora
		xMousePosition = x;
		yMousePosition = y;
		status = 1;
	}
	else if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		// Aktualizacja promienia
		R_current = y;
		status = 2;
	}
	else
		status = 0;
}

void DrawAsColors() {
	glBegin(GL_TRIANGLES);

	//musimy kolorowac raz jedna a potem drugą polowe aby jajko bylo pokolorowane tylko z zewnatrz
	for (int i = N / 2; i < N; i++) {
		int help = N - i;
		for (int j = 0; j < N - 1; j++) {
			// dla takiego i przekroczylibysmy zakres wiec musimy uzyc pierwszego elementu
			if (i == N - 1) {
				glColor3f(TableOfPoint[i][j].xColor, TableOfPoint[i][j].yColor, TableOfPoint[i][j].zColor);
				glVertex3f(TableOfPoint[i][j].x, TableOfPoint[i][j].y - 5, TableOfPoint[i][j].z);
				glColor3f(TableOfPoint[i][j + 1].xColor, TableOfPoint[i][j + 1].yColor, TableOfPoint[i][j + 1].zColor);
				glVertex3f(TableOfPoint[i][j + 1].x, TableOfPoint[i][j + 1].y - 5, TableOfPoint[i][j + 1].z);
				glColor3f(TableOfPoint[0][0].xColor, TableOfPoint[0][0].yColor, TableOfPoint[0][0].zColor);
				glVertex3f(TableOfPoint[0][0].x, TableOfPoint[0][0].y - 5, TableOfPoint[0][0].z);
			}
			//w przeciwnym wypadku kolorujemy normalnie
			else {
				glColor3f(TableOfPoint[i][j].xColor, TableOfPoint[i][j].yColor, TableOfPoint[i][j].zColor);
				glVertex3f(TableOfPoint[i][j].x, TableOfPoint[i][j].y - 5, TableOfPoint[i][j].z);
				glColor3f(TableOfPoint[i + 1][j].xColor, TableOfPoint[i + 1][j].yColor, TableOfPoint[i + 1][j].zColor);
				glVertex3f(TableOfPoint[i + 1][j].x, TableOfPoint[i + 1][j].y - 5, TableOfPoint[i + 1][j].z);
				glColor3f(TableOfPoint[i + 1][j + 1].xColor, TableOfPoint[i + 1][j + 1].yColor, TableOfPoint[i + 1][j + 1].zColor);
				glVertex3f(TableOfPoint[i + 1][j + 1].x, TableOfPoint[i + 1][j + 1].y - 5, TableOfPoint[i + 1][j + 1].z);

				glColor3f(TableOfPoint[i][j].xColor, TableOfPoint[i][j].yColor, TableOfPoint[i][j].zColor);
				glVertex3f(TableOfPoint[i][j].x, TableOfPoint[i][j].y - 5, TableOfPoint[i][j].z);
				glColor3f(TableOfPoint[i][j + 1].xColor, TableOfPoint[i][j + 1].yColor, TableOfPoint[i][j + 1].zColor);
				glVertex3f(TableOfPoint[i][j + 1].x, TableOfPoint[i][j + 1].y - 5, TableOfPoint[i][j + 1].z);
				glColor3f(TableOfPoint[i + 1][j + 1].xColor, TableOfPoint[i + 1][j + 1].yColor, TableOfPoint[i + 1][j + 1].zColor);
				glVertex3f(TableOfPoint[i + 1][j + 1].x, TableOfPoint[i + 1][j + 1].y - 5, TableOfPoint[i + 1][j + 1].z);
			}
			if (help != N) {
				glColor3f(TableOfPoint[i][0].xColor, TableOfPoint[i][0].yColor, TableOfPoint[i][0].zColor);
				glVertex3f(TableOfPoint[i][0].x, TableOfPoint[i][0].y - 5, TableOfPoint[i][0].z);
				glColor3f(TableOfPoint[help][N - 1].xColor, TableOfPoint[help][N - 1].yColor, TableOfPoint[help][N - 1].zColor);
				glVertex3f(TableOfPoint[help][N - 1].x, TableOfPoint[help][N - 1].y - 5, TableOfPoint[help][N - 1].z);
				glColor3f(TableOfPoint[help + 1][N - 1].xColor, TableOfPoint[help + 1][N - 1].yColor, TableOfPoint[help + 1][N - 1].zColor);
				glVertex3f(TableOfPoint[help + 1][N - 1].x, TableOfPoint[help + 1][N - 1].y - 5, TableOfPoint[help + 1][N - 1].z);

				if (i != N / 2) {
					glColor3f(TableOfPoint[i][0].xColor, TableOfPoint[i][0].yColor, TableOfPoint[i][0].zColor);
					glVertex3f(TableOfPoint[i][0].x, TableOfPoint[i][0].y - 5, TableOfPoint[i][0].z);
					glColor3f(TableOfPoint[i - 1][0].xColor, TableOfPoint[i - 1][0].yColor, TableOfPoint[i - 1][0].zColor);
					glVertex3f(TableOfPoint[i - 1][0].x, TableOfPoint[i - 1][0].y - 5, TableOfPoint[i - 1][0].z);
					glColor3f(TableOfPoint[help + 1][N - 1].xColor, TableOfPoint[help + 1][N - 1].yColor, TableOfPoint[help + 1][N - 1].zColor);
					glVertex3f(TableOfPoint[help + 1][N - 1].x, TableOfPoint[help + 1][N - 1].y - 5, TableOfPoint[help + 1][N - 1].z);
				}
			}
		}
	}
	glColor3f(TableOfPoint[0][0].xColor, TableOfPoint[0][0].yColor, TableOfPoint[0][0].zColor);
	glVertex3f(TableOfPoint[0][0].x, TableOfPoint[0][0].y - 5, TableOfPoint[0][0].z);
	glColor3f(TableOfPoint[N - 1][0].xColor, TableOfPoint[N - 1][0].yColor, TableOfPoint[N - 1][0].zColor);
	glVertex3f(TableOfPoint[N - 1][0].x, TableOfPoint[N - 1][0].y - 5, TableOfPoint[N - 1][0].z);
	glColor3f(TableOfPoint[1][N - 1].xColor, TableOfPoint[1][N - 1].yColor, TableOfPoint[1][N - 1].zColor);
	glVertex3f(TableOfPoint[1][N - 1].x, TableOfPoint[1][N - 1].y - 5, TableOfPoint[1][N - 1].z);

	glColor3f(TableOfPoint[0][0].xColor, TableOfPoint[0][0].yColor, TableOfPoint[0][0].zColor);
	glVertex3f(TableOfPoint[0][0].x, TableOfPoint[0][0].y - 5, TableOfPoint[0][0].z);
	glColor3f(TableOfPoint[1][0].xColor, TableOfPoint[1][0].yColor, TableOfPoint[1][0].zColor);
	glVertex3f(TableOfPoint[1][0].x, TableOfPoint[1][0].y - 5, TableOfPoint[1][0].z);
	glColor3f(TableOfPoint[N - 1][N - 1].xColor, TableOfPoint[N - 1][N - 1].yColor, TableOfPoint[N - 1][N - 1].zColor);
	glVertex3f(TableOfPoint[N - 1][N - 1].x, TableOfPoint[N - 1][N - 1].y - 5, TableOfPoint[N - 1][N - 1].z);


	for (int i = 0; i < N / 2 + 1; i++) {
		int pom = N - i;
		for (int j = 0; j < N - 1; j++) {
			if (i == 1) {
				glColor3f(TableOfPoint[i][j].xColor, TableOfPoint[i][j].yColor, TableOfPoint[i][j].zColor);
				glVertex3f(TableOfPoint[i][j].x, TableOfPoint[i][j].y - 5, TableOfPoint[i][j].z);
				glColor3f(TableOfPoint[i][j + 1].xColor, TableOfPoint[i][j + 1].yColor, TableOfPoint[i][j + 1].zColor);
				glVertex3f(TableOfPoint[i][j + 1].x, TableOfPoint[i][j + 1].y - 5, TableOfPoint[i][j + 1].z);
				glColor3f(TableOfPoint[0][0].xColor, TableOfPoint[0][0].yColor, TableOfPoint[0][0].zColor);
				glVertex3f(TableOfPoint[0][0].x, TableOfPoint[0][0].y - 5, TableOfPoint[0][0].z);
			}
			else {
				if (i != 0) {
					glColor3f(TableOfPoint[i][j].xColor, TableOfPoint[i][j].yColor, TableOfPoint[i][j].zColor);
					glVertex3f(TableOfPoint[i][j].x, TableOfPoint[i][j].y - 5, TableOfPoint[i][j].z);
					glColor3f(TableOfPoint[i - 1][j].xColor, TableOfPoint[i - 1][j].yColor, TableOfPoint[i - 1][j].zColor);
					glVertex3f(TableOfPoint[i - 1][j].x, TableOfPoint[i - 1][j].y - 5, TableOfPoint[i - 1][j].z);
					glColor3f(TableOfPoint[i - 1][j + 1].xColor, TableOfPoint[i - 1][j + 1].yColor, TableOfPoint[i - 1][j + 1].zColor);
					glVertex3f(TableOfPoint[i - 1][j + 1].x, TableOfPoint[i - 1][j + 1].y - 5, TableOfPoint[i - 1][j + 1].z);
				}

				glColor3f(TableOfPoint[i][j].xColor, TableOfPoint[i][j].yColor, TableOfPoint[i][j].zColor);
				glVertex3f(TableOfPoint[i][j].x, TableOfPoint[i][j].y - 5, TableOfPoint[i][j].z);
				glColor3f(TableOfPoint[i][j + 1].xColor, TableOfPoint[i][j + 1].yColor, TableOfPoint[i][j + 1].zColor);
				glVertex3f(TableOfPoint[i][j + 1].x, TableOfPoint[i][j + 1].y - 5, TableOfPoint[i][j + 1].z);
				glColor3f(TableOfPoint[i - 1][j + 1].xColor, TableOfPoint[i - 1][j + 1].yColor, TableOfPoint[i - 1][j + 1].zColor);
				glVertex3f(TableOfPoint[i - 1][j + 1].x, TableOfPoint[i - 1][j + 1].y - 5, TableOfPoint[i - 1][j + 1].z);
			}
			if (pom != N) {
				glColor3f(TableOfPoint[i][0].xColor, TableOfPoint[i][0].yColor, TableOfPoint[i][0].zColor);
				glVertex3f(TableOfPoint[i][0].x, TableOfPoint[i][0].y - 5, TableOfPoint[i][0].z);
				glColor3f(TableOfPoint[pom][N - 1].xColor, TableOfPoint[pom][N - 1].yColor, TableOfPoint[pom][N - 1].zColor);
				glVertex3f(TableOfPoint[pom][N - 1].x, TableOfPoint[pom][N - 1].y - 5, TableOfPoint[pom][N - 1].z);
				glColor3f(TableOfPoint[pom - 1][N - 1].xColor, TableOfPoint[pom - 1][N - 1].yColor, TableOfPoint[pom - 1][N - 1].zColor);
				glVertex3f(TableOfPoint[pom - 1][N - 1].x, TableOfPoint[pom - 1][N - 1].y - 5, TableOfPoint[pom - 1][N - 1].z);

				glColor3f(TableOfPoint[i][0].xColor, TableOfPoint[i][0].yColor, TableOfPoint[i][0].zColor);
				glVertex3f(TableOfPoint[i][0].x, TableOfPoint[i][0].y - 5, TableOfPoint[i][0].z);
				glColor3f(TableOfPoint[i + 1][0].xColor, TableOfPoint[i + 1][0].yColor, TableOfPoint[i + 1][0].zColor);
				glVertex3f(TableOfPoint[i + 1][0].x, TableOfPoint[i + 1][0].y - 5, TableOfPoint[i + 1][0].z);
				glColor3f(TableOfPoint[pom - 1][N - 1].xColor, TableOfPoint[pom - 1][N - 1].yColor, TableOfPoint[pom - 1][N - 1].zColor);
				glVertex3f(TableOfPoint[pom - 1][N - 1].x, TableOfPoint[pom - 1][N - 1].y - 5, TableOfPoint[pom - 1][N - 1].z);
			}
		}
	}
	glEnd();
}

void MousePosition(GLsizei x, GLsizei y)
{

	// Obliczenie różnicy w pozycji myszy
	delta_x = x - xMousePosition;
	delta_y = y - yMousePosition;
	delta_R = y - R_current;

	// Zapisanie aktualnej pozycji myszy
	xMousePosition = x;
	yMousePosition = y;
	R_current = y;

	// Odświeżenie widoku
	glutPostRedisplay();
}

void RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszczącym

	glLoadIdentity();
	// Czyszczenie macierzy bie??cej

	Axes();
	// Narysowanie osi przy pomocy funkcji zdefiniowanej powyżej 

	  // Zmiana stanu zmiennej okreslającej naciśnięcie guzika
	if (status == 1)
	{
		// Aktualizacja parametrów kątowych
		thetaU += delta_x * xAngleInPixels * 0.1;
		thetaV += delta_y * yAngleInPixels * 0.1;
	}
	if (status == 2)
	{
		// Aktualizacja promienia
		R += delta_R * yAngleInPixels;
	}

	// Zmiana pozycji obserwatora zgodnie z równaniami
	viever[0] = R * cos(thetaU) * cos(thetaV);
	viever[1] = R * sin(thetaV);
	viever[2] = R * sin(thetaU) * cos(thetaV);
	gluLookAt(viever[0], viever[1], viever[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);


	DrawAsColors();
	// Narysowanie czajnika 

	glFlush();
	// Przekazanie poleceń rysujących do wykonania

	glutSwapBuffers();



}

void MyInit(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Kolor czyszczący (wypełnienia okna) ustawiono na czarny
}

void ChangeSize(GLsizei horizontal, GLsizei vertical)
{
	// Przeliczenie zmiany ilości pikseli w ruchu myszy na stopnie
	xAngleInPixels = 360.0 / (float)horizontal;
	yAngleInPixels = 360.0 / (float)vertical;

	// Przejście w tryb projekcji
	glMatrixMode(GL_PROJECTION);

	// Czyszczenie macierzy bieżącej
	glLoadIdentity();

	aspectRatio = (GLfloat)horizontal / (GLfloat)vertical;

	// Ustawienie parametrów dla rzutu perspektywicznego
	gluPerspective(70, aspectRatio, 1.0, 30.0);

	// Ustawienie okna widoku w zalezności od stostunku x i y okna
	if (horizontal <= vertical)
	{
		glViewport(0, (vertical - horizontal) / 2, horizontal, horizontal);
	}
	else
	{
		glViewport((horizontal - vertical) / 2, 0, vertical, vertical);
	}

	// Powrót do trybu modelu
	glMatrixMode(GL_MODELVIEW);

	// Czyszczenie macierzy bieżącej
	glLoadIdentity();

}

int main(int argc, char** argv)
{
	MakeTableOfPoints();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	MyInit();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutMouseFunc(MouseButtonState);
	glutMotionFunc(MousePosition);
	// Ustala funkcję zwrotną odpowiedzialną za badanie ruchu myszy
	glutMainLoop();
	return 0;
}
