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
	Node * previous;
	int key;
	int value;
	int height;
	Node(int newKey, int newValue) {
		key = newKey;
		value = newValue;
		right = nullptr;
		left = nullptr;
		previous = nullptr;
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
				Node * previous, *temp, *test;
				int done = 1;
				while (done) { //gives me something to itterate over while I find a null value
					if (key < current->key) { //we are going to check to see if its going to be the left or right
						previous = current;
						current = current->left;
						if (!current) { //it was the left and I have found a null value so insert a new one
							current = new Node(key, value);
							current->previous = previous; //Make sure to update the previous the print wont work
							previous->left = current;
							test = current;//This block itterates through the tree to make sure we don't need to balance it out.
							while (test) {
								int height1 = height(test->left);
								int height2 = height(test->right);
								if ((height1 - height2) == 2) {
									singleRight(test);
								}
								else if ((height2 - height1) == 2) {
									doubleRight(test);
								}
								test = test->previous;
							}
							temp = previous; //the lower block of this code controls the updating of heights
							while (temp) {
								temp->height = height(temp);
								temp = temp->previous;
							}
							size++;
							done = 0;
						}
					}
					else if (key > current->key) { //like above we are going over the tree to the right
						previous = current;
						current = current->right;
						if (!current) { //looks like we found it on the right and we have a null value to insert it
							current = new Node(key, value);
							current->previous = previous; //Make sure to update the previous the print wont work
							previous->right = current;
							test = current;//This block itterates through the tree to make sure we don't need to balance it out.
							while (test) {
								int height1 = height(test->right);
								int height2 = height(test->left);
								if ((height1 - height2) == 2) {
									singleLeft(test);
								}
								else if ((height2 - height1) == 2) {
									doubleLeft(test);
								}
								test = test->previous;
							}
							temp = previous;//the lower block of this code controls the updating of heights
							while (temp) {
								temp->height = height(temp);
								temp = temp->previous;
							}
							size++;
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

	/*Returns the height of the head of the tree*/
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
			recursivePrint(head->right, count); //calls itself to the left
			for (int i = 0; i < count; i++) {
				cout << "      "; //Prints enough spaces to look nice
			}
			cout << head->key << "," << head->value << endl; //prints out the current node
			recursivePrint(head->left, count); //calls itself to the right

		}
	}

	/*Used in with conjunction of the insert method to update height of each node recursively of course*/
	int height(Node * current) {
		if (!current) { //base case
			return 0;
		}
		int counter1 = height(current->left);
		int counter2 = height(current->right);
		if (counter1 > counter2) { //falls down the tree to add up the heights
			current->height = counter1 + 1;
			return counter1 + 1;
		}
		current->height = counter2 + 1;
		return counter2 + 1;
	}

	/*Is used by insert to balance out the tree to the left. Its kind of a mess I know.*/
	void singleRight(Node * current) {
		Node * temp;//The following jumble does a single left rotation by moving around everything
		temp = current->left;
		current->left = temp->right;
		temp->right = current;
		temp->previous = current->previous; //dont forget to set the previous values! or you'll get a stack overflow...
		if (current->left) {
			current->left->previous = current;
		}
		if (current == head) { //need to make sure we dont need to change the head
			temp->previous = nullptr;
			head = temp;
		}
		else if (current->previous->left == current) { //change the right value so it will properly print out
			current->previous->left = temp;
		}
		else {
			current->previous->right = temp;
		}
		current->previous = temp;
	}

	/*Is used by insert to balance out the tree to the right. It is practically the same as above but with a few left or rights changed.*/
	void singleLeft(Node * current) {
		Node * temp;
		temp = current->right;
		current->right = temp->left;
		temp->left = current;
		temp->previous = current->previous;
		if (current->left) {
			current->left->previous = current;
		}
		if (current == head) {
			temp->previous = nullptr;
			head = temp;
		}
		else if (current->previous->right == current) {
			current->previous->right = temp;
		}
		else {
			current->previous->left = temp;
		}
		current->previous = temp;
	}

	/*Double rotation to keep everything balanced for the left.*/
	void doubleLeft(Node * current) {
		Node * temp;//I really tried to use the old stuff but I couldn't. Works a lot like singleLeft and singleRight.
		temp = current->left->right;
		temp->left = current->left;
		temp->right = current;
		temp->left->previous = temp;
		temp->left->right = nullptr;
		temp->right->left = nullptr;
		temp->previous = current->previous;
		if (current == head) {
			temp->previous = nullptr;
			head = temp;
		}
		else if (current->previous->right == current) {
			current->previous->right = temp;
		}
		else {
			current->previous->left = temp;
		}
		current->previous = temp;
	}

	/*Double rotation to keep everything balanced for the right. Like the previous.*/
	void doubleRight(Node * current) {
		Node * temp; //I really tried to use the old stuff but I couldn't. Works a lot like singleLeft and singleRight.
		temp = current->right->left;
		temp->right = current->right;
		temp->left = current;
		temp->right->previous = temp;
		temp->right->left = nullptr;
		temp->left->right = nullptr;
		temp->previous = current->previous;
		if (current == head) {
			temp->previous = nullptr;
			head = temp;
		}
		else if (current->previous->right == current) {
			current->previous->right = temp;
		}
		else {
			current->previous->left = temp;
		}
		current->previous = temp;
	}
};