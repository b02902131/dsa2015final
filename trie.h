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
			int key;		//if it's not end, key = -1, otherwise key = the word's key
			//int prefix_count;
			struct node * child[ALPHABET_SIZE];
		}*head;
		int char2index(char c){
			if(((int)c - (int)'0') >= 0 && ((int)c - (int)'0') <= 25)return (int)c - (int)'0';
			if(((int)c - (int)'A') >= 0 && ((int)c - (int)'A') <= 25)return (int)c - (int)'A' + 10;
			if(((int)c - (int)'a') >= 0 && ((int)c - (int)'a') <= 25)return (int)c - (int)'a' + 36;
			return -1;
		}
		void init_node(struct node * n){
			n->key = -1;
			//n->prefix_count = 0;
		}
	public:
		void init(){
			head = new node();
			//head->prefix_count = 0;
			head->key = -1;		//initialize
		}
		void insert(string word, int key){		//insert a word, with a key
			node * current = head;
			//current-> prefix_count++;
			for (int i=0;i<word.length();++i){
				int letter = char2index( word[i] );	//TODO: here should modify to 62 character
				if((current -> child[letter]) == NULL){
					current->child[letter] = new node();
					init_node(current->child[letter]);
				}
				// current->child[letter]->prefix_count++;
				current = current -> child[letter];
			}
			current->key = key;
		}
		//TODO: now returns bool, i will change it to return some data
		int search (string word){
			node * current = head;
			for(int i=0; i< word.length(); ++i){
				if(current->child[char2index(word[i])]==NULL) return -1;
				current = current -> child[char2index(word[i])];
			}
			return current->key;
		}
		//TODO: add remove function
		int remove(string word){
			//find position and key
			node * current = head;
			for(int i=0; i< word.length(); ++i){
				if(current->child[char2index(word[i])]==NULL) return -1;
				current = current -> child[char2index(word[i])];
			}
			//if key = -1 , return -1
			int key = current->key;
			if(key==-1) return -1;
			//set the position: key = -1;
			current->key=-1;
			//return the key
			return key;
		}
		int words_with_prefix(string prefix){
			return -1;
			//now i don't think that we need this, maybe try it later.
		}
};