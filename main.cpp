#include<stdio.h>
#include <windows.h>
#include <GL/glut.h>
#include<math.h>
#include <stdio.h>
#include <stdlib.h>

int counter=0;
double winHt=10.0;
char s[20]="AIRPORT";
int i;
using namespace std;
GLuint makeaTree;
float x,y,z;

int spin;
//double winHt=5.0;
GLuint texture[10];
GLboolean ambient = true;
GLboolean diffuse = true;
GLboolean specular = true;
GLfloat wall_no_mat[] = {0.0,0.0,0.0,1.0};
GLfloat wall_ambient[] = {0.373, 0.620, 0.627, 1.0};
GLfloat wall_diffuse[] = {0.30, 0.6, 0.59, 0.9};
GLfloat wall_specular[] = {0.32,0.6, 0.61, 1.0};
GLfloat wall_shininess[] = {13};
const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };



void lighting(GLfloat no_mat[4],GLfloat mat_ambient[4],GLfloat mat_diffuse[4],GLfloat mat_specular[4],GLfloat shininess[1])
{
    if(ambient)
    {
        glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
    }
    else
    {
        glMaterialfv(GL_FRONT,GL_AMBIENT,no_mat);

    }
    if(diffuse)
    {
        glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
    }
    else
    {
        glMaterialfv(GL_FRONT,GL_DIFFUSE,no_mat);
    }
    if(specular)
    {
        glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);

    }
    else
    {
        glMaterialfv(GL_FRONT,GL_SPECULAR,no_mat);
    }
    glMaterialfv(GL_FRONT,GL_SHININESS,shininess);
}

struct Image
{
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
};

int ImageLoad(char *filename, Image *image)
{
    FILE *file;
    unsigned long size; //size of the image in bytes
    unsigned long i; //standard counter
    unsigned short int planes; //number of planes in Image
    char temp; //temporary color storage for bgr-rgb conversion

    file = fopen(filename, "r");
    if(file==NULL)
    {
        printf("Can't open file!");
    }
    fseek(file,18,SEEK_CUR);
    i = fread(&image->sizeX,4,1,file);
    i = fread(&image->sizeY,4,1,file);
    size = image->sizeX * image->sizeY * 3;
    fread(&planes, 2, 1, file);
    fseek(file, 24, SEEK_CUR);
    image->data = (char*)malloc(size);

    i=fread(image->data, size, 1, file);

    for(i=0;i<size;i+=3)
    {
        temp = image->data[i];
        image->data[i] = image->data[i+2];
        image->data[i+2] = temp;

    }

    fclose(file);
return 1;

}

void loadTexture(char* file_name, int tex_id)
{
    Image *image1;
    //allocate space for texture
    image1 = (Image*) malloc(sizeof(Image));
    if(!ImageLoad(file_name,image1))
    {
        exit(1);
    }

    texture[tex_id] = tex_id;

    glBindTexture(GL_TEXTURE_2D,tex_id);

    glTexImage2D(GL_TEXTURE_2D,0,3,image1->sizeX,image1->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,image1->data);

    //scale
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //scale

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}


static void TimeEvent(int te)
{
    int spin;
    spin++;  // increase cube rotation by 1
	if (spin >360) spin = 0; // if over 360 degress, start back at zero.
	glutPostRedisplay();  // Update screen with new rotation data
	glutTimerFunc( 100, TimeEvent, 1);  // Reset our timmer.
}


void makeCylinder(float height, float base){
GLUquadric *obj = gluNewQuadric();
//gluQuadricDrawStyle(obj, GLU_LINE);
glColor3f(0.64f, 0.16, 0.16f);glPushMatrix();
glRotatef(-90, 1.0,0.0,0.0);
gluCylinder(obj, base,base-(0.2*base), height, 20,20);
glPopMatrix();
glutSwapBuffers();
}

void makeTree(float height, float base){

float angle;
makeCylinder(height, base); glTranslatef(0.0, height, 0.0);
height -= height*.2; base-= base*0.3;
for(int a= 0; a<3; a++){
angle = rand()%50+20;
if(angle >48)
angle = -(rand()%50+20);
if (height >1){
glPushMatrix();
glRotatef(angle,1,0.0,1);
makeTree(height,base);
glPopMatrix();

}
}

}


