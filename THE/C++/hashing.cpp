#include "hashing.h"
AccessControl::~AccessControl(){
	
}

int AccessControl::number_usertable(){
	int count=0;
	for(int i=0;i<tableSize1;i++){
		if(regUsers[i].first!=EMPTY && regUsers[i].first!=DELETED){
			count++;
		}
	}
	return count;
}

int AccessControl::number_activeUsers(){
	int count=0;
	for(int i=0;i<tableSize2;i++){
		if(activeUsers[i]!=EMPTY && activeUsers[i]!=DELETED){
			count++;
		}
	}
	return count;
}

int AccessControl::find_prime1(){
	int min=tableSize1*2+1;
	bool prime=false;
	while(1){
		prime=true;
		for(int i=2;i<min;i++){
			if(min%i==0){
				prime=false;	
			}
		}
		if(prime==true){
			return min;
		}
		min++;
	}
}

int AccessControl::find_prime2(){
	int min=tableSize2*2+1;
	bool prime=false;
	while(1){
		prime=true;
		for(int i=2;i<min;i++){
			if(min%i==0){
				prime=false;	
			}
		}
		if(prime==true){
			return min;
		}
		min++;
	}
}

AccessControl::AccessControl(int table1Size, int table2Size){
	
	regUsers.resize(table1Size);
	this->tableSize1=table1Size;
	
	activeUsers.resize(table2Size);
	this->tableSize2=table2Size;
	
	for(int i=0;i<tableSize1;i++){
		regUsers[i].first=EMPTY;
		regUsers[i].second=EMPTY;
	}
	
	for(int j=0;j<tableSize2;j++){
		activeUsers[j]=EMPTY;
	}
	
}

void AccessControl::rehash1(int size){
/*	std::vector<std::pair<std::string, std::string> > temp;
	temp.resize(size);
	for(int i=0;i<size;i++){
		temp[i].first=EMPTY;
		temp[i].second=EMPTY;
	}
	int count=0;
	for(int i=0;i<tableSize1;i++){
		if(regUsers[i].first!=EMPTY && regUsers[i].first!=DELETED){
			for(int j=tableSize1-1;j>=i;j--){
				if(regUsers[i].first==regUsers[j].first){
					temp[count].first=regUsers[j].first;
					temp[count].second=regUsers[j].second;
					regUsers[j].first=EMPTY;
					count++;
				}
			}
		}
	}
	regUsers=temp;*/
	int count=1;
	std::vector<std::pair<std::string, std::string> > temp;
	temp.resize(size);
	for(int i=0;i<size;i++){
		temp[i].first=EMPTY;
		temp[i].second=EMPTY;
	}
	
	for(int i=0;i<tableSize1;i++){
		if(regUsers[i].first!=EMPTY && regUsers[i].first!=DELETED){
			int m=0;
			while(1){
				int hash=hashFunction(regUsers[i].first,tableSize1,m);
				if(m==tableSize1){
					break;
				}
				if(regUsers[hash].first==regUsers[i].first){
					for(int j=0;j<size;j++){
						int hash2=hashFunction(regUsers[hash].first,size,j);
						if(temp[hash2].first==EMPTY){
							temp[hash2].first=regUsers[hash].first;
							temp[hash2].second=regUsers[hash].second;
							regUsers[hash].first=EMPTY;
							regUsers[hash].second=EMPTY;
							
							break;
						}
					}
					
				}
				m++;
			}
			for(int j=0;j<size;j++){
				int hash=hashFunction(regUsers[i].first,size,j);
				if(temp[hash].first==EMPTY){	
					temp[hash].first=regUsers[i].first;
					temp[hash].second=regUsers[i].second;
					break;
				}
			}
		}
	}
	regUsers=temp;
}
void AccessControl::rehash2(int size){
	
	std::vector<std::string > temp;
	temp.resize(size);
	for(int i=0;i<size;i++){
		temp[i]=EMPTY;
	}
	
	for(int i=0;i<tableSize2;i++){
		if(activeUsers[i]!=EMPTY && activeUsers[i]!=DELETED){
			for(int j=0;j<size;j++){
				int hash=hashFunction(activeUsers[i],size,j);
				if(temp[hash]==EMPTY){	
					temp[hash]=activeUsers[i];
					break;
				}
			}
		}

	}
	activeUsers=temp;
}
void AccessControl::table_size1(int size){
	rehash1(size);
	tableSize1=size;
}

