#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstdlib>

using namespace std;

struct gunDB {
	string desc = "";
	vector<string> brand;
	vector<string> prefix;
	vector<string> dmg;
	vector<string> range;
	vector<string> capacity;
	vector<string> reload;
	vector<string> misfire;
	vector<string> accuracy;
	vector<string> save;
	vector<string> radius;

	public: void readDB(int type) {
		fstream table;
		if (type < 6) {
			if (type == 1) {
				table.open("pistolCSV.csv");
			}
			else if (type == 2) {
				table.open("sniperCSV.csv");
			}
			else if (type == 3) {
				table.open("shotgunCSV.csv");
			}
			else if (type == 4) {
				table.open("rifleCSV.csv");
			}
			else if (type == 5) {
				table.open("smgCSV.csv");
			}
			if (!table.is_open()) {
				cout << "Error Opening File!\n\n";
			}
			else {
				// perform table read
				string line;
				//cout << "Beginning table read\n";
				int i = 0;
				while (getline(table, line)) {
					//cout << "reading row " << i + 1 << "\n";
					stringstream ls(line);
					string word;
					while (getline(ls, word, ',')) {
						switch (i) {
						case 0:
							if (desc != "") {
								break;
							}
							else if (desc == "") {
								//cout << word << "\n";
								desc = word;
								break;
							}
						case 1:
							//cout << word << "\n";
							brand.push_back(word);
							break;
						case 2:
							//cout << word << "\n";
							prefix.push_back(word);
							break;
						case 3:
							//cout << word << "\n";
							dmg.push_back(word);
							break;
						case 4:
							//cout << word << "\n";
							range.push_back(word);
							break;
						case 5:
							//cout << word << "\n";
							capacity.push_back(word);
							break;
						case 6:
							//cout << word << "\n";
							reload.push_back(word);
							break;
						case 7:
							//cout << word << "\n";
							misfire.push_back(word);
							break;
						case 8:
							//cout << word << "\n";
							accuracy.push_back(word);
							break;
						}
					}
					i++;
				}
			}
			table.close();
		}
		else {
			table.open("rpgCSV.csv");
			if (!table.is_open()) {
				cout << "Error Opening File!\n\n";
			}
			else {
				//perform table read (for rpg)
				// perform table read
				string line;
				//cout << "Beginning table read\n";
				int i = 0;
				while (getline(table, line)) {
					//cout << "reading row " << i + 1 << "\n";
					stringstream ls(line);
					string word;
					while (getline(ls, word, ',')) {
						switch (i) {
						case 0:
							if (desc != "") {
								break;
							}
							else {
								//cout << word << "\n";
								desc = word;
								break;
							}
						case 1:
							//cout << word << "\n";
							brand.push_back(word);
							break;
						case 2:
							//cout << word << "\n";
							prefix.push_back(word);
							break;
						case 3:
							//cout << word << "\n";
							dmg.push_back(word);
							break;
						case 4:
							//cout << word << "\n";
							range.push_back(word);
							break;
						case 5:
							//cout << word << "\n";
							capacity.push_back(word);
							break;
						case 6:
							//cout << word << "\n";
							reload.push_back(word);
							break;
						case 7:
							//cout << word << "\n";
							save.push_back(word);
							break;
						case 8:
							//cout << word << "\n";
							radius.push_back(word);
							break;
						}
					}
					i++;
				}
			}
			table.close();
		}
	}
};