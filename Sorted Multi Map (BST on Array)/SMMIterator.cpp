#include "SMMIterator.h"
#include "SortedMultiMap.h"

/*
* Theta(h), where h -> the height of the tree
*/
SMMIterator::SMMIterator(const SortedMultiMap& d) : map{d}
{
    currNode = map.head;
    currVal = 0;

    stackHead = nullptr;
    stackElems = 0;

    if(map.isEmpty()) {
        currNode = -1;
        return;
    }

    while (currNode != -1)
    {
        addToStack(currNode);
        currNode = map.left[currNode];
    }
    if (stackElems != 0)
    {
        currNode = stackTop();
        currVal = 0;
    }
}


/*
* Theta(h), where h -> the height of the tree
*/
void SMMIterator::first()
{
    currNode = map.head;
    currVal = 0;

    while(stackHead != nullptr) {
        auto oldNode = stackHead;
        stackHead = stackHead->next;
        delete oldNode;
    }

    if (map.isEmpty()) {
        currNode = -1;
        return;
    }

    while (currNode != -1)
    {
        addToStack(currNode);
        currNode = map.left[currNode];
    }
    if (stackElems != 0) {
        currNode = stackTop();
        currVal = 0;
    } else {
        currNode = -1;
    }

}


/*
* BC: Theta(1)
* WC: Theta(h) -> where h is the height of the tree
* AC: Theta(h)
* Total: O(h)
*/
void SMMIterator::next()
{
    if (!valid())
        throw exception();

    if(currVal++ < map.data[currNode].size - 1) {
        return;
    }

    int node = stackTop();
    popFromStack();

    if(map.right[node] != -1) {
        node = map.right[node];
        while(node != -1) {
            addToStack(node);
            node = map.left[node];
        }
    }

    if(stackElems != 0) {
        currNode = stackTop();
    }
    else {
        currNode = -1;
    }
    currVal = 0;
}


/*
* Theta(1)
*/
bool SMMIterator::valid() const
{
    return currNode != -1;
}


/*
* Theta(1)
*/
TElem SMMIterator::getCurrent() const
{
    if (!valid())
        throw exception();

    TElem elem;
    elem.first = map.data[currNode].k;
    elem.second = map.data[currNode].elems[currVal];
    return elem;
}

void SMMIterator::addToStack(int e) {

    if(stackHead == nullptr) {
        Node* newNode = new Node;
        newNode->el = e;
        newNode->next = nullptr;
        stackHead = newNode;
        stackElems = 1;
        return;
    }

    Node* newNode = new Node;
    newNode->el = e;
    newNode->next = stackHead;
    stackHead = newNode;
    stackElems++;
}

void SMMIterator::popFromStack() {
    auto old = stackHead;
    stackHead = stackHead->next;
    stackElems--;

    delete old;
}

int SMMIterator::stackTop() {
    return stackHead->el;
}