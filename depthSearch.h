
template <typename N>
linkedStack<N>* dSearch;

template <typename N>
void dBuildNewStatus(node<N>* newFather, int newCost, int startI, int startJ, int moveI, int moveJ)
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
	dSearch<N>->push(newFather, newStat, newEmpty, newLastEmpty, newCost);
}

template <typename N>
void dBuildChilds(node<N>* parent, int start)
{
	dSearch<N>->pop();
	if (parent->getCost() < 30 && !parent->isOpened())
	{
		int startI = start / 3;
		int startJ = start % 3;

		int moveI = 0;
		int moveJ = 0;

		//int curStat[3][3];
		//getCurStatus(parent, curStat);
		//dynamicView(curStat);

		if (startI > 0)
		{
			//cout << "UP" << endl;
			moveI = startI - 1;
			moveJ = startJ;
			if (parent->getLastEmptyPoint() != (moveJ + (3 * moveI)))
			{
				dBuildNewStatus(parent, parent->getCost() + 1, startI, startJ, moveI, moveJ);
			}
		}

		if (startI < 2)
		{
			//cout << "DOWN" << endl;
			moveI = startI + 1;
			moveJ = startJ;
			if (parent->getLastEmptyPoint() != (moveJ + (3 * moveI)))
			{
				dBuildNewStatus(parent, parent->getCost() + 1, startI, startJ, moveI, moveJ);
			}
		}

		if (startJ > 0)
		{
			//cout << "LEFT" << endl;
			moveI = startI;
			moveJ = startJ - 1;
			if (parent->getLastEmptyPoint() != (moveJ + (3 * moveI)))
			{
				dBuildNewStatus(parent, parent->getCost() + 1, startI, startJ, moveI, moveJ);
			}
		}

		if (startJ < 2)
		{
			//cout << "RIGHT" << endl;
			moveI = startI;
			moveJ = startJ + 1;
			if (parent->getLastEmptyPoint() != (moveJ + (3 * moveI)))
			{
				dBuildNewStatus(parent, parent->getCost() + 1, startI, startJ, moveI, moveJ);
			}
		}
	}
	else
	{
		delete parent;
	}
}

template <typename N>
void depthSearch(N start[3][3])
{
	dSearch<N> = new linkedStack<N>;
	
	dSearch<N>->push(nullptr, start, getStartingEmpty(start), 10, 0);

	node<N>* currentStat = dSearch<N>->top();

	system("CLS");
	cout << "|-----------------------Starting Status for Depth Search:-------------------------|" << endl;
	printStart(currentStat);

	cin.get();

	bool success = true;

	while (dSearch<N>->top()->getHeuristic() != 0)
	{
		try
		{
			dBuildChilds(dSearch<N>->top(), dSearch<N>->top()->getEmptyPoint());
		}
		catch (bad_alloc& fullMemory)        // Caso a memória esteja cheia
		{
			cerr << "Exception ocurred: " << fullMemory.what() << endl; // Reporta o erro
			success = false;
			break;
		}
	}

	if (success)
	{
		showResult(dSearch<N>->top());
	}
	else
	{
		cout << "Couldn´t find solution. Memory full." << endl;
	}
	cin.get();

	delete dSearch<N>;
}
