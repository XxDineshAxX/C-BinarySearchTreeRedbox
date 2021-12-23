/*
 * BSTree.h
 *
 *  Created on: Oct 21, 2020
 *      Author: Dinesh Angadipeta DXA@190032
 */

#ifndef BSTREE_H_
#define BSTREE_H_
#include "Node.h"
#include <fstream>
#include <sstream>
using namespace std;
template<class T>
class BSTree {
public:
	~BSTree();
	BSTree() {
		root = nullptr;
	}
	;
	BSTree(string filename);

	Node<T>* getRoot() {
		return root;
	}
	;
	void setRoot(Node<T> *&r) {
		this->root = r;
	}
	;

	void insert(string name, int av, int rt);
	void destructorHelper(Node<T> *curr);
	Node<T>* search(string name);
	Node<T>* deleter(string name);
protected:
	Node<T> *root;
};
//This is where the binary search tree is created.
template<class T>
BSTree<T>::BSTree(string filename) {
	//This is where the root var is initialized
	root = new Node<T>;
	//These variables will help in translating the file input into variables that can be put into the binary search tree.
	string holder;
	string movieTitle;
	string dummy;
	string availString;
	int quantAvail;
	string rentedString;
	int quantRented;
	//These nodes will help with the traversal and creation of the tree.
	Node<T> *curr;
	Node<T> *hold;
	//This is used to get the file input.
	ifstream infile;
	infile.open(filename);
	if (infile) {
		//Each iteration of the while loop is for the each of the movies in the file. This line helps hold each of the lines in the file.
		while (getline(infile, holder)) {
			//This block of code helps split and decipher the line from the file and puts the values in respective  vars.
			stringstream line(holder);
			getline(line, dummy, '"');
			getline(line, movieTitle, '"');
			getline(line, dummy, ',');
			getline(line, availString, ',');
			quantAvail = stoi(availString);
			getline(line, rentedString, ',');
			quantRented = stoi(rentedString);
			//This turns the vars into the dvd object, which is generic here due to the templated abilities of the class.
			T *t = new T(movieTitle, quantAvail, quantRented);
			hold = new Node<T>(nullptr, nullptr, *t);
//Checks if root is given values yet, if it hasn't been initialized, the root is truly created here.
			if (root->getPayload() == "") {
				root->setPayload(*t);
				root->setLeft(nullptr);
				root->setRight(nullptr);
			} else {
				curr = root;
				//This while loop constantly traverses and inserts node pointers, which the curr node helps with, to create the bst.
				while (curr != nullptr) {
//left subtree
					if (curr->getPayload() > t->getTitle()) {
						if (curr->getLeft() == nullptr) {
							curr->setLeft(hold);
							curr = nullptr;
						} else {
							curr = curr->getLeft();
						}
						//right subtree.
					} else {
						if (curr->getRight() == nullptr) {
							curr->setRight(hold);
							curr = nullptr;
						} else {
							curr = curr->getRight();
						}

					}
				}
			}

		}
	}
}
//This method helps with inserting single nodes into the bst.
template<class T>
void BSTree<T>::insert(string name, int av, int rt) {
	//Essentially same logic as the bst creation, except for only one node.
	Node<T> *curr;
	T *t = new T(name, av, rt);
	Node<T> *hold = new Node<T>(nullptr, nullptr, *t);
	//checks if tree is empty.
	if (root == nullptr) {
		root = hold;
	} else {
		curr = root;
		//else loops through the tree and finds an empty spot.
		while (curr != nullptr) {
//goes into left subtree
			if (curr->getPayload() > t->getTitle()) {
				if (curr->getLeft() == nullptr) {
					curr->setLeft(hold);
					curr = nullptr;
				} else {
					curr = curr->getLeft();
				}
				//goes into right subtree
			} else {
				if (curr->getRight() == nullptr) {
					curr->setRight(hold);
					curr = nullptr;
				} else {
					curr = curr->getRight();
				}

			}
		}
	}
}
//This helps search the bst for a node.
template<class T>
Node<T>* BSTree<T>::search(string name) {
	Node<T> *curr;

	curr = root;
	//this loop iterates through each node, checking if the name given is equal to the name of the current node, and if it isn't, it moves into the proper subtree.
	while (curr != nullptr) {

		if (curr->getPayload() == name) {
			return curr;
		} else if (curr->getPayload() > name) {
			curr = curr->getLeft();
		} else {
			curr = curr->getRight();
		}
	}
	//returns nullptr if node isn't found.
	return nullptr;
}
//This helps delete a node from the tree.
template<class T>
Node<T>* BSTree<T>::deleter(string name) {
	//These nodes help hold and delete the nodes.
	Node<T> *curr = root;
	Node<T> *previous = nullptr;
//This loop here helps increment to the node being deleted, it is very similar to the search function above.
	while (curr != nullptr) {
		if (curr->getPayload() == name) {
			break;
		} else if (curr->getPayload() > name) {
			previous = curr;
			curr = curr->getLeft();
		} else {
			previous = curr;
			curr = curr->getRight();
		}
	}
	if (curr != nullptr) {
		//Case for 0 children
		if (curr->getLeft() == nullptr && curr->getRight() == nullptr) {
			//Case for if root is being deleted.
			if (previous == nullptr) {
				root = nullptr;
				//Else the previous node is pointed to nullptr at the respective locations.
			} else if (previous->getLeft() == curr) {
				previous->setLeft(nullptr);
			} else {
				previous->setRight(nullptr);
			}
			//Case for 2 children
		} else if (curr->getLeft() && curr->getRight()) {
			//This helps hold the node to be deleted value.
			Node<T> *holder = curr;
			previous = curr;
			curr = curr->getLeft();
			//This loop here gets the predecessor of the node to be deleted.
			while (curr->getRight()) {
				previous = curr;
				curr = curr->getRight();
			}
			//Checks for cases of being the root of a subtree.
			if (previous->getLeft() == curr) {
				previous->setLeft(curr->getLeft());
			} else {
				previous->setRight(curr->getLeft());
			}
			//This is where the node is "deleted", essentially it has its values replaces, and the minimum is disconnected
			T tempHolder = holder->getPayload();
			holder->setPayload(curr->getPayload());
			curr->setPayload(tempHolder);
			curr->setLeft(nullptr);
			//Case for 1 children
		} else {
			if (!previous && curr->getLeft()) {
				root = curr->getLeft();
			} else if (!previous) {
				root = curr->getRight();
			} else if (previous->getLeft() == curr && curr->getLeft()) //LL
					{
				previous->setLeft(curr->getLeft());

			} else if (previous->getLeft() == curr)  // LR
					{
				previous->setLeft(curr->getRight());

			} else if (previous->getRight() == curr && curr->getLeft())  //RL
					{
				previous->setRight(curr->getLeft());

			} else //RR
			{
				previous->setRight(curr->getRight());
			}
			curr->setLeft(nullptr);
			curr->setRight(nullptr);
		}
	}

	return curr;

}
//This helps recursively destroy the binary search tree at the end of the program
template<class T>
void BSTree<T>::destructorHelper(Node<T> *curr) {

	if (curr != nullptr) {
		destructorHelper(curr->getLeft());
		destructorHelper(curr->getRight());
		delete curr;
	}
}
//This is the destructor of the binary search tree, which helps free the memory it allocates at the end.
template<class T>
BSTree<T>::~BSTree() {

	destructorHelper(root);
}

#endif /* BSTREE_H_ */

