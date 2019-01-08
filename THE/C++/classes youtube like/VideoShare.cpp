#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "VideoShare.hpp"
#include "User.hpp"

using namespace std;

void VideoShare::printAllVideos() {
    videos.print();
}

void VideoShare::printAllUsers() {
    users.print();
}

/* TO-DO: method implementations below */

VideoShare::VideoShare(){
	
	LinkedList<User> *u1 = new LinkedList<User>;
    LinkedList<Video> *v1 = new LinkedList<Video>;
    LinkedList<User> *uf1 = new LinkedList<User>;
    LinkedList<Video> *fv1 = new LinkedList<Video>; 
    
	users = *u1;
    videos = *v1;
	userfriends = *uf1;
	friends_videos = *fv1;
}

VideoShare::~VideoShare(){
	
}

void VideoShare::createUser(const string & userName, const string & name, const string & surname){
	User *tmp = new User(userName,name,surname);
	
	Node<User> *u1 = new Node<User>;
	Node<User> *u_head = users.getHead();
	
	u1->setNext(NULL);
	
	*(u1->getDataPtr()) = *tmp;
	if(u_head->getNext() == NULL ){
		u_head->setNext(u1);
		
	}
	else{
	
		u1->setNext(u_head->getNext());
		u_head->setNext(u1);
	}

}

void VideoShare::loadUsers(const string & fileName){
	int count = 0;
	int pos = 0;
	string line;
	string *array = new string[3];
	ifstream file(fileName.c_str());
	while(getline(file,line)){
		
		for(int i = 0;i<line.length();i++){
			if(count == 2 && i==line.length()-1){
				char *word = new char[line.length()-pos+1];
				
				for(int j=pos;j<line.length();j++){
					word[j] = line[j];
					word[j+1] == '\0';
				}
				array[2] = word;
				break;
			}
			if(line[i] == ';'){
				char *word = new char[i-pos+1];
				
				for(int j=pos;j<i;j++){
					word[j] = line[j];
					if(j==i-1){
						word[j+1] == '\0';
					}
				}
				
				/*cout << word << endl;*/
				array[count] = word;
		/* Another cout
				cout << array[count] << endl;
		*/
				pos = i;
				count++;
			}
		}
		this->createUser(array[0],array[1],array[2]);
		pos = 0;
		count = 0;
	}
}

void VideoShare::createVideo(const string & title, const string & genre){
	Video *tmp = new Video(title,genre);
	
	Node<Video> *u1 = new Node<Video>;
	Node<Video> *u_head = videos.getHead();
	
	u1->setNext(NULL);
	
	*(u1->getDataPtr()) = *tmp;
	if(u_head->getNext() == NULL ){
		u_head->setNext(u1);
		
	}
	else{
	
		u1->setNext(u_head->getNext());
		u_head->setNext(u1);
	}

}

void VideoShare::addFriendship(const string & userName1, const string & userName2){
	Node<User> *head_temp = this->users.getHead();
	Node<User> *head_temp2 = this->users.getHead();
	User *user_temp = NULL;
	User *user_temp2 = NULL;
	while(head_temp!=NULL){
		user_temp = head_temp->getDataPtr();
		
		if(user_temp->getUsername() == userName1){
			while(head_temp2!=NULL){
				user_temp2 = head_temp2->getDataPtr();
					
				if(user_temp2->getUsername() == userName2){
					
					user_temp->addFriend(user_temp2);
					user_temp2->addFriend(user_temp);
					return;					
				}	
				head_temp2 = head_temp2->getNext();	
			}
		}
		head_temp = head_temp->getNext();
	}
}    

