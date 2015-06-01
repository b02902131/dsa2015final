#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include "trie.h"

int main(){
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
			cout << "login "<<ID<<" "<<pwd << endl;
		}
		else if(strcmp(tmp, "create")==0){
			//create [ID] [password]
			tmp = strtok(NULL, ": ");
			ID.assign(tmp);
			tmp = strtok(NULL, ": ");
			pwd.assign(tmp);
			cout << "create "<<ID<<" "<<pwd << endl;
		}
		else if(strcmp(tmp, "delete")==0){
			//delete [ID] [password]
			tmp = strtok(NULL, ": ");
			ID.assign(tmp);
			tmp = strtok(NULL, ": ");
			pwd.assign(tmp);
			cout << "delete "<<ID<<" "<<pwd << endl;
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
			cout << "deposit [num]" << endl;
		}
		else if(strcmp(tmp, "withdraw")==0){
			//withdraw [num]
			cout << "withdraw [num]" << endl;
		}
		else if(strcmp(tmp, "transfer")==0){
			//transfer [ID] [num]
			cout << "transfer [ID] [num]" << endl;
		}
		else if(strcmp(tmp, "find")==0){
			//find [wildcard ID]
			cout << "find [wildcard ID]" << endl;
		}
		else if(strcmp(tmp, "search")==0){
			//search [ID]
			cout << "search [ID]";
		}
		
	}
	//while(get input)
	//switch input and dosomethings
}