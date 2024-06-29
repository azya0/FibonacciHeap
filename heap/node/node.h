#pragma ones

template <typename KeyType>
class Node {
private:
    KeyType key;

    Node<KeyType>* parent;
    Node<KeyType>* child;

    Node<KeyType>* left;
    Node<KeyType>* right;

    int size;
public:
    Node(KeyType key) {
        this->key = key;

        parent = (child = nullptr);
        left = (right = this);
        size = 0;
    };

    KeyType getKey() const {
        return key;
    }

    int getSize() const {
        return size;
    }

    void setSize(int newSize) {
        size = newSize;
    }

    const Node& getLeft() const {
        return *left;
    }

    Node<KeyType>* getLeftPtr() const {
        return left;
    }

    void setLeft(Node<KeyType>* node) {
        left = node;
    }
    
    const Node& getRight() const {
        return *left;
    }

    Node<KeyType>* getRightPtr() const {
        return right;
    }

    void setRight(Node<KeyType>* node) {
        right = node;
    }

    Node<KeyType>* getChild() const {
        return child;
    }

    void setChild(Node<KeyType>* newChild) {
        child = newChild;
    }

    Node<KeyType>* getParent() const {
        return parent;
    }

    void setParent(Node<KeyType>* newParent) {
        parent = newParent;
    }

    void addChild(Node<KeyType>* element) {
        element->getRightPtr()->setLeft(element->getLeftPtr());
        element->getLeftPtr()->setRight(element->getRightPtr());
        element->setLeft(element);
        element->setRight(element);

        if (child == nullptr) {
            child = element;
        } else {
            auto oldRight = child->getRightPtr();
            child->setRight(element);
            element->setLeft(child);
            element->setRight(oldRight);
            oldRight->setLeft(element);
        }

        size = std::max(size, element->getSize() + 1);
        element->setParent(this);
    }
};
