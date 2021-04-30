/**
 * @Date:   2020-11-07T15:43:03-08:00
 * @Last modified time: 2020-11-23T00:20:09-08:00
 */



#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <iomanip>
#include <string>
#include <fstream>
#include <ctype.h>

using namespace std;

string unsolved_word = "";

char user_guess(string& available);
void check(char letter, string word, bool& win, bool& lose, int& wrong_count);
string choose_word(ifstream& infile, string& available);
void draw_hangman(int wrong_count);
void assign_available_letters(string& available, char letter);

/*******************************************************************/

int main()
{
	ifstream infile;
	string word, available;
	bool win = false, lose = false, end = false;
	char letter;
	char* available_ptr = new char[24];
	int wrong_count = 0;
	//===============================//

	word = choose_word(infile, available);
	cout << endl << word << endl;

	do
	{
		system("cls");

		draw_hangman(wrong_count);

		if (wrong_count == 8)
		{
			lose = true;
			break;
		}

		cout << endl << "Available Letters:" << endl;
		cout << available << endl << endl << endl;

		letter = user_guess(available);

		check(letter, word, win, lose, wrong_count);

		if (win == true || lose == true)
			end = true;
	} while (end == false);

	cout << endl << endl;

	if (win == true)
		cout << "\n\nCongratulations! You win" << endl;
	cout << "The word is: '" << word << "'" << endl;
	if (lose == true)
		cout << "Rest in peace!" << endl;
	cout << endl << endl << endl;

	return 0;
}


string choose_word(ifstream& infile, string& available)
{
	bool pass;
	string fname = "input.txt";
	string word;
	int line_num;
	string line;
	int line_count = 0;

	infile.open(fname);

	// Get the total number of lines in the file.
	while (getline(infile, line))
		line_count++;

	srand(time(NULL));
	line_num = rand() % line_count + 1;

	// Set cursor back to the beginning of the file.
	infile.clear();
	infile.seekg(0, ios::beg);

	// Go to the position of the random number generated and input the word.
	for (int i = 0; i < line_num - 1; ++i)
		infile.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(infile, word);

	infile.close();

	for (int j = 0; j < word.size(); j++)
	{
		unsolved_word.push_back('*');
	}

	// Assign the available letters for the user to choose
	for (int i = 'A'; i <= 'Z'; i++)
	{
		available.push_back(i);
		available += " ";
	}

	return word;
}


char user_guess(string& available)
{
	char letter;
	bool pass, flag = false;

	cout << "This word has " << unsolved_word.size();
	cout << " letters: ";
	cout << unsolved_word << endl << endl;

	cout << "Please guess a letter: ";
	do
	{
		cin >> letter;

		if (!isalpha(letter))
		{
			pass = false;
			cout << "The input must be a letter, please re-enter: ";
		}
		else
			pass = true;

		for (int i = 0; i < available.size(); i++)
		{
			if (toupper(letter) == available.at(i))
			{
				available.at(i) = ' ';
				pass = true;
				flag = true;
				break;
			}
		}

		if (flag != true)
		{
			pass = false;
			cout << "'" << letter << "' was chosen before,";
			cout << " please re-enter: ";
		}


		/*for (int i = 0; i < unsolved_word.size(); i++)
			if (letter == unsolved_word.at(i))
			{
				pass = false;
				cout << "'" << letter << "' was chosen before,";
				cout << " please re-enter: ";
			}*/

	} while (pass == false);


	return letter;
}


void check(char letter, string word, bool& win, bool& lose, int& wrong_count)
{
	int size = word.size();
	bool flag, word_found = false;

	for (int i = 0; i < size; i++)
	{
		if (letter == word.at(i))
		{
			word_found = true;

			unsolved_word.at(i) = letter;

			for (int j = 0; j < size; j++)
			{
				if (!isalpha(unsolved_word.at(j)))
				{
					win = false;
					flag = false;
					break;
				}
				if (j == size - 1)
					flag = true;
			}
			if (flag == true)
				win = true;
		}
	}

	if (word_found != true)
		wrong_count++;
}


void draw_hangman(int wrong_count)
{
	cout << "-------------" << endl;

	if (wrong_count == 0)
		cout << "HANG MAN GAME" << endl;

	if (wrong_count >= 1)
	{
		cout << "           |" << endl;
		cout << "           |" << endl;
	}

	if (wrong_count >= 2)
		cout << "           O" << endl;

	if (wrong_count >= 3)
		cout << "          /";
	if (wrong_count >= 4)
		cout << "|";
	if (wrong_count >= 5)
		cout << "\\" << endl;

	if (wrong_count >= 6)
		cout << "           |" << endl;

	if (wrong_count >= 7)
		cout << "          / ";
	if (wrong_count >= 8)
		cout << "\\" << endl;

	cout << endl << endl;
	cout << "-----------------------" << endl;
}


void assign_available_letters(string& available, char letter)
{
	letter = toupper(letter);

	for (int i = 0; i < available.size(); i++)
	{
		if (letter == available.at(i))
			available.at(i) = ' ';
	}
}
