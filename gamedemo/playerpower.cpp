#include "playerpower.h"

playerpower :: playerpower()
{

}
 
playerpower :: ~playerpower()
{

}

void playerpower::AddPos(const int& xpos)
{
	pos_list.push_back(xpos);
}

void playerpower::Render(SDL_Surface* des)
{
	if (number_ == pos_list.size())
	{
		for (int i = 0; i < pos_list.size(); i++)
		{
			rect_.x = pos_list.at(i);
			Show(des);
		}
	}
}

void playerpower::Init()
{
	LoadImg("power4.png");
	number_ = 3;
	if (pos_list.size() > 0)
	{
		pos_list.size();
	}
	AddPos(20);
	AddPos(60);
	AddPos(100);
}

void playerpower::Decrease()
{
	number_--;
	pos_list.pop_back();
}