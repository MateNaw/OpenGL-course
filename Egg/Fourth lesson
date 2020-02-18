#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <math.h>
#include <cstdlib>

typedef float point3[3];

//stare pozycje kursora
static int xMousePosition = 0;
static int yMousePosition = 0;

// delta kursora
static int delta_x = 0;
static int delta_y = 0;

//status guzika
static int status = 0;
static GLfloat fi[2] = { 5.76f, 1.05f };
static GLfloat theta[2] = { 4.68f, 4.68f };
static GLfloat xAngleInPixels;
static GLfloat yAngleInPixels;
float aspectRatio;
float Pi = 3.1415926535897932f;
const int N = 40;
float var = 1.0f / N;
float lightRadius = 10.0;
struct eggPoints {
	float x;
	float y;
	float z;
	float normal_x;
	float normal_y;
	float normal_z;
};
eggPoints TableOfPoint[N][N];

//funkcje liczace skladowe wektora znormalizowanego
float get_Xu(float u, float v) {
	float wynik;
	wynik = (-450 * pow(u, 4) + 900 * pow(u, 3) - 810 * pow(u, 2) + 360 * u - 45) * cos(Pi * v);
	return wynik;
}

float get_Xv(float u, float v) {
	float wynik;
	wynik = Pi * (90 * pow(u, 5) - 225 * pow(u, 4) + 270 * pow(u, 3) - 180 * pow(u, 2) + 45 * u) * sin(Pi * v);
	return wynik;
}

float get_Yu(float u, float v) {
	float wynik;
	wynik = 640 * pow(u, 3) - 960 * pow(u, 2) + 320 * u;
	return wynik;
}

float get_Yv() {
	return 0;
}

float get_Zu(float u, float v) {
	float wynik;
	wynik = (-450 * pow(u, 4) + 900 * pow(u, 3) - 810 * pow(u, 2) + 360 * u - 45) * sin(Pi * v);
	return wynik;
}

float get_Zv(float u, float v) {
	float wynik;
	wynik = -1 * Pi * (90 * pow(u, 5) - 225 * pow(u, 4) + 270 * pow(u, 3) - 180 * pow(u, 2) + 45 * u) * cos(Pi * v);
	return wynik;
}

//funkcja robiaca tabele punktow
void MakeTableOfPoints() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			float u = i * var;
			float v = j * var;
			float hel = Pi * v;
			float dlugosc_wektora;
			TableOfPoint[i][j].x = ((-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * pow(u, 2) - 45 * u) * cos(hel));
			TableOfPoint[i][j].y = (160 * pow(u, 4) - 320 * pow(u, 3) + 160 * pow(u, 2));
			TableOfPoint[i][j].z = ((-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * pow(u, 2) - 45 * u) * sin(hel));
			TableOfPoint[i][j].normal_x = get_Yu(u, v) * get_Zv(u, v) - get_Zu(u, v) * get_Yv();
			TableOfPoint[i][j].normal_y = get_Zu(u, v) * get_Xv(u, v) - get_Xu(u, v) * get_Zv(u, v);
			TableOfPoint[i][j].normal_z = get_Xu(u, v) * get_Yv() - get_Yu(u, v) * get_Xv(u, v);
			dlugosc_wektora = sqrt(pow(TableOfPoint[i][j].normal_x, 2) + pow(TableOfPoint[i][j].normal_y, 2) + pow(TableOfPoint[i][j].normal_z, 2));
			TableOfPoint[i][j].normal_x /= dlugosc_wektora;
			TableOfPoint[i][j].normal_y /= dlugosc_wektora;
			TableOfPoint[i][j].normal_z /= dlugosc_wektora;
		}
	}
}

