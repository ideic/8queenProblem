// 8Queen.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "RouteFinder.h"

int main()
{
	RouteFinder rf;

	auto solution = rf.GetSolutions(4,4);
	for (const auto coordinate : solution)
	{
		std::cout << "x:" << coordinate.first << " y:" << coordinate.second << std::endl;
	}
	std::cout << "End" << std::endl;
}
