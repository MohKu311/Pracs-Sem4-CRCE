#include <Windows.h>

#include <GL/GLU.h>
#include <GL/gl.h>
#include <gl/glut.h>

void BressenhamMLess1(int x0, int y0, int xn, int yn)
{
   int dx = xn - x0;
   int dy = yn - y0;

   // Get if Increment is Positive or Negative
   int x_inc = dx / abs(dx);
   int y_inc = dy / abs(dy);

   // Calculate Initial Integral Decision Parameter
   int decision = 2 * abs(dy) - abs(dx);

   int x = x0;
   int y = y0;

   // Use pixel plotting in glBegin and glEnd
   glBegin(GL_POINTS);
   // Go from x0 point to xn point
   // In m < 1, it is X point that increases
   // While Y point that we have to choose upon
   glVertex2i(x0, y0);
   for (int i = 0; i <= abs(dx); ++i)
   {
      // If the Decision is Negative,
      // Choose Lower Point
      // As a result do NOT increment y
      if (decision < 0)
      {
         x = x + x_inc;
         y = y + 0;
         decision = decision + 2 * abs(dy);
      }
      else
      {
         x = x + x_inc;
         y = y + y_inc;
         decision = decision + 2 * abs(dy) - 2 * abs(dx);
      }
      glVertex2i(x, y);
   }
   // glVertex2f(x,y); //Sample for ploting pixel at (x,y)
   glEnd();
}
void disp()
{
   glClearColor(1, 1, 1, 1);
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0, 0, 0);
   // call your function define at beginning
   // for example WriteFunctionName();
   // Draw a Line at Angle of 30 Degrees
   BressenhamMLess1(173, 100, 0, 0);
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