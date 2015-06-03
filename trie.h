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
			long long int key;		//if it's not end, key = -1, otherwise key = the word's key
			int prefix_count;
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
			n->prefix_count = 0;
		}
	public:
		void init(){
			head = new node();
			head->prefix_count = 0;
			head->key = -1;		//initialize
		}
		void insert(string word, long long int key){		//insert a word, with a key
			node * current = head;
			current-> prefix_count++;
			for (int i=0;i<word.length();++i){
				int letter = char2index( word[i] );	//here had been modified to 62 character
				if((current -> child[letter]) == NULL){
					current->child[letter] = new node();
					init_node(current->child[letter]);
				}
				current->child[letter]->prefix_count++;
				current = current -> child[letter];
			}
			current->key = key;
		}
		long long int search (string word){
			node * current = head;
			for(int i=0; i< word.length(); ++i){
				if(current->child[char2index(word[i])]==NULL) return -1;
				current = current -> child[char2index(word[i])];
			}
			return current->key;
		}
		//remove function
		void remove(string word){
			//find position and key
			node * current = head;
			//check all nodes in the path, prefix_count--, and if prefix_count = 0, set the entry = null
			current-> prefix_count--;
			for (int i=0;i<word.length();++i){
				int letter = char2index( word[i] );	
				current->child[letter]->prefix_count--;
				if(current->child[letter]->prefix_count==0) {	//if prefix_count == 0, means there is no more word attach to the node
					current -> child[letter] = NULL;
					// cout << ">>>trie 68" << endl;
					return;
				}
				// cout << ">>>trie 71" << endl;
				current = current -> child[letter];
			}
			//set the position: key = -1;
			current->key=-1;
		}
		int words_with_prefix(string prefix){
			return -1;
			//now i don't think that we need this, maybe try it later.
		}
};