// DataStructure.h : This file contains the data structure to be used by the main program.
//

#include <iostream>
#include <new>                          // Define classe bad_alloc
#include <stdexcept>                    // Define classes de exces�es
#include <cstdlib>						// Define gera��o de n�meros rand�micos

using namespace std;

class delEmptyList : public runtime_error       // Define classe de exception para erro de lista vazia
{
public:
	delEmptyList() : runtime_error("Attempted to delete data from empty list") {}      // Define fun��o de excess�o
};


class noNodeToDel : public runtime_error       // Define classe de exception para erro de lista vazia
{
public:
	noNodeToDel() : runtime_error("Attempted to delete node not in the list") {}      // Define fun��o de excess�o
};


class getEmptyListNode : public runtime_error       // Define classe de exception para erro de lista vazia
{
public:
	getEmptyListNode() : runtime_error("Attempted to get node from empty list") {}      // Define fun��o de excess�o
};




template <typename N>
class node									// Defini��o da classe n�
{
private:
	N positions[3][3];						// Posi��o de cada pe�a
	int emptyPoint;							// Posi��o do ponto "0"
	int lastEmptyPoint;						// Posi��o do �ltimo ponto "0"
	int heuristic;							// Heur�stica do n�
	int cost;								// Custo do n�
	int fN;									// Fun��o F(n)
	bool opened;							// Verifica��o se j� foi aberto os filhos
	node<N>* parentNode;					// N� pai
	node<N>* childNodes[4];					// N�s filhos
	node<N>* nextNode;						// Ponteiro para o pr�ximo n�
	node<N>* lastNode;						// Ponteiro para o n� anterior
public:
	node(node<N>*, N[3][3], int, int, int);	// M�todo construtor do n�
	~node();								// M�todo destrutor do n�
	void changeAllPos(N[3][3]);				// M�todo para definir os dados do n�
	int hCalcManhattan(N[3][3]);			// M�todo para c�lculo de heur�stica Manhattan do n�
	int hCalcMisplaced(N[3][3]);			// M�todo para c�lculo de heur�stica Fora do Lugar do n�
	void changeNext(node<N>*);				// M�todo para redefinir pr�ximo n�
	void changeLast(node<N>*);				// M�todo para redefinir n� anterior
	int getEmptyPoint(void);				// M�todo para retornar a posi��o vazia atual 
	int getLastEmptyPoint(void);			// M�todo para retornar a posi��o vazia do n� pai
	int getCost(void);						// M�todo para retornar o custo do n�
	int getfN(void);						// M�todo para retornar o F(n) do n�
	N getPiece(int, int);					// M�todo para receber valor do n�
	int getHeuristic();						// M�todo para retornar a heur�stica do n�
	bool isOpened(void);					// M�todo para retornar se o n� j� gerou filhos
	node<N>* getParent(void);				// M�todo para retornar o n� pai
	void changeParent(node<N>*);			// M�todo para definir o n� pai
	void addChild(node<N>*);				// M�todo para adicionar um n� filho
	node<N>* getChild(void);				// M�todo para retornar um n� filho
	node<N>* getBestChild(void);			// M�todo para retornar n� filho com melhor F(n)
	void delChild(node<N>*);				// M�todo para deletar um n� filho espec�fico
	node<N>* getNext(void);					// M�todo para receber ponteiro para o pr�ximo n�
	node<N>* getLast(void);					// M�todo para receber ponteiro para o n� anterior
};

template <typename N>
node<N>::node(node<N>* constParent, N constPos[3][3], int constEmpty, int constLastEmpty, int constCost)                 // Construtor do n�
{	
	changeAllPos(constPos);
	emptyPoint = constEmpty;
	lastEmptyPoint = constLastEmpty;
	heuristic = hCalcManhattan(constPos);
	cost = constCost;
	fN = cost + heuristic;
	opened = false;
	parentNode = constParent;
	if (parentNode != nullptr) { parentNode->addChild(this); }
	for (int i = 0; i < 4; i++)
	{
		childNodes[i] = nullptr;
	}
	nextNode = nullptr;
	lastNode = nullptr;
}

template <typename N>
node<N>::~node()                           // Destrutor do n�
{
	if (parentNode != nullptr)
	{
		parentNode->delChild(this);
	}
	for (int i = 0; i < 4; i++)
	{
		if (childNodes[i] != nullptr)
		{
			childNodes[i]->changeParent(nullptr);
		}
	}
}

