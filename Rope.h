#ifndef ROPE_H
#define ROPE_H

#include "cocos2d.h"
#include <array>


static std::array<cocos2d::Vec2, 4> CONNECT_POINTS = 
{
	cocos2d::Vec2::ANCHOR_MIDDLE_LEFT,
	cocos2d::Vec2::ANCHOR_MIDDLE_TOP,
	cocos2d::Vec2::ANCHOR_MIDDLE_RIGHT,
	cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM
};

static std::array<std::string, 5> ropeFrames =
{
	"",
	"rope_1.png",
	"rope_2.png",
	"rope_3.png",
	"rope_4.png"
};

struct Coordinate
{
	Coordinate(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
	Coordinate operator+(Coordinate &second)
	{
		return Coordinate(x + second.x, y + second.y);
	}
	int x, y;
};


class Rope : public cocos2d::Sprite
{
private:
	int _id;
	int _numConnectPoint;
	int _xCoor, _yCoor;
	cocos2d::Vec2 *_connectPoints;
public:
	static Rope* create(int id, int x, int y);
	void initRope(int id, int x, int y);
	void rotate();
	bool isConnectedTo(Rope *_targetRope);
	void setCoordinate(int x, int y);
	inline cocos2d::Vec2 getGlobalCoor(int _indexConnectPoint);
	int getCoordinateX();
	int getCoordinateY();
	static cocos2d::Vec2 rotatePoint(cocos2d::Vec2 _targetPoint);
	~Rope();

};


#endif // !ROPE_H
