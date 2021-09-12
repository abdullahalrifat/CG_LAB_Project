#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include <time.h>

float speedOfHero    = 5;//hero
float speedOfBullet   = 5;//bullet
float speedOfEnemy     = 0.05;//enemy
float rotationspeedOfBullet = 0.1;//Replace value here
float r,g,bl;

int newPlane = 0;
int bulletStatus = 0;

int enemyPosition;

typedef struct Point{
    float x=0;
    float y=0;
    float z=0;
    bool draw=true;;
}Point;

Point positionOfHero = {0,-95,0}; //hero
Point positionOfBullet = {0,-95,0}; //bullet
Point positionOfEnemy = {0,95,0}; //enemy
Point positionOfEnemy2 = {0,95,0}; //enemy

Point enemy[100];
Point bullets[1000];
float angleOfSquare =0;


void drawCirle(float radius){
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
        for(int i=0;i<360;i++){
            glVertex2f(radius*cos(i),radius*sin(i));
        }
    glEnd();
}

void drawHero(float hight){
   glBegin(GL_TRIANGLES);
            glColor3f(0.3,0.4,0.3);
            int a,b;
            a = hight;
            b = (hight/10)*7;
            glVertex2f(0,a);
            glVertex2f(b,0);
            glVertex2f(-b,0);
    glEnd();
}

void drawBorder(float hight){
   glBegin(GL_TRIANGLES);
            glColor3f(0,0,0);
            int a,b;
            a = hight;
            b = (hight/10)*7;
            glVertex2f(0,-a);
            glVertex2f(b,0);
            glVertex2f(-b,0);
    glEnd();
}

void drawEnemy(float hight, int index){
    
    glBegin(GL_TRIANGLES);
    if(enemy[index].draw)
    {
            r= static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            g= static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            bl= static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            enemy[index].draw = false;   
    }
        glColor3f(r,g,bl);
            int a,b;
            a = hight;
            b = (hight/10)*7;
            glVertex2f(0,-a);
            glVertex2f(b,0);
            glVertex2f(-b,0);    
    glEnd();
   
}

void drawAxes(){
    glColor3f(1,1,1);
    glBegin(GL_LINES);
        glVertex2f(-100,0);
        glVertex2f( 100,0);

        glVertex2f(0,-100);
        glVertex2f(0, 100);
    glEnd();
}

void drawSquare(float length){
    glColor3f(0.9,0.0,0.0);
    glBegin(GL_QUADS);
        glVertex2f(-length/2,-length/2);
        glVertex2f(length/2,-length/2);
        glVertex2f(length/2,length/2);
        glVertex2f(-length/2,length/2);
    glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();

    positionOfBullet.x = positionOfHero.x;
    glPushMatrix();
                glTranslated(positionOfBullet.x,positionOfBullet.y,0);
                glRotated(angleOfSquare,0,0,1);
                drawSquare(2);
                glPopMatrix();

    // drawing hero
	glPushMatrix();
        glTranslated(positionOfHero.x,positionOfHero.y,0);
        drawCirle(1);

        glPushMatrix();
            drawHero(15);
        glPopMatrix();
    glPopMatrix();

    
    // for(int enemy_count=0; enemy_count <100; enemy_count++)
    // {
    //    enemy[enemy_count].y = positionOfEnemy.y + (enemy_count * 1000);
    //    glPushMatrix();
    //         glTranslatef(enemy[enemy_count].x,enemy[enemy_count].y,enemy[enemy_count].z);
    //         drawEnemy(14, enemy_count);
    //     glPopMatrix();
    // }     
    for(int i=0;i<3;i++)
    {
         glPushMatrix();
            glTranslatef(enemy[i].x,enemy[i].y,enemy[i].z);
            drawEnemy(14, i);
        glPopMatrix();
    }
        
	glFlush();
    glutSwapBuffers();
}

void bulletFire(void)
{
    positionOfBullet.y += .1;
    glutPostRedisplay();
}

void spinDisplay_right(void)
{
    angleOfSquare -= rotationspeedOfBullet;
    glutPostRedisplay();
}

void moveLeft(){
    positionOfEnemy.x -= speedOfEnemy;
    positionOfBullet.x -= speedOfBullet;
}

void moveRight(){
    positionOfEnemy.x += speedOfEnemy;
    positionOfBullet.x += speedOfBullet;
}

void moveUp(){
    positionOfEnemy.y += speedOfEnemy;
    positionOfBullet.y += speedOfBullet;
}

void moveDown(){
    positionOfEnemy.y -= speedOfEnemy;
    positionOfBullet.y -= speedOfBullet;
}

void animate(){
    
    for(int enemy_count=0;enemy_count<100;enemy_count++)
    {
        enemy[enemy_count].y -= speedOfEnemy;
        if(enemy[enemy_count].y < -100)
        {
            enemy[enemy_count].y =  positionOfEnemy.y + (enemy_count*10);
            enemy[enemy_count].x =  (rand()%190)-90;
            enemy[enemy_count].draw = true;
        }
    }
    // enemy[0].y -= speedOfEnemy; 
    // if(enemy[0].y < -100)  
    // {
    //     enemy[0].y =  positionOfEnemy.y;
    //     enemy[0].draw = true;
    // }
    if(bulletStatus==1){
        positionOfBullet.y += 0.1;
    }
    
    glutPostRedisplay();
}

void init(void)
{
	glClearColor (1, 1, 1, 0.0);
	glOrtho(-100.0, 100.0, -100.0,100.0, 0.0, 1.0);
    for(int i=0;i<100;i++)
    {
         enemy[i].x =  (rand()%190)-90;
         enemy[i].y =  positionOfEnemy.y + (i*10);
    }
    for(int i=0;i<1000;i++)
    {
        bullets[i].x=positionOfHero.x;
    }
}


void my_keyboard(unsigned char key, int x, int y)
{

	switch (key) {

		case 'l':
			moveLeft();
			break;

		case 'r':
			moveRight();
			break;

		case 'u':
			 moveUp();
			 break;

        case 'd':
			 moveDown();
			 break;

	  default:
			break;
	}
	glFlush();
}

void spe_key(int key, int x, int y)
{

	switch (key) {

		case GLUT_KEY_UP:
				positionOfHero.y += speedOfHero;
				glutPostRedisplay();
				break;



		case GLUT_KEY_DOWN:
				positionOfHero.y -= speedOfHero;
				glutPostRedisplay();
				break;

        case GLUT_KEY_RIGHT:
				positionOfHero.x += speedOfHero;
				glutPostRedisplay();
				break;



		case GLUT_KEY_LEFT:
		        positionOfHero.x -= speedOfHero;
				glutPostRedisplay();
				break;



        default:
                break;
	}
}


void my_mouse(int button, int state, int x, int y)
{
   switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN){
                bulletStatus = 1;
                positionOfBullet.x = positionOfHero.x;

         }
         break;
//      case GLUT_RIGHT_BUTTON:
//         if (state == GLUT_DOWN)
//            glutIdleFunc(spinDisplay_right);
//         break;
//      case GLUT_MIDDLE_BUTTON:
//        glutIdleFunc(NULL);
//      default:
//         break;
   }
}

int main(int argc, char *argv[])
{
    glutInit( & argc, argv );

	glutInitWindowSize (700, 700);
	glutInitWindowPosition (10, 10);

	glutCreateWindow ("Air Fighter");
	init();

    
    glutDisplayFunc(display);
	//glutKeyboardFunc(my_keyboard);
	glutSpecialFunc(spe_key);
	glutMouseFunc(my_mouse);
	glutIdleFunc(animate);


	glutMainLoop();
	return 0;
}
