#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <limits>
#include <algorithm>

int main()
{
	int start, end;

	std::vector<char> grid;

	std::string line;
	std::getline(std::cin, line, '\n');
	int columns = line.size();
	int lines = 0;

	while (std::cin) {
		grid.reserve(grid.size() + columns);
		for (int i=0 ; i<line.size() ; i++) {
			char c = line[i];
			if (c == 'S') {
				start = lines*columns + i;
				grid.push_back('a');
			} else if (c == 'E') {
				end = lines*columns + i;
				grid.push_back('z');
			} else {
				grid.push_back(c);
			}
		}
		lines++;
		std::getline(std::cin, line, '\n');
	}

	std::cout << "Starting point: {" << (start / columns) << ", " << (start % columns) << "}\n";
	std::cout << "Ending point: {" << (end / columns) << ", " << (end % columns) << "}\n";

	// Instead of looking at all the paths from any point 'a' to the end
	// point, we look at reverse path from 'E' to any 'a'.
	std::vector<int> weights(grid.size());
	std::fill(weights.begin(), weights.end(), std::numeric_limits<int>::max());
	weights[end] = 0;
	std::set<int> toVisit{end};
	std::set<int> visited;
	int minDistance = std::numeric_limits<int>::max();

	while (!toVisit.empty()) {
		auto it = std::min_element(toVisit.begin(), toVisit.end(), [&weights](int n1, int n2) { return weights[n1] < weights[n2]; });
		int node = *it;
		std::cout << "Visiting {" << (node / columns) << ", " << (node % columns) << "}\n";
		toVisit.erase(it);
		if (grid[node] == 'a') {
			minDistance = std::min(minDistance, weights[node]);
			continue;
		}

		int weight = weights[node];
		if (node % columns > 0 && grid[node - 1] >= grid[node] - 1 && visited.find(node - 1) == visited.end()) {
			std::cout << "Adding {" << ((node - 1) / columns) << ", " << ((node - 1) % columns) << "}\n";
			toVisit.emplace(node - 1);
			weights[node - 1] = std::min(weight + 1, weights[node - 1]);
		}
		if (node % columns < columns - 1 && grid[node + 1] >= grid[node] - 1 && visited.find(node + 1) == visited.end()) {
			std::cout << "Adding {" << ((node + 1) / columns) << ", " << ((node + 1) % columns) << "}\n";
			toVisit.emplace(node + 1);
			weights[node + 1] = std::min(weight + 1, weights[node + 1]);
		}
		if (node >= columns && grid[node - columns] >= grid[node] - 1 && visited.find(node - columns) == visited.end()) {
			std::cout << "Adding {" << ((node - columns) / columns) << ", " << ((node - columns) % columns) << "}\n";
			toVisit.emplace(node - columns);
			weights[node - columns] = std::min(weight + 1, weights[node - columns]);
		}
		if (node < (lines - 1) * columns && grid[node + columns] >= grid[node] - 1 && visited.find(node + columns) == visited.end()) {
			std::cout << "Adding {" << ((node + columns) / columns) << ", " << ((node + columns) % columns) << "}\n";
			toVisit.emplace(node + columns);
			weights[node + columns] = std::min(weight + 1, weights[node + columns]);
		}
		visited.emplace(node);
	}

	std::cout << minDistance << std::endl;
}
