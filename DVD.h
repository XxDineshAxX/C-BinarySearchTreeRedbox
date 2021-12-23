/*
 * DVD.h
 *
 *  Created on: Oct 21, 2020
 *      Author: Dinesh Angadipeta DXA@190032
 */

#ifndef DVD_H_
#define DVD_H_
#include<iostream>
using namespace std;
class DVD {
public:
	DVD();
	~DVD();
	DVD(string t, int a, int r){title = t; available = a; rented = r;};

	string getTitle(){return title;};
	void setTitle(string t){this->title = t;};

	int getAvailable(){return available;};
	void setAvailable(int a){this->available = a;};

	int getRented(){return rented;};
	void setRented(int r){this->rented = r;};

	bool operator<(const DVD &rhs);
	bool operator<(const string &rhs);
	bool operator>(const DVD &rhs);
	bool operator>(const string &rhs);
	bool operator==(const DVD &rhs);
	bool operator==(const string &rhs);


protected:
	string title;
	int available;
	int rented;
};

#endif /* DVD_H_ */
