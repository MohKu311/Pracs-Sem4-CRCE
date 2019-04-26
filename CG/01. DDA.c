#include <GL/GL.h>
#include <GL/GLU.h>
#include <GL/glut.h>
#include <Windows.h>

void DDA(int x0, int y0, int xn, int yn)
{
   // Use pixel plotting in glBegin and glEnd
   glBegin(GL_POINTS);
   int dx = xn - x0;
   int dy = yn - y0;

   int step = max(abs(dx), abs(dy));
   float x_inc = dx / (float)step;
   float y_inc = dy / (float)step;

   float x = x0;
   float y = y0;
   for (int i = 0; i < step; ++i)
   {
      x = x + x_inc;
      y = y + y_inc;
      glVertex2f(x, y);
   }

   // glVertex2f(x,y); //Sample for ploting pixel at (x,y)
   glEnd();
}
void disp(void)
{
   glClearColor(0, 0, 0, 1);
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(1, 1, 1);
   DDA(0, 0, 100, 100);
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