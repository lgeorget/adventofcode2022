#include <iostream>
#include <vector>
#include <numeric>

int main()
{
	std::vector<char> grid;

	std::string line;
	std::getline(std::cin, line, '\n');

	int lines = 0;
	int columns = line.size();

	while (std::cin)
	{
		lines++;
		grid.reserve(grid.size() + line.size());
		std::copy(line.begin(), line.end(), std::back_inserter(grid));
		std::getline(std::cin, line, '\n');
	}

	std::vector<bool> fromWest(grid.size());
	std::vector<bool> fromEast(grid.size());
	std::vector<bool> fromNorth(grid.size());
	std::vector<bool> fromSouth(grid.size());

	for (int l=0 ; l<lines ; l++) {
		int max = 0;
		for (int c=0; c<columns ; c++) {
			int coords = l * columns + c;
			if (grid[coords] > max) {
				fromWest[coords] = true;
				max = grid[coords];
			} else {
				fromWest[coords] = false;
			}
		}
	}

	for (int l=0 ; l<lines ; l++) {
		int max = 0;
		for (int c=columns-1 ; c>=0 ; c--) {
			int coords = l * columns + c;
			if (grid[coords] > max) {
				fromEast[coords] = true;
				max = grid[coords];
			} else {
				fromEast[coords] = false;
			}
		}
	}

	for (int c=0; c<columns ; c++) {
		int max = 0;
		for (int l=0 ; l<lines ; l++) {
			int coords = l * columns + c;
			if (grid[coords] > max) {
				fromNorth[coords] = true;
				max = grid[coords];
			} else {
				fromNorth[coords] = false;
			}
		}
	}

	for (int c=0; c<columns ; c++) {
		int max = 0;
		for (int l=lines-1 ; l>=0 ; l--) {
			int coords = l * columns + c;
			if (grid[coords] > max) {
				fromSouth[coords] = true;
				max = grid[coords];
			} else {
				fromSouth[coords] = false;
			}
		}
	}

	std::vector<bool> total(grid.size());
	for (int l=0 ; l<lines ; l++) {
		for (int c=0; c<columns ; c++) {
			int coords = l * columns + c;
			total[coords] = fromWest[coords] || fromEast[coords] || fromNorth[coords] || fromSouth[coords];
		}
	}

	std::cout << std::accumulate(total.begin(), total.end(), 0L) << std::endl;
}
