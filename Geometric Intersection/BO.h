//绝望，又错了

#include <queue>//priority-queue
#include "utils.h"

//needed struct:
//1. segment
//2. event
//3. point

//status sequence:
//BBST stored segments

//events priority queue

#define SegmentPosi Segment*
#define NodePosi Node*
typedef double PointType;

struct event;

struct Point {
  PointType x, y;
  Point(PointType a = 0, PointType b = 0):x(a), y(a){}
};

struct Segment
{
  Point sta, end;
  PointType k;
  Segment(){}
  Segment(Point s, Point e) :sta(s), end(e) { k = (sta.x - end.x) / (sta.y - end.y); }
  PointType height(PointType x) { return k*(x - sta.x) + sta.y; }
  bool judge(SegmentPosi other, PointType& e) {
	PointType x = (k * sta.x - other->k * other->sta.x + other->sta.y - sta.y) / (k - other->k);
	if ( (x < std::max(sta.x, end.x)) && (x > std::min(sta.x, end.x)) && (x < std::max(other->sta.x, other->end.x )) && (x > std::min(other->sta.x, other->end.x)))
	{
	  e = x;
	  return true;
	}
	else return false;
  }
};

struct event
{
  PointType priority;
  enum EventType{none, Left, Right, Intersection} type;
  Segment * line_1, *line_2;
  event(EventType e = none, PointType p = 0, Segment * l_1 = nullptr, Segment * l_2 = nullptr)
  :type(e), priority(p), line_1(l_1), line_2(l_2) {}
  friend bool operator<(const event & one ,const event & other) { return one.priority > other.priority; }
};

class eventQueue {
private:
  std::priority_queue<event> data;
public:
  eventQueue(event * array, size_t n)
  :data(array, array + n){}
  bool empty() { return data.empty(); }
  event delMin() { auto tmp = data.top(); data.pop(); return tmp; }
  void insert(event & e) { data.push(e); }
};


#define IsRoot(x) (!(x)->parent)
#define IsLChild(x) (!IsRoot(x) && (x)->parent->LChild == (x))
#define IsRChild(x) (!IsRoot(x) && (x)->parent->RChild == (x))

struct Node
{
  NodePosi parent;
  NodePosi LChild;
  NodePosi RChild;
  SegmentPosi data;
  Node(SegmentPosi d = nullptr, NodePosi p = nullptr ) :data(d), parent(p), LChild(nullptr), RChild(nullptr) {}
  NodePosi InsertAsLC(SegmentPosi s) {
	return LChild = new Node(s, this);
  }
  NodePosi InsertAsRC(SegmentPosi s) {
	return RChild = new Node(s, this);
  }
  NodePosi succ() {
	auto s = this;
	if (RChild) {
	  s = RChild;
	  while (s->LChild)
	  {
		s = s->LChild;
	  }
	}
	else { 
	  while (IsRChild(s))
	  {
		s = s->parent;
	  }
	  s = s->parent;
	}
	return s;
  }
  NodePosi pred() {
	auto s = this;
	if (LChild) {
	  s = LChild;
	  while (s->RChild)
	  {
		s = s->RChild;
	  }
	}
	else {
	  while (IsLChild(s))
	  {
		s = s->parent;
	  }
	  s = s->parent;
	}
	return s;
  }
};

class BBST {
private:
  NodePosi _root;
  NodePosi _hot;
  size_t _size;
  PointType _x;
  NodePosi& searchIn(SegmentPosi &s, NodePosi &n)
  {
	if (!n || n->data == s) return n;
	_hot = n;
	return (n->data->height(_x) >= s->height(_x) ? searchIn(s, n->LChild) : searchIn(s, n->RChild));
  }
  void removeAt(NodePosi &n, NodePosi & hot)
  {
	NodePosi succ = nullptr;
	NodePosi w = n;
	if (!n->LChild)
	{
	  succ = n = n->RChild;
	}
	else if(!n->RChild) {
	  succ = n = n->LChild;
	}
	else {
	  w = n->succ();
	  std::swap(w->data, n->data);
	  auto u = w->parent;
	  (u == n ? u->RChild : u->LChild) = succ = w->RChild;
	}
	hot = w->parent;
	if (succ) succ->parent = hot;
	delete w->data;
	delete w;
	return;
  }
  static void inorder(NodePosi n)
  {
	if (n) {
	  inorder(n->LChild);
	  SegmentPosi s = n->data;
	  std::cout << "(" << s->sta.x << "," << s->sta.y << ")" << " --> (" << s->end.x << "," << s->end.y << ")\n";
	  inorder(n->RChild);
	}
  }
  void clear(NodePosi n)
  {
	if (n)
	{
	  clear(n->LChild);
	  clear(n->RChild);
	  delete n->data;
	  delete n;
	}
  }
public:
  BBST():_size(0), _root(nullptr), _x(0){}
  void inorder()
  {
	inorder(_root);
  }
  void updateX(PointType d) { _x = d; }
  NodePosi insert(SegmentPosi s) {
	auto & e = search(s);
	if (e) return nullptr;
	e = new Node(s, _hot);
	++_size;
	return e;
  }
  void remove(SegmentPosi s) {
	auto & e = search(s);
	if (!e) return;
	removeAt(e, _hot);
  }
  NodePosi &search(SegmentPosi s) {
	_hot = nullptr;
	return searchIn(s, _root);
  }
};