void AccessControl::table_size2(int size){
	rehash2(size);
	tableSize2=size;
}
int AccessControl::adding(std::string username, std::string pass){
	bool flag = false;
	
	
	for(int i=0;i<tableSize1;i++){
		int hash=hashFunction(username,tableSize1,i);
		if(regUsers[hash].first==EMPTY || regUsers[hash].first==DELETED){
			regUsers[hash].first = username;
			regUsers[hash].second = pass;
			flag=true;
			break;	
		}
	}
	
	if(number_usertable()/float(tableSize1)>MAX_LOAD_FACTOR){
		table_size1(find_prime1());	
		
	}
	
	if(flag)
		return 1;
	return 0;
}
int AccessControl::addUser(std::string username, std::string pass){
	
	for(int i=0;i<tableSize1;i++){
		if(regUsers[i].first==username){
			return 0;
		}
	}
	
	return adding(username,pass);
}

int AccessControl::addUsers(std::string filePath){
	int count=0;
	int user_line=0;
	std::string word1;
	std::string word2;
	std::string word;
	std::ifstream file(filePath.c_str());
	while(file >> word){
		if(user_line==0){
			word1=word;
		}
		else{
			word2=word;
		}
		if(user_line==1){
			if(addUser(word1,word2)){
				count++;
			}
			user_line=-1;
		}
		user_line++;
	}
	file.close();
	return count;
}
int AccessControl::delUser(std::string username, std::vector<std::string>& oldPasswords){
	int count=0;
	for(int i=0;i<tableSize1;i++){
		if(regUsers[i].first==username){
			std::vector<std::string> passwords;
			for(int k=0;k<tableSize1;k++){
				int hash=hashFunction(username,tableSize1,k);
				if(regUsers[hash].first==username){
					passwords.resize(count+1);
					passwords[count]=regUsers[hash].second;
					count++;
				}
			}
			
			for(int j=i;j<tableSize1;j++){
				if(username==regUsers[j].first){
					regUsers[j].first=DELETED;
					regUsers[j].second=DELETED;
				}
			}
			oldPasswords=passwords;
			return 1;
		}
	}	
	return 0;
}
int AccessControl::changePass(std::string username, std::string oldpass, std::string newpass){
	for(int i=tableSize1-1;i>=0;i--){
		int hash=hashFunction(username,tableSize1,i);
		if(regUsers[hash].first==username){
			if(regUsers[hash].second==oldpass){
				adding(username,newpass);
				return 1;	
			}
			else{
				break;	
			}
		}
	}
	return 0;
}
int AccessControl::login(std::string username, std::string pass){
	bool flag=false;
	for(int i=0;i<tableSize2;i++){
		if(activeUsers[i]==username){
			return 0;
		}
	}
	for(int j=tableSize1-1;j>=0;j--){
		int hash = hashFunction(regUsers[j].first,tableSize1,j);
		if(regUsers[j].first==username){
			if(regUsers[j].second!=pass){
				return 0;
			}
			else{
				flag=true;
				for(int i=0;i<tableSize2;i++){
					int hash2=hashFunction(username,tableSize2,i);
					if(activeUsers[hash2]==EMPTY || activeUsers[hash2]==DELETED){
						activeUsers[hash2] = username;
						break;
					}
				}
				if(number_activeUsers()/float(tableSize2)>MAX_LOAD_FACTOR){
					table_size2(find_prime2());
				}
			}
		}
	}
	if(flag)
		return 1;
	return 0;
}
int AccessControl::logout(std::string username){
	for(int j=0;j<tableSize2;j++){
		if(activeUsers[j]==username){
			activeUsers[j]=DELETED;
			return 1;
		}
	}
	return 0;
}
float AccessControl::printActiveUsers(){
	for(int j=0;j<tableSize2;j++){
		
		std::cout << activeUsers[j] << std::endl;
	}
	return 1;
}
float AccessControl::printPasswords(){
	for(int i=0;i<tableSize1;i++){
		
		std::cout << regUsers[i].first << " " << regUsers[i].second << std::endl;
	}
	return 1;
}