void VideoShare::removeFriendship(const string & userName1, const string & userName2){
	Node<User> *head_temp = this->users.getHead();
	Node<User> *head_temp2 = this->users.getHead();
	User *user_temp = NULL;
	User *user_temp2 = NULL;
	while(head_temp!=NULL){
		user_temp = head_temp->getDataPtr();
		
		if(user_temp->getUsername() == userName1){
			while(head_temp2!=NULL){
				user_temp2 = head_temp2->getDataPtr();
					
				if(user_temp2->getUsername() == userName2){
					
					user_temp->removeFriend(user_temp2);
					user_temp2->removeFriend(user_temp);
					return;					
				}	
				head_temp2 = head_temp2->getNext();	
			}
		}
		head_temp = head_temp->getNext();
	}	
}
    
void VideoShare::updateUserStatus(const string & userName, Status newStatus){
	
	Node<User>* user_node = users.getHead()->getNext();	
	while(user_node!=NULL){
		if(user_node->getDataPtr()->getUsername() == userName){
			user_node->getDataPtr()->updateStatus(newStatus);
		}
		user_node = user_node->getNext();
	}

}
    
void VideoShare::subscribe(const string & userName, const string & videoTitle){
	Node<User> *head_temp = this->users.getHead();
	Node<Video> *head_video = this->videos.getHead();
	
	if(head_temp->getDataPtr()->getStatus() != SUSPENDED){
		Video *video_temp = NULL;
		while(head_video!=NULL){
			video_temp = head_video->getDataPtr();
			if(video_temp->getTitle() == videoTitle){
				
				break;					
			}	
			head_video = head_video->getNext();
		}
		User *user_temp = NULL;
		while(head_temp!=NULL){
			user_temp = head_temp->getDataPtr();
			if(user_temp->getUsername() == userName){
				user_temp->User::subscribe(video_temp);
				return;					
			}	
			head_temp = head_temp->getNext();
		}
	}
}

void VideoShare::unSubscribe(const string & userName, const string & videoTitle){
	Node<User> *head_temp = this->users.getHead();
	Node<Video> *head_video = this->videos.getHead();
	
	if(head_temp->getDataPtr()->getStatus() != SUSPENDED){
		Video *video_temp = NULL;
		while(head_video!=NULL){
			video_temp = head_video->getDataPtr();
			if(video_temp->getTitle() == videoTitle){
				
				break;					
			}	
			head_video = head_video->getNext();
		}
		User *user_temp = NULL;
		while(head_temp!=NULL){
			user_temp = head_temp->getDataPtr();
			if(user_temp->getUsername() == userName){
				user_temp->User::unSubscribe(video_temp);
				return;					
			}	
			head_temp = head_temp->getNext();
		}
	}
}

void VideoShare::deleteUser(const string & userName){
	Node<User> *head_temp = this->users.getHead()->getNext();
	Node<User> *phead_temp = this->users.getHead()->getNext();
	
	Node<User> *head_temp2 = this->users.getHead()->getNext();
	
	Node<User*> *head_friends = NULL;
	User *user_temp = NULL;

	while(head_temp){
		user_temp = head_temp->getDataPtr();
		if(user_temp->getUsername() == userName){
			head_friends = user_temp->getFriends()->getHead()->getNext();
			while(head_friends){
				while(head_temp2){
					if(head_temp2->getDataPtr()->getUsername() == head_friends->getData()->getUsername()){
						removeFriendship(userName,head_friends->getData()->getUsername());
						head_temp2 = this->users.getHead()->getNext();
						break;
					}
					head_temp2 = head_temp->getNext();
				}
				head_friends = head_friends->getNext();
			}
			if(head_temp == phead_temp){
				delete head_temp;
				this->users.getHead()->setNext(NULL);
				return;
			}
			phead_temp->setNext(head_temp->getNext());
			delete head_temp;
			return;
			
		}
		phead_temp = head_temp;
		head_temp = head_temp->getNext();
	}
	
}

