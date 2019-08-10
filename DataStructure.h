// DataStructure.h : This file contains the data structure to be used by the main program.
//

#include <iostream>
#include <new>                          // Define classe bad_alloc
#include <stdexcept>                    // Define classes de excesões
#include <cstdlib>						// Define geração de números randômicos

using namespace std;

class delEmptyList : public runtime_error       // Define classe de exception para erro de lista vazia
{
public:
	delEmptyList() : runtime_error("Attempted to delete data from empty list") {}      // Define função de excessão
};


class noNodeToDel : public runtime_error       // Define classe de exception para erro de lista vazia
{
public:
	noNodeToDel() : runtime_error("Attempted to delete node not in the list") {}      // Define função de excessão
};


class getEmptyListNode : public runtime_error       // Define classe de exception para erro de lista vazia
{
public:
	getEmptyListNode() : runtime_error("Attempted to get node from empty list") {}      // Define função de excessão
};




template <typename N>
class node									// Definição da classe nó
{
private:
	N positions[3][3];						// Posição de cada peça
	int emptyPoint;							// Posição do ponto "0"
	int lastEmptyPoint;						// Posição do último ponto "0"
	int heuristic;							// Heurística do nó
	int cost;								// Custo do nó
	int fN;									// Função F(n)
	bool opened;							// Verificação se já foi aberto os filhos
	node<N>* parentNode;					// Nó pai
	node<N>* childNodes[4];					// Nós filhos
	node<N>* nextNode;						// Ponteiro para o próximo nó
	node<N>* lastNode;						// Ponteiro para o nó anterior
public:
	node(node<N>*, N[3][3], int, int, int);	// Método construtor do nó
	~node();								// Método destrutor do nó
	void changeAllPos(N[3][3]);				// Método para definir os dados do nó
	int hCalcManhattan(N[3][3]);			// Método para cálculo de heurística Manhattan do nó
	int hCalcMisplaced(N[3][3]);			// Método para cálculo de heurística Fora do Lugar do nó
	void changeNext(node<N>*);				// Método para redefinir próximo nó
	void changeLast(node<N>*);				// Método para redefinir nó anterior
	int getEmptyPoint(void);				// Método para retornar a posição vazia atual 
	int getLastEmptyPoint(void);			// Método para retornar a posição vazia do nó pai
	int getCost(void);						// Método para retornar o custo do nó
	int getfN(void);						// Método para retornar o F(n) do nó
	N getPiece(int, int);					// Método para rectornar um valor do nó
	int getHeuristic();						// Método para retornar a heurística do nó
	bool isOpened(void);					// Método para retornar se o nó já gerou filhos
	node<N>* getParent(void);				// Método para retornar o nó pai
	void changeParent(node<N>*);			// Método para definir o nó pai
	void addChild(node<N>*);				// Método para adicionar um nó filho
	node<N>* getChild(void);				// Método para retornar um nó filho
	node<N>* getBestChild(void);			// Método para retornar nó filho com melhor F(n)
	void delChild(node<N>*);				// Método para deletar um nó filho específico
	node<N>* getNext(void);					// Método para receber ponteiro para o próximo nó
	node<N>* getLast(void);					// Método para receber ponteiro para o nó anterior
};

// Método construtor do nó
template <typename N>
node<N>::node(node<N>* constParent, N constPos[3][3], int constEmpty, int constLastEmpty, int constCost)                 // Construtor do nó
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

// Método destrutor do nó
template <typename N>
node<N>::~node()                           // Destrutor do nó
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

// Método para definir os dados do nó
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

// Método para cálculo de heurística Manhattan do nó
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

// Método para cálculo de heurística Fora do Lugar do nó
template <typename N>
int node<N>::hCalcMisplaced(N status[3][3])				// Método para cálculo de heurística Fora do Lugar do nó
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

// Método para redefinir próximo nó
template <typename N>
void node<N>::changeNext(node<N>* next)         // Método para redefinir próximo nó
{
	nextNode = next;                    // Redireciona o ponteiro
}

// Método para redefinir nó anterior
template <typename N>
void node<N>::changeLast(node<N>* last)         // Método para redefinir nó anterior
{
	lastNode = last;                    // Redireciona o ponteiro
}

// Método para retornar a posição vazia atual 
template <typename N>
int node<N>::getEmptyPoint(void)
{
	return emptyPoint;
}

// Método para retornar a posição vazia do nó pai
template <typename N>
int node<N>::getLastEmptyPoint(void)
{
	return lastEmptyPoint;
}

// Método para retornar o custo do nó
template <typename N>
int node<N>::getCost(void)
{
	return cost;
}

// Método para retornar o F(n) do nó
template <typename N>
int node<N>::getfN(void)
{
	return fN;
}

