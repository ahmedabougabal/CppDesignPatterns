#include <iostream>
#include <windows.h>
#include <cstring>
#include <string.h>

using namespace std;

#pragma region Backgrounds
// Base Background class
class Background
{
protected:
	char _theme[10]; // light or dark?
public:
	Background() {}
	virtual void getTheme() = 0;
};

// Derived Light Background class
class LightBkgd : public Background
{
public:
	LightBkgd(HANDLE hConsole)
	{
		SetConsoleTextAttribute(hConsole, 240); // set Bkgd to light
		cout << "Making the background white" << endl;
		strcpy_s(_theme, "light"); // stores light in _theme array
	}
	void getTheme()
	{
		cout << "This is a part of the light theme" << endl;
	}
};

// Derived Dark Background class
class DarkBkgd : public Background
{
public:
	DarkBkgd(HANDLE hConsole)
	{
		SetConsoleTextAttribute(hConsole, 15);
		cout << "Making the background black" << endl;
		strcpy_s(_theme, "dark");
	}
	void getTheme()
	{
		cout << "This is a part of the dark theme" << endl;
	}
};
#pragma endregion Background

#pragma region Text
// Base Text class
class Text
{
protected:
	char _theme[10];

public:
	Text()
	{
	}
	virtual void message(HANDLE hConsole) = 0;
};

// Derived Black Text class
class BlackText : public Text
{
public:
	BlackText(HANDLE hConsole)
	{
		SetConsoleTextAttribute(hConsole, 240); // black text on white bkgd
		strcpy_s(_theme, "light");
		cout << "Making the text black" << endl;
	}
	void message(HANDLE hConsole)
	{
		SetConsoleTextAttribute(hConsole, 240);
		cout << "This is the default font from the light theme" << endl;
	}
};

// Derived White Text class
class WhiteText : public Text
{
public:
	WhiteText(HANDLE hConsole)
	{
		SetConsoleTextAttribute(hConsole, 15);
		strcpy_s(_theme, "dark");
		cout << "Making the text white" << endl;
	}
	void message(HANDLE hConsole)
	{
		SetConsoleTextAttribute(hConsole, 15);
		cout << "This is the default font for the dark theme" << endl;
	}
};

// Derived Dark Green Text class (task 1)
class DarkGreenText : public Text //* this will be used with the white bkgd
{
public:
	DarkGreenText(HANDLE hConsole)
	{
		SetConsoleTextAttribute(hConsole, 242);
		strcpy_s(_theme, "DarkGreenText");
	}
	void message(HANDLE hConsole)
	{
		SetConsoleTextAttribute(hConsole, 242);
		cout << "this is the dark green text on a white bkgd" << endl;
	}
};

// Derived Light Green Text class (task 2)
class LightGreenText : public Text //* this will be used with the dark theme
{
public:
	LightGreenText(HANDLE hConsole)
	{
		SetConsoleTextAttribute(hConsole, 10);
		strcpy_s(_theme, "LightGreenText");
	}
	void message(HANDLE hConsole)
	{
		SetConsoleTextAttribute(hConsole, 10);
		cout << "this is the color 'light green text on a dark bkgd' " << endl;
	}
};

#pragma endregion Text

#pragma region Factories
// Base Factory
class ThemeFactory
{
public:
	virtual Background* setBackground(HANDLE hConsole) = 0;
	virtual Text* getDefaultText(HANDLE hConsole) = 0;
};

// Derived Light Theme Factory which pairs the white background with darker text
class LightFactory : public ThemeFactory
{
public:
	Background* setBackground(HANDLE hConsole)
	{
		return new LightBkgd(hConsole);
	}
	Text* getDefaultText(HANDLE hConsole)
	{
		return new BlackText(hConsole);
	}
};

// Derived Dark Theme Factory which pairs the black background with lighter text
class DarkFactory : public ThemeFactory
{
public:
	Background* setBackground(HANDLE hConsole)
	{
		return new DarkBkgd(hConsole);
	}
	Text* getDefaultText(HANDLE hConsole)
	{
		return new WhiteText(hConsole);
	}
};
#pragma endregion Factories

int main()
{
	// Configure console variables and colours
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 30);

	ThemeFactory* app;
	int choice;

	cout << "Select a theme: " << endl;
	cout << "1: Light" << endl;
	cout << "2: Dark" << endl;
	cout << "Selection: ";
	cin >> choice;
	cout << endl;

	// Initiate the correct factory based on user input
	switch (choice)
	{
	case 1:
		app = new LightFactory;
		break;
	case 2:
		app = new DarkFactory;
		break;
	default:
		cout << "Invalid Selection" << endl;
		app = NULL;
		break;
	}

	// Get the correct objects based on factory selected
	if (app != NULL)
	{
		Background* appBkgd = app->setBackground(hConsole);
		Text* appDefaultText = app->getDefaultText(hConsole);

		appDefaultText->message(hConsole);
	}

	cout << endl;
	system("pause");
}