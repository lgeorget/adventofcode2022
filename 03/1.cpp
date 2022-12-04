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
	std::string line;
	std::getline(std::cin, line, '\n');

	Summer s;

	while (std::cin) {
		int halfSize = line.size() / 2;
		std::vector<char> firstHalf(halfSize), secondHalf(halfSize);
		std::copy(line.c_str(), line.c_str() + halfSize, firstHalf.begin());
		std::sort(firstHalf.begin(), firstHalf.end());
		std::copy(line.c_str() + halfSize, line.c_str() + line.size(), secondHalf.begin());
		std::sort(secondHalf.begin(), secondHalf.end());

		std::set_intersection(firstHalf.begin(), firstHalf.end(),
			secondHalf.begin(), secondHalf.end(), s);
		std::getline(std::cin, line, '\n');
		s.reset();
	}

	std::cout << s.getTotal() << std::endl;
}