template <typename N>
void node<N>::changeAllPos(N newPos[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			positions[i][j] = newPos[i][j];
		}
	}
}

template <typename N>
int node<N>::hCalcManhattan(N status[3][3])
{
	int heuristic = 0;
	int hI = 0;
	int hJ = 0;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			hI = status[i][j] / 3;
			hJ = status[i][j] % 3;

			heuristic += abs(hI - i) + abs(hJ - j);
		}
	}
	return heuristic;
}

template <typename N>
int node<N>::hCalcMisplaced(N status[3][3])
{
	int heuristic = 9;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (status[i][j] == (i + (3 * j)))
			{
				heuristic--;
			}
			
		}
	}
	return heuristic;
}

template <typename N>
void node<N>::changeNext(node<N>* next)         // M�todo para redefinir pr�ximo n�
{
	nextNode = next;                    // Redireciona o ponteiro
}

template <typename N>
void node<N>::changeLast(node<N>* last)         // M�todo para redefinir n� anterior
{
	lastNode = last;                    // Redireciona o ponteiro
}

template <typename N>
int node<N>::getEmptyPoint(void)
{
	return emptyPoint;
}

template <typename N>
int node<N>::getLastEmptyPoint(void)
{
	return lastEmptyPoint;
}

template <typename N>
int node<N>::getCost(void)
{
	return cost;
}

template <typename N>
int node<N>::getfN(void)
{
	return fN;
}

template <typename N>
N node<N>::getPiece(int row, int col)                     // M�todo para receber valor do n�
{
	return positions[row][col];                        // Retorna o valor do n�
}

template <typename N>
int node<N>::getHeuristic()
{
	return heuristic;
}

template <typename N>
bool node<N>::isOpened(void)
{
	return opened;
}

template <typename N>
node<N>* node<N>::getParent(void)
{
	return parentNode;
}

template <typename N>
void node<N>::changeParent(node<N>* newP)
{
	parentNode = newP;
}

template <typename N>
void node<N>::addChild(node<N>* newChild)
{
	int i = 0;

	while (i < 4)
	{
		if (childNodes[i] == nullptr)
		{
			childNodes[i] = newChild;
			opened = true;
			return;
		}
		i++;
	}

	cout << "Error trying to add child" << endl;


}

template <typename N>
node<N>* node<N>::getChild(void)
{
	int i = 0;
	node<N>* childFound = nullptr;

	while (childFound == nullptr || i >= 4)
	{
		childFound = childNodes[i];
		i++;
	}

	return childFound;
}

template <typename N>
node<N>* node<N>::getBestChild(void)
{
	node<N>* bestChild = childNodes[0];

	for (int i = 1; i < 4; i++)
	{
		if (childNodes[i] != nullptr && bestChild->getfN() > childNodes[i]->getfN())
		{
			bestChild = childNodes[i];
		}
	}
	return bestChild;
}

template <typename N>
void node<N>::delChild(node<N>* child)
{
	for (int i = 0; i < 4; i++)
	{
		if (child == childNodes[i])
		{
			childNodes[i] = nullptr;
			return;
		}
	}
}

template <typename N>
node<N>* node<N>::getNext()                   // M�todo para receber ponteiro para o pr�ximo n�
{
	return nextNode;                    // Retorna o ponteiro para o pr�ximo n�
}

template <typename N>
node<N>* node<N>::getLast()                   // M�todo para receber ponteiro para o n� anterior
{
	return lastNode;                    // Retorna o ponteiro para o n� anterior
}




template <typename N>
class linkedList											// Defini��o da classe lista Ligada
{
private:
	node<N>* startNode;										// Ponteiro para o n� inicial
	node<N>* endNode;										// Ponteiro para o n� final
	int listSize;											// Tamanho da lista
public:
	linkedList();											// M�todo construtor da lista
	~linkedList();											// M�todo destrutor da lista
	bool isEmpty(void);										// M�todo que verifica que a lista est� vazia
	int getSize();											// M�todo que retorna o tamanho da lista
	node<N>* getStart(void);								// M�todo que retorna o ponteiro para o n� inicial
	node<N>* getEnd(void);									// M�todo que retorna o ponteiro para o n� final
	node<N>* getBestfN(void);								// M�todo que retorna melhor F(n)
	void findNodeToDel(node<N>*);							// M�todo que remove um n� identificado da lista
	void addStart(node<N>*, N[3][3],int, int, int);         // M�todo que adiciona um novo n� no in�cio da lista
	void addEnd(node<N>*, N[3][3], int, int, int);          // M�todo que adiciona um novo n� no final da lista
	void removeStart(void);									// M�todo que remove o n� no in�cio da lista
	void removeEnd(void);									// M�todo que remove o n� no final da lista
	void delStart(void);									// M�todo que deleta o n� no in�cio da lista
	void delEnd(void);										// M�todo que deleta o n� no final da lista
};

