#pragma once
#include <iostream>
#include <string>
#include <fstream> // Inputs and opens files
#include <sstream> 
#include <stdlib.h>
#include "loginsys.h" // Includes login system class
#include <math.h> // Functionality to allow for mathematical functions

using namespace std;

class doc
{
public:

	void loginmpage()
	{
		//Main page after logging in
		cout << "----------------------------------------------------------------------\n";
		cout << "| Would you like to:                                                 |\n";
		cout << "| (1)  Add new patient to database                                   |\n";
		cout << "| (2)  See list of doctors and their specialties                     |\n";
		cout << "| (3)  See list of patients with diagnosis                           |\n";
		cout << "| (4)  Exit solution                                                 |\n";
		cout << "----------------------------------------------------------------------\n";
		cout << "Input: ";
		cin >> userinput;

		bool Continue = false;
		bool Correct = false;

		while (Continue == false)
		{

			if (userinput == '1')
			{
				Continue = true;
				Correct = true;
				addpat();

			}
			if (userinput == '2')
			{
				Continue = true;
				Correct = true;
				finddocid();
			}
			if (userinput == '3')
			{
				//Displays list of patients with diagnosis
				Continue = true;
				Correct = true;
				findpats();
			}
			if (userinput == '4')
			{
				Continue = true;
				Correct = true;
				exit;
			}
			else
			{
				if (Correct == false)
				{
					cout << "Invalid input, please try again\n\n";
					loginmpage();

				}
			}
		}

	}
	//Void function to add patient data onto files which then gets encrypted
	void addpat()
	{
		cout << "================================================\n";
		cout << "|               Add a new patient              |\n";
		cout << "================================================\n";
		cout << "Please enter the following details- " << endl;
		cout << "First name of patient: ";
		cin >> fnop;
		cout << "Last name of patient: ";
		cin >> lnop;
		cout << "Date of birth (DDMMYYYY): ";
		cin >> dob;
		cout << "Age: ";
		cin >> page;
		cout << "Address of patient: ";
		cin >> aop;
		cout << "Diagnosis: ";
		cin >> diag;


		cout << "\n\nInputted data of patient: " << endl;
		cout << "Full name of patient: " << fnop << " " << lnop << endl;
		cout << "Date of birth (DD/MM/YYY): " << dob << endl;
		cout << "Age: " << page << endl;
		cout << "Address of patient: " << aop << endl;
		cout << "Diagnosis: " << diag << endl;
		confirmationap();
	}

	//Void function to ask patient 
	void confirmationap()
	{
		bool Continue = false;
		bool Correct = false;

		cout << "\nIs the inputted information correct?" << endl;
		cout << "Press (C) to confirm patient registration, or (R) to re-enter patient information" << endl;
		cout << "Input: ";
		cin >> confirm;


		while (Continue == false)
		{

			if (confirm == 'C')
			{
				Continue = true;
				Correct = true;
				regfnop(fnop);
				reglnop(lnop);
				regdob(dob);
				regpage(page);
				regadd(aop);
				regdiag(diag);
				cout << "Patient registered." << endl;
				cout << "Returning to main page..." << endl;
				loginmpage();
			}
			if (confirm == 'R')
			{
				Continue = true;
				addpat();
			}
			else
			{
				if (Correct == false)
				{
					cout << "Invalid input, please try again\n\n";
					confirmationap();
				}
			}
		}
	}


	void regfnop(const string fnop)
	{
		int id = 1 + lastid();
		savefile(fnop, "pat_fname.txt", id);
		return;
	}
	void reglnop(const string lnop)
	{
		int id = lastid();
		savefile(lnop, "pat_lname.txt", id);
		return;
	}
	void regdob(const string dob)
	{
		int id = lastid();
		savefile(dob, "pat_dob.txt", id);
		return;
	}
	void regpage(const string lnop)
	{
		int id = lastid();
		savefile(lnop, "pat_age.txt", id);
		return;
	}
	void regadd(const string add)
	{
		int id = lastid();
		savefile(add, "pat_add.txt", id);
		return;
	}
	void regdiag(const string diag)
	{
		int id = lastid();
		savefile(diag, "pat_diag.txt", id);
		return;
	}

	/*Void register function that associates doctors id/name*/

	int lastid()
	{
		fstream file;
		string a;
		//ios::in here one to the left of last character
		file.open("pat_fname.txt", ios::in);
		file.seekg(0, ios::end);

		//file case empty
		if (file.tellg() == 0)
		{
			return 0;
		}

		//string::npos means that if the # is found at a non valid position
		//it means that # is not there yet
		for (int i = -1; a.find('#') == string::npos; i--)
		{
			file.seekg(i, ios::end);
			file >> a;
		}

		file.close();
		//erases the first 4 characters of each username/password ID string after ASCII string
		//0 starting, 4 end
		a.erase(0, 4);

		int id;
		//converting string to integer
		istringstream(a) >> id;

		return id;
	}

	int doclastid()
	{
		fstream file;
		string a;
		//ios::in here one to the left of last character
		file.open("user.txt", ios::in);
		file.seekg(0, ios::end);

		//file case empty
		if (file.tellg() == 0)
		{
			return 0;
		}

		//string::npos means that if the # is found at a non valid position
		//it means that # is not there yet
		for (int i = -1; a.find('#') == string::npos; i--)
		{
			file.seekg(i, ios::end);
			file >> a;
		}

		file.close();
		//erases the first 4 characters of each username/password ID string after ASCII string
		//0 starting, 4 end
		a.erase(0, 4);

		int id;
		//converting string to integer
		istringstream(a) >> id;

		return id;
	}

