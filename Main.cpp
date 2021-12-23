//============================================================================
// Name        : Main.cpp
// Author      : Dinesh Angadipeta DXA@190032
// Description : Project Three for CS 2337
//============================================================================

#include "DVD.h"
#include "Node.h"
#include "BSTree.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <math.h>
using namespace std;
//This helps check if a certain string can be converted into an integer.
bool isValid(string s) {
	for (int i = 0; (unsigned) i < s.length(); i++) {
		if (isdigit(s[i]) == false || s.at(i) == '.') {
			return false;

		}
	}
	return true;
}
//This is the main function of the code, where the transaction log is processed.
void transaction(string transac, BSTree<DVD> &bst) {
	string holder;
	string order;
	string name;
	string sNum;
	int num;
	string dummy;
	Node<DVD> *check;
	DVD dvdHolder;
	ifstream infile;
	ofstream outfile;
	//This outfile will be used to send invalid transactions to the error log .
	outfile.open("error.log");
	infile.open(transac);
	if (infile) {
		//Loops for each of the transactions.
		while (getline(infile, holder)) {
			stringstream line(holder);
			getline(line, order, ' ');
			//This is where an add transaction is processed.
			if (order == "add") {
				//The rest of the order is processed here.
				getline(line, dummy, '"');
				getline(line, name, '"');
				getline(line, dummy, ',');
				getline(line, sNum, ',');
				//Checks if part of transaction is valid.
				if (isValid(sNum) && dummy == "" && sNum.length()>0) {
					num = stoi(sNum);
					//This var helps search for the node being processed.
					check = bst.search(name);
					//This is where the add order is processed.
					if (check != nullptr) {
						dvdHolder = check->getPayload();
						dvdHolder.setAvailable(dvdHolder.getAvailable() + num);
						check->setPayload(dvdHolder);
					} else {
						bst.insert(name, num, 0);
					}
					//If invalid, this is where the error is printed out.
				} else {
					outfile << holder;
					outfile << "\n";
				}
				//This is where the remove order is processed.
			} else if (order == "remove") {
				getline(line, dummy, '"');
				getline(line, name, '"');
				getline(line, dummy, ',');
				getline(line, sNum, ',');
				//Validation
				if (isValid(sNum) && dummy == "" && sNum.length()>0) {
					num = stoi(sNum);
					check = bst.search(name);
					//This is where the remove order is processed.
					//Validation
					if (check != nullptr) {
						dvdHolder = check->getPayload();
						dvdHolder.setAvailable(dvdHolder.getAvailable() - num);
						check->setPayload(dvdHolder);
						if (dvdHolder.getAvailable() == 0
								&& dvdHolder.getRented() == 0) {
							bst.deleter(name);

						}
						//Error outputted
					} else {
						outfile << holder;
						outfile << "\n";
					}
					//Error outputted.
				} else {
					outfile << holder;
					outfile << "\n";
				}
//This is where the rent order is processed.
			} else if (order == "rent") {
				getline(line, dummy, '"');
				getline(line, name, '"');
				getline(line, dummy);
				if (dummy.length() == 0) {
					check = bst.search(name);
					//Validation
					if (check != nullptr) {
						//This is where the rent is processed.
						dvdHolder = check->getPayload();
						dvdHolder.setAvailable(dvdHolder.getAvailable() - 1);
						dvdHolder.setRented(dvdHolder.getRented() + 1);
						check->setPayload(dvdHolder);
						//Error output
					} else {
						outfile << holder;
						outfile << "\n";
					}
				} else {
					outfile << holder;
					outfile << "\n";
				}
				//This is where the return method is processed.
			} else if (order == "return") {
				getline(line, dummy, '"');
				getline(line, name, '"');
				getline(line, dummy);
				if (dummy.length() == 0) {
					check = bst.search(name);
					//Validation
					if (check != nullptr) {
						//This is where return is processed.
						dvdHolder = check->getPayload();
						dvdHolder.setAvailable(dvdHolder.getAvailable() + 1);
						dvdHolder.setRented(dvdHolder.getRented() - 1);
						check->setPayload(dvdHolder);
						//Validation output.
					} else {
						outfile << holder;
						outfile << "\n";
					}
				} else {
					outfile << holder;
					outfile << "\n";
				}
			} else {
				outfile << holder;
				outfile << "\n";
			}

		}
	}
}
//This is where the report of the bst is outputted recursively.
void report(Node<DVD> *curr) {
	DVD dvdHolder;
	if (curr == nullptr) {
		return;
	}
	report(curr->getLeft());
	dvdHolder = curr->getPayload();
	cout << dvdHolder.getTitle() << setw(39 - dvdHolder.getTitle().length())
			<< dvdHolder.getAvailable() << setw(11) << dvdHolder.getRented()
			<< endl;
	report(curr->getRight());
}

int main() {
	//This is the user input part of the program.
	string inventory;
	string transact;
	cout << "Enter inventory filename name: ";
	cin >> inventory;
	cout << endl;
	cout << "Enter transaction filename name: ";
	cin >> transact;
	cout << endl;
	//bst initialized.
	BSTree<DVD> redbox(inventory);
	transaction(transact, redbox);
	report(redbox.getRoot());

	return 0;
}