template <typename N>
linkedList<N>::linkedList()                // M�todo construtor da lista
{
	listSize = 0;                       // Define tamanho inicial zero
	startNode = nullptr;                // Define n� inicial nulo
	endNode = nullptr;                  // Define n� final nulo
}

template <typename N>
linkedList<N>::~linkedList()               // M�todo destrutor da lista
{
	while (listSize > 0)
	{
		try                                 // Inicia tratamento de excess�o
		{
			delStart();              // Chama o m�todo para deletar o n� no final da pilha
		}
		catch (delEmptyList& delError)       // Caso haja erro
		{
			cerr << delError.what() << endl;    // Reportar o erro
		}
	}

	cout << "Linked list deleted" << endl << endl; // Avisa que a pilha foi deletada
}

template <typename N>
bool linkedList<N>::isEmpty()              // M�todo que verifica que a lista est� vazia
{
	if (listSize == 0)                   // Se a lista est� vazia
	{
		return true;                    // Retorna verdadeiro
	}
	else                                // Caso n�o seja vazia
	{
		return false;                   // Retorna falso
	}
}

template <typename N>
int linkedList<N>::getSize()               // M�todo que retorna o tamanho da lista
{
	return listSize;                    // Retorna o tamanho da lista
}

template <typename N>
node<N>* linkedList<N>::getStart(void)        // M�todo que retorna o ponteiro para o n� inicial
{
	
	if (isEmpty())
	{
		throw getEmptyListNode();
	}
	else
	{
		return startNode;                   // Retorna o ponteiro para o n� inicial
	}
	
}

template <typename N>
node<N>* linkedList<N>::getEnd(void)          // M�todo que retorna o ponteiro para o n� final
{
	
	if (isEmpty())
	{
		throw getEmptyListNode();
	}
	else
	{
		return endNode;                     // Retorna o ponteiro para o n� final
	}
}

template <class N>
node<N>* linkedList<N>::getBestfN(void)
{
	if (isEmpty())
	{
		throw getEmptyListNode();           // Inicia tratamento de excess�o
	}
	else
	{
		node<N>* lessfN = startNode;
		node<N>* testingfN = startNode;

		while (testingfN != nullptr)
		{
			if (testingfN->getfN() < lessfN->getfN())
			{
				//cout << "Got Best F(n): " << testingfN->getfN() << endl;
				lessfN = testingfN;
			}
			testingfN = testingfN->getNext();
		}
		//cout << "Best F(n): " << lessfN->getHeuristic() << endl;
		return lessfN;
	}

}

template <typename N>
void linkedList<N>::findNodeToDel(node<N>* toDel)
{

	node<N>* currentTest = startNode;

	if (!isEmpty())
	{
		while (currentTest != endNode)
		{
			if (currentTest == toDel)
			{
				if (toDel != getStart())
				{
					toDel->getLast()->changeNext(toDel->getNext());
				}
				else
				{
					toDel->getNext()->changeLast(nullptr);
					startNode = toDel->getNext();
				}
				if (toDel != getEnd())
				{
					toDel->getNext()->changeLast(toDel->getLast());
				}
				else
				{
					toDel->getLast()->changeNext(nullptr);
					endNode = toDel->getLast();
				}
				listSize--;
				return;
			}
			currentTest = currentTest->getNext();
		}

	}
	throw noNodeToDel(); // Inicia tratamento de excess�o
	return;
}

template <typename N>
void linkedList<N>::addStart(node<N>* newParent, N newStat[3][3], int newEmpty, int newLastEmpty, int newCost)  // M�todo que adiciona um novo n� no in�cio da lista
{
	node<N>* newPointer = 0;                   // Define um ponteiro para apontar para o novo n�

	newPointer = new node<N>(newParent, newStat, newEmpty, newLastEmpty, newCost); // Tenta gerar novo n�

	if (isEmpty())                       // Se a lista estiver vazia
	{
		startNode = newPointer;         // N� inicial recebe o novo n�
		endNode = newPointer;           // N� final recebe o novo n�
		listSize++;        // Atualiza o tamanho da lista
	}
	else                                // Se n�o estiver vazia
	{
		newPointer->changeNext(startNode);    // Aponta o novo n� para o primeiro n� da lista
		startNode->changeLast(newPointer);    // Aponta o primeiro n� da lista para o n� novo
		startNode = newPointer;             // Aponta o novo n� como n� inicial
		listSize++;            // Atualiza o tamanho da lista
	}
}