//funkcja rysujaca jajko
void DrawAsColors() {
	glBegin(GL_TRIANGLES);

	//musimy kolorowac raz jedna a potem drugą polowe aby jajko bylo pokolorowane tylko z zewnatrz
	for (int i = N / 2; i < N; i++) {
		int help = N - i;
		for (int j = 0; j < N - 1; j++) {
			// dla takiego i przekroczylibysmy zakres wiec musimy uzyc pierwszego elementu
			if (i == N - 1) {
				glNormal3f(-1 * TableOfPoint[i][j].normal_x, -1 * TableOfPoint[i][j].normal_y, -1 * TableOfPoint[i][j].normal_z);
				glVertex3f(TableOfPoint[i][j].x, TableOfPoint[i][j].y - 5, TableOfPoint[i][j].z);
				glNormal3f(-1 * TableOfPoint[i][j + 1].normal_x, -1 * TableOfPoint[i][j + 1].normal_y, -1 * TableOfPoint[i][j + 1].normal_z);
				glVertex3f(TableOfPoint[i][j + 1].x, TableOfPoint[i][j + 1].y - 5, TableOfPoint[i][j + 1].z);
				glNormal3f(-1 * TableOfPoint[0][0].normal_x, -1 * TableOfPoint[0][0].normal_y, -1 * TableOfPoint[0][0].normal_z);
				glVertex3f(TableOfPoint[0][0].x, TableOfPoint[0][0].y - 5, TableOfPoint[0][0].z);
			}
			//w przeciwnym wypadku kolorujemy normalnie
			else {
				glNormal3f(-1 * TableOfPoint[i][j].normal_x, -1 * TableOfPoint[i][j].normal_y, -1 * TableOfPoint[i][j].normal_z);
				glVertex3f(TableOfPoint[i][j].x, TableOfPoint[i][j].y - 5, TableOfPoint[i][j].z);
				glNormal3f(-1 * TableOfPoint[i + 1][j].normal_x, -1 * TableOfPoint[i + 1][j].normal_y, -1 * TableOfPoint[i + 1][j].normal_z);
				glVertex3f(TableOfPoint[i + 1][j].x, TableOfPoint[i + 1][j].y - 5, TableOfPoint[i + 1][j].z);
				glNormal3f(-1 * TableOfPoint[i + 1][j + 1].normal_x, -1 * TableOfPoint[i + 1][j + 1].normal_y, -1 * TableOfPoint[i + 1][j + 1].normal_z);
				glVertex3f(TableOfPoint[i + 1][j + 1].x, TableOfPoint[i + 1][j + 1].y - 5, TableOfPoint[i + 1][j + 1].z);

				glNormal3f(-1 * TableOfPoint[i][j].normal_x, -1 * TableOfPoint[i][j].normal_y, -1 * TableOfPoint[i][j].normal_z);
				glVertex3f(TableOfPoint[i][j].x, TableOfPoint[i][j].y - 5, TableOfPoint[i][j].z);
				glNormal3f(-1 * TableOfPoint[i][j + 1].normal_x, -1 * TableOfPoint[i][j + 1].normal_y, -1 * TableOfPoint[i][j + 1].normal_z);
				glVertex3f(TableOfPoint[i][j + 1].x, TableOfPoint[i][j + 1].y - 5, TableOfPoint[i][j + 1].z);
				glNormal3f(-1 * TableOfPoint[i + 1][j + 1].normal_x, -1 * TableOfPoint[i + 1][j + 1].normal_y, -1 * TableOfPoint[i + 1][j + 1].normal_z);
				glVertex3f(TableOfPoint[i + 1][j + 1].x, TableOfPoint[i + 1][j + 1].y - 5, TableOfPoint[i + 1][j + 1].z);
			}
			if (help != N) {
				glNormal3f(-1 * TableOfPoint[i][0].normal_x, -1 * TableOfPoint[i][0].normal_y, -1 * TableOfPoint[i][0].normal_z);
				glVertex3f(TableOfPoint[i][0].x, TableOfPoint[i][0].y - 5, TableOfPoint[i][0].z);
				glNormal3f(TableOfPoint[help][N - 1].normal_x, TableOfPoint[help][N - 1].normal_y, TableOfPoint[help][N - 1].normal_z);
				glVertex3f(TableOfPoint[help][N - 1].x, TableOfPoint[help][N - 1].y - 5, TableOfPoint[help][N - 1].z);
				glNormal3f(TableOfPoint[help + 1][N - 1].normal_x, TableOfPoint[help + 1][N - 1].normal_y, TableOfPoint[help + 1][N - 1].normal_z);
				glVertex3f(TableOfPoint[help + 1][N - 1].x, TableOfPoint[help + 1][N - 1].y - 5, TableOfPoint[help + 1][N - 1].z);

				if (i != N / 2) {
					glNormal3f(-1 * TableOfPoint[i][0].normal_x, -1 * TableOfPoint[i][0].normal_y, -1 * TableOfPoint[i][0].normal_z);
					glVertex3f(TableOfPoint[i][0].x, TableOfPoint[i][0].y - 5, TableOfPoint[i][0].z);
					glNormal3f(-1 * TableOfPoint[i - 1][0].normal_x, -1 * TableOfPoint[i - 1][0].normal_y, -1 * TableOfPoint[i - 1][0].normal_z);
					glVertex3f(TableOfPoint[i - 1][0].x, TableOfPoint[i - 1][0].y - 5, TableOfPoint[i - 1][0].z);
					glNormal3f(TableOfPoint[help + 1][N - 1].normal_x, TableOfPoint[help + 1][N - 1].normal_y, TableOfPoint[help + 1][N - 1].normal_z);
					glVertex3f(TableOfPoint[help + 1][N - 1].x, TableOfPoint[help + 1][N - 1].y - 5, TableOfPoint[help + 1][N - 1].z);
				}
			}
		}
	}
	glNormal3f(-1 * TableOfPoint[0][0].normal_x, -1 * TableOfPoint[0][0].normal_y, -1 * TableOfPoint[0][0].normal_z);
	glVertex3f(TableOfPoint[0][0].x, TableOfPoint[0][0].y - 5, TableOfPoint[0][0].z);
	glNormal3f(-1 * TableOfPoint[N - 1][0].normal_x, -1 * TableOfPoint[N - 1][0].normal_y, -1 * TableOfPoint[N - 1][0].normal_z);
	glVertex3f(TableOfPoint[N - 1][0].x, TableOfPoint[N - 1][0].y - 5, TableOfPoint[N - 1][0].z);
	glNormal3f(TableOfPoint[1][N - 1].normal_x, TableOfPoint[1][N - 1].normal_y, TableOfPoint[1][N - 1].normal_z);
	glVertex3f(TableOfPoint[1][N - 1].x, TableOfPoint[1][N - 1].y - 5, TableOfPoint[1][N - 1].z);


	glNormal3f(TableOfPoint[0][0].normal_x, TableOfPoint[0][0].normal_y, TableOfPoint[0][0].normal_z);
	glVertex3f(TableOfPoint[0][0].x, TableOfPoint[0][0].y - 5, TableOfPoint[0][0].z);
	glNormal3f(TableOfPoint[1][0].normal_x, TableOfPoint[1][0].normal_y, TableOfPoint[1][0].normal_z);
	glVertex3f(TableOfPoint[1][0].x, TableOfPoint[1][0].y - 5, TableOfPoint[1][0].z);
	glNormal3f(-1 * TableOfPoint[N - 1][N - 1].normal_x, -1 * TableOfPoint[N - 1][N - 1].normal_y, -1 * TableOfPoint[N - 1][N - 1].normal_z);
	glVertex3f(TableOfPoint[N - 1][N - 1].x, TableOfPoint[N - 1][N - 1].y - 5, TableOfPoint[N - 1][N - 1].z);





	for (int i = 0; i < N / 2 + 1; i++) {
		int pom = N - i;
		for (int j = 0; j < N - 1; j++) {
			if (i == 1) {
				glNormal3f(TableOfPoint[i][j].normal_x, TableOfPoint[i][j].normal_y, TableOfPoint[i][j].normal_z);
				glVertex3f(TableOfPoint[i][j].x, TableOfPoint[i][j].y - 5, TableOfPoint[i][j].z);
				glNormal3f(TableOfPoint[i][j + 1].normal_x, TableOfPoint[i][j + 1].normal_y, TableOfPoint[i][j + 1].normal_z);
				glVertex3f(TableOfPoint[i][j + 1].x, TableOfPoint[i][j + 1].y - 5, TableOfPoint[i][j + 1].z);
				glNormal3f(TableOfPoint[0][0].normal_x, TableOfPoint[0][0].normal_y, TableOfPoint[0][0].normal_z);
				glVertex3f(TableOfPoint[0][0].x, TableOfPoint[0][0].y - 5, TableOfPoint[0][0].z);
			}
			else {
				if (i != 0) {
					glNormal3f(TableOfPoint[i][j].normal_x, TableOfPoint[i][j].normal_y, TableOfPoint[i][j].normal_z);
					glVertex3f(TableOfPoint[i][j].x, TableOfPoint[i][j].y - 5, TableOfPoint[i][j].z);
					glNormal3f(TableOfPoint[i - 1][j].normal_x, TableOfPoint[i - 1][j].normal_y, TableOfPoint[i - 1][j].normal_z);
					glVertex3f(TableOfPoint[i - 1][j].x, TableOfPoint[i - 1][j].y - 5, TableOfPoint[i - 1][j].z);
					glNormal3f(TableOfPoint[i - 1][j + 1].normal_x, TableOfPoint[i - 1][j + 1].normal_y, TableOfPoint[i - 1][j + 1].normal_z);
					glVertex3f(TableOfPoint[i - 1][j + 1].x, TableOfPoint[i - 1][j + 1].y - 5, TableOfPoint[i - 1][j + 1].z);
				}
				glNormal3f(TableOfPoint[i][j].normal_x, TableOfPoint[i][j].normal_y, TableOfPoint[i][j].normal_z);
				glVertex3f(TableOfPoint[i][j].x, TableOfPoint[i][j].y - 5, TableOfPoint[i][j].z);
				glNormal3f(TableOfPoint[i][j + 1].normal_x, TableOfPoint[i][j + 1].normal_y, TableOfPoint[i][j + 1].normal_z);
				glVertex3f(TableOfPoint[i][j + 1].x, TableOfPoint[i][j + 1].y - 5, TableOfPoint[i][j + 1].z);
				glNormal3f(TableOfPoint[i - 1][j + 1].normal_x, TableOfPoint[i - 1][j + 1].normal_y, TableOfPoint[i - 1][j + 1].normal_z);
				glVertex3f(TableOfPoint[i - 1][j + 1].x, TableOfPoint[i - 1][j + 1].y - 5, TableOfPoint[i - 1][j + 1].z);
			}
			if (pom != N) {
				glNormal3f(TableOfPoint[i][0].normal_x, TableOfPoint[i][0].normal_y, TableOfPoint[i][0].normal_z);
				glVertex3f(TableOfPoint[i][0].x, TableOfPoint[i][0].y - 5, TableOfPoint[i][0].z);
				glNormal3f(-1 * TableOfPoint[pom][N - 1].normal_x, -1 * TableOfPoint[pom][N - 1].normal_y, -1 * TableOfPoint[pom][N - 1].normal_z);
				glVertex3f(TableOfPoint[pom][N - 1].x, TableOfPoint[pom][N - 1].y - 5, TableOfPoint[pom][N - 1].z);
				glNormal3f(-1 * TableOfPoint[pom - 1][N - 1].normal_x, -1 * TableOfPoint[pom - 1][N - 1].normal_y, -1 * TableOfPoint[pom - 1][N - 1].normal_z);
				glVertex3f(TableOfPoint[pom - 1][N - 1].x, TableOfPoint[pom - 1][N - 1].y - 5, TableOfPoint[pom - 1][N - 1].z);

				glNormal3f(TableOfPoint[i][0].normal_x, TableOfPoint[i][0].normal_y, TableOfPoint[i][0].normal_z);
				glVertex3f(TableOfPoint[i][0].x, TableOfPoint[i][0].y - 5, TableOfPoint[i][0].z);
				glNormal3f(TableOfPoint[i + 1][0].normal_x, TableOfPoint[i + 1][0].normal_y, TableOfPoint[i + 1][0].normal_z);
				glVertex3f(TableOfPoint[i + 1][0].x, TableOfPoint[i + 1][0].y - 5, TableOfPoint[i + 1][0].z);
				glNormal3f(-1 * TableOfPoint[pom - 1][N - 1].normal_x, -1 * TableOfPoint[pom - 1][N - 1].normal_y, -1 * TableOfPoint[pom - 1][N - 1].normal_z);
				glVertex3f(TableOfPoint[pom - 1][N - 1].x, TableOfPoint[pom - 1][N - 1].y - 5, TableOfPoint[pom - 1][N - 1].z);
			}
		}
	}
	glEnd();
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
		// Aktualizacja pozycji kursora
		xMousePosition = x;
		yMousePosition = y;
		status = 2;
	}
	else
		status = 0;
}

