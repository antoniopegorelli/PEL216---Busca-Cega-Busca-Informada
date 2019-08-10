// searchMainMenu.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "DataStructure.h"		// Header com a estrutura de dados
#include "Support.h"			// Header com funções de suporte
#include "breadthSearch.h"		// Header com a busca em largura
#include "depthSearch.h"		// Header com a busca em profundidade
#include "climbSearch.h"		// Header com a busca de subida de encosta
#include "starSearch.h"			// Header com a busca A estrela
#include "mainMenu.h"			// Header com o menu principal

// Inicialização do nó de partida
template<typename N>
node<N>* startingNode;


// Método principal
int main()
{
	startingNode<int> = new node<int>(nullptr, startingEasy, getStartingEmpty(startingEasy), 10, 0); // Geração do nó inicial
	int toResolve[3][3];
	int menu = 1;
	
	while (1)														// Ciclo de geração do menu
	{
		switch (mainMenu(startingNode<int>, menu)) { 
		case 1:
			startingNode<int>->changeAllPos(startingEasy);
			copyAllPos(startingEasy, toResolve);
			menu = 10;
			break;
		case 2:
			startingNode<int>->changeAllPos(startingMedium);
			copyAllPos(startingMedium, toResolve);
			menu = 10;
			break;
		case 3:
			startingNode<int>->changeAllPos(startingHard);
			copyAllPos(startingHard, toResolve);
			menu = 10;
			break;
		case 4:
			system("CLS");
			cout << "Sorry, it's not implemented yet..." << endl << "Please choose another option" << endl;
			cin.get();
			break;
		case 10:
			breadthSearch(toResolve);
			menu = 1;
			break;
		case 20:
			depthSearch(toResolve);
			menu = 1;
			break;
		case 30:
			climbSearch(toResolve);
			menu = 1;
			break;
		case 40:
			starSearch(toResolve);
			menu = 1;
			break;
		case 5:
			return 0;
			break;
		case 50:
			return 0;
			break;
		default:
			break;
		}
	}
	
	return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
