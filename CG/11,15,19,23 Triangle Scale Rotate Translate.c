#include <Windows.h>

#include <GL/GLU.h>
#include <GL/gl.h>
#include <gl/glut.h>

typedef struct
{
   float X;
   float Y;
} Point;

void DrawPoint(Point point)
{
   glVertex2f(point.X, point.Y);
}
void Plotter(Point points[3])
{
   // Use pixel plotting in glBegin and glEnd
   glBegin(GL_LINE_LOOP);
   // Initial Point
   DrawPoint(points[0]);
   DrawPoint(points[1]);
   DrawPoint(points[2]);
   // Back to Initial Point
   DrawPoint(points[0]);
   // glVertex2f(x,y); //Sample for ploting pixel at (x,y)
   glEnd();
}
// Scale Given Matrix
void Scale(Point points[], int count, Point scaling)
{
   for (int i = 0; i < count; ++i)
   {
      points[i].X = points[i].X * scaling.X;
      points[i].Y = points[i].Y * scaling.Y;
   }
}

// Translate Given Matrix
void Translate(Point points[], int count, Point translate)
{
   for (int i = 0; i < count; ++i)
   {
      points[i].X = points[i].X + translate.X;
      points[i].Y = points[i].Y + translate.Y;
   }
}

float DegreeToRadian(float const angle)
{
   return (3.14159 * angle) / 180.0;
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

      printf("\nX=%f\t:Y=%f\t:%f", point.X, point.Y, angle);
   }
}

Point PointAt(float const X, float const Y)
{
   Point point;
   point.X = X;
   point.Y = Y;
   return point;
}

void TriangleOperations(int side, Point lMin, int angle, Point scaling)
{
   Point triangle[3];

   // Create Triangle
   {
      triangle[0] = PointAt(0, 0);
      triangle[1] = PointAt(side, 0);
      triangle[2] = PointAt(side * cos(DegreeToRadian(60)), side * sin(DegreeToRadian(60)));
   }

   // Plot Original Triangle
   glColor3f(0, 0, 0);
   Plotter(triangle, 3);

   // Plot Scaled Triangle
   glColor3f(1, 0, 0);
   Scale(triangle, 3, scaling);
   Plotter(triangle, 3);

   // Plot Rotated Triangle
   glColor3f(0, 1, 0);
   Rotate(triangle, 3, angle);
   Plotter(triangle, 3);

   // Translate Triangle
   glColor3f(0, 0, 1);
   Translate(triangle, 3, lMin);
   Plotter(triangle, 3);
}

void disp()
{
   glClearColor(1, 1, 1, 1);
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0, 0, 0);
   // call your function define at beginning
   // for example WriteFunctionName();
   TriangleOperations(50, PointAt(50, 50), 90, PointAt(0.5, 0.5));
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