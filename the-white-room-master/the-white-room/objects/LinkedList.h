#include <stdlib.h>
#include <iostream>

using namespace std;

template<class T>
class Node {
    public:
        Node *prev, *next;
        T *data;

        Node(T *d, Node *p, Node *n);
        Node();
        ~Node();
};

template<class T>
class CullList {
    public:
    Node<T> *head;

    void add(Node<T> *data);
    Node<T>* remove();
    bool isEmpty();
    Node<T>* getHead();
    CullList();
    ~CullList();
};

template<class T>
class LinkedList {
public:
    Node<T> *head, *next;
    CullList<T> cull;

    void add(T *data);
    T* remove();
    bool hasNext();
    bool isEmpty();
    T* getNext();
    T* getCurrent();
    T* getFirst();
    void reset();
    Node<T>* getCullHead();
    LinkedList();
    ~LinkedList();
};

template<class T>
Node<T>::Node(T *d, Node *p, Node *n) {
    data = d;
    prev = p;
    next = n;
}

template<class T>
Node<T>::Node() {
    data = NULL;
    prev = this;
    next = this;
}

template<class T>
Node<T>::~Node() {
    delete data;
}

template <class T>
void CullList<T>::add(Node<T> *data) {
    data->next = head;
    data->prev = head->prev;
    head->prev->next = data;
    head->prev = data;
}
    
template<class T>
Node<T>* CullList<T>::remove() {
    Node<T> *data;

    if (head->next == head) {
        return NULL;
    }
    
    data = head->next;

    head->next->next->prev = head;
    head->next = head->next->next;
    data->next = NULL;
    data->prev = NULL;

    return data;
}
template<class T>
bool CullList<T>::isEmpty() {
    return head->next == head;
}

template<class T>
Node<T>* CullList<T>::getHead() {
    return head;
}

template<class T>
CullList<T>::CullList() {
    head = new Node<T>();
}

template<class T>
CullList<T>::~CullList() {
    Node<T> *temp1, *temp2;
    temp1 = head->next;
    temp2 = temp1->next;

    while (temp1 != head) {
        delete temp1;
        temp1 = temp2;
        temp2 = temp2->next;
    }

    delete head;
}


template<class T>
void LinkedList<T>::add(T *data) {
    Node<T> *add;
    if (cull.isEmpty()) {
        add = new Node<T>(data, head->prev, head);
    }
    else {
        add = cull.remove();
        add->data = data;
        add->prev = head->prev;
        add->next = head;
    }

    head->prev->next = add;
    head->prev = add;
}

template<class T>
T* LinkedList<T>::remove() {
    T *data;
    Node<T> *temp;
    if (next == head && next->next == head) {
        return NULL;
    }
    else if (next == head) {
        next = head->next;
        return NULL;
    }
    data = next->data;
    temp = next;
    next = next->next;
    next->prev = temp->prev;
    temp->prev->next = next;

    cull.add(temp);

    return data;
}

template<class T>
bool LinkedList<T>::hasNext() {
    return next != head;
}

template<class T>
bool LinkedList<T>::isEmpty() {
    return head->next == head;
}

template<class T>
T* LinkedList<T>::getNext() {
    T* data;

    if (next == head) {
        next = head->next;
        return NULL;
    }

    data = next->data;
    next = next->next;
    return data;
}

template<class T>
T* LinkedList<T>::getFirst() {
    if (head->next == head) {
        return NULL;
    }

    return (head->next->data);
}

template<class T>
T* LinkedList<T>::getCurrent() {
    if (next == head) {
        return NULL;
    }

    return next->data;
}

template<class T>
void LinkedList<T>::reset() {
    next = head->next;
}

template<class T>
Node<T>* LinkedList<T>::getCullHead() {
    return cull.getHead();
}

template<class T>
LinkedList<T>::LinkedList() {
    head = new Node<T>();
    next = head;
}

template<class T>
LinkedList<T>::~LinkedList() {
    Node<T> *temp1, *temp2;
    temp1 = head->next;
    temp2 = temp1->next;

    while (temp1 != head) {
        delete temp1;
        temp1 = temp2;
        temp2 = temp2->next;
    }

    delete head;
}
