#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <cstdlib>
#include <ctime>

typedef float point2[2];

int drawSquares(point2 leftDown, point2 rightDown, int counter) {

	float side = rightDown[0] - leftDown[0];
	float newSideSize = side / 3;
	// jesli licznik rowna się 1 to znaczy ze jestesmy na najmniejszym mozliwym podziale wiec nie dielimy go juz
	if (counter == 1) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				point2 newLeftDown = { leftDown[0] + (newSideSize * i), leftDown[1] + (newSideSize * j) };
				point2 newLeftUp = { leftDown[0] + (newSideSize * i), leftDown[1] + newSideSize + (newSideSize * j) };
				point2 newRightUp = { leftDown[0] + newSideSize + (newSideSize * i), leftDown[1] + newSideSize + (newSideSize * j) };
				point2 newRightDown = { leftDown[0] + newSideSize + (newSideSize * i), leftDown[1] + (newSideSize * j) };

				//jesli obie z nich nie sa rowne 1 to znaczy ze nalezy pokolorowac
				if ((i != 1) || (j != 1)) {
					//kolorowanie kwadratu losowymi kolorami
					glBegin(GL_POLYGON);
					glColor3f(float(rand() % 1000) / 1000, float(rand() % 1000) / 1000, float(rand() % 1000) / 1000);
					glVertex2fv(newLeftDown);
					glColor3f(float(rand() % 1000) / 1000, float(rand() % 1000) / 1000, float(rand() % 1000) / 1000);
					glVertex2fv(newLeftUp);
					glColor3f(float(rand() % 1000) / 1000, float(rand() % 1000) / 1000, float(rand() % 1000) / 1000);
					glVertex2fv(newRightUp);
					glColor3f(float(rand() % 1000) / 1000, float(rand() % 1000) / 1000, float(rand() % 1000) / 1000);
					glVertex2fv(newRightDown);
					glEnd();
				}
				else {
					//srodkowy kwadrat musi pozostac czarny
					glBegin(GL_POLYGON);
					glColor3f(0.0f, 0.0f, 0.0f);
					glVertex2fv(newLeftDown);
					glVertex2fv(newLeftUp);
					glVertex2fv(newRightUp);
					glVertex2fv(newRightDown);
					glEnd();
				}
			}
		}
		return 0;
	}

	// jesli licznik > 1 to wykonujemy inne petle dokonujace kolejnych podziałów
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			point2 newLeftDown = { leftDown[0] + (newSideSize * i), leftDown[1] + (newSideSize * j) };
			point2 newLeftUp = { leftDown[0] + (newSideSize * i), leftDown[1] + newSideSize + (newSideSize * j) };
			point2 newRightUp = { leftDown[0] + newSideSize + (newSideSize * i), leftDown[1] + newSideSize + (newSideSize * j) };
			point2 newRightDown = { leftDown[0] + newSideSize + (newSideSize * i), leftDown[1] + (newSideSize * j) };

			//if odpowiadający za sprawdzenie czy jest to srodkowy kwadrat
			if ((i != 1) || (j != 1)) {
				//podziel podzielony kwadrat na kolejne 9
				drawSquares(newLeftDown, newRightDown, counter - 1);
			}
			else {
				glBegin(GL_POLYGON);
				glColor3f(0.0f, 0.0f, 0.0f);
				glVertex2fv(newLeftDown);
				glVertex2fv(newLeftUp);
				glVertex2fv(newRightUp);
				glVertex2fv(newRightDown);
				glEnd();
			}
		}
	}
	return 0;
}

// Funkcaja określająca, co ma być rysowane
void RenderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT);

	//okreslenie polozenia skrajnych rogow kwadratu
	point2 leftDown = { -70, -70 };
	point2 rightDown = { 70, -70 };

	//zmienna określająca na ile ma podzielić
	int counter = 3;
	
	drawSquares(leftDown, rightDown, counter);
	glFlush();
}

// Funkcja ustalająca stan renderowania
void MyInit(void)
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
}

// Funkcja służąca do kontroli zachowania proporcji rysowanych obiektów niezależnie od rozmiarów okna graficznego
void ChangeSize(GLsizei horizontal, GLsizei vertical)
{

	GLfloat AspectRatio;
	// Deklaracja zmiennej AspectRatio określającej proporcję wymiarów okna

	if (vertical == 0)
		// Zabezpieczenie pzred dzieleniem przez 0
		vertical = 1;

	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielkościokna okna urządzenia (Viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)

	glMatrixMode(GL_PROJECTION);
	// Określenie układu współrzędnych obserwatora

	glLoadIdentity();
	// Określenie przestrzeni ograniczającej

	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie współczynnika proporcji okna

	if (horizontal <= vertical)
		glOrtho(-100.0, 100.0, -100.0 / AspectRatio, 100.0 / AspectRatio, 1.0, -1.0);
	else
		glOrtho(-100.0 * AspectRatio, 100.0 * AspectRatio, -100.0, 100.0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	// Określenie układu współrzędnych     
	glLoadIdentity();
}

// Główny punkt wejścia programu. Program działa w trybie konsoli

int main(int argc, char* argv[])
{
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	
	glutCreateWindow("Drugi program w OpenGL");
	// Utworzenie okna i określenie treści napisu w nagłówku okna

	glutDisplayFunc(RenderScene);
	// Określenie, że funkcja RenderScene będzie funkcją zwrotną (callback)

	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcję zwrotną odpowiedzialną za zamianę okna

	MyInit();
	// Funkcja MyInit (zdefiniowana powyżej) wykonuje wszelkie inicjalizacje konieczneprzed przystąpieniem do renderowania

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT
	return 0;
}
