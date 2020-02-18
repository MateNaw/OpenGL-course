#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <math.h>
#include <cstdlib>
#include <iostream>

using namespace std;

// tablica przechowujaca wspolrzedne punktow
typedef float point3[3];

// tablica przechowujaca punkty tekstury do powierzchni
GLfloat textureControlPoints[5][5][2] = { {{0.0, 0.0}, {0.0, 0.08}, {0.0, 0.16}, {0.0, 0.24}, {0.0, 0.32}, },
										 {{0.0, 0.40} ,{0.0, 0.48}, {0.0, 0.56}, {0.0, 0.64}, {0.0, 0.72}},
										 {{0.0, 0.80}, {0.0, 0.9}, {0.0, 1.0}, {0.08, 1.0}, {0.16, 1.0}},
										 {{0.24, 1.0},{0.32, 1.0},{0.40, 1.0},{0.48, 1.0},{0.56, 1.0}},
										 {{0.64, 1.0},{0.72, 1.0},{0.8, 1.0},{0.9, 1.0},{1.0, 1.0}}};
// zmienna przechowywujaca nazwe tekstury
static GLuint  textureName;

//pozycje poczatkowe myszki
static int xMousePosition = 0;
static int delta_x = 0;
static int yMousePosition = 0;
static int delta_y = 0;

//zmienna do przyciskow myszy
static int status = 0;

//zmienne uzywane do poruszania sie po kątach
static GLfloat thetaU = 1.0;
static GLfloat thetaV = 1.0;
static GLfloat xAngleInPixels;
static GLfloat yAngleInPixels;
static GLfloat R = 15.0;
static GLfloat R_current = 0.0;
static GLfloat delta_R = 0.0;
float aspectRatio;

//zmienne do edycji siatki
bool edit = false;
bool change_point = false;

//dane wybranego punktu do edycji
int wybor_x = 0;
int wybor_y = 0;
float Pi = 3.14f;

//poczatkowa pozycja obserwatora
static GLfloat viever[] = { 0.0, 5.0, 10.0 };

//zmienna przechowywujaca model ktory ma byc wyswietlany
int model = 2;

//obsluga klawiszy myszki i zapisywanie jego pozycji
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

//funkcja sledzaca pozycje myszki
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

//tablica przechowywujaca punkty kontrolne
GLfloat ctrlpoints[5][5][3] = {
	{{0,0,4}, {1,0,4}, {2,0,4}, {3,0,4}, {4,1,4}},
	{{0,0,3}, {1,1,3}, {2,1,3}, {3,1,3}, {4,1,3}},
	{{0,1,2}, {1,2,2}, {2,6,2}, {3,2,2}, {4,1,2}},
	{{0,0,1}, {1,1,1}, {2,1,1}, {3,1,1}, {4,1,1}},
	{{0,0,0}, {1,0,0}, {2,0,0}, {3,0,0}, {4,1,0}}
};

// funkcja czytająca plik zawierajacy teksture i zamieniajaca ja na bajty
GLbyte* LoadTGAImage(const char* FileName, GLint* ImWidth, GLint* ImHeight, GLint* ImComponents, GLenum* ImFormat)
{
#pragma pack(1)           
	typedef struct
	{
		GLbyte    idlength;
		GLbyte    colormaptype;
		GLbyte    datatypecode;
		unsigned short    colormapstart;
		unsigned short    colormaplength;
		unsigned char     colormapdepth;
		unsigned short    x_orgin;
		unsigned short    y_orgin;
		unsigned short    width;
		unsigned short    height;
		GLbyte    bitsperpixel;
		GLbyte    descriptor;
	}TGAHEADER;
#pragma pack(8)

	FILE* pFile;
	TGAHEADER tgaHeader;
	unsigned long lImageSize;
	short sDepth;
	GLbyte* pbitsperpixel = NULL;
	*ImWidth = 0;
	*ImHeight = 0;
	*ImFormat = GL_BGR_EXT;
	*ImComponents = GL_RGB8;
	fopen_s(&pFile, FileName, "rb");
	if (pFile == NULL)
		return NULL;
	fread(&tgaHeader, sizeof(TGAHEADER), 1, pFile);
	*ImWidth = tgaHeader.width;
	*ImHeight = tgaHeader.height;
	sDepth = tgaHeader.bitsperpixel / 8;
	if (tgaHeader.bitsperpixel != 8 && tgaHeader.bitsperpixel != 24 && tgaHeader.bitsperpixel != 32)
		return NULL;
	lImageSize = tgaHeader.width * tgaHeader.height * sDepth;
	pbitsperpixel = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));
	if (pbitsperpixel == NULL)
		return NULL;
	if (fread(pbitsperpixel, lImageSize, 1, pFile) != 1)
	{
		free(pbitsperpixel);
		return NULL;
	}
	switch (sDepth)
	{
	case 3:
		*ImFormat = GL_BGR_EXT;
		*ImComponents = GL_RGB8;
		break;
	case 4:
		*ImFormat = GL_BGRA_EXT;
		*ImComponents = GL_RGBA8;
		break;
	case 1:
		*ImFormat = GL_LUMINANCE;
		*ImComponents = GL_LUMINANCE8;
		break;
	};
	fclose(pFile);
	return pbitsperpixel;
}

