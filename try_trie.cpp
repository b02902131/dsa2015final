#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include "trie.h"

int main(){
	Trie trie;
	trie.init();
	trie.insert("Alan9",2);

	trie.insert("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHJKLMNOPQRSTUVWXYZ",999);
	cout << trie.search("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHJKLMNOPQRSTUVWXYZ") << endl;
	
	cout << trie.search("Alan9") << endl;
	trie.insert("alan",3);
	cout << trie.search("ala") << endl;
	cout << trie.search("alan") << endl;
	cout << trie.search("alan2") << endl;
	cout << trie.remove("Alan9") << endl;
	cout << trie.search("Alan9") << endl;
	trie.insert("Alan9",2);
	cout << trie.search("Alan9") << endl;
	return 0;
}