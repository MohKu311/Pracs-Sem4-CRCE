#include <Windows.h>

#include <GL/GL.h>
#include <GL/GLU.h>
#include <gl/glut.h>

#include <math.h>

typedef struct
{
   int X;
   int Y;
} Point;

// Translate Given Matrix
void Translate(Point points[], int count, Point translate)
{
   for (int i = 0; i < count; ++i)
   {
      points[i].X = points[i].X + translate.X;
      points[i].Y = points[i].Y + translate.Y;
   }
}
Point PointAt(int const X, int const Y)
{
   Point point;
   point.X = X;
   point.Y = Y;
   return point;
}

void FullCircle(int r, Point center)
{
   Point points[800];

   // Approx 5/4 = 1
   int decision = 1 - r;
   int x = 0;
   int y = r;

   // First Point
   points[0] = PointAt(0, r);

   int count = 1;
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
      points[count] = PointAt(x, y);
      ++count;
      points[count] = PointAt(y, x);
      ++count;
      points[count] = PointAt(-x, y);
      ++count;
      points[count] = PointAt(-y, x);
      ++count;
      points[count] = PointAt(-x, -y);
      ++count;
      points[count] = PointAt(-y, -x);
      ++count;
      points[count] = PointAt(x, -y);
      ++count;
      points[count] = PointAt(y, -x);
      ++count;
   }

   Translate(points, count, center);

   // Use pixel plotting in glBegin and glEnd
   glBegin(GL_POINTS);
   for (int i = 0; i < count; ++i)
   {
      glVertex2f(points[i].X, points[i].Y);
   }
   // glVertex2f(x,y); //Sample for ploting pixel at (x,y)
   glEnd();
}

void DrawPattern(int x0, int y0)
{
   // Draw Full Face
   FullCircle(80, PointAt(x0, y0));
   // Draw Eyes
   FullCircle(15, PointAt(x0 + 25, y0 + 25));
   FullCircle(15, PointAt(x0 - 25, y0 + 25));
   // Draw Mouth
   FullCircle(25, PointAt(x0, y0 - 35));
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