//funkcja wyswietlajaca siatke
void displayAsNet(void)
{
	glEnable(GL_DEPTH_TEST);
	//kolor rysowania siatki
	glColor3f(1.0, 1.0, 0.0);

	for (int j = 0; j <= 20; j++) {
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i <= 50; i++)
			//obliczanie punktu wg zadanych arametrow u i v dla lini poziomych
			glEvalCoord2f((GLfloat)i / 50.0, (GLfloat)j / 20.0);
		glEnd();
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i <= 50; i++)
			//obliczanie punktu wg zadanych arametrow u i v dla lini pionowych
			glEvalCoord2f((GLfloat)j / 20.0, (GLfloat)i / 50.0);
		glEnd();
	}
}

//funkcja rysujaca powierzchnie i siatke na niej
void displayAsSurface(void)
{
	//ewaluacja mapy punktow kontrolnych w celu wydobycia punktow siatki
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 5, 0, 1, 15, 5, &ctrlpoints[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);

	// włączeniu trybu teksturowania
	glEnable(GL_TEXTURE_2D);

	// Wybranie obiektu zawierajacego teksture
	glBindTexture(GL_TEXTURE_2D, textureName);

	//dodanie macierzy na stos
	glPushMatrix();
	for (int i = 0; i < 25; i++) {
		//rysowanie wypelnionych kwadratow siatki
		glBegin(GL_QUAD_STRIP);
		for (int j = 0; j <= 25; j++) {
			//wyewaluowanie punktow do rysowania
			glEvalCoord2f(i / 25.0, j / 25.0);
			glEvalCoord2f((i + 1) / 25.0, j / 25.0);
		}
		glEnd();
	}

	//tak samo jak wyzej rysowanie siatki
	glColor3f(1.0, 0.0, 0.0);
	for (int j = 0; j <= 20; j++) {
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i <= 50; i++)
			glEvalCoord2f((GLfloat)i / 50.0, (GLfloat)j / 20.0);
		glEnd();
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i <= 50; i++)
			glEvalCoord2f((GLfloat)j / 20.0, (GLfloat)i / 50.0);
		glEnd();
	}
	glFlush();
	glPopMatrix();
}

//funkcja rysujaca punkty kontrolne
void DrawControlPoints(void) {
	//zwiekszenie rozmiaru punktow
	glPointSize(6.0f);
	glBegin(GL_POINTS);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			// jesli edytujemy to rysujemy wybrany punkt w innym kolorze 
			if (edit) {
				if (i == wybor_y && j == wybor_x) {
					glColor3d(1.0, 1.0, 1.0);
					glVertex3f(ctrlpoints[i][j][0], ctrlpoints[i][j][1], ctrlpoints[i][j][2]);
				}
				else {
					glColor3d(0.0, 1.0, 0.0);
					glVertex3f(ctrlpoints[i][j][0], ctrlpoints[i][j][1], ctrlpoints[i][j][2]);
				}
			}
			//jesli nie edytujemy to wszstko tak samo
			else {
				glColor3d(0.0, 1.0, 0.0);
				glVertex3f(ctrlpoints[i][j][0], ctrlpoints[i][j][1], ctrlpoints[i][j][2]);
			}
		}
	}
	glEnd();

}

//rysowanie osi ukladu dostepne w poprzednich programach
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

