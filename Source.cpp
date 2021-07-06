/*
Program Name: HTML TAG CHECKER
Programmer Name: Wasim Algamal
Description: Reads an HTML file and reports its information according to specific requirements
Date Created: 12/9/20
*/

#include "tagClass.h"

using namespace std;
#include <iostream>
#include <fstream>
#include <string>

int main() {
	
	//VARIABLE DECLERATIONS
	char tmp; 
	bool enter;
	string line;
	string currentTag;
	string fileInUse = "\0";
	fstream inFile;
	fstream dupeFile;
	fstream outFile;
	node* front = NULL;
	node* rear = NULL;
	alphaNode* alphaFront = NULL;
	alphaNode* alphaRear = NULL;
	alphaNode* newNode = NULL;
	Stack myStack;

	outFile.open("Results.txt");

	//ASK USER TO ENTER HTML FILE NAME AND VERIFY NOT EMPTY
	while (fileInUse == "\0") {
		cout << "Please enter an HTML file name: ";
		outFile << "Please enter an HTML file name: ";
		cin >> fileInUse;
		outFile << fileInUse << endl;

		inFile.open(fileInUse);
		if (inFile.peek() == ifstream::traits_type::eof()) {
			cout << "YOU HAVE USED AN EMPTY FILE! TRY AGAIN!\n";
			fileInUse = "\0";
		}
		else {
			break;
		}
		inFile.close();
	}

	dupeFile.open(fileInUse);

	//PRINT HTML FILE TO OUTPUT AND SCREEN
	cout << "HTML FILE:" << endl;
	outFile << "HTML FILE:" << endl;
	while (!dupeFile.eof()){
		getline(dupeFile, line);
		cout << line << endl;
		outFile << line << endl;
	}

	//SYSTEM PROCESSING
	cout << "SYSTEM PROCCESSING: " << endl;
	outFile << "SYSTEM PROCCESSING: " << endl;
	while (!inFile.eof()) {
		
		inFile.get(tmp);

		//FIND TAGS USING CARROTS
		if (tmp == '<') {
			cout << "Tag found";
			outFile << "Tag found";
			inFile.get(tmp);

			//ENSURE SYNTAX OF CARROTS IS CORRECT
			if (tmp == '<') {
				cout << "\nERROR: DOUBLE OPEN BRACKET!";
				outFile << "\nERROR: DOUBLE OPEN BRACKET!";
			}

			//FIND END TAGS USING '/'
			if (tmp == '/') {
				inFile.get(tmp);

				cout << "\nCLOSING TAG: ";
				outFile << "\nCLOSING TAG: ";
				while (tmp != '>') {
					cout << tmp;
					outFile << tmp;
					currentTag += tmp;
					inFile.get(tmp);
				}

				//MATCH CLOSE TAG WITH OPEN TAGS TO CALL POP
				if (currentTag == myStack.Peek(outFile)) {
					myStack.Pop(outFile);
				}
				else {
					//IF NOT MATCHED, PRINT ERROR
					cout << "\nERROR: CLOSING TAG IN WRONG POSITION!";
					outFile << "\nERROR: CLOSING TAG IN WRONG POSITION!";
				}
				
			}
			else {
				//CHECK FOR <P>, <BR>, and <IMG ...> - DO NOT add these to Stack, add to a LINKED LIST
				cout << "\nOPENING TAG: ";
				outFile << "\nOPENING TAG: ";

				while (tmp != '>') {
					cout << tmp;
					outFile << tmp;
					currentTag += tmp;
					inFile.get(tmp);

					if (currentTag == "IMG") {
						break;
					}
				}

				//INSERT ALL OPENING AND NON-MATCHING TAGS INTO ALPHA LIST SORTED
				//ALSO COUNT OCCURRENCES!
				if (alphaFront == NULL) {
					alphaFront = new alphaNode;
					alphaFront->tag = currentTag;
					alphaFront->next = NULL;
					alphaFront->occurences++;
				}
				else if (currentTag == alphaFront->tag) {
					alphaFront->occurences++;
				}
				else {
					newNode = new alphaNode;
					newNode->tag = currentTag;
					newNode->next = NULL;
					newNode->occurences++;

					alphaNode* curr = alphaFront;
					alphaNode* trail = NULL;

					while (curr != NULL) {
						if (curr->tag == newNode->tag) {
							curr->occurences++;
							break;
						}
						else if(curr->tag > newNode->tag){
							if (curr == alphaFront) {
								newNode->next = alphaFront;
								alphaFront = newNode;
							}
							else {
								newNode->next = curr;
								trail->next = newNode;
							}

							break;
						}
						else if (curr->next == NULL) {
							curr->next = newNode;
							break;
						}
						else {
							trail = curr;
							curr = curr->next;
						}
					}
				}

				if (currentTag != "P" && currentTag != "BR" && currentTag != "IMG") {
					//PUSH Stack with openig tags
					myStack.Push(currentTag);
				}
				else {
					//ADD TO A LINKED LIST if <P>, <BR>, and <IMG ...> 
					if (front == NULL) {
						front = new node;
						front->noMatchTag = currentTag;
						front->next = NULL;
						front->occurences++;
					}
					else if (front->noMatchTag == currentTag) {
						front->occurences++;
					}
					else {
						node* temp = front;
						enter = true;

						while (temp->next != NULL) {
							if (temp->noMatchTag == currentTag) {
								temp->occurences++;
								enter = false;
								break;
							}

							if (temp->next->noMatchTag == currentTag) {
								temp->next->occurences++;
								enter = false;
								break;
							}

							temp = temp->next;
						}

						if (enter == true) {
							rear = new node;
							rear->noMatchTag = currentTag;
							rear->occurences++;
							rear->next = NULL;
							temp->next = rear;
						}
					}
				}
			}
			currentTag.clear();
			cout << endl;
			outFile << endl;
		}
	}
	cout << endl;
	outFile << endl;

	//LINKED LISTS' INFORMATIONS
	cout << "NON-MATCHING TAGS LIST:\n";
	outFile << "NON-MATCHING TAGS LIST:\n";
	node* temp = front;

	while (temp != NULL) {
		cout << "TAG: <" << temp->noMatchTag << "> ---- OCCURRENCES: " << temp->occurences << endl;
		outFile << "TAG: <" << temp->noMatchTag << "> ---- OCCURRENCES: " << temp->occurences << endl;
		temp = temp->next;
	}
	cout  << endl << "ALPHABETICAL LIST:\n";
	outFile << endl << "ALPHABETICAL LIST:\n";
	alphaNode*	alphaTemp = alphaFront;

	while (alphaTemp != NULL) {
		cout << "TAG: <" << alphaTemp->tag << "> ---- OCCURRENCES: " << alphaTemp->occurences << endl;
		outFile << "TAG: <" << alphaTemp->tag << "> ---- OCCURRENCES: " << alphaTemp->occurences << endl;
		alphaTemp = alphaTemp->next;
	}
	cout << endl;
	outFile << endl;

	delete front;
	delete rear;
	delete alphaFront;
	delete alphaRear;

	//STACK INFORMATION
	cout << "STACK INFO: " << endl;
	cout << "LENGTH: " << myStack.length() << endl;
	cout << "TAGS NOT PROPERLY CLOSED: ";

	outFile << "STACK INFO: " << endl;
	outFile << "LENGTH: " << myStack.length() << endl;
	outFile << "TAGS NOT PROPERLY CLOSED: ";
	myStack.Print(outFile);

	//CLOSE ALL FILES
	inFile.close();
	dupeFile.close();
	outFile.close();

	system("pause");
	return 0;
}