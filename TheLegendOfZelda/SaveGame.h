#pragma once

#include <string>

class SaveGame
{
public:
	SaveGame();
	~SaveGame();

	void SetName(std::string name) { this->name = name; }
	std::string GetName() { return name; }

	void SetNumberOfHearts(int numberOfHearts) { this->numberOfHearts = numberOfHearts; }
	int GetNumberOfHearts() { return numberOfHearts; }

	void SetNumberOfRupees(int numberOfRupees) { this->numberOfRupees = numberOfRupees; }
	int GetnumberOfRupees() { return numberOfRupees; }

	void SetNumberOfKeys(int numberOfkeys) { this->numberOfkeys = numberOfkeys; }
	int GetnumberOfkeys() { return numberOfkeys; }

	void SetNumberOfBombs(int numberOfbombs) { this->numberOfbombs = numberOfbombs; }
	int GetnumberOfbombs() { return numberOfbombs; }

	void SetSwordlevel(int swordlevel) { this->swordlevel = swordlevel; }
	int GetSwordlevel() { return swordlevel; }

private:
	std::string name;
	int numberOfHearts = 0;
	int numberOfRupees = 0;
	int numberOfkeys = 0;
	int numberOfbombs = 0;
	int swordlevel = 0;
};

