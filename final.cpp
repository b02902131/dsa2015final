#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <queue>

#include "trie.h"
#include "account.h"
#include "md5.h"

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
	long long int num;
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
				if(account[key].pwd == md5(pwd)) {
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
				Account temp(md5(pwd));
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
				if(account[key].pwd == md5(pwd)) {
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
			int key1 = trie.search(ID1);
			if(key1 >= 0){
				int key2 = trie.search(ID2);
				if(key2 >= 0){
					if(account[key1].pwd == md5(pwd1)) {
						if(account[key2].pwd == md5(pwd2)) {
							account[key1].deposit( account[key2].money );
							//TODO: leave transfer history
							trie.remove(ID2);
							cout << "success, "<<ID1<<" has "<<account[key1].money<<" dollars" << endl;
						}
						else{
							cout << "wrong password2" << endl;
						}
					}
					else{
						cout << "wrong password1" << endl;
					}
				}
				else {
					cout << "ID " << ID2 << " not found" << endl;
				}
			}
			else{ 
				cout << "ID " << ID1 << " not found" << endl;
			}
		}
		else if(strcmp(tmp, "deposit")==0){
			//deposit [num]
			tmp = strtok(NULL, ": ");
			num = atoll(tmp);
			cout << "success, "<< account[login_id].deposit(num) <<" dollars in current account" << endl;
		}
		else if(strcmp(tmp, "withdraw")==0){
			//withdraw [num]
			tmp = strtok(NULL, ": ");
			num = atoll(tmp);
			if(account[login_id].money >= num ){
				cout << "success, "<< account[login_id].withdraw(num) <<" dollars left in current account" << endl;
			}
			else {
				cout << "fail, " << account[login_id].money << " dollars only in current account" << endl;
			}
		}
		else if(strcmp(tmp, "transfer")==0){
			//transfer [ID] [num]
			tmp = strtok(NULL, ": ");
			ID.assign(tmp);
			tmp = strtok(NULL, ": ");
			num = atoll(tmp);
			int key = trie.search(ID);
			if(key >= 0) {
				if(account[login_id].money >= num ){
					account[key].deposit(num);
					cout << "success, "<< account[login_id].withdraw(num) <<" dollars left in current account" << endl;
					//TODO: leave history
				}
				else {
					cout << "fail, " << account[login_id].money << " dollars only in current account" << endl;
				}
			}
			else{
				cout << "ID " << ID << " not found" << endl;
			}
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