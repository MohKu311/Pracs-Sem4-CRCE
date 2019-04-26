#include <GL/GL.h>
#include <GL/GLU.h>
#include <Windows.h>
#include <gl/glut.h>

#include <math.h>

void Translate(float points[][3], int countPoints, float tx, float ty)
{
   for (int i = 0; i < countPoints; ++i)
   {
      // X
      points[i][0] = points[i][0] + tx;
      // Y
      points[i][1] = points[i][1] + ty;
   }
}
float DegreeToRadian(float angle)
{
   return (angle / 180.0) * 3.14159;
}

void FullCircle(int r, int xc, int yc, int angle)
{
   float matrix[800][3];

   int count = 1;

   // Approx 5/4 = 1
   int decision = 1 - r;
   int x = 0;
   int y = r;

   // First Point
   matrix[0][0] = 0; // X
   matrix[0][1] = r; // Y
   matrix[0][2] = 1;

   while (x <= y)
   {
      if (decision < 0)
      {
         decision = decision + 2 * x + 3;
         x = x + 1;
         y = y;
      }
      else
      {
         decision = decision + 2 * x - 2 * y + 5;
         x = x + 1;
         y = y - 1;
      }
      matrix[count][0] = x;
      matrix[count][1] = y;
      matrix[count][2] = 1;
      ++count;
      matrix[count][0] = y;
      matrix[count][1] = x;
      matrix[count][2] = 1;
      ++count;
      matrix[count][0] = -x;
      matrix[count][1] = y;
      matrix[count][2] = 1;
      ++count;
      matrix[count][0] = -y;
      matrix[count][1] = x;
      matrix[count][2] = 1;
      ++count;
      matrix[count][0] = -x;
      matrix[count][1] = -y;
      matrix[count][2] = 1;
      ++count;
      matrix[count][0] = -y;
      matrix[count][1] = -x;
      matrix[count][2] = 1;
      ++count;
      matrix[count][0] = x;
      matrix[count][1] = -y;
      matrix[count][2] = 1;
      ++count;
      matrix[count][0] = y;
      matrix[count][1] = -x;
      matrix[count][2] = 1;
      ++count;
   }

   Translate(matrix, count, xc, yc);

   // Use pixel plotting in glBegin and glEnd
   glBegin(GL_POINTS);
   for (int i = 0; i < count; ++i)
      glVertex2f(matrix[i][0] /*X*/, matrix[i][1] /*Y*/);
   // glVertex2f(x,y); //Sample for ploting pixel at (x,y)
   glEnd();
}
void DrawPattern(int x0, int y0)
{
   // Draw Full Face
   FullCircle(80, x0, y0, 0);
   // Draw Eyes
   FullCircle(15, x0 + 25, y0 + 25, 0);
   FullCircle(15, x0 - 25, y0 + 25, 0);
   // Draw Mouth
   FullCircle(25, x0, y0 - 35, 0);
}
void disp()
{
   glClearColor(1, 1, 1, 1);
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0, 0, 0);
   // call your function define at beginning
   // for example WriteFunctionName();
   DrawPattern(0, 0);
   glFlush();
} // disp
int main(int argv, char** argc)
{
   glutInit(&argv, argc);
   glutInitWindowSize(300, 300);
   glutCreateWindow("window");
   gluOrtho2D(-150, 150, -150, 150);
   glutDisplayFunc(disp);
   glutMainLoop();
   return 0;
}