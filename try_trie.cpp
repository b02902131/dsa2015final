#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include "trie.h"

int main(){
	Trie trie;
	trie.init();
	trie.insert("Alan9");

	cout << trie.search("alan") << endl;
	cout << trie.search("Alan9") << endl;
	cout << trie.search("bob") << endl;
	return 0;
}