#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <functional>
#include <algorithm>

struct Monkey
{
	std::deque<unsigned long> items;
	std::function<unsigned long(unsigned long)> worry;
	std::function<int(unsigned long)> test;
	unsigned long total = 0;
};

bool operator<(const Monkey& m1, const Monkey& m2) {
	return m1.total < m2.total;
}


int main()
{
	std::string line;
	std::vector<Monkey> monkeys;

	unsigned long bigdiv = 1;

	while (std::cin) {
		Monkey m;
		std::getline(std::cin, line, '\n');
		std::cout << line << std::endl;
		std::cin.ignore(18);

		char sep = ',';
		do {
			unsigned long item;
			std::cin >> item;
			sep = std::cin.get();
			m.items.push_back(item);
		} while (sep != '\n');

		std::cin.ignore(23);
		char opChar;
		std::string operandStr;
		std::cin >> opChar >> operandStr;
		std::cout << "new = old " << opChar << " " << operandStr << "\n";
		std::function<unsigned long(unsigned long, unsigned long)> op;
		if (opChar == '+') {
			op = std::plus<unsigned long>();
		} else {
			op = std::multiplies<unsigned long>();
		}
		if (operandStr == "old") {
			m.worry = [op](unsigned long old) { return op(old, old); };
		} else {
			unsigned long operandInt = std::stoi(operandStr);
			m.worry = [op, operandInt](unsigned long old) { return op(old, operandInt); };
		}

		std::cin.ignore(21);
		int div;
		std::cin >> div;
		bigdiv *= div;
		std::cin.ignore(29);
		int monkeyTrue;
		std::cin >> monkeyTrue;
		std::cin.ignore(30);
		int monkeyFalse;
		std::cin >> monkeyFalse;
		m.test = [div, monkeyTrue, monkeyFalse](unsigned long value) { return value % div == 0 ? monkeyTrue : monkeyFalse; };
		std::cin.ignore(1);

		monkeys.push_back(m);

		std::getline(std::cin, line, '\n');
	}


	for (int loop = 1 ; loop <= 10000 ; loop++) {
		for (Monkey& m : monkeys) {
			while (!m.items.empty()) {
				unsigned long item = m.items.front();
				m.items.pop_front();
				m.total++;

				unsigned long newWorry = m.worry(item) % bigdiv;
				monkeys[m.test(newWorry)].items.push_back(newWorry);
			}
		}

		if (loop % 1000 == 0) {
			std::cout << "After round " << loop << "\n";
			for (int mId = 0 ; mId < monkeys.size() ; mId++) {
				std::cout << "Monkey " << mId << ": ";
				for (unsigned long item : monkeys[mId].items) {
					std::cout << item << ", ";
				}
				std::cout << "\n";
			}
		}
	}

	for (int mId = 0 ; mId < monkeys.size() ; mId++) {
		std::cout << "Monkey " << mId << ": inspected items " << monkeys[mId].total << " times.\n";
	}

	std::make_heap(monkeys.begin(), monkeys.end());
	unsigned long total = 1;
	for (int i=0 ; i<2 ; i++) {
		std::pop_heap(monkeys.begin(), monkeys.end());
		total *= monkeys.back().total;
		monkeys.pop_back();
	}
	std::cout << total << std::endl;
}