// Método para retornar um valor do nó
template <typename N>
N node<N>::getPiece(int row, int col)                     // Método para receber valor do nó
{
	return positions[row][col];                        // Retorna o valor do nó
}

// Método para retornar a heurística do nó
template <typename N>
int node<N>::getHeuristic()
{
	return heuristic;
}

// Método para retornar se o nó já gerou filhos
template <typename N>
bool node<N>::isOpened(void)
{
	return opened;
}

// Método para retornar o nó pai
template <typename N>
node<N>* node<N>::getParent(void)
{
	return parentNode;
}

// Método para definir o nó pai
template <typename N>
void node<N>::changeParent(node<N>* newP)
{
	parentNode = newP;
}

// Método para adicionar um nó filho
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

// Método para retornar um nó filho
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

// Método para retornar nó filho com melhor F(n)
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

// Método para deletar um nó filho específico
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

// Método para receber ponteiro para o próximo nó
template <typename N>
node<N>* node<N>::getNext()                   // Método para receber ponteiro para o próximo nó
{
	return nextNode;                    // Retorna o ponteiro para o próximo nó
}

// Método para receber ponteiro para o nó anterior
template <typename N>
node<N>* node<N>::getLast()                   // Método para receber ponteiro para o nó anterior
{
	return lastNode;                    // Retorna o ponteiro para o nó anterior
}




template <typename N>
class linkedList											// Definição da classe lista Ligada
{
private:
	node<N>* startNode;										// Ponteiro para o nó inicial
	node<N>* endNode;										// Ponteiro para o nó final
	int listSize;											// Tamanho da lista
public:
	linkedList();											// Método construtor da lista
	~linkedList();											// Método destrutor da lista
	bool isEmpty(void);										// Método que verifica que a lista está vazia
	int getSize();											// Método que retorna o tamanho da lista
	node<N>* getStart(void);								// Método que retorna o ponteiro para o nó inicial
	node<N>* getEnd(void);									// Método que retorna o ponteiro para o nó final
	node<N>* getBestfN(void);								// Método que retorna melhor F(n)
	void findNodeToDel(node<N>*);							// Método que remove um nó identificado da lista
	void addStart(node<N>*, N[3][3],int, int, int);         // Método que adiciona um novo nó no início da lista
	void addEnd(node<N>*, N[3][3], int, int, int);          // Método que adiciona um novo nó no final da lista
	void removeStart(void);									// Método que remove o nó no início da lista
	void removeEnd(void);									// Método que remove o nó no final da lista
	void delStart(void);									// Método que deleta o nó no início da lista
	void delEnd(void);										// Método que deleta o nó no final da lista
};

// Método construtor da lista
template <typename N>
linkedList<N>::linkedList()                
{
	listSize = 0;                       // Define tamanho inicial zero
	startNode = nullptr;                // Define nó inicial nulo
	endNode = nullptr;                  // Define nó final nulo
}

// Método destrutor da lista
template <typename N>
linkedList<N>::~linkedList()              
{
	while (listSize > 0)
	{
		try                                 // Inicia tratamento de excessão
		{
			delStart();              // Chama o método para deletar o nó no final da pilha
		}
		catch (delEmptyList& delError)       // Caso haja erro
		{
			cerr << delError.what() << endl;    // Reportar o erro
		}
	}

	cout << "Linked list deleted" << endl << endl; // Avisa que a pilha foi deletada
}

// Método que verifica que a lista está vazia
template <typename N>
bool linkedList<N>::isEmpty()              
{
	if (listSize == 0)                   // Se a lista está vazia
	{
		return true;                    // Retorna verdadeiro
	}
	else                                // Caso não seja vazia
	{
		return false;                   // Retorna falso
	}
}

// Método que retorna o tamanho da lista
template <typename N>
int linkedList<N>::getSize()               
{
	return listSize;                    // Retorna o tamanho da lista
}

// Método que retorna o ponteiro para o nó inicial
template <typename N>
node<N>* linkedList<N>::getStart(void)        
{
	
	if (isEmpty())
	{
		throw getEmptyListNode();
	}
	else
	{
		return startNode;                   // Retorna o ponteiro para o nó inicial
	}
	
}

// Método que retorna o ponteiro para o nó final
template <typename N>
node<N>* linkedList<N>::getEnd(void)          
{
	
	if (isEmpty())
	{
		throw getEmptyListNode();
	}
	else
	{
		return endNode;                     // Retorna o ponteiro para o nó final
	}
}

