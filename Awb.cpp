#include <iostream>
#include <fstream>	// For processing files
#include <string>	// For CPP-string operations
#include <cstring>	// For C-string operations
#include <unistd.h> // For sleep()
#include <ctime>	// For time(0)
#include <cstdlib>	// For generating random numbers

using namespace std;
const string programNAME{"./Awb"};

// Functions prototypes
int toSec(string _time);
string exec(string command);
int system(string __command) {return system(__command.c_str());}
int rand(unsigned min, unsigned max, unsigned seed = time(0)) {return (srand(seed), min + rand() % (max - min + 1));}


int main(int argc, char *argv[])
{
	// Open the file "prog.block"
	ifstream progFile("prog.block");
	// Store its data in the string variable "Prog"
	string Prog;
	getline(progFile, Prog);
	// Check if the file is exist or not
	bool isFileExist {true};
	if (progFile.fail())
		isFileExist = false;
	progFile.close();

	if (argc == 1)
		cout << "PBlocker is working...\nUse our applet!";
	else if (argc == 2)
	{
		if (!strcmp(argv[1], "-su") && isFileExist)
		{
			string lmt;
			// 2 mins after PC start up
			for (char i {121}; --i; sleep(1))
			{
				ifstream lmtFile("lmt.time");
				getline(lmtFile, lmt);
				if (!lmtFile.fail())
				{
					lmtFile.close();
					break;
				}
			}

			long duration{stol(lmt) - time(0)};
			if (duration > 0)
				system(programNAME + " -h " + to_string(duration));
		}
		else if (!strcmp(argv[1], "-1t"))
		{
			ofstream lmtFile("lmt.time", ofstream::trunc);
			lmtFile << 0;
			lmtFile.close();

			string program, programs;
			cout << "Enter names of processes (after finishing enter @ and press <enter>):\n>> ";
			cin >> programs;
			while (1)
			{
				cout << ">> ";
				cin >> program;
				if (program != "@")
					programs += "\\|" + program;
				else
					break;
			}

			ofstream progFile("prog.block", ofstream::trunc);
			progFile << programs;
			progFile.close();
		}
		else
			cout << "Error(arg1)";
	}
	else if (argc == 3 && !strcmp(argv[1], "-h"))
	{
		if (isFileExist)
		{
			int timeInSec{toSec(argv[2])};
			// Change process name to a random name so that the user canNOT kill it with .sh file
			int max{stoi(exec("ps aux | grep -v \"\\b" + Prog + "\\b\" | wc -l"))};
			argv[0] = const_cast<char *>(exec("ps aux | tr -s \" \" | cut -d \" \" -f 11 | grep -v \"\\b" + Prog + "\\b\" | sed -n " + to_string(rand(1, max)) + "p").c_str());
			argv[1] = argv[2] = NULL;

			if (timeInSec <= 8 * 3600 && timeInSec > 0)
			{
				for (const unsigned lmt{time(0) + timeInSec}; time(0) < lmt; sleep(1))
				{
					system("pkill -f " + Prog);
					ofstream progFile("prog.block", ofstream::trunc);
					progFile << Prog;
					progFile.close();
					ofstream lmtFile("lmt.time", ofstream::trunc);
					lmtFile << lmt;
					lmtFile.close();
				}
			}
			else
				cout << "Error(invalid_time_value)";
		}
		else
			system("gnome-terminal -- " + programNAME + " -1t");
	}
	else
		cout << "Error(arg2)";
	cout << endl;
	return 0;
}

int toSec(string _time)
{
	switch (_time.back())
	{
	case 'h':
		return stoi(_time) * 3600;

	case 'm':
		return stoi(_time) * 60;

	case 's':
	case '0' ... '9':
		return stoi(_time);

	default:
		return -1;
		break;
	}
}

string exec(string command)
{
	/* 
       From: https://www.tutorialspoint.com/How-to-execute-a-command-and-get-the-output-of-command-within-Cplusplus-using-POSIX
       By: Abhinanda Shri
   */
	char buffer[128];
	string result{""};

	// Open pipe to file
	FILE *pipe = popen(command.c_str(), "r");
	if (!pipe)
		return "popen failed!";

	// read till end of process:
	while (!feof(pipe))
		// use buffer to read and add to result
		if (fgets(buffer, 128, pipe) != NULL)
			result += buffer;

	pclose(pipe);
	return result;
}