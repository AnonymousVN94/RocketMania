#ifndef CORE_MATRIX_H
#define CORE_MATRIX_H
#include "cocos2d.h"
#include "Rope.h"
#include <stack>
#include <queue>
#include <array>

using std::stack;
using std::queue;

class GameLayer : public cocos2d::Layer
{
private:
	int _width, _height;
	Rope ***_ropeMatrix;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
public:
	GameLayer(int width, int height);
	static GameLayer* create(int width, int height);
	virtual bool init();
	bool isCoordinateValid(int x, int y);
	bool isCoordinateValid(Coordinate coor);
	void listPathConnected(int x, int y);
	void listPathConnected(Coordinate start);
	void rotateRopeAt(int x, int y);
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
	~GameLayer();
};

#endif // !CORE_MATRIX_H

