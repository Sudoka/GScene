/* GScene API
 * Copyright (C) 2010 David Serrano
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "viewer.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <string>
using namespace std;

void update();
void reshape(int w, int h);

Node* rootNode;
int win;

void viewer_init(int argc, char** argv,
    int width, int height) {
    
    glutInit(&argc, argv);
    glutInitWindowSize(width, height);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutDisplayFunc(update);
    glutReshapeFunc(reshape);
    glutIdleFunc(update);

	glEnable(GL_DEPTH_TEST);
}

void viewer_destroy() {
    glutDestroyWindow(win);
}

void viewer_start(Node* node, const char* title) {
    win = glutCreateWindow(title);
    glutSetWindow(win);
    glutShowWindow();
    glutSetCursor(GLUT_CURSOR_NONE);

    rootNode = node;
    glutMainLoop();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    
    float ratio = 1.0 * w / h;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	
    glViewport(0, 0, w, h);
    
    gluPerspective(45,ratio,1,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0,0.0,5.0, 
            0.0,0.0,-1.0,
            0.0f,1.0f,0.0f);

}

void update() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    rootNode->render();
    glutSwapBuffers();
}
