#pragma once
#include <iostream>
#include <windows.h>
#include <vector>
#include <random>
using namespace std;
bool I(vector<vector<string>>&tmp,vector<vector<string>>&v) {
	if (v[1][4] == " " && v[1][5] == " " && v[1][6] == " " && v[1][3] == " ") {
		tmp[1][4] = "I";
		tmp[1][5] = "I";
		tmp[1][6] = "I";
		tmp[1][3] = "I";
		return 1;
	}
	else {
		return 0;
	}
}
bool L(vector<vector<string>>& tmp, vector<vector<string>>& v) {
	if (v[1][4] == " " && v[1][5] == " " && v[1][6] == " " && v[2][4] == " ") {
		tmp[1][4] = "L";
		tmp[1][5] = "L";
		tmp[1][6] = "L";
		tmp[2][4] = "L";
		return 1;
	}
	else {
		return 0;
	}
}
bool J(vector<vector<string>>& tmp, vector<vector<string>>& v) {
	if (v[1][4] == " " && v[1][5] == " " && v[1][6] == " " && v[2][6] == " ") {
		tmp[1][4] = "J";
		tmp[1][5] = "J";
		tmp[1][6] = "J";
		tmp[2][6] = "J";
		return 1;
	}
	else {
		return 0;
	}
}
bool O(vector<vector<string>>& tmp, vector<vector<string>>& v) {
	if (v[2][5] == " " && v[1][5] == " " && v[1][4] == " " && v[2][4] == " ") {
		tmp[2][5] = "O";
		tmp[1][5] = "O";
		tmp[1][4] = "O";
		tmp[2][4] = "O";
		return 1;
	}
	else {
		return 0;
	}
}
bool T(vector<vector<string>>& tmp, vector<vector<string>>& v) {
	if (v[1][4] == " " && v[1][5] == " " && v[1][6] == " " && v[2][5] == " ") {
		tmp[2][4] = "T";
		tmp[2][5] = "T";
		tmp[2][6] = "T";
		tmp[1][5] = "T";
		return 1;
	}
	else {
		return 0;
	}
}
bool S(vector<vector<string>>& tmp, vector<vector<string>>& v) {
	if (v[2][4] == " " && v[2][5] == " " && v[1][6] == " " && v[1][5] == " ") {
		tmp[2][4] = "S";
		tmp[2][5] = "S";
		tmp[1][6] = "S";
		tmp[1][5] = "S";
		return 1;
	}
	else {
		return 0;
	}
}
bool Z(vector<vector<string>>& tmp, vector<vector<string>>& v) {
	if (v[1][4] == " " && v[2][5] == " " && v[2][6] == " " && v[1][5] == " ") {
		tmp[1][4] = "Z";
		tmp[2][5] = "Z";
		tmp[2][6] = "Z";
		tmp[1][5] = "Z";
		return 1;
	}
	else {
		return 0;
	}
}

