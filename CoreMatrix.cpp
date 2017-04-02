#include "CoreMatrix.h"

USING_NS_CC;

GameLayer::GameLayer(int width, int height)
{
	_width = width;
	_height = height;
}

GameLayer * GameLayer::create(int width, int height)
{
	GameLayer *ret = new (std::nothrow) GameLayer(width, height);
	if(ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

bool GameLayer::init()
{
	int i, j;
	origin = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();

	_ropeMatrix = new Rope**[_width];
	for(i = 0; i < _width; ++i)
	{
		_ropeMatrix[i] = new Rope*[_height];
		for(j = 0; j < _height; ++j)
		{
			_ropeMatrix[i][j] = Rope::create(cocos2d::RandomHelper::random_int(1, 4), i, j);
			_ropeMatrix[i][j]->setPosition(origin.x + 90 + i * 60 + 30, origin.y + 210 + j * 60 + 30);
			this->addChild(_ropeMatrix[i][j]);
		}
	}
	auto rect = DrawNode::create();
	rect->drawRect(Vec2(90, 210), Vec2(90, 210) + Vec2(360, 540), Color4F::BLUE);
	this->addChild(rect, 1);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [=](Touch *touch, Event *event)
	{
		return true;
	};
	touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
	return true;
}

bool GameLayer::isCoordinateValid(int x, int y)
{
	return (x >= 0 && x < _width) && (y >= 0 && y < _height);
}

bool GameLayer::isCoordinateValid(Coordinate coor)
{
	return (coor.x >= 0 && coor.x < _width) && (coor.y >= 0 && coor.y < _height);
}

void GameLayer::listPathConnected(Coordinate start)
{
	queue<Coordinate> path_stack, visit_stack;
	std::array<Coordinate, 4> direct = {Coordinate(-1, 0), Coordinate(0, -1), Coordinate(1, 0), Coordinate(0, 1)};
	bool **markMatrix;
	int i, j;
	markMatrix = new bool*[_width];
	for(i = 0; i < _width; ++i)
	{
		markMatrix[i] = new bool[_height];
		for(j = 0; j < _height; ++j)
			markMatrix[i][j] = false;
	}
	visit_stack.push(start);
	markMatrix[start.x][start.y] = true;
	while(!visit_stack.empty())
	{
		auto c = visit_stack.front();
		visit_stack.pop();
		path_stack.push(c);
		for(auto &coor : direct)
		{
			auto nextCoor = c + coor;
			if(isCoordinateValid(nextCoor) && markMatrix[nextCoor.x][nextCoor.y] == false && _ropeMatrix[c.x][c.y]->isConnectedTo(_ropeMatrix[nextCoor.x][nextCoor.y]))
			{
				visit_stack.push(nextCoor);
				markMatrix[nextCoor.x][nextCoor.y] = true;
			}
		}
	}
	while(!path_stack.empty())
	{
		auto c = path_stack.front();
		path_stack.pop();
		log("(%d, %d)-", c.x, c.y);
	}
	log("=============================");
	for(i = 0; i < _width; ++i)
		delete[] markMatrix[i];
	delete[] markMatrix;
}

void GameLayer::listPathConnected(int x, int y)
{
	listPathConnected(Coordinate(x, y));
}

void GameLayer::onTouchEnded(Touch *touch, Event *event)
{
	Vec2 touchLocation = touch->getLocation();
	Rect matrix = Rect(90, 210, 360, 540);
	if(matrix.containsPoint(touchLocation))
	{
		int x, y;
		x = (touchLocation.x - 90) / 60;
		y = (touchLocation.y - 210) / 60;
		_ropeMatrix[x][y]->rotate();
		listPathConnected(x, y);
	}
}



void GameLayer::rotateRopeAt(int x, int y)
{
	_ropeMatrix[x][y]->rotate();
}



GameLayer::~GameLayer()
{
	int i;
	for(i = 0; i < _width; ++i)
	{
		delete[] _ropeMatrix[i];
	}
	delete[] _ropeMatrix;
}
