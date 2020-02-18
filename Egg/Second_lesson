#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <math.h>
#include <cstdlib>

typedef float point3[3];
static GLfloat theta[] = { 0.0, 0.0, 0.0 };
using namespace std;

struct eggPoints {
	float x;
	float y;
	float z;
	float xColor;
	float yColor;
	float zColor;
};

//zmienne potrzebne do dzialania programu
const int N = 20;
eggPoints TableOfPoint[N][N];
float var = 1.0f / N;
float Pi = 3.14f;
int model = 1;  // 1- punkty, 2- siatka, 3 - wypełnione trójkąty

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

// Funkcja rysująca osie układu współrzędnych
void Axes(void)
{
	point3  x_min = { -5.0, 0.0, 0.0 };
	point3  x_max = { 5.0, 0.0, 0.0 };
	// początek i koniec obrazu osi x
	point3  y_min = { 0.0, -5.0, 0.0 };
	point3  y_max = { 0.0,  5.0, 0.0 };
	// początek i koniec obrazu osi y
	point3  z_min = { 0.0, 0.0, -5.0 };
	point3  z_max = { 0.0, 0.0,  5.0 };
	//  początek i koniec obrazu osi y
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
	glBegin(GL_LINES); // rysowanie osi z
		glVertex3fv(z_min);
		glVertex3fv(z_max);
	glEnd();
}


void DrawAsPoints(){
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			glBegin(GL_POINTS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(TableOfPoint[i][j].x, TableOfPoint[i][j].y - 5, TableOfPoint[i][j].z);
			glEnd();
		}
	}
}

void DrawAsLines(){
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	for (int i = 0; i < N-1; i++) {
		for (int j = 0; j < N-1; j++) {
			glVertex3f(TableOfPoint[i][j].x, TableOfPoint[i][j].y - 5, TableOfPoint[i][j].z);
			glVertex3f(TableOfPoint[i][j + 1].x, TableOfPoint[i][j+1].y - 5, TableOfPoint[i][j+1].z);
			glVertex3f(TableOfPoint[i][j].x, TableOfPoint[i][j].y - 5, TableOfPoint[i][j].z);
			glVertex3f(TableOfPoint[i+1][j].x, TableOfPoint[i+1][j].y - 5, TableOfPoint[i+1][j].z);
			glVertex3f(TableOfPoint[i][j].x, TableOfPoint[i][j].y - 5, TableOfPoint[i][j].z);
			glVertex3f(TableOfPoint[i+1][j + 1].x, TableOfPoint[i+1][j+1].y - 5, TableOfPoint[i+1][j+1].z);
		}
	}
	glEnd();
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

void spinEgg()
{

	theta[0] -= 0.5;
	if (theta[0] > 360.0) theta[0] -= 360.0;

	theta[1] -= 0.5;
	if (theta[1] > 360.0) theta[1] -= 360.0;

	theta[2] -= 0.5;
	if (theta[2] > 360.0) theta[2] -= 360.0;

	glutPostRedisplay(); //odświeżenie zawartości aktualnego okna
}



// Funkcja określająca co ma być rysowane (zawsze wywoływana gdy trzeba
// przerysować scenę)
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszczącym

	glLoadIdentity();
	// Czyszczenie macierzy bieżącej
	glRotatef(theta[0], 1.0, 0.0, 0.0);

	glRotatef(theta[1], 0.0, 1.0, 0.0);

	glRotatef(theta[2], 0.0, 0.0, 1.0);

	Axes();
	// Narysowanie osi przy pomocy funkcji zdefiniowanej wyżej

	if (model == 1)
		DrawAsPoints();
	if (model == 2)
		DrawAsLines();
	if (model == 3)
		DrawAsColors();

	glFlush();
	// Przekazanie poleceń rysujących do wykonania



	glutSwapBuffers();
	//

}



void keys(unsigned char key, int x, int y)
{
	if (key == 'p') model = 1;
	if (key == 'w') model = 2;
	if (key == 's') model = 3;

	RenderScene();
}


/*************************************************************************************/

// Funkcja ustalająca stan renderowania



void MyInit(void)
{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Kolor czyszcący (wypełnienia okna) ustawiono na czarny

}

/*************************************************************************************/

// Funkcja ma za zadanie utrzymanie stałych proporcji rysowanych
// w przypadku zmiany rozmiarów okna.
// Parametry vertical i horizontal (wysokość i szerokość okna) są
// przekazywane do funkcji za każdym razem gdy zmieni się rozmiar okna.



void ChangeSize(GLsizei horizontal, GLsizei vertical)
{

	GLfloat AspectRatio;
	// Deklaracja zmiennej AspectRatio  określającej proporcję
	// wymiarów okna 

	if (vertical == 0)  // Zabezpieczenie przed dzieleniem przez 0

		vertical = 1;

	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielkościokna okna widoku (viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)  

	glMatrixMode(GL_PROJECTION);
	// Przełączenie macierzy bieżącej na macierz projekcji 

	glLoadIdentity();
	// Czyszcznie macierzy bieżącej            

	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie współczynnika  proporcji okna
	// Gdy okno nie jest kwadratem wymagane jest określenie tak zwanej
	// przestrzeni ograniczającej pozwalającej zachować właściwe
	// proporcje rysowanego obiektu.
	// Do okreslenia przestrzeni ograniczjącej służy funkcja
	// glOrtho(...)            

	if (horizontal <= vertical)

		glOrtho(-7.5, 7.5, -7.5 / AspectRatio, 7.5 / AspectRatio, 10.0, -10.0);

	else

		glOrtho(-7.5 * AspectRatio, 7.5 * AspectRatio, -7.5, 7.5, 10.0, -10.0);

	glMatrixMode(GL_MODELVIEW);
	// Przełączenie macierzy bieżącej na macierz widoku modelu                                    

	glLoadIdentity();
	// Czyszcenie macierzy bieżącej

}

/*************************************************************************************/

// Główny punkt wejścia programu. Program działa w trybie konsoli



int main(int argc, char* argv[])
{
	MakeTableOfPoints();
	
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(300, 300);

	glutCreateWindow("Układ współrzędnych 3-D");
	
	glutDisplayFunc(RenderScene);

	// Określenie, że funkcja RenderScene będzie funkcją zwrotną
	// (callback function).  Bedzie ona wywoływana za każdym razem
	// gdy zajdzie potrzba przeryswania okna 

	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcję zwrotną odpowiedzialną
	// zazmiany rozmiaru okna      
	glutIdleFunc(spinEgg);
	glutKeyboardFunc(keys);

	MyInit();
	// Funkcja MyInit() (zdefiniowana powyżej) wykonuje wszelkie
	// inicjalizacje konieczne  przed przystąpieniem do renderowania 

	glEnable(GL_DEPTH_TEST);
	// Włączenie mechanizmu usuwania powierzchni niewidocznych

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT
	return 0;
}

/*************************************************************************************/
