#include "Rope.h"

USING_NS_CC;


Rope * Rope::create(int id, int x, int y)
{
	Rope *rope = new (std::nothrow) Rope();
	if (rope && rope->initWithFile(ropeFrames[id]))
	{
		rope->initRope(id, x, y);
		rope->autorelease();
		return rope;
	}
	CC_SAFE_DELETE(rope);
	return nullptr;
}

void Rope::initRope(int id, int x, int y)
{
	_id = id;
	_xCoor = x;
	_yCoor = y;
	switch (_id)
	{
	case 1:
		_numConnectPoint = 2;
		_connectPoints = new Vec2[_numConnectPoint];
		_connectPoints[0] = CONNECT_POINTS[0];
		_connectPoints[1] = CONNECT_POINTS[2];
		break;
	case 2:
		_numConnectPoint = 3;
		_connectPoints = new Vec2[_numConnectPoint];
		_connectPoints[0] = CONNECT_POINTS[0];
		_connectPoints[1] = CONNECT_POINTS[1];
		_connectPoints[2] = CONNECT_POINTS[2];
		break;
	case 3:
		_numConnectPoint = 2;
		_connectPoints = new Vec2[_numConnectPoint];
		_connectPoints[0] = CONNECT_POINTS[0];
		_connectPoints[1] = CONNECT_POINTS[3];
		break;
	case 4:
		_numConnectPoint = 4;
		_connectPoints = new Vec2[_numConnectPoint];
		_connectPoints[0] = CONNECT_POINTS[0];
		_connectPoints[1] = CONNECT_POINTS[1];
		_connectPoints[2] = CONNECT_POINTS[2];
		_connectPoints[3] = CONNECT_POINTS[3];
		break;
	default:
		break;
	}
}

void Rope::rotate()
{
	int i;
	for (i = 0; i < _numConnectPoint; ++i)
	{
		_connectPoints[i] = rotatePoint(_connectPoints[i]);
	}
	this->setRotation(this->getRotation() + 90.0f);
}

bool Rope::isConnectedTo(Rope * _targetRope)
{
	int i, j;
	for (i = 0; i < _numConnectPoint; ++i)
	{
		for (j = 0; j < _targetRope->_numConnectPoint; ++j)
		{
			if (getGlobalCoor(i) == _targetRope->getGlobalCoor(j))
			{
				return true;
			}
		}
	}
	return false;
}

void Rope::setCoordinate(int x, int y)
{
	_xCoor = x;
	_yCoor = y;
}

cocos2d::Vec2 Rope::getGlobalCoor(int _indexConnectPoint)
{
	return cocos2d::Vec2(_xCoor + _connectPoints[_indexConnectPoint].x, _yCoor	+ _connectPoints[_indexConnectPoint].y);
}

int Rope::getCoordinateX()
{
	return _xCoor;
}

int Rope::getCoordinateY()
{
	return _yCoor;
}

cocos2d::Vec2 Rope::rotatePoint(cocos2d::Vec2 _targetPoint)
{
	if (_targetPoint == CONNECT_POINTS[0])
		return CONNECT_POINTS[1];
	else if (_targetPoint == CONNECT_POINTS[1])
		return CONNECT_POINTS[2];
	else if (_targetPoint == CONNECT_POINTS[2])
		return CONNECT_POINTS[3];
	else if (_targetPoint == CONNECT_POINTS[3])
		return CONNECT_POINTS[0];
	else
		return cocos2d::Vec2::ZERO;
}

Rope::~Rope()
{
	delete[] _connectPoints;
}
