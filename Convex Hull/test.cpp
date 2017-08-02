#pragma warning (disable : 4996)
#include "Graham.h"
#include <stdio.h>
using namespace std;
const int SZ = 1<<21;   
struct fastio{   //fast io
    char inbuf[SZ];  
    char outbuf[SZ];  
    fastio(){  
        setvbuf(stdin,inbuf,_IOFBF,SZ);  
        setvbuf(stdout,outbuf,_IOFBF,SZ);  
    }  
}io; 
int main()
{
  int n;
  scanf("%d", &n);
  Point * ps = new Point[n];
  for (int i = 0; i < n; ++i)
  {
	scanf("%d %d", &ps[i].x, &ps[i].y);
	ps[i].index = i + 1;
  }
  stack<Point> ans = Graham(ps, n);
  long long out = 1;
  int size = ans.size();
  do
  {
	out = (ans.top().index * out) % (n + 1);
	ans.pop();
  } while (!ans.empty());
  out = (out * size) % (n + 1);
  printf("%d\n", out);
  delete[]ps;
  return 0;
}