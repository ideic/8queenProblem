#pragma once
#include <vector>

class RouteFinder
{
public:
	RouteFinder();
	~RouteFinder();
	bool IsPointValid(int idx, int idy, const std::vector<std::pair<int, int>>& positions, int fieldSize);
	std::pair<int,int> GetFreePosition(
		int tableSize,
		const std::vector<std::pair<int, int>>& result, int fromx, int fromy);
	void SetNextValue(int &fromx, int &fromy, const int tableSize);
	void SetFrom(int& fromx, int& fromy, std::vector<std::pair<int, int>>& result, const int &tableSize);
	void GetRoute(const int &numberOfQueens, std::vector<std::pair<int, int>> &result, int tableSize);

	std::vector<std::pair<int, int>> GetSolutions(int tableSize, int numberOfQueens);
};

