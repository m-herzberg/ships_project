//Ship Wars Project
//Creators: Szymon Buksak, Mikołaj Herzberg

#include "pch.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <io.h>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <vector>

#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;

struct ship {
	short size;
	short amount;
	short setting_order = 0;
	string name;
	string position;
	vector <vector <unsigned short>> position_cord; //defines coordinates of vertical and horizontal position
};

struct match_config {
	string type = "standard"; // Standard | Custom
	string oponent; //Player | SI

	//default match rules
	bool ships_beside = false; //if false => there must be 1 empty space between each ship

	//default miss sound
	int miss_tone_1 = 350, miss_tone_2 = 225;
	int miss_duration_1 = 250, miss_duration_2 = 200;
	//default shot sound
	int shot_tone = 300;
	int shot_duration = 300;
	//default hit sound
	int hit_tone = 340;
	int hit_duration = 600;

	//default ship info 
	vector <ship> battleship;
	short battleship_amount = 1;
	short battleship_size = 4;
	string battleship_name = "Battleship";
	vector <ship> cruiser;
	short cruiser_amount = 2;
	short cruiser_size = 3;
	string cruiser_name = "Cruiser";
	vector <ship> destroyer;
	short destroyer_amount = 3;
	short destroyer_size = 2;
	string destroyer_name = "Destroyer";


	//custom ships
	vector < vector<ship>>custom_ship_main;
	vector <ship> custom_ship; //user can create its own ships
	short custom_ships_amount = 0;
	
	


	//default board info
	int board_size_x = 10;
	int board_size_y = 10;
};



//MAIN MENU FUNCTIONS
match_config Main_menu(match_config &match);
match_config Main_menu_help(match_config &match);
match_config Main_menu_settings(match_config &match);
match_config Main_menu_settings_sound(int &sound_choice, match_config &match, int value_1, string);
match_config Main_menu_play(match_config &match);
match_config Main_menu_play_custom(match_config &match);
match_config Main_menu_custom_ships(match_config &match);
match_config Main_menu_custom_ship_creator(match_config &match);
match_config Main_menu_custom_boards(match_config &match);
void Main_menu_copyright(match_config &match);
void Main_menu_exit(match_config &match);
int Main_menu_choice(int &);

//GENERATING FUNCTIONS
vector <ship> generating_ship(struct ship ship_struct, vector <ship> &custom_ship, match_config &match, short ship_amount, short ship_size, string ship_name);
vector <vector <short>> generating_board(vector<vector<short>> &board, match_config &match);
vector <vector<ship>> custom_ship_update(vector<vector<ship>> &custom_ship, int ship_type);

//DISPLAYING FUNCTIONS
void displaying_board(vector<vector<short>> &board);
string displaying_picture_ascii(ifstream &);
void game_intro();

//PLAY FUNCTIONS
vector<ship> setting_ship(vector<ship> &custom_ship, match_config &match, vector<vector<short>> &board, short &current_ship);
vector<vector<short>> selecting_setup(match_config &match, vector<vector<short>> &board);
void displaying_ships(match_config &);
vector<vector<short>> board_set(vector < vector<short>> &board, char cord_x_char, int cord_y, vector<ship> custom_ship, short current_ship);
bool board_collision(vector<vector<short>> &board, char cord_x, int cord_y, vector<ship> custom_ship, short current_ship, match_config match);

