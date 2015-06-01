#include <iostream>
#include "binomialHeap.h"
#include <string>
using namespace std;

class Account{
	private:
		unsigned long long int money; 
		BinomialHeap<pair<string, string> > transaction_history;

	public:
		string pwd;	//we can put it into private and write another public function to get it
		Account(string password){
			money =0;
			pwd = password;
		}

		//deposit

		//withdraw
		//merges
};
