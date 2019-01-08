#ifndef TWOPHASEBST_H
#define TWOPHASEBST_H

#include <iostream>
#include <string>
#include <stack>
#include <list>
// do not add any other library.
// modify parts as directed by assignment text and comments here.

template <class T>
class TwoPhaseBST {
private: //do not change
    struct SecondaryNode {
        std::string key;
        T data;
        SecondaryNode *left;
        SecondaryNode *right;

        SecondaryNode(const std::string &k, const T &d, SecondaryNode *l, SecondaryNode *r);
    };

    struct PrimaryNode {
        std::string key;
        PrimaryNode *left;
        PrimaryNode *right;
        SecondaryNode *rootSecondaryNode;

        PrimaryNode(const std::string &k, PrimaryNode *l, PrimaryNode *r, SecondaryNode *rsn);
    };

public: // do not change.
    TwoPhaseBST();
    ~TwoPhaseBST();
	void print1(TwoPhaseBST<int> & t1);

    TwoPhaseBST &insert(const std::string &primaryKey, const std::string &secondaryKey, const T &data);
    TwoPhaseBST &remove(const std::string &primaryKey, const std::string &secondaryKey);
    TwoPhaseBST &print(const std::string &primaryKey = "", const std::string &secondaryKey = "");
    T *find(const std::string &primaryKey, const std::string &secondaryKey);

private: // you may add your own utility member functions here.
    void destructNode(PrimaryNode * &root);
    void destructNode(SecondaryNode * &root);

public: // do not change.
    PrimaryNode *root; //designated root.
	
    // do not provide an implementation. TwoPhaseBST's are not copiable.
    TwoPhaseBST(const TwoPhaseBST &);
    const TwoPhaseBST &operator=(const TwoPhaseBST &);
};

template <class T>
TwoPhaseBST<T>::SecondaryNode::SecondaryNode(const std::string &k, const T &d, SecondaryNode *l, SecondaryNode *r)
        : key(k), data(d), left(l), right(r) {}

template <class T>
TwoPhaseBST<T>::PrimaryNode::PrimaryNode(const std::string &k, PrimaryNode *l, PrimaryNode *r, SecondaryNode *rsn)
        : key(k), left(l), right(r), rootSecondaryNode(rsn) {}

template <class T>
TwoPhaseBST<T>::TwoPhaseBST() : root(NULL) {}

template <class T>
TwoPhaseBST<T>::~TwoPhaseBST() {
    destructNode(root);
}

template <class T>
TwoPhaseBST<T> &
TwoPhaseBST<T>::insert(const std::string &primaryKey, const std::string &secondaryKey, const T &data) {
 	if(!root){
    	root = new PrimaryNode(primaryKey,NULL,NULL,new SecondaryNode(secondaryKey,data,NULL,NULL));
    }
	else{
		PrimaryNode *temp = root;
		while(temp){
			if(primaryKey > temp->key){
				if(temp->right!=NULL){
					temp = temp->right;
				}
				else{
					temp->right = new PrimaryNode(primaryKey,NULL,NULL,new SecondaryNode(secondaryKey,data,NULL,NULL));
					break;		
				} 
				
			}
			
			//std::cout << " asd " << std::endl;
			
			if(primaryKey < temp->key){
				if(temp->left!=NULL){
					temp = temp->left;
				}
				else{
					temp->left = new PrimaryNode(primaryKey,NULL,NULL,new SecondaryNode(secondaryKey,data,NULL,NULL));
					break;		
				} 
				
			}
			if(primaryKey == temp->key){
				SecondaryNode *temp_sec = temp->rootSecondaryNode;
			
				SecondaryNode *i_value = new SecondaryNode(secondaryKey,data,NULL,NULL); 
			
				while(1){
			
					if(!temp_sec){
						temp->rootSecondaryNode = i_value;
						break;
					}
					
					if(i_value->key < temp_sec->key && temp_sec->left!=NULL){
						temp_sec = temp_sec->left;
					}
					
					if(i_value->key > temp_sec->key && temp_sec->right!=NULL){
						temp_sec = temp_sec->right;
					}
					
					if(i_value->key < temp_sec->key && temp_sec->left == NULL){
						temp_sec->left = i_value;
						break;
					}
					
					if(i_value->key > temp_sec->key && temp_sec->right == NULL){
						temp_sec->right = i_value;
						break;
					}
				}
				break;
			}
			
		}
					 
	}			
			//SecondaryNode *temp_root = new SecondaryNode("","",NULL,NULL);
			//std::cout << temp_root->left->right->data << std::endl; TESTING			
	return *this;		//temp = temp->right;		
	}
	/* IMPLEMENT THIS */


