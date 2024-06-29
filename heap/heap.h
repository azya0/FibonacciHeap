#pragma ones

#include <unordered_map>

#include "node/node.h"

template <typename KeyType>
class FibbonachiHeap {
private:
    int size;
    Node<KeyType>* minNode;

    void insert(Node<KeyType>* newNode) {
        if (size == 0)
            minNode = newNode;
        else {
            auto oldRight = minNode->getRightPtr();
            minNode->setRight(newNode);
            newNode->setLeft(minNode);
            newNode->setRight(oldRight);
            oldRight->setLeft(newNode);
        }

        if (newNode->getKey() < minNode->getKey())
            minNode = newNode;

        size++;
    }

    bool exist(std::unordered_map<int, Node<KeyType>*> map, int key) {
        auto data = map.find(key);
        return (data != map.end()) && (data->second != nullptr);
    }
public:
    FibbonachiHeap() : size(0) {};

    void printTop() {
        auto element = minNode;
        
        while (element->getRightPtr() != minNode) {
            std::cout << element->getKey() << ' ';
            element = element->getRightPtr();
        }
        
        std::cout << element->getKey();
    }

    KeyType getMin() {
        return minNode->getKey();
    }

    void insert(KeyType value) {
        auto newNode = new Node<KeyType>(value);

        insert(newNode);
    }

    void static join(FibbonachiHeap<KeyType>* first, FibbonachiHeap<KeyType>* second) {
        Node<KeyType> *oldLeft = first->minNode->getLeftPtr(), *oldRight = second->minNode->getRightPtr();

        second->minNode->setRight(first->minNode);
        first->minNode->setLeft(second->minNode);

        oldLeft->setRight(oldRight);
        oldRight->setLeft(oldLeft);

        auto smallestMinNode = (first->minNode->getKey() < second->minNode->getKey() ? first->minNode : second->minNode);
        first->minNode = smallestMinNode;
        second->minNode = smallestMinNode;

        first->size += second->size;
        second->size += first->size;
    }

    void compress() {
        std::unordered_map<int, Node<KeyType>*> depthUsed;
        depthUsed[minNode->getSize()] = minNode;
        Node<KeyType> *current = minNode->getRightPtr();

        while (depthUsed[current->getSize()] != current) {
            if (!exist(depthUsed, current->getSize())) {
                depthUsed[current->getSize()] = current;
                current = current->getRightPtr();
            } else {
                Node<KeyType>* another = depthUsed[current->getSize()];
                Node<KeyType> *addTo, *adding;

                if (another->getKey() < current->getKey()) {
                    addTo = another;
                    adding = current;
                } else {
                    addTo = current;
                    adding = another;
                }

                depthUsed.erase(another->getSize());
                addTo->addChild(adding);

                if (!exist(depthUsed, addTo->getSize())) {
                    depthUsed[addTo->getSize()] = addTo;
                    current = addTo->getRightPtr();
                } else
                    current = addTo;
                
                if (addTo->getKey() < minNode->getKey())
                    minNode = addTo;
            }
        }
    }

    KeyType popMin() {
        Node<KeyType>* prevMin = minNode;
        
        FibbonachiHeap<KeyType>* childs = new FibbonachiHeap<KeyType>();
        Node<KeyType>* current = minNode->getChild();

        do {
            current->setParent(nullptr);
            current = current->getRightPtr();
        } while (current->getParent() != nullptr);

        childs->insert(current);
        int oldSize = size;

        FibbonachiHeap::join(this, childs);

        minNode->getLeftPtr()->setRight(minNode->getRightPtr());
        minNode->getRightPtr()->setLeft(minNode->getLeftPtr());

        minNode = current;
        compress();
        size = oldSize - 1;

        return prevMin->getKey();
    }

    int getSize() {
        return size;
    }
};
