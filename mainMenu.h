#include <conio.h>

// Definição de dados de informação para teclas pressionadas
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13

// Método para identificar tecla presisonada
int menuMovement(void)
{
	int c = 0;
	int key = 0;

	while (key == 0)
	{
		switch (c = _getch()) {
		case KEY_UP:
			key = KEY_UP;
			break;
		case KEY_DOWN:
			key = KEY_DOWN;
			break;
		case KEY_LEFT:
			key = KEY_LEFT;
			break;
		case KEY_RIGHT:
			key = KEY_RIGHT;
			break;
		case KEY_ENTER:
			key = KEY_ENTER;
			break;
		default:
			key = 0;
			break;
		}
	}

	return key;
}

// Método para gerar graficamente o menu principal e retornar o comando selecionado
template <typename N>
int mainMenu(node<N>* starting, int menu)
{
	bool inMenu = true;
	int menuPos = 1;

	//cin.get();
    while (inMenu)
    {
        system("CLS");
		
		if (menu == 1)
		{
			cout << "|-----------                                                   ------------|" << endl;
			cout << "|------------------              Main Menu              -------------------|" << endl;
			cout << "|-----------                                                   ------------|" << endl << endl << endl;
		}
        //cout << endl << "----------------------------------Options-----------------------------------" << endl << endl;
		if (menu == 10)
		{
			cout << endl << "|--------------------------Starting Puzzle Status--------------------------|" << endl << endl;
			//cout << "Starting puzzle status:" << endl;
			printStart(starting);
			cout << endl << endl;
		}
		cout << "    Please select action using arrow keys:" << endl << endl;

		if (menu == 1)
		{
			if (menuPos == 1) { cout << "->"; }
			else { cout << " "; }
			cout << " Select Easy difficulty starting point (6 movements)" << endl;
			if (menuPos == 2) { cout << "->"; }
			else { cout << " "; }
			cout << " Select Medium difficulty starting point (14 movements)" << endl;
			if (menuPos == 3) { cout << "->"; }
			else { cout << " "; }
			cout << " Select Hard difficulty starting point (25 movements)" << endl;
			if (menuPos == 4) { cout << "->"; }
			else { cout << " "; }
			cout << " Select random starting point (? movements)" << endl;
		}
		//if (menuPos == 3) { cout << "->"; }
		//else { cout << " "; }
  //      cout << " Scramble new starting point" << endl;
		if (menu == 10)
		{
			if (menuPos == 1) { cout << "->"; }
			else { cout << " "; }
			cout << " Resolve the puzzle using Breadth First Search" << endl;
			if (menuPos == 2) { cout << "->"; }
			else { cout << " "; }
			cout << " Resolve the puzzle using Depth First Search" << endl;
			if (menuPos == 3) { cout << "->"; }
			else { cout << " "; }
			cout << " Resolve the puzzle using Hill Climb Search" << endl;
			if (menuPos == 4) { cout << "->"; }
			else { cout << " "; }
			cout << " Resolve the puzzle using A* Search" << endl;
		}
			if (menuPos == 5) { cout << "->"; }
			else { cout << " "; }
			cout << " Exit" << endl << endl;
		
		switch (menuMovement()) {
		case KEY_UP:
			if (menuPos > 1)
			{
				menuPos--;
			}
			else
			{
				menuPos = 5;
			}
			break;
		case KEY_DOWN:
			if (menuPos < 5)
			{
				menuPos++;
			}
			else
			{
				menuPos = 1;
			}
			break;
		case KEY_ENTER:
			inMenu = false;
			break;
		default:
			break;
		}
    }

	return menuPos * menu;
}