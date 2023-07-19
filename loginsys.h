#pragma once
#include <iostream> // Standard input/output objects
#include <string> // String types and character traits
#include <fstream> // Inputs and opens files
#include <sstream> // Provides string stream classes
#include <math.h> // Functionality to allow for mathematical functions

using namespace std;

class loginsys
{
public:
	void options()
	{
		cout << "----------------------------------------------------------------------\n";
		cout << "|                         Medical Solution	                          |\n";
		cout << "|Input (1) Login as existing user or input (2) Register as new user  |\n";
		cout << "----------------------------------------------------------------------\n";
		cout << "Input: ";
		cin >> userinput;

		bool Continue = false;
		bool Correct = false;

		while (Continue == false)
		{


			if (userinput == '1')
			{

				login();
				Continue = true;
				Correct = true;
			}
			if (userinput == '2')
			{
				adduser();
				Continue = true;
			}
			else
			{
				if (Correct == false)
				{
					cout << "Invalid input, please try again\n\n";
					options();

				}
			}


		}
	}
	void login()
	{

		cout << "\nPlease enter your username and password\nUsername: ";
		cin >> userlog;

		int uid = checkfile(userlog, "user.txt");

		if (uid != 0)
		{
			cout << "Password: ";
			cin >> passlog;
			int pid = (checkfile(passlog, "pass.txt"));
			if (uid == pid)
			{
				cout << "Login succesful!" << endl;
				cout << "----------------------------------------------------------------------\n";
				cout << "|                         Medical Solution                           |\n";
				cout << "----------------------------------------------------------------------\n";
				cin.get();
			}
			else
			{
				cout << "Incorrect password\nPlease try again" << endl;
				login();
			}
		}
		else
		{
			cout << "Username not found.\nPlease try again" << endl;
			login();
		}


	}

	//Register User UI code
	void adduser()
	{
		cout << "----------------------------------------------------------------------\n";
		cout << "|                      Registering as a new user                     |\n";
		cout << "----------------------------------------------------------------------\n";
		cout << "                   Please enter clinic reference code:                \n";
		cout << "Reference: ";
		cin >> regref;

		reference = retrifile("reference.txt");

		if (regref == reference)
		{
			cout << "                        Please enter a username                       \n";
			cout << "                  /////REQUIREMENTS FOR USERNAME/////				   \n";
			cout << "                         *MUST ALL BE LETTERS*" << endl;
			bool Continue = false;
			while (Continue == false)
			{

				cout << "Username: ";
				cin >> userreg;
				if (checkfile(userreg, "user.txt") != 0)
				{
					cout << "That username is already taken." << endl;
					cout << "Please try again with another username." << endl;
				}
				else
				{
					Continue = true;
				}
			}
			cout << "                        Please enter a password                       \n";
			cout << "                  /////REQUIREMENTS FOR PASSWORD/////\n";
			cout << "                        *MUST ALL BE NUMBERS*" << endl;
			cout << "Password: ";
			cin >> passreg;
			cout << "                        Please enter specialty                        \n";
			cout << "Specialty: ";
			cin >> specreg;
			confirmationdu();
		}
		else
		{
			cout << "Clinic reference not found.\nPlease try again" << endl;
			adduser();
		}
	}
	void confirmationdu()
	{
		bool Continue = false;
		bool Correct = false;

		cout << "\nIs the inputted information correct?" << endl;
		cout << "Press (C) to confirm user registration, or (R) to re-enter user login details" << endl;
		cout << "Input: ";
		cin >> confirm;


		while (Continue == false)
		{

			if (confirm == 'C')
			{
				Continue = true;
				Correct = true;
				regun(userreg);
				regpw(passreg);
				regspec(specreg);
				cout << "\nYour username is " << userreg << ", your password is " << passreg << " and your specialty is " << specreg << "." << endl;
				cout << "Thank you for registering, returning to login page..." << endl;
				login();
			}
			if (confirm == 'R')
			{
				Continue = true;
				adduser();
			}
			else
			{
				if (Correct == false)
				{
					cout << "Invalid input, please try again\n\n";
					confirmationdu();
				}
			}
		}
	}

	//Register Username void function
	void regun(const string Username)
	{
		int id = 1 + lastid();
		savefile(Username, "user.txt", id);
		return;
	}

	//Register Password void function
	void regpw(const string Password)
	{
		int id = lastid();
		savefile(Password, "pass.txt", id);
		return;
	}

	//Register Specialty void function
	void regspec(const string Specialty)
	{
		int id = lastid();
		savefile(Specialty, "spec.txt", id);
		return;
	}

	int lastid()
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
				//cout << line << endl;
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
	int i;
	char confirm;
	char userinput;
	string regref;
	string userreg;
	string passreg;
	string specreg;
	string userlog;
	string passlog;
	string username;
	string password;
	string reference;

};
