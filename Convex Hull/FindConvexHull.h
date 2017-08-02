#ifndef __CONVEXHULL__
#define __COMVEXHULL__

typedef int ValueType;
typedef int Rank;

struct Point
{
  ValueType x, y;
  Rank succ;
  bool extreme;
  int index;
  Point(ValueType a = 0, ValueType b = 0)
	:x(a), y(b) { }
};

ValueType area(Point p, Point q, Point r)
{
  return p.x * q.y + p.y * r.x + q.x * r.y - p.x * r.y - p.y * q.x - q.y * r.x;
}

bool ToLeft(Point p, Point q, Point r)
{
  return area(p, q, r) > 0;
}

//determinant
//        |p.x p.y 1|
//2 * S = |q.x q.y 1| S's absolute value is the aera of the three points
//        |r.x r.y 1|



#endif // !__CONVEXHULL__