// Método que retorna melhor F(n)
template <class N>
node<N>* linkedList<N>::getBestfN(void)
{
	if (isEmpty())
	{
		throw getEmptyListNode();           // Inicia tratamento de excessão
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

// Método que remove um nó identificado da lista
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
	throw noNodeToDel(); // Inicia tratamento de excessão
	return;
}

// Método que adiciona um novo nó no início da lista
template <typename N>
void linkedList<N>::addStart(node<N>* newParent, N newStat[3][3], int newEmpty, int newLastEmpty, int newCost)  
{
	node<N>* newPointer = 0;                   // Define um ponteiro para apontar para o novo nó

	newPointer = new node<N>(newParent, newStat, newEmpty, newLastEmpty, newCost); // Tenta gerar novo nó

	if (isEmpty())                       // Se a lista estiver vazia
	{
		startNode = newPointer;         // Nó inicial recebe o novo nó
		endNode = newPointer;           // Nó final recebe o novo nó
		listSize++;        // Atualiza o tamanho da lista
	}
	else                                // Se não estiver vazia
	{
		newPointer->changeNext(startNode);    // Aponta o novo nó para o primeiro nó da lista
		startNode->changeLast(newPointer);    // Aponta o primeiro nó da lista para o nó novo
		startNode = newPointer;             // Aponta o novo nó como nó inicial
		listSize++;            // Atualiza o tamanho da lista
	}
}

// Método que adiciona um novo nó no final da lista
template <typename N>
void linkedList<N>::addEnd(node<N>* newParent, N newStat[3][3], int newEmpty, int newLastEmpty, int newCost)    
{
	node<N>* newPointer = 0;                   // Define um ponteiro para apontar para o novo nó

	newPointer = new node<N>(newParent, newStat, newEmpty, newLastEmpty, newCost); // Tenta gerar novo nó

	if (isEmpty())                       // Se a lista estiver vazia
	{
		startNode = newPointer;         // Nó inicial recebe o novo nó
		endNode = newPointer;           // Nó final recebe o novo nó
		listSize++;        // Atualiza o tamanho da lista
	}
	else                                // Se não estiver vazia
	{
		newPointer->changeLast(endNode);  // Aponta o novo nó para o último nó da lista
		endNode->changeNext(newPointer);  // Aponta o último nó da lista para o nó novo
		endNode = newPointer;           // Aponta o novo nó como nó final
		listSize++;        // Atualiza o tamanho da lista
	}
}

// Método que deleta o nó no início da lista
template <typename N>
void linkedList<N>::removeStart(void)        
{

	if (isEmpty())                       // Se a lista estiver vazia
	{
		throw delEmptyList();           // Inicia tratamento de excessão
	}
	else                                // Se não estiver vazia
	{
		node<N>* toDelete;
		toDelete = startNode;               // Registra nó a ser deletado
		startNode = getStart()->getNext();  // Nó inicial aponta para o próximo nó
		//startNode->changeLast(nullptr);
		listSize--;							// Atualiza tamanho da lista
		toDelete->changeNext(nullptr);
		toDelete->changeLast(nullptr);      // Deleta nó
	}

	return;
}

// Método que deleta o nó no final da lista
template <typename N>
void linkedList<N>::removeEnd(void)           
{

	if (isEmpty())                       // Se a lista estiver vazia
	{
		throw delEmptyList();           // Inicia tratamento de excessão
	}
	else                                // Se não estiver vazia
	{
		node<N>* toDelete;
		toDelete = endNode;           // Registra nó a ser deletado
		endNode = getEnd()->getLast();  // Nó final aponta para o nó anterior
		//endNode->changeNext(nullptr);
		listSize--;        // Atualiza tamanho da lista
		toDelete->changeNext(nullptr);
		toDelete->changeLast(nullptr);      // Deleta nó
	}

	return;
}

// Método que deleta o nó no início da lista
template <typename N>
void linkedList<N>::delStart(void)         
{

	if (isEmpty())                       // Se a lista estiver vazia
	{
		throw delEmptyList();           // Inicia tratamento de excessão
	}
	else                                // Se não estiver vazia
	{
		node<N>* toDelete;
		toDelete = startNode;               // Registra nó a ser deletado
		startNode = getStart()->getNext();  // Nó inicial aponta para o próximo nó
		listSize--;							// Atualiza tamanho da lista
		toDelete->changeNext(nullptr);
		toDelete->changeLast(nullptr);      
		delete toDelete;					// Deleta nó
	}

	return;
}

// Método que deleta o nó no final da lista
template <typename N>
void linkedList<N>::delEnd(void)           
{

	if (isEmpty())                       // Se a lista estiver vazia
	{
		throw delEmptyList();           // Inicia tratamento de excessão
	}
	else                                // Se não estiver vazia
	{
		node<N>* toDelete;
		toDelete = endNode;					// Registra nó a ser deletado
		endNode = getEnd()->getLast();		// Nó final aponta para o nó anterior
		listSize--;							// Atualiza tamanho da lista
		toDelete->changeNext(nullptr);
		toDelete->changeLast(nullptr);		//
		delete toDelete;					// Deleta nó
	}

	return;
}




template <typename N>
class linkedStack : public linkedList<N>			// Define a classe Pilha
{
private:
	linkedList<N> intStack;							// Define a lista para armazenar os dados
public:
	linkedStack();									// Método construtor da pilha
	~linkedStack();									// Método destrutor da pilha
	int size();										// Método que retorna o tamanho da pilha
	void push(node<N>*, N[3][3], int, int, int);    // Método para emplihar um dado
	void pop(void);									// Método para desempilhar um dado
	node<N>* top(void);								// Método para resgatar o valor no topo da pilha
};

// Método construtor da pilha
template <typename N>
linkedStack<N>::linkedStack()              
{

}

// Método destrutor da pilha
template <typename N>
linkedStack<N>::~linkedStack()             
{

	//delete intStack;

	while (intStack.getSize() > 0)
	{

		try                                 // Inicia tratamento de excessão
		{
			intStack.delEnd();              // Chama o método para deletar o nó no final da pilha
		}
		catch (delEmptyList& delError)       // Caso haja erro
		{
			cerr << delError.what() << endl;    // Reportar o erro
		}
	}

	cout << "Stack deleted" << endl << endl; // Avisa que a pilha foi deletada
}

// Método que retorna o tamanho da pilha
template <typename N>
int linkedStack<N>::size()
{
	return intStack.getSize();
}

// Método para emplihar um dado
template <typename N>
void linkedStack<N>::push(node<N>* newP, N newS[3][3], int newE, int newLE, int newC)     
{
	intStack.addEnd(newP, newS, newE, newLE, newC);           // Chama o método da lista para adicionar novo nó
}

// Método para desempilhar um dado
template <typename N>
void linkedStack<N>::pop()                  
{
	try                                 // Inicia tratamento de excessão
	{
		intStack.removeEnd();              // Chama o método para deletar o nó no final da pilha
	}
	catch (delEmptyList& delError)       // Caso haja erro
	{
		cerr << delError.what() << endl;    // Reportar o erro
	}

	return;                 // Retorna o dado do nó deletado
}

// Método para resgatar o valor no topo da pilha
template <typename N>
node<N>* linkedStack<N>::top()                  
{

	try
	{
		return intStack.getEnd();    // Retorna o valor do nó no topo da pilha
	}
	catch (getEmptyListNode& getError)
	{
		cerr << getError.what() << endl;
	}
}




template <typename N>
class linkedQueue : public linkedList<N>			// Define a classe fila
{
private:
	linkedList<N> intQueue;							// Define a lista para armazenar os dados
public:
	linkedQueue();									// Método construtor da fila
	~linkedQueue();									// Método destrutor da fila
	void enqueue(node<N>*, N[3][3], int, int, int); // Método para adicionar dado na fila
	void dequeue(void);								// Método para remover dado da fila
	node<N>* front(void);							// Método que retorna o valor do início da fila
};

// Método construtor da fila
template <typename N>
linkedQueue<N>::linkedQueue()					
{

}

// Método destrutor da fila
template <typename N>
linkedQueue<N>::~linkedQueue()					
{
	
	//delete intQueue;

	while (intQueue.getSize() > 0)
	{

		try										// Inicia tratamento de excessão
		{
			intQueue.delStart();				// Chama o método para deletar o nó no início da fila
		}
		catch (delEmptyList& delError)			// Caso haja erro
		{
			cerr << delError.what() << endl;    // Reportar o erro
		}
	}

	cout << "Queue deleted" << endl << endl;    // Avisa que a fila foi deletada
}

// Método para adicionar dado na fila
template <typename N>
void linkedQueue<N>::enqueue(node<N>* newP, N newS[3][3], int newE, int newLE, int newC)  
{
	intQueue.addEnd(newP, newS, newE, newLE, newC);           // Chama o método da lista para adicionar novo nó
}

// Método para remover dado da fila
template <typename N>
void linkedQueue<N>::dequeue(void)					
{

	try												// Inicia tratamento de excessão
	{
		intQueue.removeStart();						// Chama o método para deletar o nó no início da fila
	}
	catch (delEmptyList& delError)					// Caso haja erro
	{
		cerr << delError.what() << endl;			// Reportar o erro
	}

	return;											// Retorna o dado do nó deletado
}

// Método que retorna o valor do início da fila
template <typename N>
node<N>* linkedQueue<N>::front()					
{
	try
	{
		return intQueue.getStart();					// Retorna o valor do nó no início da fila
	}
	catch (getEmptyListNode& getError)
	{
		cerr << getError.what() << endl;			// Tratamento de excessão
	}
}