void VideoShare::sortUserSubscriptions(const string & userName){
	Node<User> *count_head = users.getHead();
	while(count_head){
		if(count_head->getDataPtr()->getUsername() == userName){
			break;
		}
		count_head = count_head->getNext();
	}
	
	Node<Video*> *c_node = count_head->getDataPtr()->getSubscriptions()->getHead();
	
	LinkedList<Video*> *linked_video = count_head->getDataPtr()->getSubscriptions();
	Node<Video *>* node_video = linked_video->getHead();
	
	int n = -1;
	while(c_node){
		n++;
		c_node = c_node->getNext();
	}
	
	bool sorted = false;
	
	for(int i = 0;(i < n - 1) && !sorted; i++){
		sorted = true; 
		node_video = linked_video->getHead();
		for(int j = 1;j <= n-i-1;j++){
			if(node_video->getNext()->getData()->getTitle() > node_video->getNext()->getNext()->getData()->getTitle()){
				linked_video->swap(j-1,j);
				sorted = false;
			}
			node_video = node_video->getNext();
		}
	}	
}

void VideoShare::printUserSubscriptions(const string & userName){
	Node<User>* node = users.getHead()->getNext();
	
    while (node) {
    	if(node->getDataPtr()->getUsername() == userName){
    		node->getDataPtr()->printSubscriptions();	
			return;
		}
        node = node->getNext();
    }
    cout << endl;
}

void VideoShare::printFriendsOfUser(const string & userName){
	Node<User>* node = users.getHead()->getNext();
	
    while (node) {
    	if(node->getDataPtr()->getName() == userName){
    		node->getDataPtr()->printFriends();	
			return;
		}
        node = node->getNext();
    }
    cout << endl;
}

void VideoShare::printCommonSubscriptions(const string & userName1, const string & userName2){
	Node<User> *user1 = NULL;
	Node<User> *user2 = NULL;
	Node<User> *user_node = users.getHead();
	
	while(user_node){
		if(userName1 == user_node->getDataPtr()->getUsername()){
			user1 = user_node;
		}
		if(userName2 == user_node->getDataPtr()->getUsername()){
			user2 = user_node;
		}
		user_node = user_node->getNext();
	}
	
	Node< Video* > *sub1 = user1->getDataPtr()->getSubscriptions()->getHead()->getNext();
	Node< Video* > *sub2 = user2->getDataPtr()->getSubscriptions()->getHead()->getNext();

	while(sub1){ /* cout ' ing the common subscriptions */
		
		while(sub2){
	
			if(sub1->getData() == sub2->getData()){
				cout << sub2->getData()->getTitle() << endl;
				break;
			}
			sub2 = sub2->getNext();
		}
		sub2 = user2->getDataPtr()->getSubscriptions()->getHead()->getNext();
		sub1 = sub1->getNext();
	}
	
}
    
