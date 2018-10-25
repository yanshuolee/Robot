#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "glm.h"
#include <stdio.h>
#include<mmsystem.h>
#include "CMP3_MCI.h"
CMP3_MCI myMP3;
GLUquadric * quad;
GLuint id;
GLMmodel* pmodel = NULL;
GLMmodel* pmode2 = NULL;
GLMmodel* pmode3 = NULL;
GLMmodel* pmode4 = NULL;
GLMmodel* pmode5 = NULL;
GLMmodel* pmode6 = NULL;

float angle[9]={0};
float oldAngle[9]={0,0,0,14,0,0,0,0,0};
float newAngle[9]={0,0,0,0,14,0,0,0,0};
float alpha = 0.0;

float angle1=0;
void interpolation()
{
    for(int i=0;i<9;i++){
        angle[i]=alpha*newAngle[i]+(1-alpha)*oldAngle[i];
    }
    alpha+=0.1;
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glPushMatrix();
        glBegin(GL_POLYGON);
            glTexCoord2f(0,0); glVertex3f(-1,+1,0);
            glTexCoord2f(1,0); glVertex3f(+1,+1,0);
            glTexCoord2f(1,1); glVertex3f(+1,-1,0);
            glTexCoord2f(0,1); glVertex3f(-1,-1,0);
        glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glPushMatrix();///start
        //angle+=0.5;
        //glRotatef(angle,0,1,0);
        if (!pmodel) {
        pmodel = glmReadOBJ("data/head.obj");
        if (!pmodel) exit(0);
        glmUnitize(pmodel);
        glmFacetNormals(pmodel);
        glmVertexNormals(pmodel, 90.0);
        }

        if (!pmode2) {
        pmode2 = glmReadOBJ("data/neck.obj");
        if (!pmode2) exit(0);
        glmUnitize(pmode2);
        glmFacetNormals(pmode2);
        glmVertexNormals(pmode2, 90.0);
        }

        if (!pmode3) {
        pmode3 = glmReadOBJ("data/body.obj");
        if (!pmode3) exit(0);
        glmUnitize(pmode3);
        glmFacetNormals(pmode3);
        glmVertexNormals(pmode3, 90.0);
        }

        if (!pmode4) {
        pmode4 = glmReadOBJ("data/righthand.obj");
        if (!pmode4) exit(0);
        glmUnitize(pmode4);
        glmFacetNormals(pmode4);
        glmVertexNormals(pmode4, 90.0);
        }

        if (!pmode5) {
        pmode5 = glmReadOBJ("data/lefthand.obj");
        if (!pmode5) exit(0);
        glmUnitize(pmode5);
        glmFacetNormals(pmode5);
        glmVertexNormals(pmode5, 90.0);
        }

        if (!pmode6) {
        pmode6 = glmReadOBJ("data/leg.obj");
        if (!pmode6) exit(0);
        glmUnitize(pmode6);
        glmFacetNormals(pmode6);
        glmVertexNormals(pmode6, 90.0);
        }
        /*------------------------------------------------*/
        glPushMatrix();///head
            glTranslatef(0,0.5,0);
            glRotatef(180,0,1,0);
            glRotatef(angle[2],0,0,1);
            glScalef(0.3,0.3,0.3);
            glmDraw(pmodel, GLM_SMOOTH | GLM_MATERIAL);
        glPopMatrix();///head

        glPushMatrix();///neck
            glTranslatef(0,0.3,0);
            glScalef(0.05,0.05,0.05);
            glmDraw(pmode2, GLM_SMOOTH | GLM_MATERIAL);
        glPopMatrix();///neck

        glPushMatrix();///body

            glPushMatrix();
                glScalef(0.3,0.3,0.3);
                glRotatef(++angle1,0,1,0);
                glmDraw(pmode3, GLM_SMOOTH | GLM_MATERIAL);
            glPopMatrix();

glPushMatrix();
            glTranslatef(0.1,0.08,0);///T
            glRotatef(angle[0],0,0,1);///R
            glTranslatef(0.2,-0.1,0);///T
            glPushMatrix();///right hand
                //glTranslatef(0.3,-0.01,0);
                glScalef(0.3,0.3,0.3);
                glmDraw(pmode4, GLM_SMOOTH | GLM_MATERIAL);
            glPopMatrix();///right hand
glPopMatrix();
            glTranslatef(-0.15,0.08,0);///T
            glRotatef(-angle[1],0,0,1);///R
            glTranslatef(-0.2,-0.1,0);///T
            glPushMatrix();///left hand
                //glTranslatef(-0.3,0.08,0);
                glScalef(0.3,0.3,0.3);
                glmDraw(pmode5, GLM_SMOOTH | GLM_MATERIAL);
            glPopMatrix();///left hand

        glPopMatrix();///body


        glPushMatrix();///left leg
            glTranslatef(-0.1,-0.3,0);
            glRotatef(angle[3],1,0,0);
            glScalef(0.3,0.3,0.3);
            glmDraw(pmode6, GLM_SMOOTH | GLM_MATERIAL);
        glPopMatrix();///left leg

        glPushMatrix();///right leg
            glTranslatef(0.1,-0.3,0);
            if(angle[4]<-14.000){

            }
            glRotatef(angle[4],1,0,0);
            glScalef(0.3,0.3,0.3);
            glmDraw(pmode6, GLM_SMOOTH | GLM_MATERIAL);
        glPopMatrix();///right leg

    glPopMatrix();///end

    glutSwapBuffers();
}
int myTexture(char *filename)
{
    IplImage * img = cvLoadImage(filename); ///OpenCV讀圖
    cvCvtColor(img,img, CV_BGR2RGB); ///OpenCV轉色彩 (需要cv.h)
    glEnable(GL_TEXTURE_2D); ///1. 開啟貼圖功能
    GLuint id; ///準備一個 unsigned int 整數, 叫 貼圖ID
    glGenTextures(1, &id); /// 產生Generate 貼圖ID
    glBindTexture(GL_TEXTURE_2D, id); ///綁定bind 貼圖ID
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); /// 貼圖參數, 超過包裝的範圖T, 就重覆貼圖
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); /// 貼圖參數, 超過包裝的範圖S, 就重覆貼圖
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); /// 貼圖參數, 放大時的內插, 用最近點
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); /// 貼圖參數, 縮小時的內插, 用最近點
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 0, GL_RGB, GL_UNSIGNED_BYTE, img->imageData);
    return id;
}
void myInit()
{   quad = gluNewQuadric();
    id = myTexture("image.jpg");
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, -5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };


