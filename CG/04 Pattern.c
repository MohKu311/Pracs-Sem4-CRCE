#include <GL/GL.h>
#include <GL/GLU.h>
#include <GL/glut.h>
#include <Windows.h>

#include <stdio.h>
void DDA(int x0, int y0, int xn, int yn)
{
   int dx = xn - x0;
   int dy = yn - y0;

   int step = max(abs(dx), abs(dy));
   float x_inc = dx / (float)step;
   float y_inc = dy / (float)step;

   float x = x0;
   float y = y0;
   glBegin(GL_POINTS);
   for (int i = 0; i < step; ++i)
   {
      x = x + x_inc;
      y = y + y_inc;
      glVertex2f(x, y);
   }

   // glVertex2f(x,y); //Sample for ploting pixel at (x,y)
   glEnd();
}

void DrawPattern(int x0, int y0, int x_inc, int y_inc, int count)
{
   // Note that if x0 is 30
   // And x_inc is 20
   // We first Draw a Line from 30 to 50
   // Then from 50 to 70
   // In X Axis
   for (int i = 0; i < count; ++i)
   {
      DDA(x0, y0, x0 + x_inc, y0 + y_inc);
      x0 = x0 + x_inc;
      DDA(x0, y0 + y_inc, x0 + x_inc, y0);
      x0 = x0 + x_inc;
   }
}

void disp(void)
{
   glClearColor(0, 0, 0, 1);
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(1, 1, 1);
   // We Need to Draw A Weird Kind of Pattern.
   // As such let us choose a few points to draw it on

   // Let us draw it at (0,0) -> (30,30) -> (60, 0) -> (90, 30) -> (120, 0)
   // As such we first set Position at Origin
   // And then Add and Subtract the x_inc and y_inc
   DrawPattern(0, 100, 30, 30, 5);
   glFlush();
} // disp
int main(int argv, char** argc)
{
   glutInit(&argv, argc);
   glutInitWindowSize(300, 300);
   glutCreateWindow("window");
   gluOrtho2D(0, 300, 0, 300);
   glutDisplayFunc(disp);
   glutMainLoop();
   return 0;
}