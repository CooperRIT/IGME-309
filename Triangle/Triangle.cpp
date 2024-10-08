#ifdef __APPLE__
#include <GLUT/glut.h> // include glut for Mac
#else
#include <GL/freeglut.h> //include glut for Windows
#include <iostream>
#endif


// the window's width and height
int width, height;

// the four vertices of a square
float v0[2];
float v1[2];
float v2[2];
float v3[2];


void createSquare(float offset, float** arrays)
{
    // initialize the Square's vertices
    v0[0] = 0.0f;
    v0[1] = 0.0f;

    v1[0] = 5.0f;
    v1[1] = 0.0f;

    v2[0] = 5.0f;
    v2[1] = 3.0f;

    v3[0] = 0.0f;
    v3[1] = 3.0f;

    float* array;
    for (int i = 0; i < 4; i++)
    {
        array = arrays[i];
        for (int j = 0; j < 2; j++)
        {
            array[j] += offset;
        }
    }
}

void init(void)
{
    // initialize the size of the window
    width = 600;
    height = 600;
    float** arrays = new float*[4];
    arrays[0] = v0;
    arrays[1] = v1;
    arrays[2] = v2;
    arrays[3] = v3;
    createSquare(2, arrays);
    delete[] arrays;
}

// called when the GL context need to be rendered
void display(void)
{
    // clear the screen to white, which is the background color
    glClearColor(1.0, 1.0, 1.0, 0.0);

    // clear the buffer stored for drawing
    glClear(GL_COLOR_BUFFER_BIT);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // specify the color for drawing
    glColor3f(0.0, 1.0, 0.0);

    // this is immedidate mode of OpenGL usded prior to OpenGL 3.0
    glBegin(GL_QUADS);
    glVertex2fv(v0);
    glVertex2fv(v1);
    glVertex2fv(v2);
    glVertex2fv(v3);
    glEnd();

    // specify the color for new drawing
    glColor3f(0.0, 0.0, 1.0);

    // draw the origin of the canvas
    glPointSize(30.0f);
    glBegin(GL_POINTS);
    glVertex2f(0.0f, 0.0f);
    glEnd();
    glPointSize(1.0f);

    glutSwapBuffers();
}

// called when window is first created or when window is resized
void reshape(int w, int h)
{
    // update thescreen dimensions
    width = w;
    height = h;

    //do an orthographic parallel projection, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 10.0, 0.0, 10.0);
    //gluOrtho2D(-5.0, 5.0, -5.0, 5.0);

    /* tell OpenGL to use the whole window for drawing */
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    //glViewport((GLsizei) width/2, (GLsizei) height/2, (GLsizei) width, (GLsizei) height);

    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    // before create a glut window,
    // initialize stuff not opengl/glut dependent
    init();

    //initialize GLUT, let it extract command-line GLUT options that you may provide
    //NOTE that the '&' before argc
    glutInit(&argc, argv);

    // specify as double bufferred can make the display faster
    // Color is speicfied to RGBA, four color channels with Red, Green, Blue and Alpha(depth)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    //set the initial window size */
    glutInitWindowSize((int)width, (int)height);

    // create the window with a title
    glutCreateWindow("First OpenGL Program");

    /* --- register callbacks with GLUT --- */

    //register function to handle window resizes
    glutReshapeFunc(reshape);

    //register function that draws in the window
    glutDisplayFunc(display);

    //start the glut main loop
    glutMainLoop();

    return 0;
}