	void displayfile(const char* file, const int& word)
	{
		fstream line;
		string a;
		string b;
		int enchar;
		int ncounter = 0;
		bool Continue = true;
		int i = 0;

		line.open(file, ios::in);

		//sizeof line give you siz eof the file
		//the for loop only runs until 1 less than the actual size of line
		//line being the file txt called upon by another function
		for (int i = 0; i < (sizeof(line)); i++)
		{
			line >> b;
			istringstream(b) >> enchar;
			//overloaded function that adds strings together
			a += (char)decryption(enchar);
			b = "";

		}

		while (Continue == true)
		{
			//word - 1 because number of nulls before the word is always be one less than word number
			//a[i] does not equal to null character and number of nulls counter is one less than the word number
			//will display the encrypted ascii in character format 
			if (((a[i] != '\0') && (ncounter == word - 1)))
			{
				cout << a[i];
			}
			//else if the ncounter is word, it would break the while loop
			else
			{
				if (ncounter == word)
				{
					Continue = false;
				}
				//second if statement is for when a null char encountered
				//it increments ncounter so the final result would go to first if statement
				//and end the whole while loop in the end
				if (a[i] == '\0')
				{
					ncounter = ncounter + 1;
				}

			}
			//increments by one each while loop iteration
			i = i + 1;
		}
	}

	//finddocid displays all the users which are the doctors of this medical solution
	void finddocid()
	{
		for (int i = 1; i <= doclastid(); i++)
		{
			cout << "Name of doctor: ";
			displayfile("user.txt", i);
			cout << ", Specialty: ";
			displayfile("spec.txt", i);
			cout << "\n";
		}
		cout << "\nReturning to main page..." << endl;
		loginmpage();
	}

	//findpats displays all information of the registered patients through the use of the 1st function of loginmainpage()
	void findpats()
	{
		for (int i = 1; i <= lastid(); i++)
		{
			cout << "Patient name: ";
			displayfile("pat_fname.txt", i);
			cout << " ";
			displayfile("pat_lname.txt", i);
			cout << ", Date of Birth (DD/MM/YYYY): ";
			displayfile("pat_dob.txt", i);
			cout << ", Age: ";
			displayfile("pat_age.txt", i);
			cout << ", Address: ";
			displayfile("pat_add.txt", i);
			cout << ", Diagnosis: ";
			displayfile("pat_diag.txt", i);
			cout << "\n";
		}
		cout << "\nReturning to main page..." << endl;
		loginmpage();
	}

	//p_ is a declaration that it is a parameter variable
	int checkfile(string att, const char* p_fileusern)
		//{} is a scope
	{
		string line;
		fstream file;
		string currents;
		//Int for encrypted characters 
		int enchar;
		int id;
		//ios::in is declaration that code is reading the file
		file.open(p_fileusern, ios::in);

		while (1)
		{

			file >> currents;
			if (currents.find("#ID:") != string::npos)
			{
				if (att == line)
				{
					file.close();
					currents.erase(0, 4);

					istringstream(currents) >> id;
					//if att is not line, then the line resets
					return id;
				}
				else
				{
					//erase erases everything inputted, where the whole line will be erased in this case
					line.erase(line.begin(), line.end());
				}
			}
			else
			{
				istringstream(currents) >> enchar;
				//overloaded function that adds strings together
				line += (char)decryption(enchar);
				currents = "";
			}
			//peek doesn't assign anything but checks whats next 
			//EOF  = end of file
			if (file.peek() == EOF)
			{
				file.close();
				//return false so to end the file is where the attemtped username/password is NOT found
				return 0;
			}
		}

	};

	//string function that refers back to the resource files
	string retrifile(const char* p_fileusern)
		//{} is a scope
	{
		string line;
		fstream file;
		//ios::in is declaration that code is inputting into the file
		file.open(p_fileusern, ios::in);
		if (file.is_open())
		{
			getline(file, line);
		}
		file.close();
		return line;
	};

	//To save whatever the user inputs as registration username and password onto resource file of user and pass.txt
	//const char is limited and takes little memory to instantiate
	//3rd parameter ID
	void savefile(string p_line, const char* p_filename, const int& id)
	{
		fstream file;
		//ios::app means that whatever is inputted is added on instead of reaplcing what is prior
		file.open(p_filename, ios::app);
		//seekg sets for anywhere on file 
		//ios::end sets cursor to very end of file
		file.seekg(0, ios::end);
		//tellg gives position of character
		//if file has text/numbers, then a line is added to avoid the input to be put into the same line

		if (file.tellg() != 0)
		{
			file << "\n";
		}
		//Setting to the beginning of the file again
		//ios::beg is beginning
		file.seekg(0, ios::beg);
		for (int i = 0; i < p_line.length(); i++)
		{
			file << encryption(p_line[i]);
			//after every character a new line is created to split the ASCII integers
			file << "\n";
		}
		file << "#ID:" << id;
		file.close();
	};

	//Encryption code
	//parameter of p_letter
	int encryption(int p_letter)
	{
		//powf= power of
		//makes the ASCII number bigger = less easy to access
		//Cannot go above 4 because the bits would be too large to compute
		//if power above 4 needed, use long function infront of int
		return powf(p_letter, 3);
	}

	//Decryption code
	//with same parameter
	int decryption(int p_letter)
	{
		//.f to return as a float
		//otherwise will be returned as integer, where point numbers cannot handle
		return powf(p_letter, 1 / 3.f);
	}


private:
	char userinput;
	char confirm;
	string fnop;
	string lnop;
	string dob;
	string page;
	string aop;
	string diag;
	string adp;
};