void MousePosition(GLsizei x, GLsizei y)
{
	// Obliczenie różnicy w pozycji myszy
	delta_x = x - xMousePosition;
	delta_y = y - yMousePosition;

	// Zapisanie aktualnej pozycji myszy
	xMousePosition = x;
	yMousePosition = y;

	// Odświeżenie widoku
	glutPostRedisplay();
}

void RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszczącym

	glLoadIdentity();
	// Czyszczenie macierzy bie??cej

	// Zmiana stanu zmiennej okreslającej naciśnięcie guzika
	if (status == 1)
	{
		// Zamiana wartości theta na przedział 0-2
		theta[0] -= delta_x * xAngleInPixels;
		if (theta[0] <= 0) theta[0] += 2 * Pi;
		if (theta[0] >= 2 * Pi) theta[0] -= 2 * Pi;
		// Zamiana wartości fi na przedział 0-2
		fi[0] -= delta_y * yAngleInPixels;
		if (fi[0] <= 0) fi[0] += 2 * Pi;
		if (fi[0] >= 2 * Pi) fi[0] -= 2 * Pi;
	}
	if (status == 2)
	{
		// Zamiana wartości theta na przedział 0-2
		theta[1] -= delta_x * xAngleInPixels;
		if (theta[1] <= 0) theta[1] += 2 * Pi;
		if (theta[1] >= 2 * Pi) theta[1] -= 2 * Pi;
		// Zamiana wartości fi na przedział 0-2
		fi[1] -= delta_y * yAngleInPixels;
		if (fi[1] <= 0) fi[1] += 2 * Pi;
		if (fi[1] >= 2 * Pi) fi[1] -= 2 * Pi;
	}

	gluLookAt(0.0, 0.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	GLfloat lightPosition[4] = { 0 };
	// Zmiana pozycji źródła pierwszego światła
	lightPosition[0] = lightRadius * cos(theta[0]) * cos(fi[0]);
	lightPosition[1] = lightRadius * sin(fi[0]);
	lightPosition[2] = lightRadius * sin(theta[0]) * cos(fi[0]);
	lightPosition[3] = 1.0;
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	// Zmiana pozycji źródła drugiego światła
	lightPosition[0] = lightRadius * cos(theta[1]) * cos(fi[1]);
	lightPosition[1] = lightRadius * sin(fi[1]);
	lightPosition[2] = lightRadius * sin(theta[1]) * cos(fi[1]);
	lightPosition[3] = 1.0;
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);

	//narysowanie jajka
	DrawAsColors();

	glFlush();
	// Przekazanie poleceń rysujących do wykonania

	glutSwapBuffers();



}

