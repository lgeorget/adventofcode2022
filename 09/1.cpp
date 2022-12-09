#include <iostream>
#include <set>

struct Coords
{
	int x;
	int y;
};

bool operator<(const Coords& c1, const Coords& c2)
{
	return c1.x < c2.x || (c1.x == c2.x && c1.y < c2.y);
}

std::ostream& operator<<(std::ostream& out, const Coords& c)
{
	out << "{" << c.x << "," << c.y << "}";
	return out;
}

int main()
{
	Coords posH{0, 0}, posT{0, 0};
	char dir;
	int length;
	std::set<Coords> visited;

	std::cin >> dir >> length;

	while (std::cin) {
		for (int d=length ; d>0 ; d--) {
			switch (dir) {
			case 'U':
				posH.y++;
				break;
			case 'D':
				posH.y--;
				break;
			case 'R':
				posH.x++;
				break;
			case 'L':
				posH.x--;
				break;
			}

			if (posH.y > posT.y + 1) {
				posT.y++;
				if (posH.x > posT.x) {
					posT.x++;
				} else if (posH.x < posT.x) {
					posT.x--;
				}
			} else if (posH.y < posT.y - 1) {
				posT.y--;
				if (posH.x > posT.x) {
					posT.x++;
				} else if (posH.x < posT.x) {
					posT.x--;
				}
			} else if (posH.x > posT.x + 1) {
				posT.x++;
				if (posH.y > posT.y) {
					posT.y++;
				} else if (posH.y < posT.y) {
					posT.y--;
				}
			} else if (posH.x < posT.x - 1) {
				posT.x--;
				if (posH.y > posT.y) {
					posT.y++;
				} else if (posH.y < posT.y) {
					posT.y--;
				}
			}
			visited.insert(posT);
			std::cout << posH << " - " << posT << std::endl;
		}
		std::cin >> dir >> length;
	}

	std::cout << visited.size() << std::endl;
}
