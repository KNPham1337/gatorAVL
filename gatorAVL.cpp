#include <iostream>
#include <queue>
#include "Tree.h"
#include "Parsing.h"
#include "Validate.h"
#include <vector>

using namespace std;

/* Note: 
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope. 
*/


// void runCommand(std::queue<std::string>& finalCommands, MyAVLTree& tree);

int main(){

    vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};

    for (const string& word : msg)
    {
        cout << word << " ";
    }
    cout << endl;
	
	MyAVLTree tree;	
/*	tree.search(12345678);
tree.search("Adam");
tree.insert("Adam", 12345678);
tree.search(23456789);
tree.search(12345678); */

/* 	std::string command;
	unsigned int num_commands;
	std::queue<std::string> commands;

	// Get number of commands
	std::getline(std::cin, command);
	num_commands = stoi(command);

	// Get each commmand string
	for (unsigned int i = 0; i < num_commands; i++){
		std::getline(std::cin, command);
		commands.push(command);
	}

	// Separate the commands into function names, student names, and ID
	std::queue<std::string> finalCommands;
	while (!commands.empty()){
		parsing::parseCommand(commands.front(), finalCommands);
		runCommand(finalCommands, tree);
		commands.pop();
	} */
 
	return 0;
}

/* void runCommand(std::queue<std::string>& finalCommands, MyAVLTree& tree){
	std::string function = finalCommands.front();
	finalCommands.pop();

	if (function == "search"){
		std::string nameID = finalCommands.front();
		finalCommands.pop();

		if(validate::validateID(nameID))
			tree.search(stoi(nameID));
		else if (validate::validateName(nameID))
			tree.search(nameID);
		else
			std::cout << "unsuccessful\n";
	}
	else if(function == "insert"){
		// Tree.insert(name, ID)

		std::string name = finalCommands.front();
		finalCommands.pop();
		std::string ID = finalCommands.front();
		finalCommands.pop();

		if (validate::validateID(ID) && validate::validateName(name)){
			tree.insert(name, stoi(ID));
		}
		else
			std::cout << "unsuccessful\n";

	}
	else if (function == "remove"){
		// Tree.remove(ID)
		if(validate::validateID(finalCommands.front()))
			tree.remove(stoi(finalCommands.front()));
		else 
			std::cout << "unsuccessful\n";
		finalCommands.pop();
	}
	else if(function == "removeInorder"){
		if(validate::validateNumber(finalCommands.front()))
			tree.removeInorder(stoi(finalCommands.front()));
		else 
			std::cout << "unsuccessful\n";
		finalCommands.pop();
	}
	else if(function == "printInorder"){
		tree.printInorder();
	}
	else if(function == "printPreorder"){
		tree.printPreorder();
	}
	else if(function == "printPostorder"){
		tree.printPostorder();
	}
	else{
		tree.printLevelCount();
	}
} 
 */
/*
tree.search(12345678);
tree.search("Adam");
tree.insert("Adam", 12345678);
tree.search(23456789);
tree.search(12345678);
*/

/*
tree.insert("David", 31239830);
tree.insert("Danielle", 27782901);
tree.insert("David", 11133245);
tree.search("Danielle");
tree.search("David");
tree.search(11133245);
tree.search(27782901);
tree.search(31239830);
*/

/*
tree.insert("Evan", 44985771);
tree.insert("Earl", 31834874);
tree.insert("Erica", 21456789);
tree.printLevelCount();
tree.insert("Enrique", 17891824);
tree.printLevelCount();
tree.printPreorder();
*/

/*
tree.insert("Brandon", 45674567);
tree.insert("Brian", 35455565);
tree.insert("Briana", 87878787);
tree.insert("Bella", 95462138);
tree.printInorder();
tree.remove(45674567);
tree.removeInorder(2);
tree.printInorder();
*/

/*
tree.insert("Caroline", 50005000);
tree.insert("Cory", 35354334);
tree.insert("Cecilia", 76543210);
tree.insert("Carla", 56567342);
tree.insert("Cody", 83711221);
tree.insert("Chris", 17449900);
tree.printInorder();
tree.printPreorder();
tree.printPostorder();
*/