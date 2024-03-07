#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <Windows.h>


class Tree {
private:
	struct Node {
		std::string word;
		int freq = 1;
		Node* left = nullptr;
		Node* right = nullptr;
	};

	Node* root;

	Node* insert(Node* node, const std::string& word) {
		if (!node)
			return new Node{ word };
		if (word < node->word)
			node->left = insert(node->left, word);
		else if (word > node->word)
			node->right = insert(node->right, word);
		else
			node->freq++;
		return node;
	}

	static void alphabetSort(
		Node* node,
		std::vector<std::pair<std::string, int>>& sortedList
	) {
		if (node) {
			alphabetSort(node->left, sortedList);
			sortedList.emplace_back(node->word, node->freq);
			alphabetSort(node->right, sortedList);
		}
	}

	static bool reverseFreqComparator(
		const std::pair<std::string, int>& a,
		const std::pair<std::string, int>& b
	) {
		return a.second > b.second;
	}

	static Node* search(Node* node, const std::string& word) {
		if (!node || node->word == word)
			return node;
		if (word < node->word)
			return search(node->left, word);
		return search(node->right, word);
	}

	static void filterByLength(
		Node* node,
		int length,
		std::vector<std::pair<std::string, int>>& filteredList
	) {
		if (node) {
			if (node->word.size() == length)
				filteredList.emplace_back(node->word, node->freq);
			filterByLength(node->left, length, filteredList);
			filterByLength(node->right, length, filteredList);
		}
	}

public:
	Tree() : root(nullptr) {}
	void buildTree(const std::string& filename) {
		std::ifstream file(filename);
		std::string line;
		while (std::getline(file, line)) {
			size_t startPos = 0;
			size_t endPos = 0;
			while ((endPos = line.find(' ', startPos)) != std::string::npos) {
				std::string word = line.substr(startPos, endPos - startPos);
				word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
				std::transform(word.begin(), word.end(), word.begin(), tolower);
				root = insert(root, word);
				startPos = endPos + 1;
			}
		}
		file.close();
	}

	void printAlphabetical() const {
		std::vector<std::pair<std::string, int>> sortedList;
		alphabetSort(root, sortedList);
		std::cout << "Частотный словарь слов в алфавитном порядке:" << std::endl;
		for (const auto& [word, freq] : sortedList) {
			std::cout << word << ": " << freq << std::endl;
		}
	}

	void printByFrequency() const {
		std::vector<std::pair<std::string, int>> sortedList;
		alphabetSort(root, sortedList);
		std::sort(sortedList.begin(), sortedList.end(), reverseFreqComparator);
		std::cout << "Частотный словарь слов по убыванию частоты:" << std::endl;
		for (const auto& [word, freq] : sortedList) {
			std::cout << word << ": " << freq << std::endl;
		}
	}

	void searchWord(const std::string& searchWord) const {
		Node* result = search(root, searchWord);
		if (result)
			std::cout << "Слово \"" << searchWord << "\" найдено. Частота употребления: " << result->freq << std::endl;
		else
			std::cout << "Слово \"" << searchWord << "\" не найдено." << std::endl;
	}

	void lengthFilter(int length) const {
		std::vector<std::pair<std::string, int>> filteredList;
		filterByLength(root, length, filteredList);
		if (!filteredList.size())
			std::cout << "Слова длины " << length << " не найдены" << std::endl;
		else {
			std::cout << "Фильтрованный словарь слов длины " << length << ":" << std::endl;
			for (const auto& [word, freq] : filteredList)
				std::cout << word << ": " << freq << std::endl;
		}
	}

};

int main() {
	setlocale(LC_ALL, "ru"); // valid file reading
	SetConsoleCP(1251); // valid console input
	SetConsoleOutputCP(1251); // valid console output
	Tree tr;
	tr.buildTree("data.txt");
	tr.printAlphabetical();
	std::cout << std::endl;
	tr.printByFrequency();
	std::string word;
	std::cout << "Введите слово: ";
	std::cin >> word;
	tr.searchWord(word);
	int len;
	std::cout << "Введите длину: ";
	std::cin >> len;
	tr.lengthFilter(len);
	return 0;
}