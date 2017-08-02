#ifndef __GRAMHAM__
#define __GRAMHAM__

#include "FindConvexHull.h"
#include <algorithm>
#include <stack>

//Lowest-then Leftest
Rank LTL(Point * ps, int n)
{
  Rank ltl = 0;
  for (int i = 1; i < n; ++i)
  {
	if (ps[i].y < ps[ltl].y || (ps[i].y == ps[ltl].y && ps[i].x < ps[ltl].x))
	  ltl = i;
  }
  return ltl;
}

class MyComp
{
private:
  Point ltl;
public:
  MyComp(Point l) :ltl(l) {}
  bool operator()(Point & one, Point & two)
  {
	return ToLeft(ltl, one, two);
  }
};

void presort(Point *ps, int n, Rank ltl)
{
  if(ltl != 0)
	std::swap(ps[0], ps[ltl]);
  std::sort(ps + 1, ps + n, MyComp(ps[0]));
}

std::stack<Point> Graham(Point *ps, int n)
{
  //preprocessing
  presort(ps, n, LTL(ps, n));
  std::stack<Point> S, T;
  S.push(ps[0]);
  S.push(ps[1]);
  for (int i = n - 1; i > 1; --i)
  {
	T.push(ps[i]);
  }
  Point S_1 = ps[1], S_0 = ps[0];
  while (!T.empty())
  {
	if (ToLeft(S_0, S_1, T.top()) || area(S_0, S_1, T.top()) == 0) {
	  S.push(T.top());
	  S_0 = S_1;
	  S_1 = S.top();
	  T.pop();
	}
	else {
	  S.pop();
	  S_1 = S.top();
	  S.pop();
	  S_0 = S.top();
	  S.push(S_1);
	}
  }
  return S;
}

#endif // !__GRAMHAM__
