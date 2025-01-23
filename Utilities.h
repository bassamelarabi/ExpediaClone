#pragma once
#include<ctime>
#include<iostream>
#include<vector>

using namespace std;

///a strucutre to represent the time/////

tm make_tm(int year, int month, int day) {
	tm tm{ 0 };
	tm.tm_year = year;
	tm.tm_mon = month - 1; // months count from January =0
	tm.tm_mday = day;
	return tm;
}


///utilities//////
int ReadInt(int low, int high) {
	cout << "\nEnter number in range " << low << " - " << high << ": ";
	int value;

	cin >> value;

	if (low <= value && value <= high)
		return value;

	cout << "ERROR: invalid number...Try again\n";
	return ReadInt(low, high);
}

int ShowReadMenu(const vector<string>& choices) {
	cout << "\nMenu:\n";
	for (int ch = 0; ch < (int)choices.size(); ++ch) {
		cout << "\t" << ch + 1 << ": " << choices[ch] << "\n";
	}
	return ReadInt(1, (int)choices.size());
}
