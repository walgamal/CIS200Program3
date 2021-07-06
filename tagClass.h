/*
Program Name: HTML TAG CHECKER
Programmer Name: Wasim Algamal
Description: Reads an HTML file and reports its information according to specific requirements
Date Created: 12/9/20
*/

#pragma once

using namespace std;
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct alphaNode {
	string tag;
	alphaNode* next;
	int occurences = 0;
};

struct node {
	string noMatchTag;
	node* next;
	int occurences = 0;
};

class Stack {
private:
	vector<string> tagVect;  
	int count;
public:
	//Description: Default constructor
	//Post-condition: Stack is created and empty - count = -1  
	Stack() {
		tagVect.clear();
		count = -1;
	}

	//Description: Destructor
	//Post-condition: Does nothing since I use a vector
	~Stack() {
		tagVect.clear();
	}

	//Description: Empties out stack
	//Pre-condition: pass the output file
	//Post-condition: Stack is made empty
	void MakeEmpty(fstream& outFile) {
		count = -1;
		tagVect.clear();
		cout << "Stack was emptied!\n";
		outFile << "Stack was emptied!\n";
	}

	//Description: Checks if stack is empty
	//Post-condition: Returns whether stack is empty or not
	bool IsEmpty() {
		if (count == -1) {
			return true;
		}
		else {
			return false;
		}
	}

	//Description: Tells stack's length size
	//Post-condition: return the number of elements in the stack
	int length() {
		return count + 1;
	}

	//Description: Prints stack
	//Pre-condition: pass the output file
	//Post-condition: Stack elements are all printed from the top to bottom
	void Print(fstream& outFile) {
		if (count == -1) {
			cout << "Nothing!\n";
			outFile << "Nothing!\n";
		}
		else {
			for (int i = 0; i <= count; i++) {
				cout << "<" << tagVect[i] << "> ";
				outFile << "<" << tagVect[i] << "> ";
			}
			cout << endl;
			outFile << endl;
		}
	}

	//Description: Adds element to stack
	//Pre-condition: memory is not full - pass element to add 
	//Post-condition: x is added to top of stack 
	void Push(string x) {
			count++;
			tagVect.push_back(x);
	}

	//Description: Removes element from top of stack 
	//Pre-condition: Stack is not empty - pass in x and pass the output file
	//Post-condition: Deletes top element and returns true if element was popped and false if not popped - x is popped element
	bool Pop(fstream& outFile) {
		if (count == -1) {
			cout << "ERROR: Stack underflow. ";
			outFile << "ERROR: Stack underflow. ";
			return false;
		}
		else {
			tagVect.pop_back();
			count--;
			return true;
		}
	}

	//Description: Peeks at top element
	//Pre-condition: Stack cannot be empty - pass the output file
	//Post-condition: Returns top element
	string Peek(fstream& outFile) {
		if (count == -1) {
			cout << "ERROR: Stack is empty. ";
			outFile << "ERROR: Stack is empty. ";
		}
		else {
			return tagVect[count];
		}
	}


};

