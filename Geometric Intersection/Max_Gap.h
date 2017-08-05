#include "utils.h"
#include <functional>
#define BucketPosi Bucket*

typedef int DataType;
const DataType INF = 1 << 20;
const DataType MIN = 0;


struct Bucket
{
  DataType data;
  BucketPosi next;
  Bucket(DataType d, BucketPosi n = nullptr)
  : data(d), next(n) { }
  static BucketPosi Last(BucketPosi node)
  {
	if (node == nullptr) return node;
	while (nullptr != node->next)
	{
	  node = node->next;
	}
	return node;
  }
  void addAsSucc(DataType d)
  {
	if (nullptr == this)
	  return;
	auto p = this;
	if (d < p->data)
	  this = new Bucket(d, this);
	while (d > p->data && nullptr != p->next)
	{
	  p = p->next;
	}
	p->next = new Bucket(d, p->next);
  }
};

size_t hashCode(DataType data, DataType interval, DataType lo)
{
  return (data - lo) / interval;
}

BucketPosi * HashTable(DataType * array, size_t n, DataType lo, DataType hi)
{
  size_t numOfBuckets = n + 1;
  DataType interval = (hi - lo) / n;
  auto Buckets = new BucketPosi[numOfBuckets];
  for (size_t i = 0; i < numOfBuckets; ++i)
	Buckets[i] = nullptr;
  for (size_t i = 0; i < n; ++i)
  {
	if (nullptr == Buckets[hashCode(array[i], interval, lo)])
	  Buckets[hashCode(array[i], interval, lo)] = new Bucket(array[i]);
	else {
	  Buckets[hashCode(array[i], interval, lo)]->addAsSucc(array[i]);
	}
  }
  return Buckets;
}

int find(DataType * array, DataType init, size_t n, std::function<DataType(const DataType a, const DataType b)> func)
{
  DataType ret = init;
  for (size_t i = 0; i < n; ++i)
  {
	ret = func(ret, array[i]);
  }
  return ret;
}

DataType Max_Grap(DataType * array, size_t n)
{
  auto Buckets = HashTable(array, n, find(array, INF, n, [](const int a, const int b)->int { return a < b ? a : b; }),
	find(array, MIN, n, [](const int a, const int b)->int { return a > b ? a : b; }));
  DataType MAX = MIN;
  BucketPosi fir;
  BucketPosi sec;
  for (size_t i = 0, t = 0; i <= n && t <= n; )
  {
	while (nullptr == Buckets[i])
	{
	  ++i;
	}
	if (i >= n)
	  break;
	fir = Buckets[i];
	t = i + 1;
	while (nullptr == Buckets[t])
	{
	  ++t;
	}
	if (t > n)
	  break;
	sec = Buckets[t];
	MAX = std::max(MAX, sec->data - Bucket::Last(fir)->data);
	++i;
  }
  return MAX;
}