template <typename N>
void linkedList<N>::addEnd(node<N>* newParent, N newStat[3][3], int newEmpty, int newLastEmpty, int newCost)    // M�todo que adiciona um novo n� no final da lista
{
	node<N>* newPointer = 0;                   // Define um ponteiro para apontar para o novo n�

	newPointer = new node<N>(newParent, newStat, newEmpty, newLastEmpty, newCost); // Tenta gerar novo n�

	if (isEmpty())                       // Se a lista estiver vazia
	{
		startNode = newPointer;         // N� inicial recebe o novo n�
		endNode = newPointer;           // N� final recebe o novo n�
		listSize++;        // Atualiza o tamanho da lista
	}
	else                                // Se n�o estiver vazia
	{
		newPointer->changeLast(endNode);  // Aponta o novo n� para o �ltimo n� da lista
		endNode->changeNext(newPointer);  // Aponta o �ltimo n� da lista para o n� novo
		endNode = newPointer;           // Aponta o novo n� como n� final
		listSize++;        // Atualiza o tamanho da lista
	}
}

template <typename N>
void linkedList<N>::removeStart(void)         // M�todo que deleta o n� no in�cio da lista
{

	if (isEmpty())                       // Se a lista estiver vazia
	{
		throw delEmptyList();           // Inicia tratamento de excess�o
	}
	else                                // Se n�o estiver vazia
	{
		node<N>* toDelete;
		toDelete = startNode;               // Registra n� a ser deletado
		startNode = getStart()->getNext();  // N� inicial aponta para o pr�ximo n�
		//startNode->changeLast(nullptr);
		listSize--;							// Atualiza tamanho da lista
		toDelete->changeNext(nullptr);
		toDelete->changeLast(nullptr);      // Deleta n�
	}

	return;
}

template <typename N>
void linkedList<N>::removeEnd(void)           // M�todo que deleta o n� no final da lista
{

	if (isEmpty())                       // Se a lista estiver vazia
	{
		throw delEmptyList();           // Inicia tratamento de excess�o
	}
	else                                // Se n�o estiver vazia
	{
		node<N>* toDelete;
		toDelete = endNode;           // Registra n� a ser deletado
		endNode = getEnd()->getLast();  // N� final aponta para o n� anterior
		//endNode->changeNext(nullptr);
		listSize--;        // Atualiza tamanho da lista
		toDelete->changeNext(nullptr);
		toDelete->changeLast(nullptr);      // Deleta n�
	}

	return;
}

template <typename N>
void linkedList<N>::delStart(void)         // M�todo que deleta o n� no in�cio da lista
{

	if (isEmpty())                       // Se a lista estiver vazia
	{
		throw delEmptyList();           // Inicia tratamento de excess�o
	}
	else                                // Se n�o estiver vazia
	{
		node<N>* toDelete;
		toDelete = startNode;               // Registra n� a ser deletado
		startNode = getStart()->getNext();  // N� inicial aponta para o pr�ximo n�
		listSize--;							// Atualiza tamanho da lista
		toDelete->changeNext(nullptr);
		toDelete->changeLast(nullptr);      
		delete toDelete;					// Deleta n�
	}

	return;
}

template <typename N>
void linkedList<N>::delEnd(void)           // M�todo que deleta o n� no final da lista
{

	if (isEmpty())                       // Se a lista estiver vazia
	{
		throw delEmptyList();           // Inicia tratamento de excess�o
	}
	else                                // Se n�o estiver vazia
	{
		node<N>* toDelete;
		toDelete = endNode;					// Registra n� a ser deletado
		endNode = getEnd()->getLast();		// N� final aponta para o n� anterior
		listSize--;							// Atualiza tamanho da lista
		toDelete->changeNext(nullptr);
		toDelete->changeLast(nullptr);		//
		delete toDelete;					// Deleta n�
	}

	return;
}




