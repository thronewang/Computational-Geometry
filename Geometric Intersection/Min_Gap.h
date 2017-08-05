#include "utils.h"

const int INF = 1 << 20;

int Min_Gap(int * array, int n)
{
  std::sort(array, array + n);
  int MinGap = INF;
  for (int i = 0; i < n - 1; ++i)
  {
	MinGap = std::min(MinGap, array[i + 1] - array[i]);
  }
  return MinGap;
}