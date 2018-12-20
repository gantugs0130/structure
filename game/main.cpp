#include <GL/glut.h>
#include <math.h>
#include <iostream>
#define PI 3.14159265
using namespace std;
double alpha =PI/90;
static float normalx=0, normaly=1, normalz=0;
static float posx=0.0f,posz=500.0f,posy=0.0f;
// Point class to keep it a little cleaner.


void SpecialKeys(int key, int x0, int y0)
    {
    if(key == GLUT_KEY_UP){
        posy = cos(PI/90) * posy - sin(PI/90) * posz;
        posz = cos(PI/90) * posz + sin(PI/90) * posy;
        normaly=cos(PI/90) * normaly - sin(PI/90) * normalz;
        normalz=cos(PI/90) * normalz + sin(PI/90) * normaly;  
        glutPostRedisplay();
    }
    else {if(key == GLUT_KEY_DOWN){
        posy = cos(PI/90) * posy + sin(PI/90) * posz;
        posz = cos(PI/90) * posz - sin(PI/90) * posy;
        normaly=cos(PI/90) * normaly + sin(PI/90) * normalz;
        normalz=cos(PI/90) * normalz - sin(PI/90) * normaly;  
        glutPostRedisplay();
    }
        else{
            if(key==GLUT_KEY_RIGHT){
            posx = cos(PI/90) * posx - sin(PI/90) * posy;
            posy = cos(PI/90) * posy + sin(PI/90) * posx;
            normaly=cos(PI/90) * normaly + sin(PI/90) * normalx;
            normalx=cos(PI/90) * normalx - sin(PI/90) * normaly; 
            glutPostRedisplay();
            }
            else{ if(key == GLUT_KEY_LEFT){
            posx = cos(PI/90) * posx + sin(PI/90) * posy;
            posy = cos(PI/90) * posy - sin(PI/90) * posx;
            normaly=cos(PI/90) * normaly - sin(PI/90) * normalx;
            normalx=cos(PI/90) * normalx + sin(PI/90) * normaly; 
            glutPostRedisplay();
            }
            else{
                if(key == GLUT_KEY_PAGE_UP){
                    float R = sqrt(posx*posx+posy*posy+posz*posz);
                    float Rotz = posz/R;
                    posz = (R - 5)*Rotz;
                    float Roty = posy/R;
                    posy = (R - 5)*Roty;
                    float Rotx = posx/R;
                    posx = (R - 5)*Rotx;
                    glutPostRedisplay();
                    }
                    else{
                        if(key == GLUT_KEY_PAGE_DOWN){
                            float R = sqrt(posx*posx+posy*posy+posz*posz);
                            float Rotz = posz/R;
                            posz = (R + 5)*Rotz;
                            float Roty = posy/R;
                            posy = (R + 5)*Roty;
                            float Rotx = posx/R;
                            posx = (R + 5)*Rotx;
                            glutPostRedisplay();
                        }
                    }
            }
            }
        }
    }

    }
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	GLfloat fAspect = (GLfloat)w / (GLfloat)h;

	glMatrixMode(GL_PROJECTION);
    gluPerspective(35.0f, fAspect, 1.0, 2000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}
void ReduceToUnit(float vector[3])
{
	float length;

	// Calculate the length of the vector
	length = float(sqrt((vector[0] * vector[0]) +
						 (vector[1] * vector[1]) +
						 (vector[2] * vector[2])));

	// Keep the program from blowing up by providing an exceptable
	// value for vectors that may calculated too close to zero.
	if (length == 0.0f)
		length = 1.0f;

	// Dividing each element by the length will result in a
	// unit normal vector.
	vector[0] /= length;
	vector[1] /= length;
	vector[2] /= length;
}

