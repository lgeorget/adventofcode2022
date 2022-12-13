#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include <optional>
#include <vector>
#include <algorithm>

struct Tree
{
	std::vector<Tree> subtrees = {};
	std::optional<int> value = std::nullopt;
	Tree* parent = nullptr;

	friend std::ostream& operator<<(std::ostream& os, const Tree& t);

	static Tree parse(const std::string& packet)
	{
		std::istringstream is{packet};
		Tree root;
		Tree* currentBranch = &root;

		char c = is.get();
		while (is) {
			if (c == '[') {
				Tree& subtree = currentBranch->subtrees.emplace_back();
				subtree.parent = currentBranch;
				currentBranch = &subtree;
			} else if (c == ']') {
				currentBranch = currentBranch->parent;
			} else if (c >= '0' && c <= '9') {
				is.unget();
				int value;
				is >> value;
				Tree& subtree = currentBranch->subtrees.emplace_back();
				subtree.value = value;
				subtree.parent = currentBranch;
			} /* otherwise (',', ' ', etc.) ignore */

			c = is.get();
		}
		return root;
	}

	static int compare(Tree& t1, Tree& t2)
	{
		if (t1.value && t2.value) {
			if (*(t1.value) < *(t2.value))
				return -1;
			else if (*(t1.value) > *(t2.value))
				return 1;
			else
				return 0;
		} else if (!t1.value && !t2.value) {
			auto itLeft = t1.subtrees.begin();
			auto itRight = t2.subtrees.begin();

			while (itLeft != t1.subtrees.end() && itRight != t2.subtrees.end()) {
				int c = compare(*itLeft, *itRight);
				if (c != 0)
					return c;
				++itLeft;
				++itRight;
			}
			if (itLeft == t1.subtrees.end() && itRight == t2.subtrees.end())
				return 0;
			else if (itLeft == t1.subtrees.end())
				return -1;
			else if (itRight == t2.subtrees.end())
				return 1;
		} else if (t1.value && !t2.value) {
			Tree& fakeTree = t1.subtrees.emplace_back();
			fakeTree.value = *(t1.value);
			fakeTree.parent = t1.parent;
			t1.value = std::nullopt;
			int c = compare(t1, t2);
			if (c != 0)
				return c;
		} else if (t2.value && !t1.value) {
			Tree& fakeTree = t2.subtrees.emplace_back();
			fakeTree.value = *(t2.value);
			fakeTree.parent = t2.parent;
			t2.value = std::nullopt;
			int c = compare(t1, t2);
			if (c != 0)
				return c;
		}
		return 0;
	}
};

std::ostream& operator<<(std::ostream& os, const Tree& t)
{
	os << "[";
	if (t.value) {
		os << *(t.value);
	} else {
		for (const Tree& subt: t.subtrees) {
			os << subt << ", ";
		}
	}
	os << "]";

	return os;
}

int main()
{
	std::string line1, line2;
	std::getline(std::cin, line1, '\n');
	std::getline(std::cin, line2, '\n');
	std::cin.ignore(1);

	std::vector<Tree> packets;

	while (std::cin) {
		packets.emplace_back(Tree::parse(line1));
		packets.emplace_back(Tree::parse(line2));
		std::cin.ignore(1);
		std::getline(std::cin, line1, '\n');
		std::getline(std::cin, line2, '\n');
	}

	const Tree& firstMarker = packets.emplace_back(Tree::parse("[[2]]"));
	const Tree& secondMarker = packets.emplace_back(Tree::parse("[[6]]"));

	std::vector<Tree*> shadowVector(packets.size());
	std::transform(packets.begin(), packets.end(), shadowVector.begin(), [](Tree& t) { return &t; });

	std::sort(shadowVector.begin(), shadowVector.end(), [](Tree* t1, Tree* t2) { return Tree::compare(*t1, *t2) < 0; });

	for (auto&& p : shadowVector) {
		std::cout << (*p) << "\n";
	}

	int product = 1;
	for (int i=0 ; i!=shadowVector.size() ; i++) {
		if (shadowVector[i] == &firstMarker || shadowVector[i] == &secondMarker)
			product *= i + 1;
	}

	std::cout << product << std::endl;
}