int main()
{
	//EARLY SETTINGS
	match_config match;

	//BOARDS
	vector< vector<short>> board_1, board_2;
	//START



	//game_intro();
	cout << "If this is your first time using this app, we recommend to see help page. To select a help page input '4' on your keyboard and click 'Enter' button." << endl;
	
	
	

	
	Main_menu(match);
	generating_board(board_1, match);
	generating_board(board_2, match);
	cout << "Battleship: " << endl;
	generating_ship(ship(), match.battleship, match, match.battleship_amount, match.battleship_size, match.battleship_name);
	cout << "Cruiser: " << endl;
	generating_ship(ship(), match.cruiser, match, match.cruiser_amount, match.cruiser_size, match.cruiser_name);
	cout << "Destroyer: " << endl;
	generating_ship(ship(), match.destroyer, match, match.destroyer_amount, match.destroyer_size, match.destroyer_name);

	
	system("cls");
	
	cout << "\n\n";


	displaying_board(board_1);
	selecting_setup(match, board_1);
	displaying_board(board_1);
	cout << "\n\n";
	cout << match.type << endl;
	cout << match.oponent << endl;
	cout << "\nMISS SOUND: " << endl;
	cout << match.miss_duration_1 << endl;
	cout << match.miss_duration_2 << endl;
	cout << match.miss_tone_1 << endl;
	cout << match.miss_tone_2 << endl;
	cout << "\nSHOT SOUND: " << endl;
	cout << match.shot_duration << endl;
	cout << match.shot_tone << endl;
	cout << "\nHIT SOUND: " << endl;
	cout << match.hit_duration << endl;
	cout << match.hit_tone << endl;

	cout << "TEST DESTROYER: " << endl;
	for (int i = 0; i < match.destroyer_amount; i++) {
		cout << "size: " << match.destroyer[i].size << endl;
	}


	return 0;

}

