#include <iostream>
#include <set>
#include <string>

struct Coords
{
	int x;
	int y;

	Coords(int x, int y): x{x}, y{y} {}
};

bool operator<(const Coords& c1, const Coords& c2) {
	return c1.x < c2.x || (c1.x == c2.x && c1.y < c2.y);
}


void print(const std::set<Coords>& terrain, char t, const std::set<Coords>& occupied, char o)
{
	int xmin=500, xmax=500, ymax=0;
	for (auto&& c : occupied) {
		if (c.x < xmin) {
			xmin = c.x - 3;
		}
		if (c.x > xmax) {
			xmax = c.x + 3;
		}
		if (c.y > ymax) {
			ymax = c.y + 3;
		}
	}

	for (int y=0 ; y<ymax ; y++) {
		for (int x=xmin ; x<=xmax ; x++) {
			if (terrain.find(Coords(x, y)) != terrain.end()) {
				std::cout << t;
			} else if (occupied.find(Coords(x, y)) != occupied.end()) {
				std::cout << o;
			} else {
				std::cout << '.';
			}
		}
		std::cout << '\n';
	}
}

int main()
{
	std::set<Coords> terrain;

	int x1, x2, y1, y2;
	char c = ' ';

	do {
		std::cin >> x1;
		std::cin.ignore(1); // ","
		std::cin >> y1;
		c = std::cin.get();

		while (std::cin && c != '\n') {
			std::cin.ignore(3); // "-> "
			std::cin >> x2;
			std::cin.ignore(1);
			std::cin >> y2;

			std::cout << x1 << "," << y1 << " -- " << x2 << "," << y2 << std::endl;

			if (x1 == x2) {
				if (y1 > y2) {
					for (int y=y2 ; y<=y1 ; y++) {
						terrain.emplace(x1, y);
					}
				} else {
					for (int y=y1 ; y<=y2 ; y++) {
						terrain.emplace(x1, y);
					}
				}
			} else /* y1 == y2 */ {
				if (x1 > x2) {
					for (int x=x2 ; x<=x1 ; x++) {
						terrain.emplace(x, y1);
					}
				} else {
					for (int x=x1 ; x<=x2 ; x++) {
						terrain.emplace(x, y1);
					}
				}
			}
			x1 = x2;
			y1 = y2;

			c = std::cin.get();
		}
	} while (std::cin);

	int maxTerrain = 0;
	for (auto&& c : terrain) {
		if (c.y > maxTerrain) {
			maxTerrain = c.y + 2;
		}
	}

	print(terrain, '#', terrain, '#');
	std::cout << "\n";


	std::set<Coords> occupied = terrain;
	int sand = 0;
	for (;;) {
		Coords pos{500, 0};

		for (;;) {
			pos.y++;
			if (pos.y > maxTerrain + 1) {
				pos.y--;
				break;
			}
			if (occupied.find(pos) != occupied.end()) {
				pos.x--;
				if (occupied.find(pos) != occupied.end()) {
					pos.x += 2;
					if (occupied.find(pos) != occupied.end()) {
						pos.x--;
						pos.y--;
						break;
					}
				}
			}
			std::cerr << "New pos: {" << pos.x << "," << pos.y << "}\n";
		};

		std::cerr << "The grain of sand comes to rest at {" << pos.x << "," << pos.y << "}\n";
		occupied.insert(pos);
		sand++;

		if (pos.x == 500 && pos.y == 0) {
			break;
		}
	}
	print(terrain, '#', occupied, 'o');

	std::cout << sand << std::endl;
}
