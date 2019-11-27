#pragma once

#include <Utils.h>
#include <Object.h>
#include <Hero.h>


class DGenerator
{
public:
	DGenerator(void){};
	~DGenerator(void){};

	// Generation of map for level
	MMap generate(int Width, int Height);

};

