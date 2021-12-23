/*
 * Node.h
 *
 *  Created on: Oct 21, 2020
 *      Author: Dinesh Angadipeta DXA@190032
 */

#ifndef NODE_H_
#define NODE_H_
template<class T>
class Node{
public:
	Node(){left = nullptr; right = nullptr; payload = T();};

	Node(Node *l, Node *r, T obj){left = l; right = r; payload = obj;};

	Node<T>* getLeft(){return left;};
	void setLeft(Node <T>*l){this->left = l;};

	Node<T>* getRight(){return right;};
	void setRight(Node <T>*r){this->right = r;};

	T getPayload(){return payload;};
	void setPayload(T p){this->payload = p;};
protected:
	Node<T> *left;
	Node<T> *right;
	T payload;
};

#endif /* NODE_H_ */