void calcNormal(float v[3][3], float out[3])
{
	float v1[3], v2[3];
	static const int x = 0;
	static const int y = 1;
	static const int z = 2;

	// Calculate two vectors from the three points
	v1[x] = v[0][x] - v[1][x];
	v1[y] = v[0][y] - v[1][y];
	v1[z] = v[0][z] - v[1][z];

	v2[x] = v[1][x] - v[2][x];
	v2[y] = v[1][y] - v[2][y];
	v2[z] = v[1][z] - v[2][z];

	// Take the cross product of the two vectors to get
	// the normal vector which will be stored in out
	out[x] = v1[y] * v2[z] - v1[z] * v2[y];
	out[y] = v1[z] * v2[x] - v1[x] * v2[z];
	out[z] = v1[x] * v2[y] - v1[y] * v2[x];

	// Normalize the vector (shorten length to one)
	ReduceToUnit(out);
}
void setup()
{
	GLfloat  ambientLight[] = {0.4f, 0.4f, 0.4f, 1.0f };
    GLfloat  diffuseLight[] = {0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat  specular[] = { 0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat  lightPos[] = { 2000.0f, 2000.0f, 2000.0f, 1.0f };
    GLfloat  specref[] =  { 0.6f, 0.6f, 0.6f, 1.0f };
        glEnable(GL_DEPTH_TEST);    // Hidden surface removal
        glEnable(GL_CULL_FACE);        // Do not calculate inside of solid object
        glFrontFace(GL_CCW);

       // Enable lighting
       glEnable(GL_LIGHTING);

    // Setup light 0
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambientLight);
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
    glLightfv(GL_LIGHT0,GL_SPECULAR,specular);

//    Position and turn on the light
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
    glEnable(GL_LIGHT0);

//    Enable color tracking
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_CONSTANT_ALPHA);
    glEnable(GL_COLOR_MATERIAL);

//    Set Material properties to follow glColor values
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

//    All materials hereafter have full specular reflectivity
 //   with a moderate shine
    glMaterialfv(GL_FRONT, GL_SPECULAR,specref);
    glMateriali(GL_FRONT,GL_SHININESS,64);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}


// Calculate the next bezier point.
void draw_world(float fx, float fy, float fz, float r){
    glPushMatrix();
    
    glColor3f(0.7,0.7,0.7);
    glBegin(GL_QUADS);
    glVertex3f(fx+r,fy+r/2,fz-0.5);
    glVertex3f(fx-r,fy+r/2,fz-0.5);
    glVertex3f(fx-r,fy-r/2,fz-0.5);
    glVertex3f(fx+r,fy-r/2,fz-0.5);
    glEnd();

    
    glEnable(GL_BLEND);
    glColor4f(0,1,0.8, 0.5);
    glBegin(GL_QUADS);
    glVertex3f(fx+r,fy+r/2,fz);
    glVertex3f(fx-r,fy+r/2,fz);
    glVertex3f(fx-r,fy-r/2,fz);
    glVertex3f(fx+r,fy-r/2,fz);
    glEnd();
    glDisable(GL_BLEND);

    glColor3f(0.9,0.9,0.9);
    glBegin(GL_QUADS);
    glVertex3f(fx+r,fy-r/2,fz);
    glVertex3f(fx-r,fy-r/2,fz);
    glVertex3f(fx-r,fy-r/2,fz+r/4);
    glVertex3f(fx+r,fy-r/2,fz+r/4);
    
    glEnd();

    glColor3f(0.9,0.9,0.9);
    glBegin(GL_QUADS);

    glVertex3f(fx-r,fy+r/2,fz);
    glVertex3f(fx+r,fy+r/2,fz);
    glVertex3f(fx+r,fy+r/2,fz+r/4);
    glVertex3f(fx-r,fy+r/2,fz+r/4);
    
    glEnd();

    glColor3f(0.9,0.9,0.9);
    glBegin(GL_QUADS);
    glVertex3f(fx-r,fy-r/2,fz);
    glVertex3f(fx-r,fy+r/2,fz);
    glVertex3f(fx-r,fy+r/2,fz+r/4);
    glVertex3f(fx-r,fy-r/2,fz+r/4);
    glEnd();

    glColor3f(0.9,0.9,0.9);
    glBegin(GL_QUADS);
    glVertex3f(fx+r,fy+r/2,fz+r/4);
    glVertex3f(fx+r,fy+r/2,fz);
    glVertex3f(fx+r,fy-r/2,fz);
    glVertex3f(fx+r,fy-r/2,fz+r/4);
    glEnd();
    glPopMatrix();

}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
    gluLookAt(	posx, posy, posz,
			0, 0, 0,
			normalx, normaly, normalz); 

    glColor3f(1,1,1);
    draw_world( 0 , 0 , 0 , 100);
    glPopMatrix();
    glutSwapBuffers();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100,150);
    glutCreateWindow("Bezier Curve");   
    glutReshapeFunc(resize);
    glutDisplayFunc(myDisplay);
    glutSpecialFunc(SpecialKeys);
    setup();
    glutMainLoop();
    return 0;
}