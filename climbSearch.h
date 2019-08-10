// Define a lista usada para a seleção de nós
template <typename N>
linkedList<N>* cSearch;

// Método para geração de um novo estado
template <typename N>
void cBuildNewStatus(node<N>* newFather, int newCost, int startI, int startJ, int moveI, int moveJ)
{
	int newStat[3][3];
	int newEmpty = moveJ + (3 * moveI);
	int newLastEmpty = startJ + (3 * startI);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i == startI && j == startJ)
			{
				newStat[i][j] = newFather->getPiece(moveI, moveJ);
			}
			else if (i == moveI && j == moveJ)
			{
				newStat[i][j] = newFather->getPiece(startI, startJ);
			}
			else
			{
				newStat[i][j] = newFather->getPiece(i, j);
			}
		}
	}
	cSearch<int>->addEnd(newFather, newStat, newEmpty, newLastEmpty, newCost);

	//printStat(newStat);
}

// Método para gerar os nós filhos
template <typename N>
void cBuildChilds(node<N>* parent, int start)
{
	if (parent->getCost() < 50 && !parent->isOpened())
	{
		int startI = start / 3;
		int startJ = start % 3;

		int moveI = 0;
		int moveJ = 0;

		//dynamicView(parent);

		if (startI > 0)
		{
			//cout << "UP" << endl;
			moveI = startI - 1;
			moveJ = startJ;
			if (parent->getLastEmptyPoint() != (moveJ + (3 * moveI)))
			{
				cBuildNewStatus(parent, parent->getCost() + 1, startI, startJ, moveI, moveJ);
			}
		}

		if (startI < 2)
		{
			//cout << "DOWN" << endl;
			moveI = startI + 1;
			moveJ = startJ;
			if (parent->getLastEmptyPoint() != (moveJ + (3 * moveI)))
			{
				cBuildNewStatus(parent, parent->getCost() + 1, startI, startJ, moveI, moveJ);
			}
		}

		if (startJ > 0)
		{
			//cout << "LEFT" << endl;
			moveI = startI;
			moveJ = startJ - 1;
			if (parent->getLastEmptyPoint() != (moveJ + (3 * moveI)))
			{
				cBuildNewStatus(parent, parent->getCost() + 1, startI, startJ, moveI, moveJ);
			}
		}

		if (startJ < 2)
		{
			//cout << "RIGHT" << endl;
			moveI = startI;
			moveJ = startJ + 1;
			if (parent->getLastEmptyPoint() != (moveJ + (3 * moveI)))
			{
				cBuildNewStatus(parent, parent->getCost() + 1, startI, startJ, moveI, moveJ);
			}
		}
		try
		{
			cSearch<int>->findNodeToDel(parent);
		}
		catch (noNodeToDel& delError)       // Caso haja erro
		{
			cerr << delError.what() << endl;    // Reportar o erro
		}
	}
	else
	{
		try
		{
			cSearch<int>->findNodeToDel(parent);
		}
		catch (noNodeToDel& delError)       // Caso haja erro
		{
			cerr << delError.what() << endl;    // Reportar o erro
		}
	}
}

// Método principal para a busca de subida de encosta
template <typename N>
void climbSearch(N start[3][3])
{
	cSearch<int> = new linkedList<int>;

	cSearch<int>->addStart(nullptr, start, getStartingEmpty(start), 10, 0);

	node<int>* currentStat = cSearch<int>->getStart();

	system("CLS");
	cout << "|----------------------Starting Status for Hill Climb:-------------------------|" << endl;
	printStart(currentStat);

	cin.get();

	while (currentStat->getHeuristic() > 0)
	{
		cBuildChilds(currentStat, getStartingPoint(currentStat));
		if (currentStat->getBestChild()->getHeuristic() <= currentStat->getHeuristic())
		{
			currentStat = currentStat->getBestChild();
		}
		else
		{
			break;
		}
	}

	if (currentStat->getHeuristic() == 0)
	{
		showResult(currentStat);
	}
	else
	{
		cout << "Solution not found... Best status:" << endl;
		printStat(currentStat);
		cout << "Solution steps: " << currentStat->getCost() << endl;
		cout << "Solution heuristic: " << currentStat->getHeuristic() << endl;

	}

	cin.get();

	delete cSearch<int>;
}
