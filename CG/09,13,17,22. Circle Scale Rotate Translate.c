#include <Windows.h>

#include <GL/GLU.h>
#include <GL/gl.h>
#include <gl/glut.h>
#include <math.h>

typedef struct
{
   float X;
   float Y;
} Point;

// Scale Given Matrix
void Scale(Point points[], int count, Point scalingFactors)
{
   for (int i = 0; i < count; ++i)
   {
      points[i].X = points[i].X * scalingFactors.X;
      points[i].Y = points[i].Y * scalingFactors.Y;
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

void CircleScalingRotationTranslation(Point centre, int radius, int angle, Point scalingFactors/*Scaling Factors*/)
{
   // First we draw circle at origin
   Point circle[360];

   // Now we have all points of Circle
   int count = 360; // No Of Angles
   {
      for (int i = 0; i < count; i++)
      {
         circle[i].X = radius * cosf(DegreeToRadian(i));
         circle[i].Y = radius * sinf(DegreeToRadian(i));
      }
   }

   glColor3f(0, 0, 0);
   // Plot Original Circle At Origin
   Plotter(circle, count);

   // Scale Circle At Origin
   glColor3f(0, 0, 1);
   Scale(circle, count, scalingFactors);
   Plotter(circle, count);

   // Plot Scaled Circle at Location
   // Translate Circle to Point
   glColor3f(0, 1, 0);
   Translate(circle, count, centre);
   Plotter(circle, count);

   // Plot Rotated Circle
   glColor3f(1, 0, 0);
   Rotate(circle, count, angle);
   Plotter(circle, count);
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
   CircleScalingRotationTranslation(PointAt(50, 50), 20, 40, PointAt(0.5, 0.5) /*Scaling Factors*/);
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