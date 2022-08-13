#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <limits>
#include <ios>
#include <fstream>
#include <iomanip>

#undef max					//to be used in numeric limits 

#define BLUE "\033[1m\033[34m"
#define RESET "\033[0m"

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


/*
Description:
	checks user input for if it is an integer
Example:
	asad
	Wrong Choice Enter an integer
	12
Return:
	12 is returned
*/
int inputValidation() {
	int num;
	while (true)													//input validation only integer
	{
		cin >> num;
		if (!cin)
		{
			cout << "Wrong Choice. Enter an integer" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		else break;
	}
	return num;
}


/*
Description draws a menu for the three options and 4 for exit

Example 
1.Produce a list of all items purchased in a given day along with the number of times each item was purchased.
2.Produce a number representing how many times a specific item was purchased in a given day.
3.Produce a text-based histogram listing all items purchased in a given day, along with a representation of the number of times each item was purchased.
4. Exit

no return
*/
void displayMenu() {
	cout << "1.Produce a list of all items purchased in a given day along with the number of times each item was purchased." << endl;
	cout << "2.Produce a number representing how many times a specific item was purchased in a given day." << endl;
	cout << "3.Produce a text - based histogram listing all items purchased in a given day, along with a representation of the number of times each item was purchased." << endl;
	cout << "4. Exit" << endl;
}

int main()
{
	//variable declaration
	int num = -1;						//used to hold user input number
	int multNum = 0;					//num to be multiplied
	int itemFreq = 0;					//number of times item occurs
	string userItem;					//holds userinput
	ifstream file;						//open ifstream for file
	string itemName;
	int itemQuantity = 0;
	//while loop exits upon user input of 3
	while (num != 4) {
		
		displayMenu();
		cin >> num;
		//clears input stream so no matter what they input it has to be a number
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		switch (num)
		{
		case 1:												//Write C++ code for when a user selects option 1 from the menu.
			CallProcedure("produceList");				//Select and apply a C++ function to call the appropriate Python function, which will display the number of times each item (or word) appears.
			cout << "\n\n";
			break;
		case 2:												//Use C++ to validate user input for option 2 in the menu.
			cout << "Enter the item you wish to look for.\n"; //Prompt a user to input the item, or word, they wish to look for. 
			getline(cin, userItem);
			itemFreq = callIntFunc("itemFreq", userItem);
			(itemFreq == -1) ? (cout << "Item not found\n") : (cout << userItem << " : " << itemFreq << endl);		//ternary check if item is in list
			cout << "\n\n";
			break;
			
		case 3:			
			CallProcedure("writeToFile");										//creates a new file frequency.dat
			file.open("frequency.dat");
			file >> itemName;
			file >> itemQuantity;
			while (!file.fail()) {													//Loop through the newly created file and read the name and frequency on each row.
				cout << RESET << setw(15) << left << itemName;
				for (int i = 0; i < itemQuantity; i++) {							//Then print the name, followed by asterisks or another special character to represent the numeric amount.
					cout << BLUE  << "*"; 
				}																	//blue asterix   //However, you can alter the appearance or color of the histogram in any way you choose.
				cout << endl;
				file >> itemName;
				file >> itemQuantity;
			}
			cout << RESET << "\n\n";												//returns to original color
			file.close();
			break;
		case 4:
			break;
		default:
			cout << "Not a valid input\n\n";
			break;
		}
	}
	return 0;
}