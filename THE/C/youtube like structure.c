#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void ADD(char *username);
void SUBSCRIBE(char *username,char *topicname);
void SEND(char *username,char *topicname);
void UNSUBSCRIBE(char *username,char *topicname);
void DELETEUSER(char *username);	

int userid=1;
int topicid=1;
int message=1;

struct node{
	int data; 
	struct node *next; 
}; 

struct message_node{ 
	int sender_id; 
	int topic_id; 
	int message_id; 
	struct message_node *next; 
};

struct topic_node{ 
	char *topic_name; 
	int topic_id; 
	struct node *follower_list; /**hold user ID’s in data field**/ 
	struct topic_node *next; 
	/**Add additional fields as needed **/
};

 struct user_node{ 
 	char *user_name; 
	int user_id; 
	struct node *followed_topics; /**hold topic ID’s in data field**/ 
	struct message_node *inbox;
	struct user_node *next; 
	/** Add additional fields as needed **/
};

struct user_node *head_user;
struct topic_node *head_topic;
struct message_node *head_message;

void ADD(char *username){
	struct user_node *temp;
	char *string;
	string=(char *)malloc(30*sizeof(char));
	strcpy(string,username);
	temp=head_user;
	while(temp->next!=NULL){
		temp=temp->next;
	}
	temp->user_name=string; 
	temp->user_id=userid; 
	temp->followed_topics=(struct node*)malloc(sizeof(struct node)); /**hold topic ID’s in data field**/ 
	temp->inbox=(struct message_node*)malloc(sizeof(struct node));
	temp->next=(struct user_node *)malloc(sizeof(struct user_node));
	temp->followed_topics->data=0;
	temp->followed_topics->next=NULL;
	temp->inbox->message_id=0;
	temp->inbox->next=NULL;
	temp=temp->next;
	temp->next=NULL;
	
	userid++;
}

void SUBSCRIBE(char *username,char *topicname){
	struct topic_node *comparison=head_topic;
	struct user_node *temp=head_user;
	struct topic_node *temp_topic=head_topic;
	struct user_node *find_id=head_user;
	struct user_node *insert_id=head_user;
	
	struct node *ftops;
	struct node *flist;
	
	char *string_user; /** ||| **/
	char *string_topic; /** ||| **/
	int adduserid=0;
	int insert_tid;
	string_user=(char *)malloc(30*sizeof(char));
	strcpy(string_user,username);

	string_topic=(char *)malloc(30*sizeof(char));
	strcpy(string_topic,topicname);

	
	
	
	while(1){
		if(!(strcmp(find_id->user_name,string_user))){
		adduserid=find_id->user_id;
		break;	
		}
		find_id=find_id->next;
	}

	while(1){
		int exit=0;
		if(!(strcmp(temp_topic->topic_name,string_topic))){
			insert_tid=temp_topic->topic_id;
			if(temp_topic->follower_list!=NULL)
			flist=temp_topic->follower_list;
			while(1){
				if(flist->data==0){
					flist->data=adduserid;
					flist->next=NULL;
					exit=1;
					break;
				}
				if(flist->next==NULL){
					flist->next=(struct node*)malloc(sizeof(struct node));
					flist=flist->next;
					flist->data=adduserid;
					flist->next=NULL;
					exit=1;
					break;
				}	
				flist=flist->next;
			}
		}
		if(exit){
			break;
		}
		if(temp_topic->next!=NULL){
		temp_topic=temp_topic->next;
		}
		else{
			if(!(strcmp(temp_topic->topic_name,"Hassan"))){
				temp_topic->topic_name=string_topic;
				temp_topic->next=NULL;
				temp_topic->follower_list->data=adduserid;
				temp_topic->follower_list->next=NULL;
				temp_topic->topic_id=topicid;
				insert_tid=topicid;
				topicid++;
				break;
			}
			else{
				temp_topic->next=(struct topic_node*)malloc(sizeof(struct topic_node));
				temp_topic=temp_topic->next;
				temp_topic->topic_name=string_topic;
				temp_topic->next=NULL;
				temp_topic->follower_list=(struct node*)malloc(sizeof(struct node));
				temp_topic->follower_list->data=adduserid;
				temp_topic->follower_list->next=NULL;
				temp_topic->topic_id=topicid;
				insert_tid=topicid;
				topicid++;
				break;
			}	
		}
	}
	
	while(1){
		if(!(strcmp(insert_id->user_name,string_user))){
			ftops=insert_id->followed_topics;

			while(1){
				if(ftops->next==NULL){
					if(ftops->data==0){
						ftops->data=insert_tid;
						ftops->next=NULL;
						return;
					}
					else{
						ftops->next=(struct node*)malloc(sizeof(struct node));
						ftops=ftops->next;
						ftops->data=insert_tid;
						ftops->next=NULL;
						return;
					}					
				}
				ftops=ftops->next;
			}
		}
		insert_id=insert_id->next;
	}
}

