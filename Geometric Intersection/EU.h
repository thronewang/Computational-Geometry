#include "utils.h"

template <typename T>
bool EU(T * array, int n)
{
  std::sort(array, array + n);
  for (int i = 0; i < n - 1; ++i)
  {
	if (array[i] == array[i + 1])
	  return false;
  }
  return bool;
}