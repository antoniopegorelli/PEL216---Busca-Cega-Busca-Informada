// Define a fila usada para a sele��o de n�s
template <typename N>
linkedQueue<N>* bSearch;

// M�todo para gera��o de um novo estado
template <typename N>
void bBuildNewStatus(node<N>* old, int newCost, int startI, int startJ, int moveI, int moveJ)
{
	int newStat[3][3];
	int newEmpty = moveJ + (3 * moveI);

	for (int i = 0; i < 3; i++)		// Define a matriz de dados do novo n�
	{
		for (int j = 0; j < 3; j++)
		{
			if (i == startI && j == startJ)
			{
				newStat[i][j] = old->getPiece(moveI, moveJ);
			}
			else if (i == moveI && j == moveJ)
			{
				newStat[i][j] = old->getPiece(startI, startJ);
			}
			else
			{
				newStat[i][j] = old->getPiece(i, j);
			}
		}
	}
	bSearch<N>->enqueue(old, newStat, newEmpty, old->getEmptyPoint(), newCost);		// Enfileira o novo n�

	//printStat(newStat);
}

// M�todo para gerar os n�s filhos
template <typename N>
void bBuildChilds(node<N>* father, int start)
{
	int startI = start / 3;
	int startJ = start % 3;

	int moveI = 0;
	int moveJ = 0;

	if (startI > 0)					// Verifica se existe cada movimento e gera os n�s filhos
	{
		moveI = startI - 1;
		moveJ = startJ;

		bBuildNewStatus(father, father->getCost() + 1, startI, startJ, moveI, moveJ);
	}

	if (startI < 2)
	{
		moveI = startI + 1;
		moveJ = startJ;

		bBuildNewStatus(father, father->getCost() + 1, startI, startJ, moveI, moveJ);
	}

	if (startJ > 0)
	{
		moveI = startI;
		moveJ = startJ - 1;

		bBuildNewStatus(father, father->getCost() + 1, startI, startJ, moveI, moveJ);
	}

	if (startJ < 2)
	{
		moveI = startI;
		moveJ = startJ + 1;

		bBuildNewStatus(father, father->getCost() + 1, startI, startJ, moveI, moveJ);
	}
	bSearch<N>->dequeue();			// Desenfileira o n� pai

}

// M�todo principal para a busca em largura
template <typename N>
void breadthSearch(N start[3][3])
{
	bSearch<N> = new linkedQueue<N>;								// Define fila para a an�lise dos n�s

	bSearch<N>->enqueue(nullptr, start, getStartingEmpty(start), 10, 0);

	node<N>* currentStat = bSearch<N>->front();

	system("CLS");
	cout << "|----------------------Starting Status for Breadth Search:------------------------|" << endl;
	printStart(currentStat);

	cin.get();

	while (bSearch<N>->front()->getHeuristic() != 0)				// Looop de gera��o de n�s e avalia��o de objetivo
	{

		try
		{
			bBuildChilds(bSearch<N>->front(), bSearch<N>->front()->getEmptyPoint()); // Gera n�s filhos
		}
		catch (bad_alloc& fullMemory)        // Caso a mem�ria esteja cheia
		{
			cerr << "Exception ocurred: " << fullMemory.what() << endl; // Reporta o erro
			break;
		}

	}

	if (bSearch<N>->front()->getHeuristic() == 0)				// Exibe os resultados da busca
	{
		showResult(bSearch<N>->front());
	}
	else
	{
		cout << "Solution not found" << endl;
	}

	cin.get();

	delete bSearch<N>;
}