void SEND(char *username,char *topicname){
	
	struct user_node *temp_user=head_user,*inbox_appender=head_user;
	struct topic_node *temp_topic=head_topic;
	struct message_node *temp_message=head_message;
	struct user_node *sender_append=head_user;
	struct message_node *append_here;

	char *string_user; /** ||| **/
	char *string_topic; /** ||| **/
	struct node* flist;
	int user;
	int topic;	
	string_user=(char *)malloc(30*sizeof(char));
	strcpy(string_user,username);

	string_topic=(char *)malloc(30*sizeof(char));
	strcpy(string_topic,topicname);

	while(1){
		if((strcmp(temp_user->user_name,string_user))==0)
		{
			user=temp_user->user_id;
			break;
		}
		temp_user=temp_user->next;
	}
	while(1){
		if((strcmp(temp_topic->topic_name,string_topic))==0)
		{
			topic=temp_topic->topic_id;			
			break;
		}
		temp_topic=temp_topic->next;
	}
	while(temp_message->next!=NULL)
	temp_message=temp_message->next;
	if(temp_message->sender_id==0){
		temp_message->sender_id=user;
		temp_message->topic_id=topic;
		temp_message->message_id=message;
		temp_message->next=NULL;
		message++;
	}
	else{
		struct message_node *p;
		p=(struct message_node*)malloc(sizeof(struct message_node));
		temp_message->next=p;
		temp_message=temp_message->next;
		temp_message->sender_id=user;
		temp_message->topic_id=topic;
		temp_message->message_id=message;
		temp_message->next=NULL;
		message++;
	}
	while(1){
		flist=inbox_appender->followed_topics;
		while(1){
			if(flist->data==topic && inbox_appender->user_id!=temp_message->sender_id){
			
				if(inbox_appender->inbox->message_id==0){
					struct message_node *append; /** try this**/
					append=(struct message_node*)malloc(sizeof(struct message_node));
					append->message_id=temp_message->message_id;
					append->next=NULL;
					append->sender_id=temp_message->sender_id;
					append->topic_id=temp_message->topic_id;
					inbox_appender->inbox=append;
			
				}
				else {
					struct message_node *ylist=inbox_appender->inbox;
					while(1){
						if(ylist->next==NULL){
							struct message_node *append; /** try this**/
							append=(struct message_node*)malloc(sizeof(struct message_node));
							append->message_id=temp_message->message_id;
							append->next=NULL;
							append->sender_id=temp_message->sender_id;
							append->topic_id=temp_message->topic_id;
							ylist->next=append;
							break;
						}
						ylist=ylist->next;
					}
		
				}
				break;		
			}
			if(flist->next==NULL){
			
				break;
			}
			flist=flist->next;
		}
		
		if(inbox_appender->next==NULL || inbox_appender->next->next==NULL){
			break;
		}
		inbox_appender=inbox_appender->next;
	}
	while(1){
		if(sender_append->user_id==temp_message->sender_id){
			if(sender_append->inbox->message_id==0){
				struct message_node *append_s; /** try this**/
				append_s=(struct message_node*)malloc(sizeof(struct message_node));
				append_s->message_id=temp_message->message_id;
				append_s->next=NULL;
				append_s->sender_id=temp_message->sender_id;
				append_s->topic_id=temp_message->topic_id;
				sender_append->inbox=append_s;
				return;
			}
			else{
				struct message_node *ylist_s=sender_append->inbox;
				while(1){
					if(ylist_s->next==NULL){
						struct message_node *append_s; /** try this**/
						append_s=(struct message_node*)malloc(sizeof(struct message_node));
						append_s->message_id=temp_message->message_id;
						append_s->next=NULL;
						append_s->sender_id=temp_message->sender_id;
						append_s->topic_id=temp_message->topic_id;
						ylist_s->next=append_s;
						break;
					}
					ylist_s=ylist_s->next;
				}
			}
		}
		if(sender_append->next==NULL || sender_append->next->next==NULL){
			return;
		}
		sender_append=sender_append->next;
	}
	
}

