#include <iostream>
#include <iomanip>
#include <algorithm>

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"

using namespace std;

void Display(void);
void Reshape(int w, int h);
void Simulation(int value);
void KeyboardFunc(unsigned char key, int x, int y);
void ChangeColor();

// Массив цветов, требуемый в задании
GLclampf colors[4][3]
{
	{ 0, 0, 0 },
	{ 1, 0, 1 },
	{ 0, 0, 1 },
	{ 1, 0, 0 }
};
// Текущий индекс цвета
int currentColor = 0;
int counter = 0;

byte R = 0;
bool red = false;

int main(int argc, char* argv[]) {
	// Инициализация библиотеки GLUT
	glutInit(&argc, argv);
	// Инициализация дисплея (формат вывода)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	// Создание окна:
	// 1. Устанавливаем верхний левый угол окна
	glutInitWindowPosition(200, 200);
	// 2. Устанавливаем размер окна
	glutInitWindowSize(600, 600);
	// 3. Создаем окно
	glutCreateWindow("lab1");

	// Устанавливаем функцию, которая будет вызываться для перерисовки окна
	glutDisplayFunc(Display);
	// Устанавливаем функцию, которая будет вызываться при изменении размеров окна
	glutReshapeFunc(Reshape);
	// Устанавливаем функцию которая будет вызвана через 20 мс
	glutTimerFunc(20, Simulation, 0);
	// Устанавливаем функцию, которая будет вызываться при нажатии на клавишу
	glutKeyboardFunc(KeyboardFunc);

	glutMainLoop();
}

// Функция вызывается при перерисовке окна в том числе и принудительно, по командам glutPostRedisplay
void Display(void)
{
	// отчищаем буфер цвета
	glClearColor(0.22, 0.88, 0.11, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// включаем тест глубины
	glEnable(GL_DEPTH_TEST);
	// устанавливаем камеру
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5, 5, 7.5, 0, 0, 0, 0, 1, 0);
	// выводим объект ‐ красный (1,0,0) чайник
	//glColor3f(1.0, 0.0, 0.0);


	glColor3b(R, R, R);

	glutWireTeapot(1.0);
	// смена переднего и заднего буферов
	glutSwapBuffers();
};

// Функция, вызываемая при изменении размеров окна
void Reshape(int w, int h)
{
	// Установить новую область просмотра, равную всей области окна
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	// Установить матрицу проекции с правильным аспектом
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25, (float)w / h, 0.2, 70);
};

// Функция вызывается каждые 20 мс
void Simulation(int value)
{

	glutInitWindowPosition(value, 200);

	
	if (red == false)
	{
		R += 1;
		if (R == 127)
			red = true;
	}
	else
	{
		R -= 1;
		if (R == 0)
			red = false;
	}

	// Устанавливаем признак того, что окно нуждается в перерисовке
	glutPostRedisplay();

	// Эта же функция будет вызвана еще раз через 20 мс
	glutTimerFunc(20, Simulation, 0);
};

// Функция обработки нажатия клавиш
void KeyboardFunc(unsigned char key, int x, int y)
{
	printf("Key code is %i\n", (unsigned int)key);

	if ((unsigned int)key)
	{
		ChangeColor();
	}
};

void ChangeColor()
{
	
}