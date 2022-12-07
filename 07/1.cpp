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


	// Print
	/*
	std::vector<std::pair<Dir*, int>> fifo{std::make_pair(&dirs["/"], 0)};
	while (!fifo.empty()) {
		std::pair<Dir*, int> d = fifo.back();
		fifo.pop_back();

		std::cout << std::string(d.second, ' ') << "- " << d.first->name << "\n";
		for (Dir* subdir : d.first->subdirs) {
			fifo.emplace_back(subdir, d.second + 2);
		}
		for (const File& file : d.first->files) {
			std::cout << std::string(d.second + 2, ' ') << "- " << file.name << " (" << file.size << ")\n";
		}
	}
	*/

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


	for (auto&& [d, size] : visited) {
		std::cout << "Dir " << d->name << ": " << size << "\n";
	}

	std::cout << std::accumulate(visited.begin(), visited.end(), 0ULL,
		[](unsigned long long int total, const auto& v) { return v.second <= 100000 ? total + v.second : total; }) << std::endl;

}
