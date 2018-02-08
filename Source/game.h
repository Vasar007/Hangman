#pragma once
/// File which contais game logic
bool mon = false, retry = false;

int outWord(std::string &w, std::vector<bool> &v, std::vector<char> &c, std::string &str)			//output fuction
{
	int kol = 0;
	str.clear();
	std::cout << "Game phase\n";
	std::cout << "Known letters: ";
	std::sort(c.begin(), c.end());
	for (unsigned int i = 0; i < c.size(); i++) {
		if (c[i] >= 65 && c[i] <= 90)
			c[i] = c[i] + 32;
		std::cout << c[i] << " ";
	}
	std::cout << std::endl;
	for (unsigned int i = 0; i < v.size(); i++) {
		if (v[i] == true) {
			std::cout << w[i] << " ";
			str += w.substr(i, 1) + " ";
			kol++;
		}
		else if (w[i] == ' ') {
			std::cout << " ";
			str += "  ";
			v[i] = true;
			kol++;
		}
		else {
			std::cout << "_ ";
			str += "_ ";
		}
	}
	std::cout << std::endl;
	if (kol == w.size())
		return 1;
	else
		return 0;
}

bool chWord(char &var, std::string &w, std::vector<bool> &v, std::vector<char> &c)			//function which watching for chars and opening letters in hiden word
{
	bool flag = false;
	char var2 = ' ';
	int ck = 0;
	retry = false;
	if ((var >= 65) & (var <= 90))
		var2 = var + 32;
	else if ((var >= 97) & (var <= 122))
		var2 = var - 32;

	for (unsigned int i = 0; i < v.size(); i++)
		if ((var == w[i]) | (var2 == w[i])) {
			if (v[i] == false) {
				v[i] = true;
				flag = true;
			}
		}
	if (flag == true) {
		if (mon == true)
			c.push_back(var);
		return true;
	}
	else {
		if (mon == true) {
			for (unsigned int i = 0; i < c.size(); i++)
				if (var != c[i])
					ck++;
			if (ck == c.size()) {
				c.push_back(var);
			}
			else {
				retry = true;
				return false;
			}
		}
		return false;
	}
}

bool checkChars(std::string word)			//function which checking entered string
{
	std::vector<char> count;
	for (unsigned int i = 0; i < word.size(); i++)
		if ((word[0] >= 65) & (word[0] <= 90))
			word[i] = word[i] + 32;

	count.push_back(word[0]);
	bool uniq = true;
	for (unsigned int i = 0; i < word.size(); i++) {
		uniq = true;
		for (unsigned int j = 0; j < count.size(); j++)
			if (word[i] == count[j])
				uniq = false;
		if (uniq == true)
			count.push_back(word[i]);
	}
	if (count.size() > 2)
		return true;
	else
		return false;
}

std::string getWordPVE()
{
	std::string word, buff, mes, s;
	std::vector<std::string> inpt;

	int strnum = 0, numstr;
	std::ifstream input("Other/input.txt");			//input data file
	if (!input.is_open()) {
		std::cout << "Error 040: Input error! Didn't find file 'input.txt' in game folder." << std::endl;			//check input file
		return "";
	}
	while (!input.eof()) {			//reading before the end of input file
		std::getline(input, s);			//getting array of symbols of the line
		strnum++;
		inpt.push_back(s);
	}
	s.clear();
	srand(time(0));
	numstr = rand() % strnum;			//random number from 0-X
	word = inpt[numstr];
	inpt.clear();
	bool worcdcheck = true;
	if (word.size() < 3) {
		std::cout << "Error! You entered little word! Try again." << std::endl;
		worcdcheck = false;
	}
	else if (checkChars(word) == false) {
		std::cout << "Error! Word consists of only two letters! Fix it in input file." << std::endl;
		worcdcheck = false;
	}
	else {
		for (unsigned int i = 0; i < word.size(); i++)
			if ((i == 0) | (i == word.size() - 1)) {
				if ((((char)word[i] < 65) | ((char)word[i] > 90)) & (((char)word[i] < 97) | ((char)word[i] > 122))) {
					std::cout << "Word consists not only English letters! Fix it in input file." << std::endl;
					worcdcheck = false;
					break;
				}
			}
			else if ((((char)word[i] < 65) | ((char)word[i] > 90)) & (((char)word[i] < 97) | ((char)word[i] > 122)) & ((char)word[i] != 32)) {
				std::cout << "Word consists not only English letters! Fix it in input file." << std::endl;
				worcdcheck = false;
				break;
			}
	}
	return word;
}