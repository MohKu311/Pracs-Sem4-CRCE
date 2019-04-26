#include <Windows.h>

#include <GL/GLU.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>

typedef struct
{
   float X;
   float Y;
} Point;

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
void Plotter(Point points[], int count)
{
   // Use pixel plotting in glBegin and glEnd
   glBegin(GL_POINTS);
   for (int i = 0; i < count; ++i)
   {
      glVertex2f(points[i].X, points[i].Y);
   }
   // glVertex2f(x,y); //Sample for ploting pixel at (x,y)
   glEnd();
}

void EllipseScalingRotationTranslation(Point centre, Point radius, int angle, Point scaling)
{
   // First we draw Ellipse at origin
   Point Ellipse[360];

   // Now we have all points of Ellipse
   int count = 360; // No Of Angles
   {
      for (int i = 0; i < count; i++)
      {
         Ellipse[i].X = radius.X * cosf(DegreeToRadian(i));
         Ellipse[i].Y = radius.Y * sinf(DegreeToRadian(i));
      }
   }

   glColor3f(0, 0, 0);
   // Plot Original Ellipse At Origin
   Plotter(Ellipse, count);

   // Scale Ellipse At Origin
   glColor3f(0, 0, 1);
   Scale(Ellipse, count, scaling);
   Plotter(Ellipse, count);

   // Plot Rotated Ellipse
   glColor3f(1, 0, 0);
   Rotate(Ellipse, count, angle);
   Plotter(Ellipse, count);

   // Plot Scaled Ellipse at Location
   // Translate Ellipse to Point
   glColor3f(0, 1, 0);
   Translate(Ellipse, count, centre);
   Plotter(Ellipse, count);
}

Point PointAt(float const X, float const Y)
{
   Point point;
   point.X = X;
   point.Y = Y;
   return point;
}

void disp()
{
   glClearColor(1, 1, 1, 1);
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0, 0, 0);
   // call your function define at beginning
   // for example WriteFunctionName();
   EllipseScalingRotationTranslation(PointAt(50, 50), PointAt(20, 10), 90, PointAt(0.5, 0.5));
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