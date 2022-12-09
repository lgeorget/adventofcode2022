#include <iostream>
#include <set>
#include <array>

struct Coords
{
	int x = 0;
	int y = 0;
};

bool operator<(const Coords& c1, const Coords& c2)
{
	return c1.x < c2.x || (c1.x == c2.x && c1.y < c2.y);
}

int main()
{
	constexpr int ROPE_LENGTH = 10;
	std::array<Coords, ROPE_LENGTH> pos;
	char dir;
	int length;
	std::set<Coords> visited;

	std::cin >> dir >> length;

	while (std::cin) {
		for (int d=length ; d>0 ; d--) {
			switch (dir) {
			case 'U':
				pos[0].y++;
				break;
			case 'D':
				pos[0].y--;
				break;
			case 'R':
				pos[0].x++;
				break;
			case 'L':
				pos[0].x--;
				break;
			}

			for (int i=1 ; i<ROPE_LENGTH ; i++) {
				if (pos[i - 1].y > pos[i].y + 1) {
					pos[i].y++;
					if (pos[i - 1].x > pos[i].x) {
						pos[i].x++;
					} else if (pos[i - 1].x < pos[i].x) {
						pos[i].x--;
					}
				} else if (pos[i - 1].y < pos[i].y - 1) {
					pos[i].y--;
					if (pos[i - 1].x > pos[i].x) {
						pos[i].x++;
					} else if (pos[i - 1].x < pos[i].x) {
						pos[i].x--;
					}
				} else if (pos[i - 1].x > pos[i].x + 1) {
					pos[i].x++;
					if (pos[i - 1].y > pos[i].y) {
						pos[i].y++;
					} else if (pos[i - 1].y < pos[i].y) {
						pos[i].y--;
					}
				} else if (pos[i - 1].x < pos[i].x - 1) {
					pos[i].x--;
					if (pos[i - 1].y > pos[i].y) {
						pos[i].y++;
					} else if (pos[i - 1].y < pos[i].y) {
						pos[i].y--;
					}
				}
			}
			visited.insert(pos[ROPE_LENGTH - 1]);
		}
		std::cin >> dir >> length;
	}

	std::cout << visited.size() << std::endl;
}
