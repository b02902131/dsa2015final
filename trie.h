#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>

#define ALPHABET_SIZE 62

using namespace std;

class Trie{
	private:
		struct node
		{
			bool is_end;
			int key;
			int prefix_count;
			struct node * child[ALPHABET_SIZE];
		}*head;
		int char2index(char c){
			if(((int)c - (int)'0') >= 0 && ((int)c - (int)'0') <= 25)return (int)c - (int)'0';
			if(((int)c - (int)'A') >= 0 && ((int)c - (int)'A') <= 25)return (int)c - (int)'A' + 10;
			if(((int)c - (int)'a') >= 0 && ((int)c - (int)'a') <= 25)return (int)c - (int)'a' + 36;
			return -1;
		}
	public:
		void init(){
			head = new node();
			head->prefix_count = 0;
			head->is_end = false;
			head->key = -1;
		}
		void insert(string word){
			node * current = head;
			current-> prefix_count++;
			for (int i=0;i<word.length();++i){
				int letter = char2index( word[i] );	//TODO: here should modify to 62 character
				if((current -> child[letter]) == NULL)
					current->child[letter] = new node();
				current->child[letter]->prefix_count++;
				current = current -> child[letter];
			}
			current->is_end = true;
		}
		//TODO: add delete function

		//TODO: now returns bool, i will change it to return some data
		bool search (string word){
			node * current = head;
			for(int i=0; i< word.length(); ++i){
				if(current->child[char2index(word[i])]==NULL) return false;
				current = current -> child[char2index(word[i])];
			}
			return current->is_end;
		}
		int words_with_prefix(string prefix){
			return -1;
			//now i don't think that we need this, maybe try it later.
		}
};