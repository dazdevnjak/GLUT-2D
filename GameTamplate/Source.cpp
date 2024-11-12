#include "GameObject.h"
#include <vector>

#define DEG2RAD 3.14 / 180.0

float delta_time;
int previous_time;

std::vector<GameObject> game_objects;

void initialize() {
	GameObject circle(
		glm::vec2(200.0f, 150.0f),
		glm::vec2(0.0f),
		primitive::create_circle(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.5), 50.0f)
	);

	game_objects.push_back(circle);

	GameObject cube(
		glm::vec2(400.0f, 300.0f),
		glm::vec2(0.0f),
		primitive::create_cube(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 60.0f)
	);

	game_objects.push_back(cube);

	GameObject triangle(
		glm::vec2(200.0f, 350.0f),
		glm::vec2(0.0f),
		primitive::create_triangle(glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f), 80.0f, 100.0f)
	);

	game_objects.push_back(triangle);
}

void update(float dt) {
	for (auto& obj : game_objects) {
		obj.update(dt);
	}
}

void render() {

	//Cistimo sve piksele
	glClear(GL_COLOR_BUFFER_BIT);

	//Renderujemo kod
	for (auto& obj : game_objects) {
		obj.render();
	}

	//Menjamo bafer
	glutSwapBuffers();

}

void game_loop(void) {
	int current_time = glutGet(GLUT_ELAPSED_TIME);
	delta_time = (float)(current_time - previous_time) / 1000;
	previous_time = current_time;

	update(delta_time);
	render();

	glutPostRedisplay();

}

void init_game(void) {

	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void reshape(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, w, 0.0, h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Tamplate!");

	init_game();

	initialize();

	glutDisplayFunc(game_loop);
	glutReshapeFunc(reshape);

	glutMainLoop();


	return 0;
}

