#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <iterator>
#include <set>
#include <vector>

int total = 0;

class Summer
{
private:
	bool done = false;

public:
	Summer& operator*() { return *this; };
	Summer& operator++() { return *this; };
	const Summer& operator++(int) { return *this; };
	Summer& operator=(char c) {
		if (done)
			return *this;

		if (c >= 'a' && c <= 'z')
			total += c - 'a' + 1;
		else
			total += c - 'A' + 27;
		done = true;
		std::cout << "found: " << c << ", total: " << total << std::endl;
		return *this;
	}

	void reset() { done = false; }
	int getTotal() const { return total; }
};

int main()
{
	std::string line1, line2, line3;
	std::getline(std::cin, line1, '\n');
	std::getline(std::cin, line2, '\n');
	std::getline(std::cin, line3, '\n');

	Summer s;

	while (std::cin) {
		std::vector<char> v1(line1.size());
		std::vector<char> v2(line2.size());
		std::vector<char> v3(line3.size());
		std::copy(line1.begin(), line1.end(), v1.begin());
		std::sort(v1.begin(), v1.end());
		std::copy(line2.begin(), line2.end(), v2.begin());
		std::sort(v2.begin(), v2.end());
		std::copy(line3.begin(), line3.end(), v3.begin());
		std::sort(v3.begin(), v3.end());

		std::vector<char> intersect;
		std::set_intersection(v1.begin(), v1.end(),
			v2.begin(), v2.end(), std::back_inserter(intersect));
		std::set_intersection(intersect.begin(), intersect.end(),
			v3.begin(), v3.end(), s);
		std::getline(std::cin, line1, '\n');
		std::getline(std::cin, line2, '\n');
		std::getline(std::cin, line3, '\n');
		s.reset();
	}

	std::cout << s.getTotal() << std::endl;
}
