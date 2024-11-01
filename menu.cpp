#include <GL/glut.h>
#include <iostream>

// Variables 
bool gameStarted = false;

// Funcion para Mostrar texto en pantalla
void renderBitmapString(float x, float y, void* font, const char* string) {
    const char* c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

// Función para manejar el dibujo de la ventana
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (gameStarted) {
        // Mostrar pantalla del juego
        glColor3f(1.0, 1.0, 0.0);  // Color amarillo como Pac-Man
        renderBitmapString(-0.2f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Juego de Pacman");
    }
    else {
        // Mostrar menú principal
        glColor3f(1.0, 1.0, 0.0);  // Color amarillo para el título del menú
        renderBitmapString(-0.2f, 0.8f, GLUT_BITMAP_HELVETICA_18, "Pac-Man");

        glColor3f(1.0, 1.0, 1.0);  // Color blanco para el texto del menú
        renderBitmapString(-0.2f, 0.4f, GLUT_BITMAP_HELVETICA_18, "Start Game");
        renderBitmapString(-0.2f, 0.2f, GLUT_BITMAP_HELVETICA_18, "Instructions");
        renderBitmapString(-0.2f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Exit");
    }

    glFlush();
}

// Función para manejar las opciones seleccionadas
void selectOption(int option) {
    switch (option) {
    case 1:
        gameStarted = true;  // Cambiar al estado de juego
        break;
    case 2:
        std::cout << "Instructions selected" << std::endl;
        break;
    case 3:
        exit(0);  // Salir del programa
        break;
    }
    glutPostRedisplay();
}

// Función para manejar los clics del mouse
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Convertir coordenadas de pantalla a coordenadas de OpenGL
        float oglX = (float(x) / 250.0f) - 1.0f;
        float oglY = 1.0f - (float(y) / 250.0f);

        // Verificar en qué área del menú se hizo clic
        if (oglY > 0.3f && oglY < 0.5f) {
            selectOption(1);  // Start Game
        }
        else if (oglY > 0.1f && oglY < 0.3f) {
            selectOption(2);  // Instructions
        }
        else if (oglY > -0.1f && oglY < 0.1f) {
            selectOption(3);  // Exit
        }
    }
}

// Inicialización de OpenGL
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Fondo negro
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

// Función principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Pac-Man Menu");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);  // Detecta clics del mouse

    glutMainLoop();
    return 0;
}
