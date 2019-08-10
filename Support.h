int startingHard[3][3] = { {8, 7, 3},
							{6, 2, 1},
							{4, 0, 5} };

int startingMedium[3][3] = { {1, 7, 0},
							{6, 3, 4},
							{8, 5, 2} };

int startingEasy[3][3] = { {3, 1, 0},
							{4, 7, 2},
							{6, 8, 5} };

int startingObjective[3][3] = { {0, 1, 2},
								{3, 4, 5},
								{6, 7, 8} };

template <typename N>
int getStartingEmpty(N starting[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (starting[i][j] == 0)
			{
				return (j + (3 * i));
			}
		}
	}
	return 0;
}

template <typename N>
void copyAllPos(N source[3][3], N output[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			output[i][j] = source[i][j];
		}
	}
}

template <typename N>
int getStartingPoint(node<N>* currentState)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (currentState->getPiece(i, j) == 0)
			{
				return j + (3 * i);
			}
		}
	}
	return 10;
}

template <typename N>
void printStart(node<N>* stat)
{
	cout << "                                    " << stat->getPiece(0, 0) << " " << stat->getPiece(0, 1) << " " << stat->getPiece(0, 2) << endl;
	cout << "                                    " << stat->getPiece(1, 0) << " " << stat->getPiece(1, 1) << " " << stat->getPiece(1, 2) << endl;
	cout << "                                    " << stat->getPiece(2, 0) << " " << stat->getPiece(2, 1) << " " << stat->getPiece(2, 2) << endl;
}

template <typename N>
void printStat(node<N>* stat)
{
	cout << "Status: " << endl;
	cout << "                                    " << stat->getPiece(0, 0) << " " << stat->getPiece(0, 1) << " " << stat->getPiece(0, 2) << endl;
	cout << "                                    " << stat->getPiece(1, 0) << " " << stat->getPiece(1, 1) << " " << stat->getPiece(1, 2) << endl;
	cout << "                                    " << stat->getPiece(2, 0) << " " << stat->getPiece(2, 1) << " " << stat->getPiece(2, 2) << endl;
}

template <typename N>
void dynamicView(node<N>* curStat)
{
	system("CLS");
	cout << "------------------------------Analyzing...-------------------------------------" << endl;
	printStat(curStat);
	//cout << "Current last starting point: " << curStat->getLastEmptyPoint() << endl;
	//cout << "Current starting point: " << curStat->getEmptyPoint() << endl;
	//cout << "Current Heuristic: " << curStat->getHeuristic() << endl;
	//cout << "Current Cost: " << curStat->getCost() << endl << endl;
	cout << "Current F(n): " << curStat->getfN() << endl << endl;
	//cout << "Childs: " << endl;
}

template <typename N>
void solutionSteps(node<N>* solution)
{
	node<N>* curStep;
	node<N>* startStep;

	int x = 0;
	int y = 0;
	int total = 0;

	startStep = solution;
	curStep = solution;

	while (curStep != nullptr)
	{
		for (int i = -1; i < 3; i++)
		{
			curStep = startStep;
			y = 0;
			while (y < 10 && curStep != nullptr)
			{

				if (i == -1)
				{
					if (x / 10 == 0)
					{
						cout << " ";
					}

					cout << " " << x << "     ";

					x++;
				}
				else
				{
					cout << curStep->getPiece(i, 0) << " " << curStep->getPiece(i, 1) << " " << curStep->getPiece(i, 2) << "   ";
				}

				curStep = curStep->getParent();
				y++;
			}
			cout << endl;
		}
		startStep = curStep;
		cout << endl << endl;
	}
}

template <typename N>
void showResult(node<N>* toShow)
{
	system("CLS");
	cout << "|-----------------------------SOLUTION FOUND!---------------------------------|" << endl;
	printStat(toShow);
	cout << "Total Cost: " << toShow->getCost() << endl << endl;
	cout << "|-----------------------------SOLUTION STEPS:---------------------------------|" << endl << endl;
	solutionSteps(toShow);
}