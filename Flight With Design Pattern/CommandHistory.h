#ifndef COMMAND_HISTORY_H
#define COMMAND_HISTORY_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class CommandHistory
{
private:
	vector<string> history;

public:
	// Constructor
	CommandHistory();

	// Get history
	vector<string> getHistory();

	// Add command to history
	void addCommandToHistory(string commandToAdd);

	// Print all commands history
	void printAllCommandsHistory();
};



#endif // !COMMAND_HISTORY_H