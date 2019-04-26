#include <GL/GLU.h>
#include <GL/gl.h>
#include <Windows.h>
#include <gl/glut.h>

#include <math.h>
#include <stdio.h>

void MatrixMultiply(float left[][3], float right[3][3], float result[][3], int leftRows)
{
   // Left has 3 Cols
   // Right has 3 Rows and 3 Cols
   for (int rL = 0; rL < leftRows; ++rL)
   {
      for (int cR = 0; cR < 3; ++cR)
      {
         result[rL][cR] = 0;
         for (int cLrR = 0; cLrR < 3; ++cLrR)
         {
            result[rL][cR] += left[rL][cLrR] * right[cLrR][cR];
         }
      }
   }
}

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

void Rotate(float points[][3], int countPoints, double angle, float result[][3])
{
   angle = (angle / 180.0) * 3.14159;
   float rotationMatrix[3][3] = {{cos(angle), sin(angle), 0}, {-sin(angle), cos(angle), 0}, {0, 0, 1}};
   MatrixMultiply(points, rotationMatrix, result, countPoints);
}

void SemiCircle(int r, int xc, int yc, int angle)
{
   float matrix[1000][3];

   // Approx 5/4 = 1
   int decision = 1 - r;
   int x = 0;
   int y = r;

   // First Point
   matrix[0][0] = 0; // X
   matrix[0][1] = r; // Y
   matrix[0][2] = 1;

   int count = 1;
   while (x <= y)
   {
      if (decision < 0)
      {
         decision = decision + 2 * x + 3;
         x = x + 1;
         y = y + 0;
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
   }

   float result[300][3];
   Rotate(matrix, count, angle, result);
   Translate(result, count, xc, yc);

   // Use pixel plotting in glBegin and glEnd
   glBegin(GL_POINTS);
   for (int i = 0; i < count; ++i)
      glVertex2f(result[i][0] /*X*/, result[i][1] /*Y*/);
   // glVertex2f(x,y); //Sample for ploting pixel at (x,y)
   glEnd();
}
void DrawPattern(int x0, int y0, int radius, int counts)
{
   int angle = 0;
   for (int i = 1; i <= counts; ++i)
   {
      SemiCircle(radius, x0, y0, angle);
      angle = (angle + 180) % 360;
      x0 = x0 + 2 * radius;
   }
}
void disp()
{
   glClearColor(1, 1, 1, 1);
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0, 0, 0);
   // call your function define at beginning
   // for example WriteFunctionName();
   DrawPattern(0, 0, 20, 3);
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