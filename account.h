#include <iostream>
#include "binomialHeap.h"
#include <string>
using namespace std;

class Account{
	public:
		BinomialHeap<pair<string, string> > transaction_history;
		long long int money; 
		string pwd;	

		Account(string password){
			money =0;
			pwd = password;
		}

		//deposit
		long long int deposit(long long int num){	//return current money
			money += num;
			return money;
		}
		//withdraw
		long long int withdraw(long long int num){	//return current money or -1 for fail
			money -= num;
			return money;

		}

		//merges
};
