#ifndef __JARVIS__
#define __JARVIS__

#include "FindConvexHull.h"
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

//Jarvis March
void Jarvis(Point * ps, int n)
{
  for (int i = 0; i < n; ++i)
	ps[i].extreme = false;
  Rank ltl = LTL(ps, n);
  Rank pred = ltl;
  do
  {
	ps[ltl].extreme = true;
	Rank cur = -1;//cur is the the candidate for the next extreme point
	for (Rank i = 0; i < n; ++i)
	{
	  if (i != pred && i != cur && (-1 == cur || !ToLeft(ps[pred], ps[cur], ps[i])))
		cur = i;
	}
	ps[pred].succ = cur;
	pred = cur;
  } while (pred != ltl);
}

#endif //!__JARVIS__