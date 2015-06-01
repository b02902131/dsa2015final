#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <queue>

#include "trie.h"
#include "account.h"

using namespace std;

std::vector<Account> account;
Trie trie;
priority_queue<int, std::vector<int>, std::greater<int> > id_queue;
long long int login_id;

int get_next_Id(){
	int id = id_queue.top();
	id_queue.pop();
	if(id_queue.empty()) id_queue.push(id+1);
	return id;
}

int main(){

	//initial id queue, trie
	id_queue.push(0);
	trie.init();

	// declare
	string ID, ID1, ID2, pwd, pwd1, pwd2, wildID;
	int num;
	string istring;

	//while loop
	while(getline(cin, istring)){
		char *cstring ,*tmp;
		cstring = new char[istring.size()+1];
		strncpy(cstring, istring.c_str(), istring.size()+1);
		tmp = cstring;
		tmp = strtok(cstring, " ");
		if(strcmp(tmp, "login")==0){
			//login [ID] [password]
			tmp = strtok(NULL, ": ");
			ID.assign(tmp);
			tmp = strtok(NULL, ": ");
			pwd.assign(tmp);
			int key = trie.search(ID);
			if(key >= 0) {
				if(account[key].pwd == pwd) {
					login_id = key;
					cout << "success" << endl;
				}
				else{
					cout << "wrong password" << endl;
				}
			}
			else{
				cout << "ID " << ID << " not found" << endl;
			}
		}
		else if(strcmp(tmp, "create")==0){
			//create [ID] [password]
			tmp = strtok(NULL, ": ");
			ID.assign(tmp);
			tmp = strtok(NULL, ": ");
			pwd.assign(tmp);
			if( trie.search(ID)>=0 ) {
				cout << "ID " << ID <<" exists, [best 10 unused IDs]" << endl;
			}
			else {
				//successful create operation
				int key = get_next_Id();
				trie.insert(ID, key);
				Account temp(pwd);
				if(key>=account.size()) account.push_back(temp);
				else account[key] = temp;
				cout << "success" << endl;
			}
		}
		else if(strcmp(tmp, "delete")==0){
			//delete [ID] [password]
			tmp = strtok(NULL, ": ");
			ID.assign(tmp);
			tmp = strtok(NULL, ": ");
			pwd.assign(tmp);
			int key = trie.search(ID);
			if(key >= 0) {
				if(account[key].pwd == pwd) {
					trie.remove(ID);
					cout << "success" << endl;
				}
				else{
					cout << "wrong password" << endl;
				}
			}
			else{
				cout << "ID " << ID << " not found" << endl;
			}
		}
		else if(strcmp(tmp, "merge")==0){
			//merge [ID1] [password1] [ID2] [password2]
			tmp = strtok(NULL, ": ");
			ID1.assign(tmp);
			tmp = strtok(NULL, ": ");
			pwd1.assign(tmp);
			tmp = strtok(NULL, ": ");
			ID2.assign(tmp);
			tmp = strtok(NULL, ": ");
			pwd2.assign(tmp);
			cout << "merge "<<ID1<<" "<<pwd1<<" "<<ID2<<" "<<pwd2 << endl;
		}
		else if(strcmp(tmp, "deposit")==0){
			//deposit [num]
			tmp = strtok(NULL, ": ");
			num = atoi(tmp);
			cout << "deposit [num]" << endl;
		}
		else if(strcmp(tmp, "withdraw")==0){
			//withdraw [num]
			tmp = strtok(NULL, ": ");
			num = atoi(tmp);
			cout << "withdraw [num]" << endl;
		}
		else if(strcmp(tmp, "transfer")==0){
			//transfer [ID] [num]
			tmp = strtok(NULL, ": ");
			ID.assign(tmp);
			tmp = strtok(NULL, ": ");
			num = atoi(tmp);
			cout << "transfer [ID] [num]" << endl;
		}
		else if(strcmp(tmp, "find")==0){
			//find [wildcard ID]
			cout << "find [wildcard ID]" << endl;
		}
		else if(strcmp(tmp, "search")==0){
			//search [ID]
			cout << "search [ID]"<<endl;
		}
		
	}
	//while(get input)
	//switch input and dosomethings
}