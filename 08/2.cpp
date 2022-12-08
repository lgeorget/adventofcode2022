#include <iostream>
#include <vector>
#include <algorithm>

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

	std::vector<int> total(grid.size());

	for (int l=0 ; l<lines ; l++) {
		for (int c=0; c<columns ; c++) {
			int coords = l * columns + c;
			char max = grid[coords];

			int north = 0;
			int south = 0;
			int west = 0;
			int east = 0;
			for (int ll=l-1 ; ll>=0 ; ll--) {
				north++;
				if (grid[ll * columns + c] >= max)
					break;
			}
			for (int ll=l+1 ; ll<lines ; ll++) {
				south++;
				if (grid[ll * columns + c] >= max)
					break;
			}
			for (int cc=c-1 ; cc>=0 ; cc--) {
				west++;
				if (grid[l * columns + cc]  >= max)
					break;
			}
			for (int cc=c+1 ; cc<columns ; cc++) {
				east++;
				if (grid[l * columns + cc] >= max)
					break;
			}
			total[coords] = north * south * west * east;
		}
	}

	std::cout << *std::max_element(total.begin(), total.end()) << std::endl;
}
