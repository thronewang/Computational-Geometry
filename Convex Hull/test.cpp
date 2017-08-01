#include "Jarvis.h"
#include <iostream>

using namespace std;

int main()
{
  int x, y;
  Point ps[11];
  for (int i = 0; i < 11; ++i)
  {
	cin >> x >> y;
	ps[i].x = x; ps[i].y = y;
  }
  Jarvis(ps, 11);
  Rank cur = 0;
  do
  {
	cout << "(" << ps[cur].x << "," << ps[cur].y << ")";
	cur = ps[cur].succ;
	if(cur != 0) cout << " --> ";
  } while (cur != 0);
  cout << endl;
  system("pause");
  return 0;
}