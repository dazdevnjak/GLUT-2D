#pragma once
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

#include <glut.h>

#define DEG2RAD 3.14 / 180.0

enum primitive_type {
	circle,
	cube,
	triangle
};

struct primitive {
	primitive_type type;
	glm::vec3 line;
	glm::vec3 fill;

	primitive() = default;

	//krug
	float radius;

	static primitive create_circle(const glm::vec3& line_color, const glm::vec3& fill_color, float r) {
		primitive p;
		p.type = primitive_type::circle;
		p.line = line_color;
		p.fill = fill_color;
		p.radius = r;
		return p;
	}

	//kocka
	float size;

	static primitive create_cube(const glm::vec3& line_color, const glm::vec3& fill_color, float s) {
		primitive p;
		p.type = primitive_type::cube;
		p.line = line_color;
		p.fill = fill_color;
		p.size = s;
		return p;
	}

	//trougao
	float base;
	float height;

	static primitive create_triangle(const glm::vec3& line_color, const glm::vec3& fill_color, float b, float h) {
		primitive p;
		p.type = primitive_type::triangle;
		p.line = line_color;
		p.fill = fill_color;
		p.base = b;
		p.height = h;
		return p;
	}
};

class GameObject {
private:
	glm::vec2 position;
	float rotation;
	glm::vec2 scale;

	primitive primitive;

	glm::vec2 velocity;

public:
	GameObject()
		: position(0.0f, 0.0f), velocity(0.0f, 0.0f),
		rotation(0.0f), scale(1.0f, 1.0f), primitive() {}

	GameObject(const glm::vec2& pos, const glm::vec2& vel, const struct primitive& prim)
		: position(pos), velocity(vel), rotation(0.0f), scale(1.0f, 1.0f),
		primitive(prim) {}

	~GameObject() {}

	glm::vec2 get_position() const { return position; }
	void set_position(const glm::vec2& new_position) { position = new_position; }

	glm::vec2 get_velocity() const { return velocity; }
	void set_velocity(const glm::vec2& new_velocity) { velocity = new_velocity; }

	glm::vec3 get_line() const { return primitive.line; }
	void set_line(const glm::vec3& new_line) { primitive.line = new_line; }

	glm::vec3 get_fill() const { return primitive.fill; }
	void set_fill(const glm::vec3& new_fill) { primitive.fill = new_fill; }

	float get_rotation() const { return rotation; }
	void set_rotation(float new_rotation) { rotation = new_rotation; }

	glm::vec2 get_scale() const { return scale; }
	void set_scale(const glm::vec2& new_scale) { scale = new_scale; }

	primitive_type get_primitive_type() const { return primitive.type; }

	void update(float dt) {
		position += velocity * dt;
		check_edges();
	}

	void render() {
		glPushMatrix();

		glTranslatef(position.x, position.y, 0.0f);
		glRotatef(rotation, 0.0f, 0.0f, 1.0f);
		glScalef(scale.x, scale.y, 1.0f);

		switch (primitive.type) {
		case primitive_type::circle:
			draw_circle(primitive.radius);
			break;
		case primitive_type::cube:
			draw_cube(primitive.size);
			break;
		case primitive_type::triangle:
			draw_triangle(primitive.base, primitive.height);
			break;
		default:
			break;
		}

		glPopMatrix();
	}

private:
	void draw_circle(float radius) {
		glLineWidth(2.0f);
		glColor3f(primitive.line.r, primitive.line.g, primitive.line.b);
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < 360; i++) {
			float theta = i * DEG2RAD;
			glVertex2f(cos(theta) * radius, sin(theta) * radius);
		}
		glEnd();

		glColor3f(primitive.fill.r, primitive.fill.g, primitive.fill.b);
		glBegin(GL_POLYGON);
		for (int i = 0; i < 360; i++) {
			float theta = i * DEG2RAD;
			glVertex2f(cos(theta) * radius, sin(theta) * radius);
		}
		glEnd();
	}

	void draw_cube(float size) {
		glLineWidth(2.0f);
		glColor3f(primitive.line.r, primitive.line.g, primitive.line.b);
		glBegin(GL_LINE_LOOP);
		glVertex2f(-size / 2, -size / 2);
		glVertex2f(size / 2, -size / 2);
		glVertex2f(size / 2, size / 2);
		glVertex2f(-size / 2, size / 2);
		glEnd();

		glColor3f(primitive.fill.r, primitive.fill.g, primitive.fill.b);
		glBegin(GL_POLYGON);
		glVertex2f(-size / 2, -size / 2);
		glVertex2f(size / 2, -size / 2);
		glVertex2f(size / 2, size / 2);
		glVertex2f(-size / 2, size / 2);
		glEnd();
	}

	void draw_triangle(float base, float height) {
		glLineWidth(2.0f);
		glColor3f(primitive.line.r, primitive.line.g, primitive.line.b);
		glBegin(GL_LINE_LOOP);
		glVertex2f(-base / 2, -height / 2);
		glVertex2f(base / 2, -height / 2);
		glVertex2f(0.0f, height / 2);
		glEnd();

		glColor3f(primitive.fill.r, primitive.fill.g, primitive.fill.b);
		glBegin(GL_POLYGON);
		glVertex2f(-base / 2, -height / 2);
		glVertex2f(base / 2, -height / 2);
		glVertex2f(0.0f, height / 2);
		glEnd();
	}

	void check_edges() {
		if (position.x > glutGet(GLUT_WINDOW_WIDTH)) {
			position.x = static_cast<float>(glutGet(GLUT_WINDOW_WIDTH));
		}
		else if (position.x < 0) {
			position.x = 0.0f;
		}
		if (position.y > glutGet(GLUT_WINDOW_HEIGHT)) {
			position.y = static_cast<float>(glutGet(GLUT_WINDOW_HEIGHT));
		}
		else if (position.y < 0) {
			position.y = 0.0f;
		}
	}
};

