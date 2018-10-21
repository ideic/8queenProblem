#include "pch.h"
#include "RouteFinder.h"
#include <algorithm>


RouteFinder::RouteFinder()
{
}


RouteFinder::~RouteFinder()
{
}

bool RouteFinder::IsPointValid(int idx, int idy, const std::vector<std::pair<int, int>>& positions, int fieldSize)
{
	std::vector<std::pair< int, int>> criticalPositions;

	int tidx = idx -1;
	int tidy = idy -1;


	while (tidx>=0 && tidy >= 0)
	{
		criticalPositions.emplace_back(tidx, tidy);
		--tidx;
		--tidy;
	}

	tidx = idx + 1;
	tidy = idy + 1;


	while (tidx < fieldSize && tidy < fieldSize)
	{
		criticalPositions.emplace_back(tidx, tidy);
		++tidx;
		++tidy;
	}

	tidx = idx - 1;
	tidy = idy + 1;

	while (tidx >= 0 && tidy < fieldSize)
	{
		criticalPositions.emplace_back(tidx, tidy);
		--tidx;
		++tidy;
	}

	tidx = idx + 1;
	tidy = idy - 1;


	while (tidx < fieldSize && tidy >= 0)
	{
		criticalPositions.emplace_back(tidx, tidy);
		++tidx;
		--tidy;
	}

	return !std::any_of(begin(positions), end(positions), [&idx, &idy, &criticalPositions](auto position)
	{
		return position.first == idx || position.second == idy
		|| std::any_of(begin(criticalPositions), end(criticalPositions), [&position](const auto criticalPosition)
		{
			return criticalPosition.first == position.first && criticalPosition.second == position.second;
		})
		;
	});
}

std::pair<int, int> RouteFinder::GetFreePosition(
	int tableSize, 
	const std::vector<std::pair<int, int>> &result,
	int fromx,
	int fromy)
{
	while (fromy < tableSize)
	{
		if (IsPointValid(fromx, fromy, result, tableSize))
		{
			return std::pair<int, int>(fromx, fromy);
		}

		SetNextValue(fromx, fromy, tableSize);
	}
	
	return std::pair<int, int>(-1, -1);
}

void RouteFinder::SetNextValue(int & fromx, int & fromy, const int tableSize)
{
	fromx++;
	if (fromx >= tableSize)
	{
		fromx = 0;
		fromy++;
	}
	
}

void RouteFinder::SetFrom(int& fromx, int& fromy, std::vector<std::pair<int, int>>& result, const int &tableSize)
{
	if (result.size() == 0) return;

	fromx = result.back().first;
	fromy = result.back().second;

	SetNextValue(fromx, fromy, tableSize);

	if (fromy >= tableSize)
		{
			result.erase(result.end() - 1);
			SetFrom(fromx, fromy, result, tableSize);
		}

	if (result.size() > 0)
		result.erase(result.end() - 1);
}

void RouteFinder::GetRoute(const int &numberOfQueens, 
	std::vector<std::pair<int, int>> &result, 
	int tableSize)
{
	int fromx = 0;
	int fromy = 0;

	while (static_cast<int>( result.size()) < numberOfQueens)
	{
		auto newPosition = GetFreePosition(tableSize, result, fromx, fromy);
		if (newPosition.first >= 0)
		{
			//prohibitedPositions.clear();

			result.push_back(newPosition);
			fromx = 0;
			fromy = 0;
		}
		else
		{
			if (result.size() == 0) return;
			SetFrom(fromx, fromy, result, tableSize);
			if (fromy >= tableSize) return;
		}
	}
}

std::vector<std::pair<int, int>> RouteFinder::GetSolutions(int tableSize, int numberOfQueens)
{
	std::vector<std::pair<int, int>> result;

	GetRoute(numberOfQueens, result, tableSize);

	return result;
}
