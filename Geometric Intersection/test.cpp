#include "BO.h"

int main()
{
  int num;
  int count = 0;
  std::cin >> num;
  SegmentPosi * segs = new SegmentPosi[num];
  Point c, d;
  BBST tree;
  for(size_t i = 0; i < num; ++i)
  {
	std::cin >> c.x >> c.y
	  >> d.x >> d.y;
	segs[i] = new Segment(c, d);
  }
  event* array = new event[2 * num];
  for (size_t i = 0, t = 0; i < num; ++i)
  {
    array[t++] = event(event::EventType::Left, segs[i]->sta.x, segs[i]);
    array[t++] = event(event::EventType::Right, segs[i]->end.x, segs[i]);
  }
  eventQueue que(array, 2 * num);
  event cur;

  while (!que.empty())
  {
	cur = que.delMin();
	tree.updateX(cur.priority);
	PointType x;
	if (cur.type == event::EventType::Left)
	{
	  NodePosi n = tree.insert(cur.line_1);
	  //ÅÐ½»
	  event e;
	  if(n->succ())
		if (n->data->judge(n->succ()->data, x))
		{
		  ++count;
		  e.priority = x;
		  e.type = event::EventType::Intersection;
		  e.line_1 = n->data;
		  e.line_2 = n->succ()->data;
		  que.insert(e);
		}
	  if(n->pred())
		if (n->data->judge(n->pred()->data, x)) {
		  ++count;
		  e.priority = x;
		  e.type = event::EventType::Intersection;
		  e.line_1 = n->data;
		  e.line_2 = n->pred()->data;
		  que.insert(e);
		}
	}
	else if(cur.type == event::EventType::Right) {
	  NodePosi n = tree.search(cur.line_1);
	  //succºÍpredÅÐ½»
	  event e;
	  if(n->succ() && n->pred())
		if (n->succ()->data->judge(n->pred()->data, x))
		{
		  ++count;
		  e.priority = x;
		  e.type = event::EventType::Intersection;
		  e.line_1 = n->succ()->data;
		  e.line_2 = n->pred()->data;
		  que.insert(e);
		}
	  tree.remove(cur.line_1);
	}
	else {
	  NodePosi a;
	  NodePosi b;
	  std::swap((a = tree.search(cur.line_1))->data, (b = tree.search(cur.line_2))->data);
	  //
	  if (a->succ() == b)
	  {
		event e;
		if (a->pred())
		  if (a->data->judge(a->pred()->data, x))
		  {
			++count;
			e.type = event::EventType::Intersection;
			e.priority = x;
			e.line_1 = a->data;
			e.line_2 = a->pred()->data;
			que.insert(e);
		  }
		if(b->succ())
		  if (b->data->judge(b->succ()->data, x))
		  {
			++count;
			e.priority = x;
			e.type = event::EventType::Intersection;
			e.line_1 = b->data;
			e.line_2 = b->succ()->data;
			que.insert(e);
		  }
	  }
	  else {
		event e;
		if (a->succ())
		  if (a->data->judge(a->succ()->data, x))
		  {
			++count;
			e.priority = x;
			e.type = event::EventType::Intersection;
			e.line_1 = a->data;
			e.line_2 = a->succ()->data;
			que.insert(e);
		  }
		if (b->pred())
		  if (b->data->judge(b->pred()->data, x))
		  {
			++count;
			e.priority = x;
			e.type = event::EventType::Intersection;
			e.line_1 = b->data;
			e.line_2 = b->pred()->data;
			que.insert(e);
		  }
	  }

	}
  }
  std::cout << count << std::endl;
  system("pause");
  return 0;
}