void UNSUBSCRIBE(char *username,char *topicname){
	
	struct topic_node *temp_topic=head_topic;
	struct user_node *temp_user=head_user;
	struct user_node *id_=head_user;
	struct message_node *m_user;
	struct message_node *temp_muser;	
	struct message_node *temp_mmuser;	
	
	char *string_user; /** ||| **/
	char *string_topic; /** ||| **/
	int id;
	int t_id;
	
	string_user=(char *)malloc(30*sizeof(char));
	strcpy(string_user,username);
	string_topic=(char *)malloc(30*sizeof(char));
	strcpy(string_topic,topicname);

	
	while(1){
		if((strcmp(id_->user_name,string_user))==0){
		id=id_->user_id;
		break;
		}
		id_=id_->next;
	}
	
	while(1){
		int count=0;
		if((strcmp(temp_topic->topic_name,string_topic))==0){
			struct node *temp_tlist=temp_topic->follower_list;	
			t_id=temp_topic->topic_id;			
			while(1){
		
				if(temp_tlist->data==id && count==0){
					if(temp_tlist->next==NULL){
						temp_tlist->data=0;
						break;
					}
					temp_topic->follower_list=temp_tlist->next;
					free(temp_tlist);
					break;
				}
				count=1;
				if(temp_tlist->next->data==id){
					struct node *b=temp_tlist->next;
					temp_tlist->next=b->next;
					free(b);
					break;
				}
				if(temp_tlist->next!=NULL)
				temp_tlist=temp_tlist->next;
			}
			break;
		}
		
		temp_topic=temp_topic->next;
	}
	while(1){
		int count=0;
		if((strcmp(temp_user->user_name,string_user))==0){
			struct node *temp_flist=temp_user->followed_topics;
			id=temp_user->user_id;
			while(1){
				if(temp_flist->data==t_id && count==0){
					if(temp_flist->next==NULL){
						temp_flist->data=0;
						break;
					}
					temp_user->followed_topics=temp_flist->next;
					free(temp_flist);
					break;
				}
				count=1;
				if(temp_flist->next->data==t_id){
					struct node *a=temp_flist->next;
					temp_flist->next=a->next;
					free(a);
					break;
				}
				
				if(temp_flist->next!=NULL)
				temp_flist=temp_flist->next;
			}
			break;	
		}
		
		temp_user=temp_user->next;
	}	
	
	m_user=temp_user->inbox; /** used for deleting inbox **/
	
	if(m_user->message_id==0){
			return;
	}
	else{
		if(m_user->topic_id==t_id){
			if(m_user->next==NULL){
				m_user->message_id=0;
				return;
			}
			else{
				struct message_node *o;
				temp_mmuser=temp_user->inbox->next;
				while(1){
					
					if(temp_mmuser==NULL){
						m_user->message_id=0;
						m_user->next=NULL;
						return;						
					}
					if(temp_mmuser->topic_id!=t_id){
						temp_user->inbox=temp_mmuser;
						break;
					}
					o=temp_mmuser;
					temp_mmuser=temp_mmuser->next;
					free(o);
				}
			}
		}
		
	}
	m_user=temp_user->inbox;
	/** --**/
	while(1){
		if(m_user->next==NULL)
			return;
		if(m_user->next->topic_id==t_id){
			temp_muser=m_user->next->next;
			free(m_user->next);
			while(1){
				if(temp_muser==NULL){
					m_user->next=temp_muser;
					return;
				}
				if(temp_muser->topic_id!=t_id){
					m_user->next=temp_muser;
					break;
				}
				else{
					struct message_node *i=temp_muser->next;
					free(temp_muser);
					temp_muser=i;	
				}		
			}	
		}
			
		if(m_user->next==NULL)
		break;
		m_user=m_user->next;
	}
	
}

