#pragma once
#include <vector>
#include <iostream>
using namespace std;

template <typename T>
class LinkedList {
public:
	struct Node {
		Node* next = nullptr;
		Node* prev = nullptr;
		T data;
	};
	// Behaviors
	void PrintForward() const;
	void PrintReverse() const;
	void PrintForwardRecursive(const Node* node) const;
	void PrintReverseRecursive(const Node* node) const;

	// Accessors
	unsigned int NodeCount() const;
	void FindAll(vector<Node*>& outData, const T& value) const;
	const Node* Find(const T& data) const;
	Node* Find(const T& data);
	const Node* GetNode(unsigned int index) const;
	Node* GetNode(unsigned int index);
	Node* Head();
	const Node* Head() const;
	Node* Tail();
	const Node* Tail() const;

	// Insertion
	void AddHead(const T& data);
	void AddTail(const T& data);
	void AddNodesHead(const T* data, unsigned int count);
	void AddNodesTail(const T* data, unsigned int count);
	void InsertAfter(Node* node, const T& data);
	void InsertBefore(Node* node, const T& data);
	void InsertAt(const T& data, unsigned int index);

	// Removal
	bool RemoveHead();
	bool RemoveTail();
	unsigned int Remove(const T& data);
	bool RemoveAt(unsigned int index);
	void Clear();

	// Operators
	const T& operator[](unsigned int index) const;
	T& operator[](unsigned int index);
	bool operator==(const LinkedList<T>& rhs) const;
	LinkedList<T>& operator=(const LinkedList<T>& rhs);

	// Constructors and Destructor
	LinkedList();
	LinkedList(const LinkedList<T>& list);
	~LinkedList();

private:
	Node* head = nullptr;
	Node* tail = nullptr;
	unsigned int nodeCount;
};

template <typename T>
void LinkedList<T>::AddHead(const T& data) {
	Node* newNode = new Node;
	newNode->data = data;
	
	// If there are no nodes in the list...
	if (head == nullptr) {
		head = newNode;
		tail = newNode;
	}
	// If there is at least one node in the list...
	else {
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}
	nodeCount++;    // Number of nodes increases by one after adding a new head.
}

template <typename T>
void LinkedList<T>::AddTail(const T& data) {
	Node* newNode = new Node;
	newNode->data = data;

	/* Originally checked if nodeCount was equal to 0 but ran into issues w/ copy constructor
	 * trying to access the next pointer after a null pointer.
	 */
	if (head == nullptr) {
		head = newNode;
		tail = newNode;
	}
	else {
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
	}
	nodeCount++;
}

template <typename T>
void LinkedList<T>::AddNodesHead(const T* data, unsigned int count) {
	// Must insert array elements in reverse order at the front to maintain original order.
	// Ran into an issue with unsigned int indexes, switched to int instead.
	for (int i = (int)count - 1; i >= 0; i--) {
		AddHead(data[i]);
	}
}

template <typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count) {
	// Inserting at the end in original order will maintain the original order.
	for (unsigned int i = 0; i < count; i++) {
		AddTail(data[i]);
	}
}

template <typename T>
unsigned int LinkedList<T>::NodeCount() const {
	return nodeCount;
}

template <typename T>
void LinkedList<T>::PrintForward() const {
	Node* currentNode = head;

	// Traverse the list one by one and print out the data in each node.
	while (currentNode != nullptr) {
		cout << currentNode->data << endl;
		currentNode = currentNode->next;
	}
}

template <typename T>
void LinkedList<T>::PrintReverse() const {
	Node* currentNode = tail;

	// Traverse the list in reverse order and print out the data.
	while (currentNode != nullptr) {
		cout << currentNode->data << endl;
		currentNode = currentNode->prev;
	}
}

template <typename T>
LinkedList<T>::LinkedList() {
	nodeCount = 0;
	head = nullptr;
	tail = nullptr;
}

