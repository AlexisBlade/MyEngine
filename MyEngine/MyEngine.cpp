// MyEngine.cpp
//

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

const float PI = 3.14159265359f;

class Cube {
public:
    Cube(float startX, float startY, float startZ)
        : x(startX), y(startY), z(startZ), directionX(0), directionY(0), directionZ(0), angle(0) {}

    void move(float dx, float dy, float dz) {
        x += dx;
        y += dy;
        z += dz;
    }

    void draw() {
        glPushMatrix();
        glRotatef(angle, 0.1f, 1.0f, 0.0f);
        glTranslatef(x, y, z);
        glColor3f(0.7f, 0.0f, 1.0f); // Red color

        // Draw a cube
        glBegin(GL_QUADS);

        // Front face
        glVertex3f(-1.0f, -1.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, 1.0f);

        // Back face
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(1.0f, 1.0f, -1.0f);
        glVertex3f(1.0f, -1.0f, -1.0f);

        // Top face
        glVertex3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(-1.0f, 1.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, -1.0f);

        // Bottom face
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(1.0f, -1.0f, -1.0f);
        glVertex3f(1.0f, -1.0f, 1.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);

        // Right face
        glVertex3f(1.0f, -1.0f, -1.0f);
        glVertex3f(1.0f, 1.0f, -1.0f);
        glVertex3f(1.0f, 1.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, 1.0f);

        // Left face
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, -1.0f);

        glEnd();

        glPopMatrix();
    }

    void setDirection(float dx, float dy, float dz) {
        directionX = dx;
        directionY = dy;
        directionZ = dz;
    }

    void update() {
        move(directionX, directionY, directionZ);
        //angle += 0.0005f;
    }

private:
    float x, y, z;
    float directionX, directionY, directionZ;
    float angle;
};

void setPerspective(float fov, float aspect, float zNear, float zFar) {
    const float h = 1.0f / tan(fov * PI / 360.0f);
    float neg_depth = zNear - zFar;

    float perspectiveMatrix[16];
    memset(perspectiveMatrix, 0, sizeof(perspectiveMatrix));

    perspectiveMatrix[0] = h / aspect;
    perspectiveMatrix[5] = h;
    perspectiveMatrix[10] = (zFar + zNear) / neg_depth;
    perspectiveMatrix[11] = -1.0f;
    perspectiveMatrix[14] = 2.0f * zFar * zNear / neg_depth;

    glMultMatrixf(perspectiveMatrix);
}


int main() {
    // Create the main window
    sf::Window window(sf::VideoMode(1920, 1080), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);

    // Set the current active window before using any OpenGL command
    window.setActive(true);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearDepth(1.f);

    // Setup a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    setPerspective(90.f, 1.f, 1.f, 500.f);

    Cube cube(0, 0, -5);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Right) cube.setDirection(0.1f, 0, 0);
                else if (event.key.code == sf::Keyboard::Left) cube.setDirection(-0.1f, 0, 0);
                else if (event.key.code == sf::Keyboard::Up) cube.setDirection(0, 0.1f, 0);
                else if (event.key.code == sf::Keyboard::Down) cube.setDirection(0, -0.1f, 0);
                else if (event.key.code == sf::Keyboard::W) cube.setDirection(0, 0, 0.1f);
                else if (event.key.code == sf::Keyboard::S) cube.setDirection(0, 0, -0.1f);
            }

            if (event.type == sf::Event::KeyReleased) {
                cube.setDirection(0, 0, 0);
            }
        }

        cube.update();

        // Clear the depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cube.draw();

        // Update the window
        window.display();
    }

    return 0;
}