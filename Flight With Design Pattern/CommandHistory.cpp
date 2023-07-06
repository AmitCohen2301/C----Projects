#include "CommandHistory.h"

// Constructor
CommandHistory::CommandHistory() {}

// Gets
vector<string> CommandHistory::getHistory() // Get history
{
	return this->history;
}

// Add command to history
void CommandHistory::addCommandToHistory(string commandToAdd)
{
	this->history.push_back(commandToAdd);
}

// Print all commands history
void CommandHistory::printAllCommandsHistory()
{
	cout << "Commands History:" << endl;
	cout << "You made " << this->history.size() << " command";
	if (this->history.size() != 1) // Need to print 's'
		cout << "s";
	if (this->history.size() == 0) // No commands to print
	{
		cout << endl;
		return;
	}
	cout << ":" << endl;
	for (int commandIndex = 0; commandIndex < (int)(history.size()); commandIndex++) // Print every command
		cout << "\t" << (commandIndex + 1) << ") " << history[commandIndex] << endl;
}