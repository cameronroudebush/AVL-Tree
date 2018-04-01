#pragma once
#include <iostream>
#define NULLNODE NULL //Needed to use these two for the find method
#define NODEPTR Node*
#include <vector>

using namespace std;

/*Gotta have a way to store all of our important information right?*/
class Node {
public:
	Node * right;
	Node * left;
	int key;
	int value;
	int height;
	Node(int newKey, int newValue) {
		key = newKey;
		value = newValue;
		right = nullptr;
		left = nullptr;
		height = 1;
	}
};

/*Youll find the meat of the project somewhere in here*/
class AVLTree {
public:
	Node * head;
	int size;
	AVLTree() {
		head = nullptr;
		size = 0;
	}

	/*Inserts a value into the tree so long it already doesn't exist. If it does it exist it will return a false boolean
		else it will return true. Also updates all of the tree heights and the size of the overall tree*/
	bool insert(int key, int value) {
		if (head == nullptr) { //if the head is empty we can just toss it in there. Also don't need to check if its already in the tree
			head = new Node(key, value);
			size++;
			return true; //woo it worked!
		}
		else {
			if (!recursiveFindKeyBool(head, key)) { //make sure the key isnt already in the tree
				Node * current = head;
				Node * previous = head;
				int done = 1;
				while (done) { //gives me something to itterate over while I find a null value
					if (current->key < key) { //we are going to check to see if its going to be the left or right
						previous = current;
						current = current->left;
						if (!current) { //it was the left and I have found a null value so insert a new one
							current = new Node(key, value);
							previous->left = current; //Make sure to update the previous left or the print wont work
							size++;
							updateHeights();
							done = 0;
						}
					}
					else if (current->key >= key) { //like above we are going over the tree to the right
						previous = current;
						current = current->right;
						if (!current) { //looks like we found it on the right and we have a null value to insert it
							current = new Node(key, value);
							previous->right = current;
							size++;
							updateHeights();
							done = 0;
						}
					}
				}
				return true; //everyting worked fine
			}
			else {
				return false; //in the case it is already in the tree
			}
		}
	}

	/*Prints the tree sideways to make it all nice and pretty*/
	void print() {
		int count = -1; //because using 0 didn't work
		recursivePrint(head, count); //call the recursive version so I save like a billion lines
	}

	/*Kind of self explanitory but returns the size that is kept track of when adding a new node*/
	int getSize() {
		return size;
	}

	/*Returns the height of the head of the tree that is kept track of from updaingTrees*/
	int getHeight() {
		return head->height;
	}

	/*Calls the recursive find to be able to find the address of where the key is located and replace the value of that key*/
	bool find(int key, int& value) {
		Node * temp = recursiveFindKeyAddress(head, key); //call the recursive version and give me a temp node to work with
		if (temp != NULLNODE) { //as long as its not null we can deal with it
			temp->value = value; //just set the value because of public variables
			return true; //we did it!
		}
		return false; //Houston we have a problem
	}

	/*Returns a vector of keys and values for anything with a key inside the lowKey and highKey variables*/
	vector<int> findRange(int lowKey, int highKey) {
		vector<int> list; //make a list to pass through
		return recursiveFindKeyVector(head, lowKey, highKey, list); //call the recursive version because recursion is great and makes my head hurt
	}

private:
	/*What was this used for again... Oh right used to make sure that a key isn't already in the tree. This recursive version is used when adding
		a new node much earlier in the code*/
	bool recursiveFindKeyBool(Node * current, int keyToFind) {
		if (!current) { //base case
			return false;
		}
		if (current->key == keyToFind) {
			return true; //found the key so we've got a problem
		}
		else {
			bool returner = recursiveFindKeyBool(current->left, keyToFind); // call a recursive search on the left side
			if (returner) {
				return returner; //if we already found it then just start the return process instead of searching the right side
			}
			return recursiveFindKeyBool(current->right, keyToFind); // call a recursive search on the right side
		}
	}
	/*Used in the find method to find the address of the key we gave*/
	NODEPTR recursiveFindKeyAddress(Node * current, int keyToFind) {
		if (!current) { //base case
			return NULLNODE;
		}
		if (current->key == keyToFind) { 
			return current; //congrats we found it! Go ahead and return it so I can deal with it
		}
		else {
			Node * temp = recursiveFindKeyAddress(current->left, keyToFind); // call a recursive search on the left side
			if (temp) {
				return temp; //If we found it go ahead and return instead of searching the right side
			}
			return recursiveFindKeyAddress(current->right, keyToFind); // call a recursive search on the right side
		}
	}

	/*I love writing these. I wonder if you even see them. Anyways this one is used to recursively add the key and value into a vector so long that
		the key is within range of highKey and lowKey.*/
	vector<int> recursiveFindKeyVector(Node * current, int lowKey, int highKey, vector<int> &list) {
		if (!current) { //base case
			return list;
		}
		if ((current->key >= lowKey) && (current->key <= highKey)) { //If you satisfy both of these conditions you have made it and are acceptable to add it to the list
			list.push_back(current->key);
			list.push_back(current->value);
		}
		recursiveFindKeyVector(current->left, lowKey, highKey, list); // call a recursive search on the left side
		recursiveFindKeyVector(current->right, lowKey, highKey, list); // call a recursive search on the right side
		return list; //return everything we found so we can return it back to who wanted it
	}

	/*Recursively prints the entire AVLTree sideways to make everything pretty*/
	void recursivePrint(Node * head, int count) {
		if (!head) {
			return; //base case
		}
		else {
			count++; //before we call left we should shove everything over a bit
			recursivePrint(head->left, count); //calls itself to the left
			for (int i = 0; i < count; i++) {
				cout << "      "; //Prints enough spaces to look nice
			}
			cout << head->key << "," << head->value << endl; //prints out the current node
			recursivePrint(head->right, count); //calls itself to the right

		}
	}

	/*This method is only used as an inbetween point that the user never needs to touch. Hands off!*/
	void updateHeights() {
		updateHeightsRecursive(head); //Call the recursive version
	}

	/*This method is used to recursively run through the list and update the heights of every node. The goal here is to make it easier for myself
		when I go to do the auto balancing*/
	int updateHeightsRecursive(Node * current) {
		if (!current) { //base case
			return 0;
		}
		int counter1 = updateHeightsRecursive(current->left); //navigate down the tree to the right
		int counter2 = updateHeightsRecursive(current->right); //navigate to the left!
		if (counter1 > counter2) { //well if one is greater than the other then we need to use that number
			current->height = counter1 + 1; //update the height
			return current->height; //return it for the recursion to use in the future (or is it considered the past?)
		}
		else { //either we didn't get a higher value or the second one is bigger
			current->height = counter2 + 1; //update the height
			return current->height; //return it like above
		}
	}
};