template <typename N>
class linkedStack : public linkedList<N>   // Define a classe Pilha
{
private:
	linkedList<N> intStack;                // Define a lista para armazenar os dados
public:
	linkedStack();                      // M�todo construtor da pilha
	~linkedStack();                     // M�todo destrutor da pilha
	int size();
	void push(node<N>*, N[3][3], int, int, int);                // M�todo para emplihar um dado
	void pop(void);                     // M�todo para desempilhar um dado
	node<N>* top(void);                    // M�todo para resgatar o valor no topo da pilha
};

template <typename N>
linkedStack<N>::linkedStack()              // M�todo construtor da pilha
{

}

template <typename N>
linkedStack<N>::~linkedStack()             // M�todo destrutor da pilha
{

	//delete intStack;

	while (intStack.getSize() > 0)
	{

		try                                 // Inicia tratamento de excess�o
		{
			intStack.delEnd();              // Chama o m�todo para deletar o n� no final da pilha
		}
		catch (delEmptyList& delError)       // Caso haja erro
		{
			cerr << delError.what() << endl;    // Reportar o erro
		}
	}

	cout << "Stack deleted" << endl << endl; // Avisa que a pilha foi deletada
}

template <typename N>
int linkedStack<N>::size()
{
	return intStack.getSize();
}

template <typename N>
void linkedStack<N>::push(node<N>* newP, N newS[3][3], int newE, int newLE, int newC)     // M�todo para emplihar um dado
{
	intStack.addEnd(newP, newS, newE, newLE, newC);           // Chama o m�todo da lista para adicionar novo n�
}

template <typename N>
void linkedStack<N>::pop()                  // M�todo para desempilhar um dado
{
	try                                 // Inicia tratamento de excess�o
	{
		intStack.removeEnd();              // Chama o m�todo para deletar o n� no final da pilha
	}
	catch (delEmptyList& delError)       // Caso haja erro
	{
		cerr << delError.what() << endl;    // Reportar o erro
	}

	return;                 // Retorna o dado do n� deletado
}

template <typename N>
node<N>* linkedStack<N>::top()                  // M�todo para resgatar o valor no topo da pilha
{

	try
	{
		return intStack.getEnd();    // Retorna o valor do n� no topo da pilha
	}
	catch (getEmptyListNode& getError)
	{
		cerr << getError.what() << endl;
	}
}




template <typename N>
class linkedQueue : public linkedList<N>   // Define a classe fila
{
private:
	linkedList<N> intQueue;                // Define a lista para armazenar os dados
public:
	linkedQueue();                      // M�todo construtor da fila
	~linkedQueue();                     // M�todo destrutor da fila
	void enqueue(node<N>*, N[3][3], int, int, int);                  // M�todo para adicionar dado na fila
	void dequeue(void);                  // M�todo para remover dado da fila
	node<N>* front(void);                   // M�todo que retorna o valor do in�cio da fila
};

template <typename N>
linkedQueue<N>::linkedQueue()              // M�todo construtor da fila
{

}

template <typename N>
linkedQueue<N>::~linkedQueue()             // M�todo destrutor da fila
{
	
	//delete intQueue;

	while (intQueue.getSize() > 0)
	{

		try                                 // Inicia tratamento de excess�o
		{
			intQueue.delStart();            // Chama o m�todo para deletar o n� no in�cio da fila
		}
		catch (delEmptyList& delError)       // Caso haja erro
		{
			cerr << delError.what() << endl;    // Reportar o erro
		}
	}

	cout << "Queue deleted" << endl << endl;    // Avisa que a fila foi deletada
}

template <typename N>
void linkedQueue<N>::enqueue(node<N>* newP, N newS[3][3], int newE, int newLE, int newC)  // M�todo para adicionar dado na fila
{
	intQueue.addEnd(newP, newS, newE, newLE, newC);           // Chama o m�todo da lista para adicionar novo n�
}

template <typename N>
void linkedQueue<N>::dequeue(void)          // M�todo para remover dado da fila
{

	try                                 // Inicia tratamento de excess�o
	{
		intQueue.removeStart();            // Chama o m�todo para deletar o n� no in�cio da fila
	}
	catch (delEmptyList& delError)       // Caso haja erro
	{
		cerr << delError.what() << endl;    // Reportar o erro
	}

	return;                 // Retorna o dado do n� deletado
}

template <typename N>
node<N>* linkedQueue<N>::front()               // M�todo que retorna o valor do in�cio da fila
{
	try
	{
		return intQueue.getStart();  // Retorna o valor do n� no in�cio da fila
	}
	catch (getEmptyListNode& getError)
	{
		cerr << getError.what() << endl;
	}
}