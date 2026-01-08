#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <fstream>
#include <iostream>

struct Point {
    float x, y;
    float r, g, b;
};

std::vector<Point> points;

float cr = 1.0f, cg = 0.0f, cb = 0.0f;
float brushSize = 6.0f;

void saveScreenshot(const char* name, int w, int h) {
    glFinish();
    glReadBuffer(GL_FRONT);

    std::vector<unsigned char> pixels(w * h * 3);
    glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());

    std::ofstream file(name);
    file << "P3\n" << w << " " << h << "\n255\n";

    for (int y = h - 1; y >= 0; y--) {
        for (int x = 0; x < w; x++) {
            int i = (y * w + x) * 3;
            file << (int)pixels[i] << " "
                 << (int)pixels[i + 1] << " "
                 << (int)pixels[i + 2] << " ";
        }
        file << "\n";
    }

    file.close();
    std::cout << "Screenshot saved as " << name << "\n";
}

int main() {
    if (!glfwInit()) return -1;

    // FORCE LEGACY OPENGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Mini Draw Tool", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 800, 600, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            saveScreenshot("drawing.ppm", 800, 600);
            glfwSetWindowShouldClose(window, true);
        }

        // COLORS
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) { cr=1; cg=0; cb=0; }
        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) { cr=0; cg=1; cb=0; }
        if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) { cr=0; cg=0; cb=1; }
        if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) { cr=1; cg=1; cb=0; }

        // BRUSH SIZE
        if (glfwGetKey(window, GLFW_KEY_LEFT_BRACKET) == GLFW_PRESS && brushSize > 1)
            brushSize -= 0.3f;
        if (glfwGetKey(window, GLFW_KEY_RIGHT_BRACKET) == GLFW_PRESS)
            brushSize += 0.3f;

        // DRAW
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            double x, y;
            glfwGetCursorPos(window, &x, &y);
            points.push_back({(float)x, (float)y, cr, cg, cb});
        }

        glClearColor(0.12f, 0.12f, 0.12f, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glPointSize(brushSize);
        glBegin(GL_POINTS);
        for (auto &p : points) {
            glColor3f(p.r, p.g, p.b);
            glVertex2f(p.x, p.y);
        }
        glEnd();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