template <typename T>
LinkedList<T>::~LinkedList() {
	Node* currentNode = head;
	Node* temp = currentNode;

	// Traverse the list and delete each node one by one.
	while (currentNode != nullptr) {
		temp = currentNode->next;
		delete currentNode;
		currentNode = temp;
	}
	/* Error with copy assignment operator, fixed by reassigning head
	 * and tail pointers to null after the list was deleted.
	 */ 
	head = nullptr;
	tail = nullptr;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head() {
	return head;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const {
	return head;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail() {
	return tail;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const {
	return tail;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) {
	Node* currentNode = head;
	unsigned int traverse = 0;

	if (index >= nodeCount || index < 0) {
		throw out_of_range("");
	}
	// Iterate through list until the node at the index is found.
	while (traverse != index) {
		traverse++;
		currentNode = currentNode->next;
	}
	return currentNode;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const {
	Node* currentNode = head;
	unsigned int traverse = 0;

	if (index >= nodeCount || index < 0) {
		throw out_of_range("");
	}
	while (traverse != index) {
		traverse++;
		currentNode = currentNode->next;
	}
	return currentNode;
}

template <typename T>
const T& LinkedList<T>::operator[](unsigned int index) const {
	Node* currentNode = head;
	unsigned int traverse = 0;
	
	if (index >= nodeCount || index < 0) {
		throw out_of_range("");
	}
	while (traverse != index) {
		traverse++;
		currentNode = currentNode->next;
	}
	return currentNode->data;
}

template <typename T>
T& LinkedList<T>::operator[](unsigned int index) {
	Node* currentNode = head;
	unsigned int traverse = 0;

	if (index >= nodeCount || index < 0) {
		throw out_of_range("");
	}
	while (traverse != index) {
		traverse++;
		currentNode = currentNode->next;
	}
	return currentNode->data;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) {
	Node* currentNode = head;
	for (unsigned int i = 0; i < nodeCount; i++) {
		if (currentNode->data == data) {
			return currentNode;
		}
		currentNode = currentNode->next;
	}
	return nullptr;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const {
	Node* currentNode = head;
	for (unsigned int i = 0; i < nodeCount; i++) {
		if (currentNode->data == data) {
			return currentNode;
		}
		currentNode = currentNode->next;
	}
	return nullptr;
}

template <typename T>
void LinkedList<T>::FindAll(vector<Node*>& outData, const T& value) const {
	Node* currentNode = head;
	for (unsigned int i = 0; i < nodeCount; i++) {
		if (currentNode->data == value) {
			outData.push_back(currentNode);
		}
		currentNode = currentNode->next;
	}
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
	// Delete old list.
	this->~LinkedList();
	Node* copy = list.head;
	while (copy != nullptr) {
		// Allocate space for new list and copy data.
		AddTail(copy->data);
		copy = copy->next;
	}
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs) {
	this->~LinkedList();
	Node* copy = rhs.head;
	while (copy != nullptr) {
		AddTail(copy->data);
		copy = copy->next;
	}
	return *this;
}

template <typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& data) {
	Node* newNode = new Node;
	newNode->data = data;

	// Set newNode's next and prev pointers.
	newNode->next = node->next;
	newNode->prev = node;

	// Account for other affected next and prev pointers.
	node->next->prev = newNode;
	node->next = newNode;

	// Increment node count.
	nodeCount++;
}

template <typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data) {
	Node* newNode = new Node;
	newNode->data = data;

	// Set newNode's next and prev pointers.
	newNode->next = node;
	newNode->prev = node->prev;

	// Account for the other affected next and prev pointers.
	node->prev->next = newNode;
	node->prev = newNode;

	// Increment node count.
	nodeCount++;
}

template <typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index) {
	if (index > nodeCount || index < 0) {
		throw out_of_range("");
	}
	// First index is the head.
	if (index == 0) {
		AddHead(data);
	}
	// Last index is the tail.
	else if (index == nodeCount) {
		AddTail(data);
	}
	// Else insert after the previous index.
	else {
		InsertAfter(GetNode(index - 1), data);
	}
}

template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const {
	// Create two nodes, one for lhs and one for rhs.
	Node* lhs = head;
	Node* rhsNode = rhs.head;
	
	// Iterate through list...
	while (rhsNode->next != nullptr) {
		// Check if node counts are equal.
		if (nodeCount != rhs.nodeCount) {
			return false;
		}
		// Check if the data the pointer is pointing to is equal.
		if (lhs->data != rhsNode->data) {
			return false;
		}
		lhs = lhs->next;
		rhsNode = rhsNode->next;
	}
	return true;
}

template <typename T>
bool LinkedList<T>::RemoveHead() {
	// If there are no nodes, you can't remove anything.
	if (nodeCount == 0) {
		return false;
	}
	// If there's only one node to remove, set head and tail to nullptr afterwards.
	else if (nodeCount == 1) {
		delete head;
		head = nullptr;
		tail = nullptr;
		nodeCount--;
		return true;
	}
	// Otherwise...
	else {
		// Create a new head pointer.
		Node* newHead = head->next;
		newHead->prev = nullptr;
		
		// Delete old head.
		delete head;

		// Set head pointer to the new created head.
		head = newHead;

		// Decrement node count.
		nodeCount--;
		return true;
	}
}

template <typename T>
bool LinkedList<T>::RemoveTail() {
	if (nodeCount == 0) {
		return false;
	}
	else if (nodeCount == 1) {
		delete tail;
		head = nullptr;
		tail = nullptr;
		nodeCount--;
		return true;
	}
	else {
		Node* newTail = tail->prev;
		newTail->next = nullptr;
		delete tail;
		tail = newTail;
		nodeCount--;
		return true;
	}
}

template <typename T>
unsigned int LinkedList<T>::Remove(const T& data) {
	Node* currentNode = head;
	unsigned int count = 0;      // Count number of removed nodes.

	while (currentNode->next != nullptr) {
		// If data at current node matches passed in data...
		if (currentNode->data == data) {
			// Store the current node into a temporary new node.
			Node* remove = currentNode;

			// Set the next and previous pointers accordingly.
			currentNode->prev->next = currentNode->next;
			currentNode->next->prev = currentNode->prev;

			// Iterate to next element in the list.
			currentNode = currentNode->next;

			// Delete the current node.
			delete remove;

			// Decrement and increment counts accordingly.
			nodeCount--;
			count++;
		}
		/* Else loop added due to an error with the current node iterating
		 * twice through the list when the if switch was activated.
		 */ 
		else {
			currentNode = currentNode->next;
		}
	}
	return count;
}

template <typename T>
bool LinkedList<T>::RemoveAt(unsigned int index) {
	// If there are no nodes to remove or the index is invalid, return false.
	if (nodeCount == 0 || index > nodeCount || index < 0) {
		return false;
	}
	// First index is the head.
	else if (index == 0) {
		return RemoveHead();
	}
	// Last index is the tail.
	else if (index == nodeCount) {
		return RemoveTail();
	}
	else {
		Node* currentNode = head;
		for (unsigned int i = 0; i < nodeCount; i++) {
			if (i == index) {
				Node* remove = currentNode;
				currentNode->next->prev = currentNode->prev;
				currentNode->prev->next = currentNode->next;
				currentNode = currentNode->next;
				delete remove;
				nodeCount--;
				break;
			}
			else {
				currentNode = currentNode->next;
			}
		}
		return true;
	}
}

template <typename T>
void LinkedList<T>::Clear() {
	Node* currentNode = head;
	Node* temp = currentNode;
	// Traverse the list and delete each node one by one.
	while (currentNode != nullptr) {
		temp = currentNode->next;
		delete currentNode;
		currentNode = temp;
	}
	head = nullptr;
	tail = nullptr;
	nodeCount = 0;
}

template <typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const {
	// Base case.
	if (node->next == nullptr) {
		cout << node->data << endl;
	}
	else {
		cout << node->data << endl;
		PrintForwardRecursive(node->next);
	}
}

template <typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) const {
	// Base case.
	if (node->prev == nullptr) {
		cout << node->data << endl;
	}
	else {
		cout << node->data << endl;
		PrintReverseRecursive(node->prev);
	}
}