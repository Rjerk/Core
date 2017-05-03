#include "bplustree.h"
#include <iostream>

int main()
{
	char command;
	KeyType key;
	BPlusTree tree(4);
	while (true) {
		std::cout << "b+tree> ";
		std::cin >> command;
		switch (command) {
			case 's':
				std::cin >> key;
				if (tree.search(key))
					std::cout << key << " exists in tree.\n";
				else
					std::cout << "Not found.\n";
				break;
			case 'i':
				std::cin >> key;
				tree.insert(key, key);
				tree.print();
				break;
			case 'd':
				std::cin >> key;
				tree.remove(key);
				tree.print();
				break;
			case 'p':
				tree.print();
				break;
			default:
				std::cin.ignore(256, '\n');
				std::cout << "Unknown command.\n";
				break;
		}
	}
}