template <class T>
TwoPhaseBST<T> &
TwoPhaseBST<T>::remove(const std::string &primaryKey, const std::string &secondaryKey) {
	PrimaryNode *temp = root;
	PrimaryNode *del1;
	
	SecondaryNode *swapnode;
	SecondaryNode *middle;
	SecondaryNode *del2;
	SecondaryNode *temp_sec;
	
	while(temp){
		if(temp->key==primaryKey){
			break;
		}
		else if(primaryKey > temp->key){
			temp = temp->right;
		}
		else if(primaryKey < temp->key){
			temp = temp->left;
		}
	}
	temp_sec = temp->rootSecondaryNode;
	if(!temp_sec){
		return *this;
	}
	if(temp_sec->left==NULL && temp_sec->right==NULL && temp_sec->key == secondaryKey){ // if empty
		del2 = temp->rootSecondaryNode;		    
        temp->rootSecondaryNode = NULL;
        delete del2;
		return *this;
	}
	else if(temp_sec->left==NULL && temp_sec->right!=NULL && temp_sec->key == secondaryKey){ // only right children
	
		del2 = temp_sec;
		temp->rootSecondaryNode = temp_sec->right;
	//	delete del2;
		return *this;
	}
	else if(temp_sec->left!=NULL && temp_sec->right==NULL && temp_sec->key == secondaryKey){ // only left children
		del2 = temp_sec;
		
		temp->rootSecondaryNode = temp_sec->left;
	//	delete del2;
		return *this;
	}
	else if(temp_sec->left!=NULL && temp_sec->right!=NULL && temp_sec->key == secondaryKey){ // left and right children
		
		swapnode = temp_sec->right; //right sub tree.
		while(swapnode->left){ // get leftmost element at temp_sec
			swapnode = temp_sec->left;
		}
		
		middle = swapnode;// first first get the data from to-be-swapped-Node
		
		this->remove(primaryKey,swapnode->key); // first delete the to-be-swapped-Node
		temp_sec->key = middle->key;//then swap the values.
		temp_sec->data = middle->data;	
		return *this;
	}
	//if not the root node of secondarynode look for other nodes
	else{
		while(temp_sec){
			if(temp_sec->left && temp_sec->left->key == secondaryKey){ // we found it,the value is at the left node
				
				if(temp_sec->left->left ==NULL && temp_sec->left->right ==NULL){ //left node has no children
					//delete temp_sec->left; error.
					temp_sec->left = NULL;
					return *this;
				}
				else if(temp_sec->left->left !=NULL && temp_sec->left->right ==NULL){ //left node has left children
					del2 = temp_sec->left;
					temp_sec->left = temp_sec->left->left;
					//delete del2;
					return *this;	
				}
				else if(temp_sec->left->left ==NULL && temp_sec->left->right !=NULL){ //left node has right children
					del2 = temp_sec->left;
					temp_sec->left = temp_sec->left->right;
					//delete del2;
					return *this;
					
				}
				else if(temp_sec->left->left !=NULL && temp_sec->left->right !=NULL){ //left node has two children
					swapnode = temp_sec->left->right; //right sub tree.
					
					while(swapnode->left){ // get leftmost element at temp_sec
						swapnode = swapnode->left;
					}
					
					middle = swapnode;// first first get the data from to-be-swapped-Node
					
					this->remove(primaryKey,swapnode->key); // first delete the to-be-swapped-Node
					temp_sec->left->key = middle->key;//then swap the values.
					temp_sec->left->data = middle->data;	
					return *this;											
				}
			}
			else if(temp_sec->right && temp_sec->right->key == secondaryKey){ // we found it,value is at the right node
				
				if(temp_sec->right->left ==NULL && temp_sec->right->right ==NULL){ //right node has no children
					//delete temp_sec->right; error
					temp_sec->right = NULL;
					return *this;
				}
				else if(temp_sec->right->left !=NULL && temp_sec->right->right ==NULL){ //right node has left children
					del2 = temp_sec->right;
					temp_sec->right = temp_sec->right->left;
					//delete del2;
					return *this;
				}
				else if(temp_sec->right->left ==NULL && temp_sec->right->right !=NULL){ //right node has right children
					del2 = temp_sec->right;
					temp_sec->right = temp_sec->right->right;
					//delete del2;
					return *this;
				}
				else if(temp_sec->left->left !=NULL && temp_sec->left->right !=NULL){ //right node has two children
					swapnode = temp_sec->right->right; //right sub tree.
					
					while(swapnode->left){ // get leftmost element at temp_sec
						swapnode = swapnode->left;
					}
					
					middle = swapnode;// first first get the data from to-be-swapped-Node
					
					this->remove(primaryKey,swapnode->key); // first delete the to-be-swapped-Node
					temp_sec->right->key = middle->key;//then swap the values.
					temp_sec->right->data = middle->data;	
					return *this;											
				}
				
			}
			else if(secondaryKey > temp_sec->key){
				temp_sec = temp_sec->right;
			}
			else if(secondaryKey < temp_sec->key){
				
				temp_sec = temp_sec->left;
			}
		}
	}
}

