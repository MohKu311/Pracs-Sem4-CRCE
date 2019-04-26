#include<Windows.h>
#include<GL/gl.h>
#include<GL/GLU.h>
#include<gl/glut.h>

void BressenhamMGreater1 (int x0, int y0, int xn, int yn)
{
   int dx = xn - x0;
   int dy = yn - y0;

   // Get if Increment is Positive or Negative
   int x_inc = dx / abs (dx);
   int y_inc = dy / abs (dy);

   // Calculate Decision Parameter
   int decision = 2 * abs (dx) - abs (dy);

   int x = x0;
   int y = y0;

   //Use pixel plotting in glBegin and glEnd
   glBegin (GL_POINTS);

   glVertex2i (x0, y0);
   for (int i = 0; i < abs (dy); ++i)
   {
      if (decision < 0)
      {
         x = x + 0;
         y = y + y_inc;
         decision = decision + 2 * abs (dx);
      }
      else
      {
         x = x + x_inc;
         y = y + y_inc;
         decision = decision + 2 * abs (dx) - 2 * abs (dy);
      }
      glVertex2i (x, y);
   }

   //glVertex2f(x,y); //Sample for ploting pixel at (x,y)
   glEnd ();
}
void disp ()
{
   glClearColor (1, 1, 1, 1);
   glClear (GL_COLOR_BUFFER_BIT);
   glColor3f (0, 0, 0);
   //call your function define at beginning
   //for example WriteFunctionName();
   // Draw a Line at Angle of 60 Degrees
   BressenhamMGreater1 (0, 0, 100, 173);
   glFlush ();
}//disp
int main (int argv, char** argc)
{
   glutInit (&argv, argc);
   glutInitWindowSize (300, 300);
   glutCreateWindow ("window");
   gluOrtho2D (0, 300, 0, 300);
   glutDisplayFunc (disp);
   glutMainLoop ();
   return 0;

}