void DELETEUSER(char *username){
	struct user_node *temp_user=head_user;
	struct user_node *delete_user=head_user;
	struct user_node *inbox_deleter=head_user;
	struct message_node *m_user;
	struct message_node *temp_mmuser;
	struct message_node *temp_muser;

	char *string_user; /** ||| **/
	int id;
	int exit=0;
	
	string_user=(char *)malloc(30*sizeof(char));
	strcpy(string_user,username);



	while(1){
		if((strcmp(temp_user->user_name,string_user))==0){
			id=temp_user->user_id;
			break;
		}
		temp_user=temp_user->next;
	}
	
	if(temp_user==head_user && temp_user->next->next!=NULL){
		struct node *nb,*na;
		struct message_node *mnb,*mna;
		head_user=head_user->next;
		nb=temp_user->followed_topics;
		do{
			if(nb->data!=0){
				na=nb->next;
				free(nb);
			}
			else
			break;
			nb=na;
		}while(nb!=NULL);
		mnb=temp_user->inbox;
		do{
			if(mnb->message_id!=0){
				mna=mnb->next;
				free(mnb);
			}
			else
			break;
			mnb=mna;
		}while(mnb!=NULL);
	
		free(temp_user->user_name);
		free(temp_user);
	}
	
	else if(temp_user==head_user && temp_user->next->next==NULL){
		struct node *nb,*na;
		struct message_node *mnb,*mna;
		int count=0; 
		temp_user->user_id=0; 
		nb=temp_user->followed_topics;
		do{
			if(nb->data!=0){
				if(count!=0){
				na=nb->next;
				free(nb);
				}
				else{
					nb->data=0;
					na=nb->next;
				}
			}
			else
			break;
			count++;
			nb=na;
		}while(nb!=NULL);
		count=0;
		mnb=temp_user->inbox;
		do{
			if(mnb->message_id!=0){
				if(count!=0){
				mna=mnb->next;
				free(mnb);
				}
				else{
					mnb->message_id=0;
					mnb->sender_id=0;
					mnb->topic_id=0;
					mna=mnb->next;
				}
			}
			else
			break;
			count++;
			mnb=mna;
		}while(mnb!=NULL);
		temp_user->followed_topics->data=0;
		temp_user->inbox->message_id=0;
		temp_user->next=NULL;
	}
	else{
		while(1){
			if(delete_user->next->user_id==id){
				struct node *nb,*na;
				struct message_node *mnb,*mna;
				nb=delete_user->next->followed_topics;
				do{
					if(nb->data!=0){
						na=nb->next;
						free(nb);
					}
					else
					break;
					nb=na;
				}while(nb!=NULL);
				mnb=delete_user->next->inbox;
				do{
					if(mnb->message_id!=0){
						mna=mnb->next;
						free(mnb);
					}
					else
					break;
					mnb=mna;
				}while(mnb!=NULL);
				temp_user=delete_user->next;
				delete_user->next=delete_user->next->next;
				free(temp_user->user_name);
				free(temp_user);
				break;
			}
			delete_user=delete_user->next;
		}
	}
	
	inbox_deleter=head_user;
	temp_user=head_user;
	while(1){
		exit=0;
		/** -- **/
		m_user=inbox_deleter->inbox; /** used for deleting inbox **/
		
		if(m_user->message_id==0){
			if(inbox_deleter->next==NULL || inbox_deleter->next->next==NULL)
			return;
			inbox_deleter=inbox_deleter->next;
			continue;
		}
		else{
			if(m_user->sender_id==id){
				if(m_user->next==NULL){
					m_user->message_id=0;
					if(inbox_deleter->next==NULL || inbox_deleter->next->next==NULL)
					return;
					inbox_deleter=inbox_deleter->next;
					continue;
				}
				else{
					struct message_node *o;
					temp_mmuser=m_user;
					while(1){
						
						if(temp_mmuser==NULL){
							m_user->message_id=0;
							m_user->next=NULL;
							if(inbox_deleter->next==NULL || inbox_deleter->next->next==NULL)
							return;
					  exit=1;
							inbox_deleter=inbox_deleter->next;
							break;					
						}
						if(temp_mmuser->sender_id!=id){
							inbox_deleter->inbox=temp_mmuser;
							break;
						}
						o=temp_mmuser;
						temp_mmuser=temp_mmuser->next;
						free(o);
					}
					if(exit==1){
						exit=0;
						continue;
					}
				}
			}
			
		}
		m_user=inbox_deleter->inbox;
		while(1){
			
			if(m_user->next==NULL)
				break;
			if(m_user->next->sender_id==id){
				temp_muser=m_user->next->next;
				free(m_user->next);
				while(1){
					
					if(temp_muser==NULL){
						m_user->next=temp_muser;
						if(inbox_deleter->next==NULL || inbox_deleter->next->next==NULL)
						return;
						exit=1;
						break;
					}
					if(temp_muser->sender_id!=id){
						m_user->next=temp_muser;
						break;
					}
					else{
						struct message_node *i=temp_muser->next;
						free(temp_muser);
						temp_muser=i;	
					}		
				}	
				if(exit==1){
					break;
				}
			}
			if(m_user->next==NULL)
			break;
			m_user=m_user->next;
		}
	
	if(inbox_deleter->next==NULL || inbox_deleter->next->next==NULL)
	return;
	inbox_deleter=inbox_deleter->next;

	}
	
}

