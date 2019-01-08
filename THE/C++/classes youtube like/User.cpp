#include <iostream>
#include "User.hpp"
#include "Video.hpp"
/* #include "Video.cpp" I added that  */

void User::printSubscriptions() {
    Node< Video*> * first = subscriptions.first();
    while (first) {
        cout << *(first->getData());
        first = first->getNext();
    }
    cout << std::endl;
}

void User::printFriends() {
    Node< User*> * first = friends.first();
    while (first) {
        cout << *(first->getData());
        first = first->getNext();
    }
    cout << std::endl;
}

ostream& operator<<(ostream& out, const User & user) {
    string st = (user.status == ACTIVE) ? "active" : "suspended";
    out << "username:" << user.username << ",name:" << user.name << ",surname:" << user.surname << ",Status:" << st << endl;
    return out;
}

/* TO-DO: method implementations below */

User::User(){
	
	username = "";
	name = "";
	surname = "";
	status = ACTIVE;
	/* I added after */
	LinkedList< Video* > subscriptions = *(new LinkedList<Video*>);
    LinkedList< User* > friends = *(new LinkedList<User*>);
}

User::User(string username, string name , string surname ){
	this->username = username;
	this->name = name;
	this->surname = surname;
	this->status = ACTIVE;
	/* I added after */
	LinkedList< Video* > subscriptions = *(new LinkedList<Video*>);
    LinkedList< User* > friends = *(new LinkedList<User*>);
	
}

User::~User(){
}

const string& User::getUsername() const{
	return username;
}
    
const string& User::getName() const{
	return name;
}

const string& User::getSurname() const{
	return surname;
}

Status User::getStatus() const{
	return status;
}

void User::updateStatus(Status st){
	status = st;	
}

/* There is a problem with Node.hpp ' s data. It ' s private I can ' t access to it */
void User::subscribe(Video * video){
	Node<Video *> *tnode_head = subscriptions.getHead();
	Node<Video *> *tvideo = new Node<Video *>;
	
	*(tvideo->getDataPtr()) = video;
	
	if(tnode_head->getNext() == NULL ){
		
		tnode_head->setNext(tvideo);
		tvideo->setNext(NULL);
	}
	else{
		
		tvideo->setNext(tnode_head->getNext());
		tnode_head->setNext(tvideo);
	}
	
}

void User::unSubscribe(Video * video){
	Node<Video *> *tnode_head = subscriptions.getHead();
	Node<Video *> *temp_p = new Node<Video *>;
	
	while(true){
		if(tnode_head->getData() == video){
			temp_p->setNext(tnode_head->getNext());
			delete tnode_head;
			break;
		}
		temp_p=tnode_head;
		tnode_head=tnode_head->getNext();
	}
}



void User::addFriend(User * user){
	Node<User *> *usernode_head = friends.getHead();
	Node<User *> *tuser = new Node<User *>;

	*(tuser->getDataPtr()) = user;
	
	if(usernode_head->getNext() == NULL ){
		
		usernode_head->setNext(tuser);
		tuser->setNext(NULL);
	}
	else{
		
		tuser->setNext(usernode_head->getNext());
		usernode_head->setNext(tuser);
	}
}

void User::removeFriend(User * user){
	Node<User *> *usernode_head = friends.getHead();
	Node<User *> *temp_p = new Node<User *>;
	
	while(true){
		if(usernode_head->getData() == user){
			temp_p->setNext(usernode_head->getNext());
			delete usernode_head;
			break;
		}
		temp_p=usernode_head;
		usernode_head=usernode_head->getNext();
	}
}

LinkedList<Video* >* User::getSubscriptions(){
	return &subscriptions;
}

LinkedList< User* >* User::getFriends(){
	return &friends;
}

bool User::operator==(const User& rhs) const{
	if(name == rhs.name){
		return true;
	}
	else{
		return false;
	}
}        

