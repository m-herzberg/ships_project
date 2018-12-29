//Ship Wars Project
//Creators: Szymon Buksak, Mikołaj Herzberg

#include "pch.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>

#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;

struct match_config {
	string type = "standard";
	string oponent;
};

//MAIN MENU FUNCTIONS
void Main_menu(match_config &match);
void Main_menu_help(match_config match);
void Main_menu_copyright(match_config match);
void Main_menu_exit(match_config match);
match_config Main_menu_play(match_config &match); 
int Main_menu_choice(int &);

//GENERATING FUNCTIONS



int main()
{
	//EARLY SETTINGS
	match_config match;
	//
	Main_menu(match);
	cout << match.type << endl;
	cout << match.oponent << endl;
	return 0;

}

void Main_menu(match_config &match) {
	cout << "[1] PLAY\n[2] SETTINGS\n[3] COPYRIGHT\n[4] HELP\n[5] EXIT\n";

	int choice = 0;
	cin >> choice;
	switch (choice) {
	case 1: {

		system("cls");
		Main_menu_play(match);
	}break;
	case 2: {
		system("cls");
		//Settings();
	}break;
	case 3: {
		system("cls");
		Main_menu_copyright(match);
	}break;
	case 4: {
		system("cls");
		Main_menu_help(match);
	}break;
	case 5: {
		system("cls");
		Main_menu_exit(match);
	} break;
	default: {
		cout << "Unexpected choice!" << endl;
		Main_menu(match);
	}break;

	}
}

void Main_menu_help(match_config match){
	cout << "      --HELP--\n" << endl;
	cout << "--- [BASIC INPUT] ---\n" << endl;
	cout << "[1],[2],[3],[n]  - Enter respectively 1,2,3 etc. value on your keyboard to choose that option " << endl;
	cout << "[ < ], [ > ] - Press [ < ]  LEFT ARROW or [ > ] RIGHT ARROW on keyboard to choose this option " << endl;
	
	cout << "\n\n\n\n [ < ] GO BACK     [ > ] GO NEXT\n";
	
	
	int choice_value = 0;
	
Main_menu_choice(choice_value);
	while (choice_value != -1) {
		switch (choice_value) {
		case 0: {
			system("cls");
			Main_menu_help(match);
		}break;
		case 1: {
			system("cls");
			cout << "      --HELP--\n" << endl;
			cout << "--- [GENERAL RULES] --- " << endl;
			cout << "\n\n In first step You will have to set up Your formation of ships. After that the battle begins. Your purpose is to destroy all enemy units." << endl;
			cout << "There is standard match and custom match. To learn more about it [ > ] GO NEXT ";
			cout << "\n\n [ < ] GO BACK     [ > ] GO NEXT\n";
			Main_menu_choice(choice_value);

		}break;

		case 2: {
			system("cls");
			cout << "      --HELP--\n" << endl;
			cout << "--- [STANDARD MATCH RULES] ---" << endl;
			cout << "1. Players have 2 boards (10x10). Columns are marked by letters (from A to J) and digits (from 1 to 10). " << endl;
			cout << "2. On first board Player sets up his formation of ships. On the second board Game marks Player's shots." << endl;
			cout << "3. Ships can be set up as vertical or horizontal. " << endl;
			cout << "4. There must be at least one empty space betweeen each ship. " << endl;
			cout << "5. Each player has: 1 Large Ship, 2 Medium Ships and 3 Small Ships. " << endl;
			cout << "6. Shots are rendered by guessing enemy ship's position. (For example: C3 )" << endl;
			cout << "\n\n [ < ] GO BACK     [ > ] GO NEXT\n";
			Main_menu_choice(choice_value);
		}break;

		case 3: {
			system("cls");
			cout << "      --HELP--\n" << endl;
			cout << "--- [CUSTOM MATCH RULES] ---" << endl;
			cout << "In custom match You are creating new rules or editting the standard rules." << endl;
			cout << "For example You can choose that there won't be necessary empty space between ships (make point '4' from standard match useless) " << endl;
			cout << "You can even change the amount of ships, create new ships or change the boards' size " << endl;
			cout << "\n\n [ < ] GO BACK" << endl;
			Main_menu_choice(choice_value);
		}break;
		case 4: {
			system("cls");
			Main_menu_help(match);
		}break;
		}
	}
	if (choice_value == -1) {
		system("cls");
		Main_menu(match);
	}
	
	
}

void Main_menu_copyright(match_config match) {
	cout << "    --COPYRIGHT--\n" << endl;
	cout << "SHIP WARS THE FIRST" << endl;
	cout << "Creators: Szymon Buksak and Mikolaj Herzberg" << endl;
	cout << "\nThis game is on Public Copyright License." << endl;
	cout << "Project started in [28-12-2018] " << endl;
	

	cout << "\n\n\n\n [ < ] GO BACK TO MAIN MENU";
	int choice_value = 0;
	Main_menu_choice(choice_value);
	
	while (choice_value != -1) {
		choice_value = 0;
		Main_menu_choice(choice_value);
		
	}
	if (choice_value == -1) {
		system("cls");
		Main_menu(match);
	}
}

void Main_menu_exit(match_config match) {
	cout << "Do you really want to exit?" << endl;
	cout << "\n\n [ < ] HELL NO!      [ > ] YES" << endl;
	int choice_value = 0;
	Main_menu_choice(choice_value);
	
	if (choice_value == -1) {
		system("cls");
		Main_menu(match); 
	}
	else {
		system("cls");
		cout << "Thanks for playing!" << endl;
		exit(1); 
		
	}
	
}

match_config Main_menu_play(match_config &match) {
	cout << "Please select a type of match: \n\n[1] STANDARD MATCH\n[2] CUSTOM MATCH\n" << endl;
	
	int choice = 0;
	
	 do{
		cin >> choice;
		if (choice == 1) {
			match.type = "standard";
			
		}
		else if (choice == 2) {
			match.type = "custom";

		}
		else {
			cout << "Unexpected choice! Please try again..." << endl;

		}
	}while (choice < 1 || choice > 2);
	
	system("cls");
	cout << "Please select the oponent: \n\n[1] PLAYER\n[2] COMPUTER\n" << endl;
	choice = 0;
	
	do{
		cin >> choice;
		if (choice == 1) {
			match.oponent = "player";
		}
		else if (choice == 2) {
			match.oponent = "computer";
		}
		else {
			cout << "Unexpected choice! Please try again..." << endl;
		}
	}while (choice < 1 || choice > 2);
	system("cls");
	return match;
}

int Main_menu_choice(int &choice_value) {
	char key = _getch(); //_getch() read the key value from keyboard without displaying it.
	int choice = key;
	while (1) {
		switch (choice) {
		case KEY_RIGHT: {
			choice_value++;
			return choice_value;
		}break;
		case KEY_LEFT: {
			choice_value--;
			return choice_value;
		} break;

		}
		key = _getch();
		choice = key;

	}
	
}

