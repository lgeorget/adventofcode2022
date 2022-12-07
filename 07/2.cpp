#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <numeric>

struct File
{
	std::string name;
	unsigned long size;
};


struct Dir
{
	std::string path;
	std::string name;
	Dir* parent;
	std::vector<Dir*> subdirs;
	std::vector<File> files;
};

int main()
{
	std::map<std::string, Dir> dirs;
	auto it = dirs.emplace("/", Dir{"/", "/", nullptr, std::vector<Dir*>{}, std::vector<File>{}});
	it.first->second.parent = &(it.first->second);

	std::string firstWord;
	std::cin >> firstWord;

	Dir* currentDir = &(it.first->second);

	while (std::cin)
	{
		if (firstWord == "$") {
			std::string command;
			std::cin >> command;
			if (command == "cd") {
				std::string d;
				std::cin >> d;
				if (d == "/") {
					std::cerr << "Going to root /" << std::endl;
					currentDir = &dirs["/"];
				} else if (d == "..") {
					std::cerr << "Going up to dir " << currentDir->parent->path << std::endl;
					currentDir = currentDir->parent;
				} else {
					std::cerr << "Going down to dir " << d << std::endl;
					currentDir = &dirs[currentDir->path + d + "/"];
				}
			} else if (command == "ls") {
				std::cerr << "Listing dir " << currentDir->path << std::endl;
			}
		} else {
			if (firstWord == "dir") {
				std::string dirName;
				std::cin >> dirName;
				std::cerr << "Found dir " << dirName << std::endl;
				std::string path = currentDir->path + dirName + "/";
				auto jt = dirs.try_emplace(path, Dir{path, dirName, currentDir, std::vector<Dir*>{}, std::vector<File>{}});
				currentDir->subdirs.push_back(&(jt.first->second));
			} else {
				std::string fileName;
				std::cin >> fileName;
				unsigned long size = std::stoul(firstWord);
				std::cerr << "Found file " << fileName << " (" << size << ")" << std::endl;
				currentDir->files.emplace_back(File{fileName, size});
			}
		}
		std::cin >> firstWord;
	}

	std::vector<Dir*> fifo{&dirs["/"]};
	std::vector<std::pair<Dir*, unsigned long int>> acc{};
	std::map<Dir*, unsigned long int> visited;
	while (!fifo.empty()) {
		Dir* d = fifo.back();
		fifo.pop_back();

		unsigned long int size = std::accumulate(
			d->files.begin(),
			d->files.end(),
			0UL,
			[](unsigned long int total, const File& f) { return total + f.size; }
		);
		acc.emplace_back(d, size);
		for (Dir* subdir : d->subdirs) {
			fifo.emplace_back(subdir);
		}
	}

	while (!acc.empty()) {
		std::pair<Dir*, unsigned long int> d = acc.back();
		acc.pop_back();

		visited[d.first] = d.second;
		for (Dir* subdir : d.first->subdirs) {
			visited[d.first] += visited[subdir];
		}
	}

	unsigned long long int target = 30'000'000 - (70'000'000 - visited[&dirs["/"]]);
	auto del = std::min_element(visited.begin(), visited.end(),
		[target](auto&& d1, auto&& d2) {
			if (d1.second < target) {
				if (d2.second < target) {
					return d1.second < d2.second;
				} else {
					return false;
				}
			} else {
				if (d2.second < target) {
					return true;
				} else {
					return d1.second < d2.second;
				}
			}
		});

	std::cout << "I suggest to delete " << del->first->path << " (" << del->second << ")" << std::endl;
}
