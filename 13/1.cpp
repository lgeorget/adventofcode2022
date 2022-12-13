#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include <optional>
#include <vector>

struct Tree
{
	std::vector<Tree> subtrees = {};
	std::optional<int> value = std::nullopt;
	Tree* parent = nullptr;

	friend std::ostream& operator<<(std::ostream& os, const Tree& t);

	static Tree parse(std::istream& is)
	{
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
		std::cerr << "Comparing:\n" << t1 << "\twith:\n" << t2 << std::endl;
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

	int index = 1;
	int total = 0;

	while (std::cin) {
		std::istringstream is{line1};
		Tree treeLeft = Tree::parse(is);
		std::istringstream is2{line2};
		Tree treeRight = Tree::parse(is2);

		if (Tree::compare(treeLeft, treeRight) < 0) {
			std::cout << "At index " << index << ", left tree is smaller than right tree\n";
			total += index;
		}

		std::getline(std::cin, line1, '\n');
		std::getline(std::cin, line2, '\n');
		std::cin.ignore(1);
		index++;
	}

	std::cout << total << std::endl;
}