template <class T>
TwoPhaseBST<T> &TwoPhaseBST<T>::print(const std::string &primaryKey, const std::string &secondaryKey) {
    std::stack<PrimaryNode*> s;
    PrimaryNode *current = root;
	while(current!=NULL || !s.empty()){
    	while(current!=NULL){
		s.push(current);
		current = current->left;
		}
		current = s.top();
		std::cout << current->key << std::endl;
		s.pop();
		
		current = current->right;
	}
	
	return *this;
}

template <class T>
T *TwoPhaseBST<T>::find(const std::string &primaryKey, const std::string &secondaryKey) {
	if(!root){
		return NULL;
	}
	else{
		PrimaryNode *temp = root;
		while(temp){
			if(temp->key == primaryKey){
				SecondaryNode *temp_sec = temp->rootSecondaryNode;
				while(temp_sec){
					if(temp_sec != NULL && temp_sec->key == secondaryKey){
						return &(temp_sec->data);
					}
					if(temp_sec != NULL && secondaryKey < temp_sec->key){
						temp_sec = temp_sec->left;
					}
				
					if(temp_sec != NULL && secondaryKey > temp_sec->key){
						temp_sec = temp_sec->right;
					}		
					if(temp_sec==NULL){
						temp=NULL;
					}
				}
			}
			if(temp==NULL){
				break;
			}
			if(primaryKey < temp->key){
				temp = temp->left;
			}
			if(primaryKey > temp->key){
				temp = temp->right;
			}
		}
		return NULL;
	}
	
    /* IMPLEMENT THIS */
}

template <class T>
void TwoPhaseBST<T>::destructNode(TwoPhaseBST::PrimaryNode * &root)
{
    if (root == NULL)
        return;

    destructNode(root->left);
    destructNode(root->right);

    destructNode(root->rootSecondaryNode);

    delete root;

    root = NULL;
}

template <class T>
void TwoPhaseBST<T>::destructNode(TwoPhaseBST::SecondaryNode * &root)
{
    if (root == NULL)
        return;

    destructNode(root->left);
    destructNode(root->right);

    delete root;

    root = NULL;
}

#endif //TWOPHASEBST_H
