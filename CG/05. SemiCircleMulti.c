#include <Windows.h>

#include <GL/GLU.h>
#include <GL/gl.h>
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

float DegreeToRadian(int const angle)
{
   return (3.14159 / 180) * angle;
}

// Rotate A Point
void Rotate(Point points[], int count, float angle)
{
   angle = DegreeToRadian(angle);
   for (int i = 0; i < count; ++i)
   {
      // Let us See Rotation Matrix
      Point point;
      point.X = points[i].X * cosf(angle) - points[i].Y * sinf(angle);
      point.Y = points[i].X * sinf(angle) + points[i].Y * cosf(angle);

      points[i].X = point.X;
      points[i].Y = point.Y;
   }
}

Point PointAt(int const X, int const Y)
{
   Point point;
   point.X = X;
   point.Y = Y;
   return point;
}

void SemiCircle(int r, Point center, int angle)
{
   Point points[1000];

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
         y = y + 0;
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
   }

   Rotate(points, count, angle);
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
void DrawPattern(int x0, int y0, int radius, int counts)
{
   int angle = 0;
   for (int i = 1; i <= counts; ++i)
   {
      SemiCircle(radius, PointAt(x0, y0), angle);
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