void initGL()
{
   glClearColor(0.0f, 0.7f, 1.0f, 0.0f); // Set background color to black and opaque
   glClearDepth(1.0f);
   glShadeModel(GL_SMOOTH);                  // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);
   glClearColor(0.0f, 0.7f, 1.0f, 0.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading

      // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
   makeaTree=glGenLists(1);
   glNewList(makeaTree, GL_COMPILE);
   makeTree(4,0.2);
   glEndList();  // Nice perspective corrections
}

void drawobjects()
{
    //surface
glPushMatrix();
glColor3f(0.576,0.8588,0.439);
glTranslated(0,-2.5,-5);
glScaled(60,0.7,80);
glutSolidCube(0.5);
glPopMatrix();


 //wall boundary h
glPushMatrix();
glColor3f(0.623,0.623,0.372);
glTranslated(0.0,-0.52,-20.0);
glScaled(60,0.5,5);
glutSolidCube(0.5);
glPopMatrix();

//wall boundary v
glPushMatrix();
glColor3f(0.623,0.623,0.372);
glRotatef(90,0,1,0);
glTranslated(2.0,-0.52,-15.0);
glScaled(85,0.5,3);
glutSolidCube(0.4);
glPopMatrix();

//wall boundary h
glPushMatrix();
glColor3f(0.623,0.623,0.372);
glTranslated(0.0,-0.52,17.0);
glScaled(65,0.5,7);
glutSolidCube(0.5);
glPopMatrix();


//wall boundary v
glPushMatrix();
glColor3f(0.623,0.623,0.372);
glRotatef(90,0,1,0);
glTranslated(2.0,-0.52,15.0);
glScaled(85,0.5,3);
glutSolidCube(0.4);
glPopMatrix();



glPushMatrix();//road
glColor3f(0.0,0.0,0.0);
glTranslated(0,-1.8,5.7);
glScaled(60,1.5,15);
glutSolidCube(0.5);
glPopMatrix();
glPushMatrix();
glTranslated(0,-1.4,-2);
glPushMatrix();
glColor3f(1.0,1.0,1.0);
glTranslated(7.5,0,8.8);
glScaled(3,0.3,1);
glutSolidCube(0.5);
glPopMatrix();

glPushMatrix();
glColor3f(1.0,1.0,1.0);
glTranslated(4.5,0,8.8);
glScaled(3,0.3,1);
glutSolidCube(0.5);
glPopMatrix();


glPushMatrix();
glColor3f(1.0,1.0,1.0);
glTranslated(1.5,0,8.8);
glScaled(3,0.3,1);
glutSolidCube(0.5);
glPopMatrix();

glPushMatrix();
glColor3f(1.0,1.0,1.0);
glTranslated(-1.5,0,8.8);
glScaled(3,0.3,1);
glutSolidCube(0.5);
glPopMatrix();

glPushMatrix();
glColor3f(1.0,1.0,1.0);
glTranslated(-4.5,0,8.8);
glScaled(3,0.3,1);
glutSolidCube(0.5);
glPopMatrix();

glPushMatrix();
glColor3f(1.0,1.0,1.0);
glTranslated(-7.5,0,8.8);
glScaled(3,0.3,1);
glutSolidCube(0.5);
glPopMatrix();
glPopMatrix();
//joyeeta
glPushMatrix();
glTranslated(0,-1,-8);
    glRotated(220,0,1,0);

    glPushMatrix();
    glTranslated(-2,0,2.5);
    glRotated(180,0,1,0);
    glPushMatrix();//runway
    glColor3f(0,0.0,0.0);
    glRotated(50,0,1,0);
    glTranslated(-3.5,-0.7,0.0);
    glScaled(5.5,0.05,10.5);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();//whiteline1
    glColor3f(1.0,1.0,1.0);
    glRotated(50,0,1,0);
    glTranslated(-4.5,-0.67,0.0);
    glScaled(0.1,0.05,10.5);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();//whiteline2
    glColor3f(1.0,1.0,1.0);
    glRotated(50,0,1,0);
    glTranslated(-5.5,-0.67,0.0);
    glScaled(0.1,0.05,10.5);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();//dotted line1
    glColor3f(1.0,1.0,1.0);
    glRotated(50,0,1,0);
    glTranslated(-5.0,-0.67,0.0);
    glScaled(0.1,0.05,2.0);
    glutSolidCube(1.0);
    glPopMatrix();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-8,0,-2.5);
    glRotated(180,0,1,0);
    glPushMatrix();//runway
    glColor3f(0,0.0,0.0);
    glRotated(50,0,1,0);
    glTranslated(-3.5,-0.7,0.0);
    glScaled(5.5,0.05,10.5);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();//whiteline1
    glColor3f(1.0,1.0,1.0);
    glRotated(50,0,1,0);
    glTranslated(-4.5,-0.67,0.0);
    glScaled(0.1,0.05,10.5);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();//whiteline2
    glColor3f(1.0,1.0,1.0);
    glRotated(50,0,1,0);
    glTranslated(-5.5,-0.67,0.0);
    glScaled(0.1,0.05,10.5);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();//dotted line1
    glColor3f(1.0,1.0,1.0);
    glRotated(50,0,1,0);
    glTranslated(-5.0,-0.67,0.0);
    glScaled(0.1,0.05,2.0);
    glutSolidCube(1.0);
    glPopMatrix();
    glPopMatrix();


    glPushMatrix();
    glTranslated(-0,0,-2.5);
    glRotated(180,0,1,0);
    glPushMatrix();//runway
    glColor3f(0,0.0,0.0);
    glRotated(50,0,1,0);
    glTranslated(-3.5,-0.7,0.0);
    glScaled(5.5,0.05,10.5);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();//whiteline1
    glColor3f(1.0,1.0,1.0);
    glRotated(50,0,1,0);
    glTranslated(-4.5,-0.67,0.0);
    glScaled(0.1,0.05,10.5);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();//whiteline2
    glColor3f(1.0,1.0,1.0);
    glRotated(50,0,1,0);
    glTranslated(-5.5,-0.67,0.0);
    glScaled(0.1,0.05,10.5);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();//dotted line1
    glColor3f(1.0,1.0,1.0);
    glRotated(50,0,1,0);
    glTranslated(-5.0,-0.67,0.0);
    glScaled(0.1,0.05,2.0);
    glutSolidCube(1.0);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslated(2,0,-5);
    glRotated(180,0,1,0);
    glPushMatrix();//runway
    glColor3f(0,0.0,0.0);
    glRotated(50,0,1,0);
    glTranslated(-3.5,-0.7,0.0);
    glScaled(5.5,0.05,10.5);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();//whiteline1
    glColor3f(1.0,1.0,1.0);
    glRotated(50,0,1,0);
    glTranslated(-4.5,-0.67,0.0);
    glScaled(0.1,0.05,10.5);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();//whiteline2
    glColor3f(1.0,1.0,1.0);
    glRotated(50,0,1,0);
    glTranslated(-5.5,-0.67,0.0);
    glScaled(0.1,0.05,10.5);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();//dotted line1
    glColor3f(1.0,1.0,1.0);
    glRotated(50,0,1,0);
    glTranslated(-5.0,-0.67,0.0);
    glScaled(0.1,0.05,2.0);
    glutSolidCube(1.0);
    glPopMatrix();
    glPopMatrix();

lighting(wall_no_mat,wall_ambient,wall_diffuse,wall_specular,wall_shininess);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glPushMatrix();// right wall
    glColor3f(0.45,0.45,0.45);
    glRotated(230,0,1,0);
    glTranslated(1.15,0.7,1.7);
    glScaled(3.0,2.0,0.8);
    glutSolidCube(1.5);
    glPopMatrix();

     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glPushMatrix();//left wall
    glColor3f(0.45,0.45,0.45);
    glRotated(230,0,1,0);
    glTranslated(1.15,0.7,-1.9);
    glScaled(3.25,3.0,1.3);
    glutSolidCube(1.0);
    glPopMatrix();

     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glPushMatrix();//main building
    glColor3f(0.45,0.45,0.45);
    glRotated(230,0,1,0);
    glTranslated(2.0,-0.3,-0.1);
    glScaled(1.5,1.0,1.0);
    glutSolidCube(1.0);
    glPopMatrix();

     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glPushMatrix();//right building
    glColor3f(0.65,0.50,0.39);
    glRotated(230,0,1,0);
    glTranslated(2.1,-0.2,0.795);
    glScaled(1.3,1.2,0.8);
    glutSolidCube(1.0);
    glPopMatrix();

     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glPushMatrix();//left building
    glColor3f(0.65,0.50,0.39);
    glRotated(230,0,1,0);
    glTranslated(2.1,-0.2,-1.0);
    glScaled(1.3,1.2,0.8);
    glutSolidCube(1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();//radar cylinder
    glColor3f(0.0,0.0,0.0);
    glRotated(230,0,1,0);
    glTranslated(1.9,0.5,0.1);
    glScaled(0.1,0.6,0.1);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();//radar cone
    glColor3f(0.85,0.53,0.1);
    glRotated(45,1,0,0);
    glTranslated(-1.4,1.5,0.3);
   glRotatef(spin++, 1.0, 0, 1.0); // spin cube
    glScaled(0.1,0.6,0.1);
    glutWireCone(1.2,2.0,50,50);
    glPopMatrix();
    glPushMatrix();//right shed
    glColor3f(0.5,0.5,0.5);
    glRotated(230,0,1,0);
    glTranslated(0.5,0.2,3.45);
    glScaled(2.0,0.05,2.5);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();//left wall upper window
    glColor3f(0.80,0.80,0.80);
    glRotated(230,0,1,0);
    glTranslated(-0.39,1.0,-1.9);
    glScaled(0.2,0.8,0.9);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();//left wall lower window
    glColor3f(0.80,0.80,0.80);
    glRotated(230,0,1,0);
    glTranslated(-0.39,-0.3,-1.9);
    glScaled(0.2,0.8,0.9);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();//right wall upper window
    glColor3f(0.80,0.80,0.80);
    glRotated(230,0,1,0);
    glTranslated(-1.06,1.0,1.72);
    glScaled(0.2,0.8,0.9);
    glutSolidCube(1.2);
    glPopMatrix();
    glPushMatrix();//right wall lower window
    glColor3f(0.80,0.80,0.80);
    glRotated(230,0,1,0);
    glTranslated(-1.06,-0.2,1.72);
    glScaled(0.2,0.8,0.9);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();//main building lower window
    glColor3f(0.80,0.80,0.80);
    glRotated(230,0,1,0);
    glTranslated(1.2555,-0.5,-0.1);
    glScaled(0.2,0.3,0.9);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();//main building upper window
    glColor3f(0.80,0.80,0.80);
    glRotated(230,0,1,0);
    glTranslated(1.2555,-0.1,-0.1);
    glScaled(0.2,0.3,0.9);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();//left wall door1
    glColor3f(0.80,0.80,0.80);
    glRotated(230,0,1,0);
    glTranslated(-0.1,-0.2,-2.35);
    glScaled(0.5,1.0,0.5);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();//left wall door2
    glColor3f(0.80,0.80,0.80);
    glRotated(230,0,1,0);
    glTranslated(0.6,-0.2,-2.35);
    glScaled(0.5,1.0,0.5);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();//left wall door3
    glColor3f(0.80,0.80,0.80);
    glRotated(230,0,1,0);
    glTranslated(1.2,-0.2,-2.35);
    glScaled(0.5,1.0,0.5);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();//left wall door4
    glColor3f(0.80,0.80,0.80);
    glRotated(230,0,1,0);
    glTranslated(1.8,-0.2,-2.35);
    glScaled(0.5,1.0,0.5);
    glutSolidCube(1.0);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glPushMatrix();//car1
    glColor3f(0.80,0.80,0.80);
    glRotated(230,0,1,0);
    glTranslated(1.0,-0.2,-4.0);
    glScaled(1.0,0.7,0.5);
    glutSolidCube(1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();//car1 ty1
    glColor3f(0.80,0.80,0.80);
    glRotated(230,0,1,0);
    glTranslated(1.2,-0.5,-4.2);
    glScaled(1.0,0.7,0.5);
    glutSolidSphere(0.2,20,20);
    glPopMatrix();
    glPushMatrix();//car1 ty2
    glColor3f(0.80,0.80,0.80);
    glRotated(230,0,1,0);
    glTranslated(0.7,-0.5,-4.2);
    glScaled(1.0,0.7,0.5);
    glutSolidSphere(0.2,20,20);
    glPopMatrix();
    glPushMatrix();//car1 window
    glColor3f(0.80,0.80,0.80);
    glRotated(230,0,1,0);
    glTranslated(1.0,-0.05,-4.2);
    glScaled(4.0,1.5,1.0);
    glutSolidCube(0.2);
    glPopMatrix();
    glPushMatrix();//car1 window
    glColor3f(0.80,0.80,0.80);
    glRotated(230,0,1,0);
    glTranslated(1.0,-0.05,-3.8);
    glScaled(4.0,1.5,1.0);
    glutSolidCube(0.2);
    glPopMatrix();
    glPushMatrix();//car1 ty3
    glColor3f(0.80,0.80,0.80);
    glRotated(230,0,1,0);
    glTranslated(1.2,-0.5,-3.8);
    glScaled(1.0,0.7,0.5);
    glutSolidSphere(0.2,20,20);
    glPopMatrix();
    glPushMatrix();//car1 ty4
    glColor3f(0.80,0.80,0.80);
    glRotated(230,0,1,0);
    glTranslated(0.7,-0.5,-3.8);
    glScaled(1.0,0.7,0.5);
    glutSolidSphere(0.2,20,20);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glPushMatrix();//car2
    glColor3f(0.80,0.80,0.80);
    glRotated(230,0,1,0);
    glTranslated(-0.8,-0.2,-4.0);
    glScaled(1.0,0.7,0.5);
    glutSolidCube(1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();//car2 ty1
    glColor3f(0.80,0.80,0.80);
    glRotated(230,0,1,0);
    glTranslated(-1.0,-0.5,-4.2);
    glScaled(1.0,0.7,0.5);
    glutSolidSphere(0.2,20,20);
    glPopMatrix();
    glPushMatrix();//car2 ty2
    glColor3f(0.80,0.80,0.80);
    glRotated(230,0,1,0);
    glTranslated(-0.6,-0.5,-4.2);
    glScaled(1.0,0.7,0.5);
    glutSolidSphere(0.2,20,20);
    glPopMatrix();
    glPushMatrix();//car2 window
    glColor3f(0.80,0.80,0.80);
    glRotated(230,0,1,0);
    glTranslated(-0.8,-0.05,-4.2);
    glScaled(4.0,1.5,1.0);
    glutSolidCube(0.2);
    glPopMatrix();
    glPushMatrix();//car2 window
    glColor3f(0.80,0.80,0.80);
    glRotated(230,0,1,0);
    glTranslated(-0.8,-0.05,-3.8);
    glScaled(4.0,1.5,1.0);
    glutSolidCube(0.2);
    glPopMatrix();
    glPushMatrix();//car2 ty3
    glColor3f(0.80,0.80,0.80);
    glRotated(230,0,1,0);
    glTranslated(-1.1,-0.5,-3.8);
    glScaled(1.0,0.7,0.5);
    glutSolidSphere(0.2,20,20);
    glPopMatrix();
    glPushMatrix();//car2 ty4
    glColor3f(0.80,0.80,0.80);
    glRotated(230,0,1,0);
    glTranslated(-0.5,-0.5,-3.8);
    glScaled(1.0,0.7,0.5);
    glutSolidSphere(0.2,20,20);
    glPopMatrix();
    glPushMatrix();//left building glass
    glColor3f(0.80,0.80,0.80);
    glRotated(230,0,1,0);
    glTranslated(1.5,-0.5,-0.95);
    glScaled(0.3,0.7,0.5);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();//right building glass
    glColor3f(0.80,0.80,0.80);
    glRotated(230,0,1,0);
    glTranslated(1.5,-0.5,0.8);
    glScaled(0.3,0.7,0.5);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();//light 2
    glColor3f(0.52,0.37,0.26);
    glRotated(230,0,1,0);
    glTranslated(2.5,-0.52,-4.5);
    glScaled(0.05,0.6,0.05);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();//light3
    glColor3f(0.52,0.37,0.26);
    glRotated(230,0,1,0);
    glTranslated(2.5,-0.52,-3.0);
    glScaled(0.05,0.6,0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();//light1
    glColor3f(0.52,0.37,0.26);
    glRotated(230,0,1,0);
    glTranslated(2.5,-0.52,-5.0);
    glScaled(0.05,0.6,0.05);
    glutSolidCube(1.0);
    glPopMatrix();

     glPushMatrix();//light4
    glColor3f(0.52,0.37,0.26);
    glRotated(230,0,1,0);
    glTranslated(2.5,-0.52,-3.5);
    glScaled(0.05,0.6,0.05);
    glutSolidCube(1.0);
    glPopMatrix();

     glPushMatrix();//light5
    glColor3f(0.52,0.37,0.26);
    glRotated(230,0,1,0);
    glTranslated(2.5,-0.52,-4.0);
    glScaled(0.05,0.6,0.05);
    glutSolidCube(1.0);
    glPopMatrix();

     glPushMatrix();//light6
    glColor3f(0.52,0.37,0.26);
    glRotated(230,0,1,0);
    glTranslated(2.5,-0.52,5.0);
    glScaled(0.05,0.6,0.05);
    glutSolidCube(1.0);
    glPopMatrix();

     glPushMatrix();//light7
    glColor3f(0.52,0.37,0.26);
    glRotated(230,0,1,0);
    glTranslated(2.5,-0.52,5.5);
    glScaled(0.05,0.6,0.05);
    glutSolidCube(1.0);
    glPopMatrix();

     glPushMatrix();//light8
    glColor3f(0.52,0.37,0.26);
    glRotated(230,0,1,0);
    glTranslated(2.5,-0.52,6.0);
    glScaled(0.05,0.6,0.05);
    glutSolidCube(1.0);
    glPopMatrix();

     glPushMatrix();//light9
    glColor3f(0.52,0.37,0.26);
    glRotated(230,0,1,0);
    glTranslated(2.5,-0.52,6.5);
    glScaled(0.05,0.6,0.05);
    glutSolidCube(1.0);
    glPopMatrix();

     glPushMatrix();//light10
    glColor3f(0.52,0.37,0.26);
    glRotated(230,0,1,0);
    glTranslated(2.5,-0.52,7.0);
    glScaled(0.05,0.6,0.05);
    glutSolidCube(1.0);
    glPopMatrix();

 glPushMatrix();//light11
    glColor3f(0.52,0.37,0.26);
    glRotated(230,0,1,0);
    glTranslated(2.5,-0.52,7.5);
    glScaled(0.05,0.6,0.05);
    glutSolidCube(1.0);
    glPopMatrix();

 glPushMatrix();//light12
    glColor3f(0.52,0.37,0.26);
    glRotated(230,0,1,0);
    glTranslated(2.5,-0.52,8.0);
    glScaled(0.05,0.6,0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();//light sphere2
    glColor3f(0.81,0.71,0.23);
    glRotated(230,0,1,0);
    glTranslated(2.5,-0.08,-4.5);
    glScaled(0.5,0.6,0.5);
    glutSolidSphere(0.4,25,25);
    glPopMatrix();

    glPushMatrix();//light sphere3
    glColor3f(0.81,0.71,0.23);
    glRotated(230,0,1,0);
    glTranslated(2.5,-0.08,-3.0);
    glScaled(0.5,0.6,0.5);
    glutSolidSphere(0.4,25,25);
    glPopMatrix();

    glPushMatrix();//lightsphere1
    glColor3f(0.81,0.71,0.23);
    glRotated(230,0,1,0);
    glTranslated(2.5,-0.08,-5.0);
    glScaled(0.5,0.6,0.5);
    glutSolidSphere(0.4,25,25);
    glPopMatrix();

    glPushMatrix();//light sphere4
    glColor3f(0.81,0.71,0.23);
    glRotated(230,0,1,0);
    glTranslated(2.5,-0.08,-3.5);
    glScaled(0.5,0.6,0.5);
    glutSolidSphere(0.4,25,25);
    glPopMatrix();

    glPushMatrix();//light sphere5
    glColor3f(0.81,0.71,0.23);
    glRotated(230,0,1,0);
    glTranslated(2.5,-0.08,-4.0);
    glScaled(0.5,0.6,0.5);
    glutSolidSphere(0.4,25,25);
    glPopMatrix();
    glPushMatrix();

    glPushMatrix();//lightsphere6
    glColor3f(0.81,0.71,0.23);
    glRotated(230,0,1,0);
    glTranslated(2.5,-0.08,5.0);
    glScaled(0.5,0.6,0.5);
    glutSolidSphere(0.4,25,25);
    glPopMatrix();

    glPushMatrix();//lightsphere7
    glColor3f(0.81,0.71,0.23);
    glRotated(230,0,1,0);
    glTranslated(2.5,-0.08,5.5);
    glScaled(0.5,0.6,0.5);
    glutSolidSphere(0.4,25,25);
    glPopMatrix();

    glPushMatrix();//lightsphere8
    glColor3f(0.81,0.71,0.23);
    glRotated(230,0,1,0);
    glTranslated(2.5,-0.08,6.0);
    glScaled(0.5,0.6,0.5);
    glutSolidSphere(0.4,25,25);
    glPopMatrix();

    glPushMatrix();//lightsphere9
    glColor3f(0.81,0.71,0.23);
    glRotated(230,0,1,0);
    glTranslated(2.5,-0.08,6.5);
    glScaled(0.5,0.6,0.5);
    glutSolidSphere(0.4,25,25);
    glPopMatrix();

    glPushMatrix();//lightsphere10
    glColor3f(0.81,0.71,0.23);
    glRotated(230,0,1,0);
    glTranslated(2.5,-0.08,7.0);
    glScaled(0.5,0.6,0.5);
    glutSolidSphere(0.4,25,25);
    glPopMatrix();

    glPushMatrix();//lightsphere11
    glColor3f(0.81,0.71,0.23);
    glRotated(230,0,1,0);
    glTranslated(2.5,-0.08,7.5);
    glScaled(0.5,0.6,0.5);
    glutSolidSphere(0.4,25,25);
    glPopMatrix();

    glPushMatrix();//lightsphere12
    glColor3f(0.81,0.71,0.23);
    glRotated(230,0,1,0);
    glTranslated(2.5,-0.08,8.0);
    glScaled(0.5,0.6,0.5);
    glutSolidSphere(0.4,25,25);
    glPopMatrix();

    glPushMatrix();//aero1
    glColor3f(1.0,1.0,1.0);
    glRotated(-90,1,0,0);
    glTranslated(-2.0,2.7,-0.4);
    glScaled(0.5,2.0,0.5);
    glutSolidSphere(0.4,30,30);
    glPopMatrix();

    glPushMatrix();//aero2
    glColor3f(1.0,1.0,1.0);
    glRotated(-90,1,0,0);
    glTranslated(-3.5,2.7,-0.4);
    glScaled(0.5,2.0,0.5);
    glutSolidSphere(0.4,30,30);
    glPopMatrix();

    glPushMatrix();//left plane back wings
    glColor3f(0.80,0.80,0.80);
    glRotated(20,1,0,0);
    glTranslated(-2.0,-1.5,-2.8);
    glScaled(0.5,0.05,0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();//right plane back wings
    glColor3f(0.80,0.80,0.80);
    glRotated(20,1,0,0);
    glTranslated(-3.5,-1.5,-2.8);
    glScaled(0.5,0.05,0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();//left plane front wings
    glColor3f(0.80,0.80,0.80);
    glRotated(20,1,0,0);
    glTranslated(-2.0,-1.2,-2.0);
    glScaled(1.3,0.05,0.3);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();//right plane front wings
    glColor3f(0.80,0.80,0.80);
    glRotated(20,1,0,0);
    glTranslated(-3.5,-1.3,-2.5);
    glScaled(1.3,0.05,0.3);
    glutSolidCube(1.0);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
}
int theta[5]={0};

void lighting()
{
	GLfloat mat_ambient[] = { 2, 2, 0.8, 1 };
	GLfloat mat_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat mat_specular[] = { 2, 2, 2, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
    GLfloat mat_emission[] = {0.5, 0.5, 0.0, 1.0};
    GLfloat lightintensity[] = { 1, 1, 0.7, 1.0 };
	GLfloat lightPosition[] = { 3900, 8900, 3900, 0 };
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glLightfv(GL_LIGHT0, GL_AMBIENT, mat_ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, lightintensity);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightintensity);
    GLfloat materialEmission[] = {1.0f,1.0f,0, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, materialEmission);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
    // Render a color-cube consisting of 6 quads with different colors
	glLoadIdentity();                // Reset the model-view matrix
    //set the camera
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-winHt*64/48.0,winHt*64/48.0,-winHt,winHt,0.1,100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(10.5,10.3,20.0,0.0,0.25,0.0,0.0,100.0,0.0);

    glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 1.0, 0.0, 0.0);
	glRotatef(theta[2], 0.0, 1.0, 0.0);
	glRotatef(theta[3], 0.0, 1.0, 0.0);
    glPushMatrix();
    glPushMatrix();
    glColor3f(0.0,0.0,0.0);
    glScalef(1,1,0);
    glRasterPos3f(-3,9,0.8);
    for(i=0;s[i]!='\0';i++)
    glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-11.5,0.1,0.8);
    glScalef(0.5,0.5,0);//left tree
    glCallList(makeaTree);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-11.5,0.1,4.5);
    glScalef(0.5,0.5,0);//left tree
    glCallList(makeaTree);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-11.5,0.1,12.5);
    glScalef(0.5,0.5,0);//left tree
    glCallList(makeaTree);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-11.5,0.1,-9.5);
    glScalef(0.5,0.5,0);//left tree
    glCallList(makeaTree);
    glPopMatrix();

     glPushMatrix();
    glTranslatef(-11.5,0.1,-4.5);
    glScalef(0.5,0.5,0);//left tree
    glCallList(makeaTree);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3,0.7,-15.8);
    glScalef(0.5,0.5,0);
    glCallList(makeaTree);
    glPopMatrix();
    glPushMatrix();//tree3
    glTranslatef(-3,0.7,-13.8);
    glScalef(0.5,0.5,0);
    glCallList(makeaTree);
    glPopMatrix();
     glPushMatrix();//tree3
    glTranslatef(-2,0.7,-11.8);
    glScalef(0.5,0.5,0);
    glCallList(makeaTree);
    glPopMatrix();

    glPushMatrix();
    glRotatef(30,0.0,0.8,0.0);
    glScaled(1.5,1.3,1.5);
    drawobjects();
    glPopMatrix();
    glPopMatrix();
    glFlush();
	glutSwapBuffers();

}
void mouse(int btn,int state,int x,int y)
{
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
winHt+=0.5;
if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    winHt-=0.5;
glutPostRedisplay();
}
void keyboard(unsigned char key,int x,int y)
{
    if(key=='w')
    {theta[0] += 5.0;
	if( theta[0] > 45.0 ) theta[0] -= 45.0;
	glutPostRedisplay();
    }
    else

    if(key=='s')
    {theta[0] -= 5.0;
	if( theta[0] > 45.0 || theta[0] < -20 ) theta[0] = 0.0;
	glutPostRedisplay();
    }
    else

    if(key=='a')
    {theta[2] -= 8.0;
	if( theta[2] > 360.0 ) theta[2] -= 360.0;
	glutPostRedisplay();
    }
    else

    if(key=='d')
    {theta[3] += 8.0;
	if( theta[3] > 360.0  ) theta[3] -= 360.0;
	glutPostRedisplay();
    }

}
static void idle(void)
{
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
   glutInit(&argc,argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(1400,700);
   glutInitWindowPosition(0,0);
   glutCreateWindow("3D Airport");
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   glutMouseFunc(mouse);
   glutIdleFunc(idle);
   glEnable(GL_NORMALIZE);
    glutTimerFunc( 10, TimeEvent, 1);
    glGenTextures(10,texture);
    loadTexture("D:\\Airport\\glass1.bmp",1);
    loadTexture("D:\\Airport\\logo.bmp",2);
    glEnable(GL_COLOR_MATERIAL);


    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);


   glEnable(GL_DEPTH_TEST);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   initGL();
   glutMainLoop();
   return 0;

}