void MyInit(void)
{
	// Definicja koloru czyszczączego
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Definicja parametrów materiału
	GLfloat materialAmbient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat materialDiffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat materialSpecular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat materialShine = { 40.0 };
	// Definicja parametrów świateł
	GLfloat lightOnePosition[] = { -10.0, -10.0, -10.0, 1.0 };
	GLfloat lightTwoPosition[] = { -10.0, -10.0, -10.0, 1.0 };
	GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat lightOneDiffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat lightTwoDiffuse[] = { 0.0, 0.0, 1.0, 1.0 };
	GLfloat lightOneSpecular[] = { 0.6f, 0.6f, 0.0f, 0.6f };
	GLfloat lightTwoSpecular[] = { 0.6f, 0.6f, 0.6f, 0.6f };
	// Osłabienie świateł
	GLfloat attenuationConstant = { 1.0f };
	GLfloat attenuationLinear = { 0.001f };
	GLfloat attenuationQuadratic = { 0.001f };
	// Zastosowanie parametrów materiału
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

	glMaterialf(GL_FRONT, GL_SHININESS, materialShine);
	// Zastosowanie parametrów światła pierwszego
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightOneDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightOneSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightOnePosition);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, attenuationConstant);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, attenuationLinear);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, attenuationQuadratic);
	// Zastosowanie parametrów światła drugiego
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightTwoDiffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightTwoSpecular);
	glLightfv(GL_LIGHT1, GL_POSITION, lightTwoPosition);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, attenuationConstant);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, attenuationLinear);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, attenuationQuadratic);
	// Wygładzanie cieni
	glShadeModel(GL_SMOOTH);
	// Aktywacja świateł
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);
}

void ChangeSize(GLsizei horizontal, GLsizei vertical)
{
	// Przeliczenie zmiany ilości pikseli w ruchu myszy na stopnie
	xAngleInPixels = 360.0 * 0.0125 / (float)horizontal;
	yAngleInPixels = 360.0 * 0.0125/ (float)vertical;

	// Przejście w tryb projekcji
	glMatrixMode(GL_PROJECTION);

	// Czyszczenie macierzy bieżącej
	glLoadIdentity();

	aspectRatio = (GLfloat)horizontal / (GLfloat)vertical;

	// Ustawienie parametrów dla rzutu perspektywicznego
	gluPerspective(70, 1.0, 1.0, 30.0);

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