int oldx=0,oldy=0;
int now=0;
/*void mouse (int button,int state,int x,int y)
{
    oldx=x; oldy=y;
    glutPostRedisplay();
}*/
/*void motion(int x,int y)
{
    angle[now] += (x-oldx);
    oldx=x;
    glutPostRedisplay();
}*/
FILE * fout=NULL;
FILE * fin=NULL;
/*void keyboard(unsigned char key,int x,int y)
{
    if(key=='0') now=0;
    if(key=='1') now=1;
    if(key=='2') now=2;
    if(key=='3') now=3;
    if(key=='4') now=4;
    if(key=='q') {
        if(fout==NULL){
            fout=fopen("file.txt","w+");
        }
        fprintf(fout,"%.2f %.2f %.2f %.2f %.2f\n",angle[0],angle[1],angle[2],angle[3],angle[4]);
    }

    if(key=='z') {
        if(fin==NULL){
            fin=fopen("file.txt","r");
            fscanf(fin,"%f %f %f %f %f\n",&newAngle[0],&newAngle[1],&newAngle[2],&newAngle[3],&newAngle[4]);
        }
        if(alpha>=1.0){
            for (int i=0;i<9;i++) oldAngle[i]=newAngle[i];
            fscanf(fin,"%f %f %f %f %f\n",&newAngle[0],&newAngle[1],&newAngle[2],&newAngle[3],&newAngle[4]);
            alpha=0.0;
        }

        for(int i=0;i<9;i++){
            angle[i]=alpha*newAngle[i]+(1-alpha)*oldAngle[i];
        }
        alpha+=0.1;

        glutPostRedisplay();
    }

}*/
void timer(int t)
{
		glutTimerFunc(5,timer,t+1);
        if(fin==NULL){
            fin=fopen("file.txt","r");
            fscanf(fin,"%f %f %f %f %f\n",&newAngle[0],&newAngle[1],&newAngle[2],&newAngle[3],&newAngle[4]);
        }

        if(alpha>=1.0){
            for (int i=0;i<9;i++) oldAngle[i]=newAngle[i];
            fscanf(fin,"%f %f %f %f %f\n",&newAngle[0],&newAngle[1],&newAngle[2],&newAngle[3],&newAngle[4]);
            alpha=0.0;
            if(newAngle[0]==1){
                printf("\nThank you for watching!!!\n");
                printf("Thank you for watching!!!\n");
                printf("Thank you for watching!!!\n");
                exit(0);
            }
        }

        for(int i=0;i<9;i++){
            angle[i]=alpha*newAngle[i]+(1-alpha)*oldAngle[i];
        }
        alpha+=0.01;

        glutPostRedisplay();
}
int main(int argc, char**argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutCreateWindow("Patrick Lee ;>");
    myMP3.Load("music1.mp3");
    myMP3.Play();

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutTimerFunc(100,timer,0);


    glClearColor(1,1,1,1);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

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

    myInit(); ///我的 init 初始化 把貼圖準備好 前面OpenCV 2行, 後面 OpenGL 9行
    ///must before mainloop
    glutMainLoop();
}
