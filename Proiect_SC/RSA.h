#pragma once

#include <tuple>
#include <string>
#include <stdlib.h> 

using namespace std;


typedef tuple<int, int> Key;
typedef unsigned long long int number;

class RSA
{
private:
	Key _publicKey;
	Key _privateKey;
	string message;

	static bool isPrime(number n) {
		if ( n % 2 == 0  && n!=2) {
			return false;
		}
		for ( number i = 3; i < n / 2; i++ ) {
			if ( n % i == 0 ) return false;
		}
		return true;
	}

	static number getPhi(number n1, number n2) {
		return (n1 - 1) * (n2 - 1);
	}

	static number getDecryptPart(number E, number PHI) {
		number i = 1;
		while ( true ) {
			if ((E*i) % PHI == 1 ) {
				return i;
			}	
			i++;
		}

	}

	static bool isCoprime(number num, number N, number PHI) {
		for ( number i = 2; i <= num; i++ ) {
			if ( num % i == 0 ) {
				if(N % i == 0 || PHI % i == 0)
				return false;
			}
		}
		return true;
	}

	static number pow(number n1, number n2) {
		number result = n1;
		for ( int i = 1; i < n2; i++ ) {
			result=result*n1;
		}

		return result;
	}


	static Key generatePublicKey(Key seed) {
		if ( get<0>(seed) == 0 || get<1>(seed) == 0 || !isPrime(get<0>(seed)) || !isPrime(get<1>(seed)) ) {
			throw "Numbers must be greater than 0 and prime!";
		}
		number n1 = get<0>(seed);
		number n2 = get<1>(seed);
		number N = n1 * n2;
		number PHI = getPhi(n1, n2);

		number e;
		for ( number i = 2; i < PHI; i++ ) {
			if ( isCoprime(i, N, PHI) ) {
				e = i;
				break;
			}
		}
		return make_tuple(e, N);
	}


public:
	

	RSA(Key publicKey, string message) {		
		this->_publicKey = publicKey;
		this->message = message;
	}
	RSA(string message) {
		this->message = message;
	}
	~RSA() {}

	string crypt() {
		string result = "";
		for ( number i = 0; i < this->message.length(); i++ ) {
			if ( this->message[i] == ' ' || this->message[i] == '.' || this->message[i] == ',' || this->message[i] == '?' || this->message[i] == ':' || this->message[i] == ';' || this->message[i] == '(' || this->message[i] == ')' || this->message[i] == '\'' || this->message[i] == '!' ) {
			result.push_back(this->message[i]);
			continue;
		}
			if ( this->message[i] > 96 ) {
				result.push_back((char)((pow((number)this->message[i]-96 , get<0>(_publicKey))) % get<1>(_publicKey) + 96));
			}
			else result.push_back((char)((pow((number)this->message[i]-64 , get<0>(_publicKey))) % get<1>(_publicKey) + 64));
		}
		return result;
	}

	string crypt(Key _publicKey) {
		string result = "";
		for ( number i = 0; i < this->message.length(); i++ ) {
			if ( this->message[i] == ' ' || this->message[i] == '.' || this->message[i] == ',' || this->message[i] == '?' || this->message[i] == ':' || this->message[i] == ';' || this->message[i] == '(' || this->message[i] == ')' || this->message[i] == '\'' || this->message[i] == '!' ) {
				result.push_back(this->message[i]);
				continue;
			}
			if ( this->message[i] > 96 ) {
				result.push_back((char)((pow((number)this->message[i] - 96, get<0>(_publicKey))) % get<1>(_publicKey) + 96));
			}
			else result.push_back((char)((pow((number)this->message[i] - 64, get<0>(_publicKey))) % get<1>(_publicKey) + 64));
		}
		return result;
	}


	string decrypt(string message) {
		string result = "";
		for ( number i = 0; i < message.length(); i++ ) {
			if ( message[i] == ' ' || message[i] == '.' || message[i] == ',' || message[i] == '?' || message[i] == ':' || message[i] == ';' || message[i] == '(' || message[i] == ')' || message[i] == '\'' || message[i] == '!' ) {
				result.push_back(message[i]);
				continue;
			} 
			if (message[i] > 96 ) {
				result.push_back((char)((pow((number)message[i]-96 , get<0>(_privateKey))) % get<1>(_privateKey) + 96));
			}
			else result.push_back((char)((pow((number)message[i]-64 , get<0>(_privateKey))) % get<1>(_privateKey) + 64));
		}
		return result;
	}
	string decrypt(string message,Key _privateKey) {
		string result = "";
		for ( number i = 0; i < message.length(); i++ ) {
			if ( message[i] == ' ' || message[i] == '.' || message[i] == ',' || message[i] == '?' || message[i] == ':' || message[i] == ';' || message[i] == '(' || message[i] == ')' || message[i] == '\'' || message[i] == '!' ) {
				result.push_back(message[i]);
				continue;
			}
			if ( message[i] > 96 ) {
				result.push_back((char)((pow((number)message[i] - 96, get<0>(_privateKey))) % get<1>(_privateKey) + 96));
			}
			else result.push_back((char)((pow((number)message[i] - 64, get<0>(_privateKey))) % get<1>(_privateKey) + 64));
		}
		return result;
	}

	static Key generatePublicKey(int p,int q) {
		Key seed = make_tuple(p,q);
		if ( get<0>(seed) == 0 || get<1>(seed) == 0 || !isPrime(get<0>(seed)) || !isPrime(get<1>(seed)) ) {
			throw "Numbers must be greater than 0 and prime!";
		}
		number n1 = get<0>(seed);
		number n2 = get<1>(seed);
		number N = n1 * n2;
		number PHI = getPhi(n1, n2);

		number e;
		for ( number i = 2; i < PHI; i++ ) {
			if ( isCoprime(i, N, PHI) ) {
				e = i;
				break;
			}
		}
		return make_tuple(e, N);
	}

	static Key generatePrivateKey(int p, int q) {
		Key seed = make_tuple(p, q);
		if ( get<0>(seed) == 0 || get<1>(seed) == 0 || !isPrime(get<0>(seed)) || !isPrime(get<1>(seed)) ) {
			throw "Numbers must be greater than 0 and prime!";
		}
		number n1 = get<0>(seed);
		number n2 = get<1>(seed);
		number N = n1 * n2;
		number PHI = getPhi(n1, n2);
		number e = get<0>(generatePublicKey(seed));
		number d = getDecryptPart(e, PHI);
		return make_tuple(d, N);
	}

	void setPublicKey(Key key) {
		this->_publicKey = key;
	}
	void setPrivateKey(Key key) {
		this->_privateKey = key;
	}

	string getMessage() {
		return this->message;
	}

};

