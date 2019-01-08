#ifndef LINKEDLIST_HPP
#define	LINKEDLIST_HPP

#include <iostream>
#include "Node.hpp"

using namespace std;

/*....DO NOT EDIT BELOW....*/
template <class T>
class LinkedList {
private:
    Node<T>* head; 
    int length;
public:
    LinkedList();
    LinkedList(const LinkedList<T>& ll);
    LinkedList<T>& operator=(const LinkedList<T>& ll);
    ~LinkedList();


    Node<T>* getHead() const;
    Node<T>* first() const;
    Node<T>* findPrev(const T& data) const;
    Node<T>* findNode(const T& data) const;
    void insertNode(Node<T>* prev, const T& data); 
    void deleteNode(Node<T>* prevNode);
    void clear();
    size_t getLength() const;
    void print() const;
    void swap(int index1, int index2);
};


template <class T>
LinkedList<T>::~LinkedList(){
}

    
template <class T>
void LinkedList<T>::print() const {
    const Node<T>* node = first();
    while (node) {
        std::cout << node->getData();
        node = node->getNext();
    }
    cout << std::endl;
}

/*....DO NOT EDIT ABOVE....*/

/* TO-DO: method implementations below */

template <class T>
LinkedList<T>::LinkedList(){

	head = new Node<T>;
	length = 0;

}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& ll){
	/*
	head = ll;
	length = ll.length;
*/
	head = new Node<T>;
	*this = ll; 
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& ll){
	this->head = ll.head;
	this->length = 4;
	return *this;
}

template <class T>
Node<T>* LinkedList<T>::getHead() const{
	return head;
}

template <class T>
Node<T>* LinkedList<T>::first() const{
	return head->getNext();
}

template <class T>
Node<T>* LinkedList<T>::findPrev(const T& data) const{
	Node<T> *first_node = head->getNext();
    while(first_node){
        
        if(first_node->getNext()==NULL){
            return NULL;
        }
        if(first_node->getNext()->getData() == data){
            return first_node;
        }

        first_node = first_node->getNext();
    }
        return NULL;
}

template <class T>
Node<T>* LinkedList<T>::findNode(const T& data) const{
	
	Node<T> *first_node = head->getNext();
	while(first_node){
		
		if(first_node->getData() == data){
		
			return first_node;
		}
		first_node = first_node->getNext();
	}
	return NULL;
}

template <class T>
void LinkedList<T>::insertNode(Node<T>* prev, const T& data){
	Node<T> *temp_n = NULL;
    Node<T> *temp_add = new Node<T>;
    
    *(temp_add->getDataPtr()) = data;
    temp_add->setNext(NULL);

    if(prev){
        temp_n = prev->getNext();
        prev->setNext(temp_add);
        temp_add->setNext(temp_n);
    }
}

template <class T>
void LinkedList<T>::deleteNode(Node<T>* prevNode){
	Node<T> *temp1 = prevNode->getNext();
    Node<T> *temp2 = NULL;
    
    if(temp1){
        temp2 = temp1;
        prevNode->setNext(temp1->getNext());
        delete temp2;
    }
}

template <class T>
void LinkedList<T>::clear(){
	/* I think the problem stems from the destructors. Look it up
	Node<T> *head_node = head;
	Node<T> *first_node = head->getNext();
	
	while(first_node){
		head_node = first_node;
		first_node = first_node->getNext();
		delete head_node->getDataPtr();
		delete head_node;
	}
	*/
}

template <class T>
size_t LinkedList<T>::getLength() const{
	return length;
}

template <class T>
void LinkedList<T>::swap(int index1, int index2){
	int count = 0;
	int count2 = 0;
	Node<T> *head_node = getHead();
	Node<T> *head_nnext = NULL;

	Node<T> *head_node2 = getHead();
	Node<T> *head_nnext2 = NULL;
	
	Node<T> *temp = NULL;
	
	while(head_node){
		if(count == index1){
			while(head_node2){
				if(count2 == index2){/* Now we have both address values that preceeds the numbers that we want to swap */
					if(count-count2!=1 && count-count2!=-1){
					head_nnext = head_node->getNext();			
					head_nnext2 = head_node2->getNext();	
					
					head_node->setNext(head_nnext2);
					temp = head_nnext2->getNext();
					head_nnext2->setNext(head_nnext->getNext());
					
					head_node2->setNext(head_nnext);
					head_nnext->setNext(temp);
					
					return;
					}
					else{
					head_nnext2 = head_node2->getNext()->getNext();
					
					head_node->setNext(head_node2->getNext());
					head_node2->getNext()->setNext(head_node2);
					head_node2->setNext(head_nnext2);	
					}
				}
				count2++;
				head_node2 = head_node2->getNext();
			}
		}
		count++;
		head_node = head_node->getNext();
	}
}

/* end of your implementations*/
#endif	