//odswierzanie sceny i rysowanie jej
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//instrukcje odpowiadajace za przemieszczanie sie 
	if (status == 1)		// 1 dla poruszania po x i y
	{
		// Aktualizacja parametrów kątowych
		thetaU += delta_x / 2 * xAngleInPixels * 0.1;
		thetaV += delta_y / 2 * yAngleInPixels * 0.1;
	}
	if (status == 2)		// 2 dla zmiany odleglosci R od punktu
	{
		// Aktualizacja promienia
		R += delta_R * yAngleInPixels;
	}

	// przypisanie nowych wspolrzednych obserwatorowi
	viever[0] = R * cos(thetaU) * cos(thetaV);
	viever[1] = R * sin(thetaV);
	viever[2] = R * sin(thetaU) * cos(thetaV);
	gluLookAt(viever[0], viever[1], viever[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	Axes();

	//instrukcje odpowiadajace za wyswietlanie porzadanego modelu
	if (model == 1)
		displayAsNet();
	if (model == 2)
		displayAsSurface();
	if (model == 3) {
		DrawControlPoints();
	}

	// instrukcja pozwalajaca podac nam nowe wspolrzedne punktu z konsoli
	if (edit && change_point) {
		//obsluga dialogu z urzytkownikiem
		cout << "podaj nowe wspolrzedne punktu x, y i z\n";
		int x, y, z;
		cin >> x >> y >> z;
		ctrlpoints[wybor_y][wybor_x][0] = x;
		ctrlpoints[wybor_y][wybor_x][1] = y;
		ctrlpoints[wybor_y][wybor_x][2] = z;
		edit = false;
		change_point = false;
	}
	glFlush();
	glutSwapBuffers();
}

//funkcja sledzaca wcisane klawisze
void keys(unsigned char key, int x, int y)
{
	//klawisze do obslugi wyswietlania
	if (key == 'q') {
		model = 1;
		edit = false;
		change_point = false;
	}
	if (key == 'w') {
		model = 2;
		edit = false;
		change_point = false;
	}
	if (key == 'e') {
		model = 3;
		change_point = false;
	}
	//klawisz zmieniajacy tryb na tryb edycji
	if (key == 'p' && model == 3) {
		edit = true;
	}
	//przemieszacznie sie po siatce
	if (edit && key == 's')
		if (wybor_y < 4)
			wybor_y++;
	if (edit && key == 'x')
		if (wybor_y > 0)
			wybor_y--;
	if (edit && key == 'c')
		if (wybor_x < 4)
			wybor_x++;
	if (edit && key == 'z')
		if (wybor_x > 0)
			wybor_x--;
	if (edit && key == 'f')
		change_point = true;

	RenderScene();
}

//funkcja inicjujaca parametry programu ( światło, tekstura itd.)
void MyInit(void)
{
	// zmienne przechowuywujace bajty tekstury oraz jej rozmiar
	GLbyte* pBytes;
	GLint ImWidth, ImHeight, ImComponents;
	GLenum ImFormat;

	// ustawienie koloru czyszczacego na czarny
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// wczytanie pliku zombi.tga jako tekstury uzywanej w programie
	pBytes = LoadTGAImage("zombi.tga", &ImWidth, &ImHeight, &ImComponents, &ImFormat);

	// przypisanie tekstury do wskaznika textureName
	glGenTextures(1, &textureName);
	glBindTexture(GL_TEXTURE_2D, textureName);

	// Ustawienie parametrów tekstury
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// Stworzenie obiektu tekstury
	glTexImage2D(GL_TEXTURE_2D, 0, ImComponents, ImWidth, ImHeight, 0, ImFormat, GL_UNSIGNED_BYTE, pBytes);

	// Mapowanie tekstury
	glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 3, 5, 0, 1, 15, 5, &textureControlPoints[4][4][0]);

	// włącz wyświetlanie
	glEnable(GL_MAP2_TEXTURE_COORD_2);
	glEnable(GL_MAP2_VERTEX_3);

	// Definicja parametrów materiału
	GLfloat materialAmbient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat materialDiffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat materialSpecular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat materialShine = { 40.0 };

	// Definicja parametrów światła
	GLfloat lightOnePosition[] = { 0.0, 5.0, 0.0, 1.0 };
	GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };

	//kolor swiatla - biały
	GLfloat lightOneDiffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat lightOneSpecular[] = { 0.6f, 0.6f, 0.0f, 0.6f };

	// Osłabienie światła
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

	// Wygładzanie cieni
	glShadeModel(GL_SMOOTH);

	// Aktywacja światła
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_AUTO_NORMAL);

}

//funkcja utrzymująca parametry wyswietlania przy zmianie rozmiaru okna
void reshape(int w, int h)
{
	//ustawienie poczatkowych wartosci obserwatora
	xAngleInPixels = 360.0 / (float)h;
	yAngleInPixels = 360.0 / (float)w;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	// Macierz jako tryb projekcji
	glMatrixMode(GL_PROJECTION);

	// Czyszczenie macierzy bieżącej
	glLoadIdentity();

	aspectRatio = (GLfloat)h / (GLfloat)w;
	gluPerspective(70, aspectRatio, 1.0, 30.0);

	if (h <= w)
	{
		glViewport(0, (w - h) / 2, h, h);
	}
	else
	{
		glViewport((h - w) / 2, 0, w, h);
	}

	// Powrót do trybu modelu
	glMatrixMode(GL_MODELVIEW);

	// Czyszczenie macierzy bieżącej
	glLoadIdentity();
}

//glowna funkcja programu
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	MyInit();
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(200, 0.0, 1.0, 200, 0.0, 1.0);
	glutDisplayFunc(RenderScene);
	glutMouseFunc(MouseButtonState);
	glutMotionFunc(MousePosition);
	glutKeyboardFunc(keys);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
