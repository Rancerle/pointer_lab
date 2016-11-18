#include<iostream>
#include<string>
#include<fstream>

//Represents a movie

struct Movie
{
	std::string movieName;
	int yearReleased;
};



//node represents a single node in the linked list
struct node
{
	Movie aMovie;
	node* prevPtr;
};

//Function: menu is used to display an interactive menu to the user
void menu();


void showBeforeYear(node*, int);

//Function: listMovies is used to display all movies in the linked list
void listMovies(node*);

int main()
{
	std::ifstream inputHandler;		//file handler for input file
	std::string movieNameFromFile;	//store movie name from file
	int movieYearFromFile;			//store movie year from file
	int userInput;					//get user input for menu interaction
	int userYear;					//get year from user to list movies
	node* currentPtr = NULL;		//currentPtr points to current list element, initialized to NULL
	node* headPtr = NULL;			//headPtr points to top of list, initialized to NULL

	//Open the movies.text file
	inputHandler.open("movies.txt");
	//Read the first line from the file
	inputHandler >> movieNameFromFile >> movieYearFromFile;

	while (!inputHandler.eof())
	{
		//create a new node called currentPtr
		currentPtr = new node;
	
		//set the value for currentPtr to the values read from the file
		currentPtr->aMovie.movieName = movieNameFromFile;
		currentPtr->aMovie.yearReleased = movieYearFromFile;
		
		//set currentPtr->prevPtr to headPtr
		currentPtr->prevPtr = headPtr;

		//update headPtr to currentPtr
		headPtr = currentPtr;

		//read the next line from the file
		inputHandler >> movieNameFromFile >> movieYearFromFile;
	}

	//Close the file
	inputHandler.close();

	//Display the menu to the user
	menu();
	std::cin >> userInput;

	//Validate input
	while (userInput > 3 || userInput < 1)
	{
		//Display the menu to the user
		menu();
		std::cin >> userInput;
	}

	//List movies by year
	if (userInput == 1)
	{
		// ask the user to enter the year
		std::cout << "What year would you like to see?: ";
		std::cin >> userYear;
		//Store the year entered by the user in userYear
		//Call function showBeforeYear with currentPtr and userYear
		showBeforeYear(currentPtr, userYear);
		return 0;
	}
	//List all movies
	else if (userInput == 2)
	{
		//Call function listMovies to print all movies
		listMovies(currentPtr);
		return 0;
	}
	//Exit program
	else
	{
		//Show exit message and terminate program
		std::cout << "Exiting program." << std::endl;
		return 0;
	}
}

//Function: menu
//Inputs: none
//Outputs: none
//Errors: none
void menu()
{
	std::cout << "Press 1 to list movies released before a specific year." << std::endl;
	std::cout << "Press 2 to list all movies." << std::endl;
	std::cout << "Press 3 to quit." << std::endl;
	std::cout << "Enter your choice: ";
}

//Function: showBeforeYear
//Inputs: node* currentPtr and int userYear
//Outputs: displays all movies before a specific year
//Errors: none
void showBeforeYear(node* currentPtr, int userYear)
{
	int i = 0; //indicates if there are no movies prior to the user's choice

	while (currentPtr)
	{
		if (currentPtr->aMovie.yearReleased < userYear)
		{
			std::cout << currentPtr->aMovie.movieName << " released in " << currentPtr->aMovie.yearReleased << std::endl;
			i++;
		}
		currentPtr = currentPtr->prevPtr;
	}
	//if you find 0 movies before userYear, tell the user that you found no movies
	if (i == 0)
	{
		std::cout << "I'm sorry, but there are no movies listed as being released before " << userYear << std::endl;
	}
}

//Function: listMovies
//Inputs: node* currentPtr
//Outputs: displays all movies stored in linked list
//Errors: none
void listMovies(node* currentPtr)
{
	//Loop until currentPtr hits NULL
	while(currentPtr)
	{
		//Print entry from linked list
		std::cout << currentPtr->aMovie.movieName << " released in " << currentPtr->aMovie.yearReleased << std::endl;
		//Move currentPtr to next location
		currentPtr = currentPtr->prevPtr;
	}
}