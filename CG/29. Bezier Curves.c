#include <Windows.h>

#include <GL/GLU.h>
#include <GL/gl.h>
#include <gl/glut.h>
#include <math.h>
#include <stdio.h>

double Combination(int n, int r)
{
   double res = 1;
   for (int i = n; i >= (n - r + 1); --i)
      res *= i;
   for (int i = r; i >= 2; --i)
      res /= i;
   return res;
}

void BezierCurves(int points[][2], int n)
{
   // Use pixel plotting in glBegin and glEnd
   glBegin(GL_POINTS);

   // Formula is
   // XPoint = Combination of (No Of Points-1, Index) * power(u, Index) * power( u, No Of Points - 1 - Index) * X at
   // Index
   for (double u = 0.000; u <= 1; u += 0.0001)
   {
      double xp = 0;
      double yp = 0;
      for (int k = 0; k < n; ++k)
      {
         xp += Combination(n - 1, k) * pow(u, k) * pow(1 - u, n - k - 1) * points[k][0] /*X*/;
         yp += Combination(n - 1, k) * pow(u, k) * pow(1 - u, n - k - 1) * points[k][1] /*Y*/;
      }
      glVertex2d(xp, yp);
   }

   // glVertex2f(x,y); //Sample for ploting pixel at (x,y)
   glEnd();
}
void disp(void)
{
   glClearColor(1, 1, 1, 1);
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0, 0, 0);
   int points[][2] = {
       {150 + 0, 150 + 0}, {150 + 30, 150 + 30}, {150 + 0, 150 + 60}, {150 - 30, 150 + 30}, {150 + 0, 150 + 0}};
   BezierCurves(points, 5);
   // call your function define at beginning
   // for example WriteFunctionName();
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