void VideoShare::printFriendSubscriptions(const string & userName){
	LinkedList<Video> *list_video = new LinkedList<Video>;
	Node<Video> *head_node = list_video->getHead(); /* friends subscribed videos */
	head_node->setNext(NULL);
	
	Node<User> *user_node = users.getHead();
	
	Node<User> *user1 = NULL;
	
	while(user_node){
		if(userName == user_node->getDataPtr()->getUsername()){
			user1 = user_node;
			break;
		}
		user_node = user_node->getNext(); 
	}
	
	Node<Video*> *user_sub = user_node->getDataPtr()->getSubscriptions()->getHead(); /* our own subscribed videos */
	
	LinkedList< User* > *friend_list = user1->getDataPtr()->getFriends();
	
	Node<User*> *_friends = friend_list->getHead()->getNext();

	while(_friends){
		/*Node<Video> *addnode = new Node<Video>;*/
		LinkedList< Video* > *sub_link = _friends->getData()->getSubscriptions();
		Node<Video* > *sub_node = sub_link->getHead()->getNext();	
			while(sub_node){
				/**(addnode->getDataPtr()) = *(sub_node->getData());*/
				head_node->setNext(new Node<Video>);
				head_node = head_node->getNext();
				*(head_node->getDataPtr()) = *(sub_node->getData());
				sub_node = sub_node->getNext();
			}
		
		_friends = _friends->getNext();
	}
	
	VideoShare a2;
	
	a2.createUser("template","1","2");
	head_node = list_video->getHead()->getNext(); 
	while(head_node){
		a2.createVideo(head_node->getDataPtr()->getTitle(),head_node->getDataPtr()->getGenre());
		a2.subscribe("template",head_node->getDataPtr()->getTitle());
		head_node = head_node->getNext();
	}
	a2.printAllUsers();
	a2.sortUserSubscriptions("template");
	
	/*cout << a2.users.getHead()->getNext()->getDataPtr()->getSubscriptions()->getHead()->getNext()->getNext()->getNext()->getData()->getTitle()<< endl;*/
	Node<Video*> *subs = a2.users.getHead()->getNext()->getDataPtr()->getSubscriptions()->getHead()->getNext();
	Node<Video*> *subs_prew = a2.users.getHead()->getNext()->getDataPtr()->getSubscriptions()->getHead();
	

	Node<Video*> *user_prew = user_sub;
	user_sub = user_sub->getNext();	
	int deleted = 0;
	while(subs){ /* removing duplicates */
		deleted = 0; 	
		if(subs_prew->getData()!=NULL && subs_prew->getData()->getTitle() == subs->getData()->getTitle()){ 
			while(subs){
				if(subs->getNext() == NULL || subs->getData()->getTitle() != subs_prew->getData()->getTitle()){
					if(subs->getNext()==NULL){
						subs_prew->setNext(NULL);
						deleted = 1;
						subs = NULL;
						break;
					}
					subs_prew->setNext(subs);
					subs_prew = subs;
					subs = subs->getNext();
					deleted = 1;
					break;
				}
				subs = subs->getNext();
			}
		}
		if(deleted){
			continue;	
		}
		subs_prew = subs_prew->getNext();
		subs = subs->getNext();
		
	}
	
	subs = a2.users.getHead()->getNext()->getDataPtr()->getSubscriptions()->getHead()->getNext();
	subs_prew = a2.users.getHead()->getNext()->getDataPtr()->getSubscriptions()->getHead();
	
	while(user_sub){ /* removing user ' s not distinct videos */
	int deleted = 0;
	subs = a2.users.getHead()->getNext()->getDataPtr()->getSubscriptions()->getHead()->getNext();
	subs_prew = a2.users.getHead()->getNext()->getDataPtr()->getSubscriptions()->getHead();
		
		while(subs){
			if(user_sub->getData()->getTitle() == subs->getData()->getTitle()){ /* user_sub is our subscribed videos */
				subs_prew->setNext(subs->getNext());
				deleted = 1;
				break;
			}
			
		subs_prew = subs_prew->getNext();
		subs = subs->getNext();
		}

		user_sub = user_sub->getNext();
		
	}
	

	a2.printUserSubscriptions("template");
}
    
    
bool VideoShare::isConnected(const string & userName1, const string & userName2){
	Node<User> *f_node = userfriends.getHead();

	while(f_node){
		if(f_node->getDataPtr()->getUsername() == userName1){
			return true;
		}
		f_node = f_node->getNext();
	}
	
	Node<User> *user1 = NULL;
	Node<User> *user2 = NULL;
	Node<User> *user_node = users.getHead();
	
	Node< User* > *friend_node = NULL;
	while(user_node){
		if(userName1 == user_node->getDataPtr()->getUsername()){
			user1 = user_node;
		}
		if(userName2 == user_node->getDataPtr()->getUsername()){
			user2 = user_node;
		}
		user_node = user_node->getNext();
	}
	friend_node = user1->getDataPtr()->getFriends()->getHead()->getNext();
	
	while(friend_node){
		isConnected(friend_node->getData()->getUsername() , userName2);
		while(f_node){
			if(f_node->getNext()==NULL){
				Node<User> *f_add = new Node<User>;
				*(f_add->getDataPtr()) = user1->getData();
				f_node->setNext(f_add);
				break;
			}
			f_node = f_node->getNext();
		}
		friend_node = friend_node->getNext();
	}
	
}
    