//MAIN MENU
match_config Main_menu(match_config &match) {
	//cout << "[1] PLAY\n[2] SETTINGS\n[3] COPYRIGHT\n[4] HELP\n[5] EXIT\n";
	ifstream Intro_image("menu_ascii.txt");
	string ascii_picture = displaying_picture_ascii(Intro_image);
	cout << ascii_picture << endl;
	Intro_image.close();


	int choice = 0;
	cin >> choice;
	switch (choice) {
	case 1: {
		system("cls");
		Main_menu_play(match);
	}break;
	case 2: {
		system("cls");
		Main_menu_settings(match);
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
	return match;
}


match_config Main_menu_help(match_config &match) {
	cout << "      --HELP--\n" << endl;
	cout << "--- [BASIC INPUT] ---\n" << endl;
	cout << "[1],[2],[3],[n]  - Enter respectively 1,2,3 etc. value on your keyboard to choose that option " << endl;
	cout << "[ < ], [ > ] - Press [ < ]  LEFT ARROW or [ > ] RIGHT ARROW on keyboard to choose this option " << endl;
	cout << "\n\n\n\n [ < ] GO BACK     [ > ] GO NEXT\n";

	int choice_value = 0;
	Main_menu_choice(choice_value);
	do {

		switch (choice_value) {
		case -1: {
			system("cls");
			return Main_menu(match);
		}
		case 0: {
			system("cls");
			return Main_menu_help(match);
		}break;
		case 1: {
			system("cls");
			cout << "      --HELP--\n" << endl;
			cout << "--- [GENERAL RULES] --- " << endl;
			cout << "\n\n In first step You will have to set up Your formation of ships. After that the battle begins. Your purpose is to destroy all enemy units." << endl;
			cout << "There is standard match and custom match. To learn more about it [ > ] GO NEXT ";
			cout << "\n\n [ < ] GO BACK     [ > ] GO NEXT\n";
			Main_menu_choice(choice_value);
			system("cls");

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
			system("cls");
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
			system("cls");
		}break;
		case 4: {
			system("cls");
			return Main_menu_help(match);
		}break;
		}
	} while (choice_value != -1);
	return Main_menu(match);
}

void Main_menu_copyright(match_config &match) {
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

void Main_menu_exit(match_config &match) {
	ifstream Intro_image("exit_ascii.txt");
	string ascii_picture = displaying_picture_ascii(Intro_image);
	cout << ascii_picture << endl;
	Sleep(2000);
	Intro_image.close();
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
	ifstream Intro_image("match_choice_ascii.txt");
	string ascii_picture = displaying_picture_ascii(Intro_image);
	cout << ascii_picture << endl;
	Intro_image.close();
	int choice = 0;
	do {
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
	} while (choice < 1 || choice > 2);
	system("cls");
	Intro_image.open("oponent_choice_ascii.txt");
	ascii_picture = displaying_picture_ascii(Intro_image);
	cout << ascii_picture << endl;
	Intro_image.close();
	choice = 0;
	do {
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
	} while (choice < 1 || choice > 2);
	system("cls");
	if (match.type == "custom") {
		system("cls");
		Main_menu_play_custom(match);
	}
	return match;
}

match_config Main_menu_settings(match_config &match) {
	cout << "   --SETTINGS-- \n" << endl;
	cout << "[1] Change shot sound\n[2] Change hit sound\n[3] Change miss sound\n\n\n[4] MAIN MENU" << endl;
	int choice = 0, choice_value = 0, sound_choice = 0;
	while (choice < 1 || choice > 4) {
		choice = 0;
		cin >> choice;
		switch (choice) {
		case 1: {
			system("cls");
			cout << "[1] - Default sound\n[2] - Sound #1\n[3] - Sound #2\n\n" << endl;
			sound_choice = 1;
			Main_menu_settings_sound(sound_choice, match, 300, "shot sound");
			Main_menu_settings(match);
		}break;
		case 2: {
			system("cls");
			cout << "[1] - Default sound\n[2] - Sound #1\n[3] - Sound #2\n\n" << endl;
			sound_choice = 2;
			Main_menu_settings_sound(sound_choice, match, 300, "hit sound");
			Main_menu_settings(match);

		}break;
		case 3: {
			system("cls");
			cout << "[1] - Default Sound\n[2] - Sound #1\n[3] - Sound #2\n\n" << endl;
			sound_choice = 3;
			Main_menu_settings_sound(sound_choice, match, 300, "miss sound");
			Main_menu_settings(match);
		}break;
		case 4: {
			system("cls");
			Main_menu(match);
		}break;
		default: {
			cout << "Unexpected choice! Please try again..." << endl;
		}break;
		}
	}
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

match_config Main_menu_settings_sound(int &sound_choice, match_config &match, int value_1, string sound_name) {
	int duration_1 = 300, duration_2 = 400;
	int value_2 = 200;
	if (sound_choice == 2) {
		duration_1 = 600;
		value_1 += 40;
	}
	else if (sound_choice == 3) {
		duration_1 = 250;
		duration_2 = 200;
		value_1 += 50;
		value_2 += 25;
	}
	int second_sound_choice;
	do {
		cin >> second_sound_choice;
		if (second_sound_choice == 1) {
			system("cls");
			//Playing sound
			Beep(value_1, duration_1);
			if (sound_choice == 3) Beep(value_2, duration_2);
			cout << "//Default Sound has been set up as [" << sound_name << "] \n\n";
		}
		else if (second_sound_choice == 2) {
			system("cls");
			//Playing sound
			Beep(value_1 + 100, duration_1);
			if (sound_choice == 3) {
				Beep(value_2, duration_2);
				value_2 -= 40;
			}
			value_1 += 100;
			cout << "//Sound #1 has been set up as [" << sound_name << "] \n\n";
		}
		else if (second_sound_choice == 3) {
			system("cls");
			//Playing sound
			Beep(value_1 + 300, duration_1);
			if (sound_choice == 3) {
				Beep(value_2 + 150, duration_2);
				value_2 += 150;
			}
			value_1 += 300;
			cout << "//Sound #2 has been set up as [" << sound_name << "] \n\n";
		}
		else {
			cout << "Unexpected choice! Please try again..." << endl;
		}
	} while (sound_choice < 1 || sound_choice > 3);

	if (sound_name == "miss sound") {
		match.miss_tone_1 = value_1;
		match.miss_tone_2 = value_2;
		match.miss_duration_1 = duration_1;
		match.miss_duration_2 = duration_2;
	}
	else if (sound_name == "hit sound") {
		match.hit_tone = value_1;
		match.hit_duration = duration_1;
	}
	else if (sound_name == "shot sound") {
		match.shot_tone = value_1;
		match.shot_duration = duration_1;
	}
	//Setting up miss sound
	return match;
}

match_config Main_menu_play_custom(match_config &match) {
	system("cls");
	cout << "You can change the game rules by selecting options below...\n\n[1] Ships section\n[2] Boards section\n[3] Ship Creator\n[4] APPLY CHANGES & EXIT\n" << endl;
	short choice;
	do {
		cin >> choice;
		switch (choice) {
		case 1: {
			system("cls");
			Main_menu_custom_ships(match);

		}break;
		case 2: {
			system("cls");
			Main_menu_custom_boards(match);

		}break;
		case 3: {
			system("cls");
			Main_menu_custom_ship_creator(match);
		}
		case 4: {
			return match;
		}break;
		default: {
			cout << "Unexpected choice! Please try again..." << endl;
		}break;
		}
	} while (choice < 1 || choice > 4);
	return match;
}

match_config Main_menu_custom_ships(match_config &match) {
	short choice, second_choice;
	short max_choice = 4 + match.custom_ships_amount; //used to navigate to go back
	do {
		system("cls");
		ifstream Intro_image("ships_section_ascii.txt");
		string ascii_picture = displaying_picture_ascii(Intro_image);
		cout << ascii_picture << endl;
		Intro_image.close();
		cout << "\n\nSelect a specific ship to make some changes...\n\n";



		displaying_ships(match);

		
	
		cin >> choice;
		if (choice > -1 && choice < 4) {
			switch (choice) {
			case 0: {
				cin >> choice;
			}break;
			case 1: {
				do {
					system("cls");
					cout << "[" << match.battleship_name << "]\n";
					cout << "Ship size: " << match.battleship_size << "\nAmount: " << match.battleship_amount << endl;
					cout << "\n[1] Change ship size\n[2] Change amount of this ship\n[3] Change the name\n\n[4] GO BACK" << endl;
					cin >> second_choice;
					switch (second_choice) {
					case 1: {
						cout << "Enter a value: ";
						cin >> match.battleship_size;
						second_choice = 0;
					}break;
					case 2: {
						cout << "Enter a value: ";
						cin >> match.battleship_amount;
						second_choice = 0;
					}break;
					case 3: {
						cout << "Enter a name: ";
						cin >> match.battleship_name;
						second_choice = 0;
					}
					case 4: {
						choice = 0;
						break;
					}break;
					default: {
						cout << "Unexpected choice! Please try again..." << endl;
						Sleep(1000);
					}
					}
				} while (second_choice < 1 || second_choice > 4);
			}break;
			case 2: {
				do {
					system("cls");
					cout << "[" << match.cruiser_name << "]\n";
					cout << "Ship size: " << match.cruiser_size << "\nAmount: " << match.cruiser_amount << endl;
					cout << "\n[1] Change ship size\n[2] Change amount of this ship\n[3] Change the name\n\n[4] GO BACK" << endl;
					cin >> second_choice;
					switch (second_choice) {
					case 1: {
						cout << "Enter a value: ";
						cin >> match.cruiser_size;
						second_choice = 0;
					}break;
					case 2: {
						cout << "Enter a value: ";
						cin >> match.cruiser_amount;
						second_choice = 0;
					}break;
					case 3: {
						cout << "Enter a name: ";
						cin >> match.cruiser_name;
						second_choice = 0;
					}
					case 4: {
						choice = 0;
						break;
					}break;
					default: {
						cout << "Unexpected choice! Please try again..." << endl;
						Sleep(1000);
					}
					}
				} while (second_choice < 1 || second_choice > 4);
			}break;
			case 3: {
				do {
					system("cls");
					cout << "[" << match.destroyer_name << "]\n";
					cout << "Ship size: " << match.destroyer_size << "\nAmount: " << match.destroyer_amount << endl;
					cout << "\n[1] Change ship size\n[2] Change amount of this ship\n[3] Change the name\n\n[4] GO BACK" << endl;
					cin >> second_choice;
					switch (second_choice) {
					case 1: {
						cout << "Enter a value: ";
						cin >> match.destroyer_size;
						second_choice = 0;
					}break;
					case 2: {
						cout << "Enter a value: ";
						cin >> match.destroyer_amount;
						second_choice = 0;
					}break;
					case 3: {
						cout << "Enter a name: ";
						cin >> match.destroyer_name;
						second_choice = 0;
					}
					case 4: {
						choice = 0;
						break;
					}break;
					default: {
						cout << "Unexpected choice! Please try again..." << endl;
						Sleep(1000);
					}
					}
				} while (second_choice < 1 || second_choice > 4);
			}break;
			default: {
				cout << "Unexpected choice! Please try again..." << endl;
				Sleep(2000);
				system("cls");
			}break;
				/*case 4: {
					return Main_menu_play_custom(match);
				}break;
				default: {
					cout << "Unexpected choice! Please try again..." << endl;
					Sleep(2000);
					system("cls");
				}break;*/
			}
		}
		else if(choice == max_choice )
		return Main_menu_play_custom(match);
		else {
		choice = choice - 4;
		do {
			system("cls");
			cout << "[" << match.custom_ship_main[choice][0].name << "]\n";
			cout << "Ship size: " << match.custom_ship_main[choice][0].size << "\nAmount: " << match.custom_ship_main[choice][0].amount << endl;
			cout << "\n[1] Change ship size\n[2] Change amount of this ship\n[3] Change the name\n\n[4] GO BACK" << endl;
			cin >> second_choice;
			switch (second_choice) {
			case 1: {
				cout << "Enter a value: ";
				cin >> match.custom_ship_main[choice][0].size;
				custom_ship_update(match.custom_ship_main, choice);
				second_choice = 0;
			}break;
			case 2: {
				cout << "Enter a value: ";
				cin >> match.custom_ship_main[choice][0].amount;
				custom_ship_update(match.custom_ship_main, choice);
				second_choice = 0;
			}break;
			case 3: {
				cout << "Enter a name: ";
				cin >> match.custom_ship_main[choice][0].name;
				custom_ship_update(match.custom_ship_main, choice);
				second_choice = 0;
			}
			case 4: {
				choice = 0;
				break;
			}break;
			default: {
				cout << "Unexpected choice! Please try again..." << endl;
				Sleep(1000);
			}
			}
		} while (second_choice < 1 || second_choice > 4);
}
	} while (choice < 1 || choice > 3);
	return match;
}

match_config Main_menu_custom_ship_creator(match_config &match) {
	ifstream Intro_image("ship_creator_ascii.txt");
	string ascii_picture = displaying_picture_ascii(Intro_image);
	cout << ascii_picture << endl;
	Intro_image.close();

	cout << "\n\n[1] Create a new ship\n\n[2] GO BACK\n";
	int choice;
	string ship_name;
	int ship_size, ship_amount;
	do {
		cin >> choice;
		switch (choice) {
		case 1: {
			cout << "Enter a ship name: ";
			cin >> ship_name;
			cout << "Enter a size of this ship: ";
			cin >> ship_size;
			cout << "Enter an amount of this ship: ";
			cin >> ship_amount;
			match.custom_ships_amount++;
		}break;
		case 2: {
			return Main_menu_play_custom(match);
		}break;
		default: {
			cout << "Unexpected choice! Please try again..." << endl;
		}break;
		}
	} while (choice < 1 || choice > 2);
	generating_ship(ship(), match.custom_ship, match, ship_amount, ship_size, ship_name);
	match.custom_ship_main.push_back(match.custom_ship);
	match.custom_ship.clear();
	return Main_menu_play_custom(match);
}

match_config Main_menu_custom_boards(match_config &match) {

	short choice;

	do {
		ifstream Intro_image("boards_section_ascii.txt");
		string ascii_picture = displaying_picture_ascii(Intro_image);
		cout << ascii_picture << endl;
		Intro_image.close();
		cout << "\n\nBoard dimensions:\nvertical: " << match.board_size_y << " horizontal: " << match.board_size_x << endl;
		cout << "\n[1] Change dimensions\n[2] GO BACK\n" << endl;
		cin >> choice;
		switch (choice) {
		case 0: {

		}break;
		case 1: {
			cout << "Enter vertical dimension: ";
			cin >> match.board_size_y;
			cout << "\nEnter horizontal dimension: ";
			cin >> match.board_size_x;
			system("cls");
			choice = 0;
		}break;
		case 2: {
			return Main_menu_play_custom(match);
		}break;
		default: {
			cout << "Unexpected choice! Please try again..." << endl;
			Sleep(2000);
			system("cls");
		}break;
		}
	} while (choice < 1 || choice > 2);
	return match;
}

//GENERATING
vector <ship> generating_ship(struct ship ship_struct, vector <ship> &custom_ship, match_config &match, short ship_amount, short ship_size, string ship_name) {
	for (int i = 0; i < ship_amount; i++) {
		custom_ship.push_back(ship_struct);
		custom_ship[i].size = ship_size;
		custom_ship[i].amount = ship_amount;
		custom_ship[i].name = ship_name;
		//for tests only
		cout << "Ship [" << i << "] size: " << custom_ship[i].size << endl;
	}

	return custom_ship;
}

vector <vector <short>> generating_board(vector<vector<short>> &board, match_config &match) {
	vector <short> board_fill; //used temporarily to initialize the board
	for (int i = 0; i < match.board_size_x; i++) {
		board_fill.push_back(0);


	}
	for (int j = 0; j < match.board_size_y; j++) {
		board.push_back(board_fill);
	}

	return board;
}

//DISPLAYING
void displaying_board(vector<vector <short>> &board) {
	//using size_t to solve mismatch warning
	cout << "  ";
	//displaying A - x on board where x is the last char of board_X dimension
	for (size_t i = 0; i < board[0].size(); i++) {
		cout << char(65 + i) << "  ";
	}
	cout << endl;
	//main display
	for (size_t i = 0; i < board.size(); i++) {
		cout << i + 1 << "|";
		for (size_t j = 0; j < board[0].size(); j++) {
			if (board[i][j] == 0)
				cout << "*";
			else if (board[i][j] == 1)
				cout << char(254);
			cout << "  ";
		}
		cout << endl;
	}
}

string displaying_picture_ascii(ifstream &ascii_picture) {
	string lines = "";
	if (ascii_picture) {
		while (ascii_picture.good()) {
			string templine;
			getline(ascii_picture, templine);
			templine += "\n";
			lines = lines + templine;
		}
		return lines;
	}
	else
	{
		return "ASCII image is missing...";
	}
}

void game_intro() {
	system("pause");
	ifstream Intro_image("intro_ascii_1.txt");
	string ascii_picture = displaying_picture_ascii(Intro_image);
	cout << ascii_picture << endl;
	Sleep(2000);
	Intro_image.close();
	system("cls");

	Intro_image.open("intro_ascii_2.txt");
	ascii_picture = displaying_picture_ascii(Intro_image);
	cout << ascii_picture << endl;
	Sleep(500);
	Intro_image.close();
	system("cls");

	Intro_image.open("intro_ascii_3.txt");
	ascii_picture = displaying_picture_ascii(Intro_image);
	cout << ascii_picture << endl;
	Sleep(500);
	Intro_image.close();
	system("cls");

	Intro_image.open("intro_ascii_1.txt");
	ascii_picture = displaying_picture_ascii(Intro_image);
	cout << ascii_picture << endl;
	Sleep(1000);
	Intro_image.close();
	system("cls");

	Intro_image.open("intro_ascii_2.txt");
	ascii_picture = displaying_picture_ascii(Intro_image);
	cout << ascii_picture << endl;
	Sleep(500);
	Intro_image.close();
	system("cls");

	Intro_image.open("intro_ascii_3.txt");
	ascii_picture = displaying_picture_ascii(Intro_image);
	cout << ascii_picture << endl;
	Sleep(500);
	Intro_image.close();
	system("cls");

	Intro_image.open("intro_ascii_end.txt");
	ascii_picture = displaying_picture_ascii(Intro_image);
	cout << ascii_picture << endl;
	Sleep(1500);
	Intro_image.close();
	system("cls");
}

//OTHER

vector<ship> setting_ship(vector<ship> &custom_ship, match_config &match, vector<vector<short>> &board, short &current_ship) {
	int choice;
	int cord_y;
	char cord_x;

	//setting positon (vertical or horizontal)
	do {
		int cord_y_local;
		char cord_x_local;

		cout << "Select position:\n[1] Vertical\n[2] Horizontal\n";
		do {
			cin >> choice;
			if (choice == 1) {
				custom_ship[current_ship].position = "vertical";
			}
			else if (choice == 2) {
				custom_ship[current_ship].position = "horizontal";
			}
			else {
				cout << "Unexpected choice! Please try again..." << endl;
			}
		} while (choice < 1 || choice > 2);

		
		//setting coordinates
		do {
			cout << "Enter coordinate from: A to " << char(int('A') + match.board_size_x - 1) << endl;
			cin >> cord_x_local;
			if (int(cord_x_local) < int('A') || int(cord_x_local) > int(char('A') + match.board_size_x - 1))
				cout << "The cord is out of range! Please try again..." << endl;

		} while (int(cord_x_local) < int('A') || (int(cord_x_local) > int(char('A') + match.board_size_x - 1)));
		//correcting cord_x value
		cord_x_local = cord_x_local - 65;

		
		do {
			cout << "Enter coordinate from: 1 to " << match.board_size_y << endl;
			cin >> cord_y_local;
			if (cord_y_local < 1 || cord_y_local > match.board_size_y)
				cout << "The cord is out of range! Please try again..." << endl;

		} while (cord_y_local < 1 || cord_y_local > match.board_size_y);
		//correcting cord_y value
		cord_y_local -= 1;

		cord_y = cord_y_local;
		cord_x = cord_x_local;
	} while (board_collision(board, cord_x, cord_y, custom_ship, current_ship, match) == true);
	board_set(board, cord_x, cord_y, custom_ship, current_ship);

	
	return custom_ship;
}

bool board_collision(vector<vector<short>> &board, char cord_x_char, int cord_y, vector<ship> custom_ship, short current_ship, match_config match) {
	int cord_x = int(cord_x_char);
	if (custom_ship[current_ship].position == "vertical") {
		for (int i = 0; i < custom_ship[current_ship].size; i++) {
			if (board[cord_y + i][cord_x] == 1)
			{
				cout << "Ooops! There would be a collision. Please try again..." << endl;
				return true;
			}
				
			if (cord_y + i > match.board_size_y) {
				cout << "This place is out of range! Please try again..." << endl;
				return true;
			}
		}
		//there is no collision
		return false;
	}
	else {
		for (int i = 0; i < custom_ship[current_ship].size; i++) {
			if (board[cord_y][cord_x + i] == 1)
				return true;
		}
		//there is no collision
		return false;

	}
}


vector<vector<short>> selecting_setup(match_config &match, vector<vector<short>> &board) {
	cout << "Select a following ship to set up the formation: " << endl;
	short custom_ship_order = 0;
	for (int i = 0; i < 3 + match.custom_ships_amount; i++) {
		cout << "[" << i + 1 << "] ";
		switch (i) {
		case 0: {
			cout << match.battleship_name << "[Available: " << (match.battleship_amount - match.battleship[0].setting_order)  << "]" << endl;

		}break;
		case 1: {
			cout << match.cruiser_name << "[Available: " << (match.cruiser_amount - match.cruiser[0].setting_order) << "]" << endl;
		}break;
		case 2: {
			cout << match.destroyer_name << "[Available: " << (match.destroyer_amount - match.destroyer[0].setting_order) << "]" << endl;
		}break;
		default: {
			cout << match.custom_ship_main[custom_ship_order][0].name;
			cout << "[Available: " << (match.custom_ship_main[custom_ship_order][0].amount - match.custom_ship_main[custom_ship_order][0].setting_order) << "]" << endl;
			custom_ship_order++;
		}break;
		}
	}
	int choice;
	do {
		cin >> choice;
		switch (choice) {
		case 1: {
			setting_ship(match.battleship, match, board, match.battleship[0].setting_order);
			match.battleship[0].setting_order++;
		}break;
		case 2: {
			setting_ship(match.cruiser, match, board, match.cruiser[0].setting_order);
			match.cruiser[0].setting_order++;

		}break;
		case 3: {
			setting_ship(match.destroyer, match, board, match.destroyer[0].setting_order);
			match.destroyer[0].setting_order++;
		}break;
		default: {
			if (choice < 1 || choice > 3 + match.custom_ships_amount) {
				cout << "Unexpected choice! Please try again...";
				break;
			}
			else {
				choice = choice - 4;
				setting_ship(match.custom_ship_main[choice], match, board, match.custom_ship_main[choice][0].setting_order);
				match.custom_ship_main[choice][0].setting_order++;
			}

		}break;
		}
	} while (choice < 1 || choice > 3 + match.custom_ships_amount);
	return board;
}

void displaying_ships(match_config &match) {
	for (int i = 0; i < 3 + match.custom_ships_amount; i++) {
		cout << "[" << i + 1 << "] ";
		switch (i) {
		case 0: {
			cout << match.battleship_name << endl;
		}break;
		case 1: {
			cout << match.cruiser_name << endl;
		}break;
		case 2: {
			cout << match.destroyer_name << endl;
		}break;
		default: {
			cout << match.custom_ship_main[i - 3][0].name << endl;
		}break;
		}
	}
	cout << "[" << 4 + match.custom_ships_amount << "]" << " GO BACK" << endl;
	
}

vector<vector<short>> board_set(vector < vector<short>> &board, char cord_x_char, int cord_y, vector<ship> custom_ship, short current_ship) {
	int cord_x = int(cord_x_char);
	if (custom_ship[current_ship].position == "vertical") {
		for (int i = 0; i < custom_ship[current_ship].size; i++) {
			board[cord_y + i][cord_x] = 1;
				
		}
		
	}
	else {
		for (int i = 0; i < custom_ship[current_ship].size; i++) {
			board[cord_y][cord_x + i] = 1;
				
		}
		

	}
	return board;
}

vector <vector<ship>> custom_ship_update(vector<vector<ship>> &custom_ship, int ship_type) {
	//Setting basic parameters(size,amount,name) of every ship as the first one
	int general_size;
	int general_amount;
	string general_name;

	general_size = custom_ship[ship_type][0].size;
	general_amount = custom_ship[ship_type][0].amount;
	general_name = custom_ship[ship_type][0].name;

	for (size_t i = 0; i < custom_ship[ship_type].size(); i++) {
		custom_ship[ship_type][i].size = general_size;
		custom_ship[ship_type][i].amount = general_amount;
		custom_ship[ship_type][i].name = general_name;
	}
	return custom_ship;
}
