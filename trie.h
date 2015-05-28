#include <cstdio>
#include <cstdlib>
#include <cstring>

#define ALPHABET_SIZE 62

class Trie{
	private:
		struct node
		{
			bool is_end;
			int prefix_count;
			struct node * child[ALPHABET_SIZE];
		}*head;
		int char2index(char c){
			return (int)c - (int)'a';
		}
	public:
		void init(){
			head = new node();
			head->prefix_count = 0;
			head->is_end = false;
		}
		void insert(string word){
			node * current = head;
			current-> prefix_count++;
			for (unsigned int i=0;i<word.length();++i){
				int letter = char2index(word[i]);	//TODO: here should modify to 62 character
				if(current -> child[letter]) == NULL)
					current->child[letter] = new node();
				current->child[letter]->prefix_count++
				current = current -> child[letter];
			}
			current->is_end = true;
		}
		bool search (string word){
			node * current = head;
			for(unsigned int i=0; i< word.length(); ++i){
				if(current->child[char2index(word[i])]==NULL) return false;
				current = current -> child[char2index(word[i])];
			}
			return current->is_end;
		}
		int words_with_prefix(string prefix){
			return -1;
			//now i don't think that we need this, maybe try it later.
		}
}