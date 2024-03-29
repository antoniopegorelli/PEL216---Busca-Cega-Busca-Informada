// Define a lista usada para a sele��o de n�s
template <typename N>
linkedList<N>* aSearch;

// M�todo para gera��o de um novo estado
template <typename N>
void aBuildNewStatus(node<N>* newFather, int newCost, int startI, int startJ, int moveI, int moveJ)
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
	aSearch<N>->addEnd(newFather, newStat, newEmpty, newLastEmpty, newCost);

	//printStat(newStat);
}

// M�todo para gerar os n�s filhos
template <typename N>
void aBuildChilds(node<N>* parent, int start)
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
				aBuildNewStatus(parent, parent->getCost() + 1, startI, startJ, moveI, moveJ);
			}
		}

		if (startI < 2)
		{
			//cout << "DOWN" << endl;
			moveI = startI + 1;
			moveJ = startJ;
			if (parent->getLastEmptyPoint() != (moveJ + (3 * moveI)))
			{
				aBuildNewStatus(parent, parent->getCost() + 1, startI, startJ, moveI, moveJ);
			}
		}

		if (startJ > 0)
		{
			//cout << "LEFT" << endl;
			moveI = startI;
			moveJ = startJ - 1;
			if (parent->getLastEmptyPoint() != (moveJ + (3 * moveI)))
			{
				aBuildNewStatus(parent, parent->getCost() + 1, startI, startJ, moveI, moveJ);
			}
		}

		if (startJ < 2)
		{
			//cout << "RIGHT" << endl;
			moveI = startI;
			moveJ = startJ + 1;
			if (parent->getLastEmptyPoint() != (moveJ + (3 * moveI)))
			{
				aBuildNewStatus(parent, parent->getCost() + 1, startI, startJ, moveI, moveJ);
			}
		}
		try
		{
			aSearch<N>->findNodeToDel(parent);
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
			aSearch<N>->findNodeToDel(parent);
		}
		catch (noNodeToDel& delError)       // Caso haja erro
		{
			cerr << delError.what() << endl;    // Reportar o erro
		}
	}
}

// M�todo principal para a busca em profundidade
template <typename N>
void starSearch(N start[3][3])
{
	aSearch<int> = new linkedList<int>;

	aSearch<int>->addStart(nullptr, start, getStartingEmpty(start), 10, 0);
	//aSearch<int>->addStart(nullptr, start->getAllPos(), getStartingEmpty(start->getAllPos()), 10, 0);

	node<int>* currentStat = aSearch<int>->getStart();

	system("CLS");
	cout << "|--------------------------Starting Status for A*:----------------------------|" << endl;
	printStart(currentStat);

	cin.get();

	while (currentStat->getHeuristic() > 0)
	{
		aBuildChilds(currentStat, getStartingPoint(currentStat));
		try
		{
			currentStat = aSearch<int>->getBestfN();
		}
		catch (getEmptyListNode& getError)
		{
			cerr << getError.what() << endl;
		}
	}

	showResult(currentStat);

	cin.get();

	delete aSearch<int>;
}

