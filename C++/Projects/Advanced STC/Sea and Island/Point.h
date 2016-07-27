#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>

struct point{
	int x, y;
	point(int x, int y);
	point();
	point *next;
	bool equal(point s);
};

struct point2{
	int x, y;
	point2();
	point2(int x, int y);
};

int Length(point *head);
void AddQueue(point *add);
void DeQueue();
void Free(point *head);

#endif