int main(void){
	int i;
	int a=0;
	struct message_node* deneme;
	struct message_node *message;
	struct message_node *printer;
	struct user_node *p=head_user;
	char command[15];
	char x[30],y[30];
	
	head_user=(struct user_node*)malloc(sizeof(struct user_node));
	head_user->next=NULL;
	head_user->followed_topics=(struct node*)malloc(sizeof(struct node));
	head_user->followed_topics->data=0;
	head_user->followed_topics->next=NULL;
	head_topic=(struct topic_node*)malloc(sizeof(struct topic_node));
	head_topic->next=NULL;	
	head_topic->topic_name="Hassan";
	head_topic->follower_list=(struct node*)malloc(sizeof(struct node));
	head_topic->follower_list->next=NULL;
	head_topic->follower_list->data=0;
	head_message=(struct message_node*)malloc(sizeof(struct message_node));
	head_message->next=NULL;
	head_message->sender_id=0;

	while(scanf("%s",command)!=EOF){ 
		if((strcmp(command,"ADD"))==0){
			scanf("%s",x);
			ADD(x);
			
		}
		if((strcmp(command,"SUBSCRIBE"))==0){
			scanf("%s",x);
			scanf("%s",y);
			SUBSCRIBE(x,y);
		}
		if((strcmp(command,"SEND"))==0){
			scanf("%s",x);
			scanf("%s",y);
			SEND(x,y);
		}
		if((strcmp(command,"UNSUBSCRIBE"))==0){
			scanf("%s",x);
			scanf("%s",y);
			UNSUBSCRIBE(x,y);
		}
		if((strcmp(command,"DELETEUSER"))==0){
			scanf("%s",x);
			DELETEUSER(x);
		}
		
	}

	if(head_user->user_id==0){
			return 0;
		}
	while(1){ /** PRINT **/
		printer=head_user->inbox;
		printf("%d:",head_user->user_id);
		while(1){
			if(head_user->inbox->message_id==0)
			break;
			printf(" %d",printer->message_id);
			if(printer->next==NULL)
			break;
			printer=printer->next;
		}
		
		printf("\n");
		
		if(head_user->next->next==NULL || head_user->next==NULL)
		break;
		head_user=head_user->next;
	}
	
	return 0;		
	
}
	
