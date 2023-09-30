#include "Parsing.h"

void parsing::parseCommand(std::string& instructions, std::queue<std::string>& q){
	// Can assume that the names of the functions are free of errors
	std::string functionName = parsing::parseFunction(instructions);
	q.push(functionName);

	// if else if statements for each case
	if(functionName == "search"){
		// Check for name and or ID
		std::string token;

		// ID case
		if (instructions.find('"') == -1)
		{
			token = parsing::parseID(instructions);
		}
		else // name case
		{
			token = parsing::parseName(instructions);
		}
		q.push(token);
	}

	// insert
	else if(functionName == "insert"){
		std::string name = parsing::parseName(instructions);
		std::string ID = parsing::parseID(instructions);
		q.push(name);
		q.push(ID);
	}
	// Remove
	else if (functionName == "remove")
	{
		std::string ID = parsing::parseID(instructions);
		q.push(ID);
	}
	// RemoveInorder
	else if (functionName == "removeInorder")
	{
		std::string number = parsing::parseID(instructions);
		q.push(number);
	}
}

std::string parsing::parseFunction(std::string& instructions){
	size_t start = 0;
	size_t end = instructions.find_first_of(' ');
	return instructions.substr(start, end - start);
}

std::string parsing::parseName(std::string& instructions){
	size_t start = instructions.find_first_of('"') + 1;
	size_t end = instructions.find_last_of('"');
	return instructions.substr(start, end - start);
}

std::string parsing::parseID(std::string& instructions){
	size_t start = instructions.find_last_of(' ') + 1;
	return instructions.substr(start);
}