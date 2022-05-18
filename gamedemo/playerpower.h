#pragma once
#ifndef PLAYER_POWER_H_
#define PLAYER_POWER_H_
#include "BaseObject.h"
#include <vector>

class playerpower : public BaseObject
{
public :
	playerpower();
	~playerpower();
	void SetNumber(const int& num) { number_ = num; }
	void AddPos(const int& xpos);
	void Render(SDL_Surface* des);
	void Init();
	void Decrease();
private :
	int number_;
	std::vector<int> pos_list;
};

#endif // !PLAYER_POWER_H_


