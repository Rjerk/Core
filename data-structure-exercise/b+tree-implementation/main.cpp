#include "bplustree.h"
#include <iostream>

int main()
{
	char instruction;
	BPlusTree tree(4);
	int key;
	
	for (;;) {
		std::cout << "> ";
		std::cin >> instruction;
		switch (instruction) {
			case 's':
				std::cin >> key;
				if (tree.search(key) != nullptr)
					std::cout << key << " exists in tree.\n";
				else
					std::cout << "Not found.\n";
				break;
			case 'i':
				std::cin >> key;
				tree.insert(key, key);
				//tree.print();
				break;
			case 'd':
				std::cin >> key;
				tree.remove(key);
				//tree.print();
				break;
			default:
				std::cin.ignore(256, '\n');
				std::cout << "useless instruction.\n";
				break;
		}
	}
}
