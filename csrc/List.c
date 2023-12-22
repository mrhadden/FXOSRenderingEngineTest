#include "List.h"

struct node *head    = NULL;
struct node *current = NULL;



//insertion at the beginning
void insertatbegin(void* data){

   //create a link
   struct node *lk = (struct node*) malloc(sizeof(struct node));
   lk->data = data;

   // point it to old first node
   lk->next = head;

   //point first to new first node
   head = lk;
}

void insertatend(void* data){

   //create a link
   struct node *lk = (struct node*) malloc(sizeof(struct node));
   lk->data = data;
   struct node *linkedlist = head;

   // point it to old first node
   while(linkedlist->next != NULL)
      linkedlist = linkedlist->next;

   //point first to new first node
   linkedlist->next = lk;
}

void insertafternode(struct node *list, void* data){
   struct node *lk = (struct node*) malloc(sizeof(struct node));
   lk->data = data;
   lk->next = list->next;
   list->next = lk;
}

void deleteatbegin(){
   head = head->next;
}

void deleteatend(){
   struct node *linkedlist = head;
   while (linkedlist->next->next != NULL)
      linkedlist = linkedlist->next;
   linkedlist->next = NULL;
}

void deletenode(void* key){
   struct node *temp = head, *prev;
   if (temp != NULL && temp->data == key) {
      head = temp->next;
      return;
   }

   // Find the key to be deleted
   while (temp != NULL && temp->data != key) {
      prev = temp;
      temp = temp->next;
   }

   // If the key is not present
   if (temp == NULL) return;

   // Remove the node
   prev->next = temp->next;
}

int searchlist(void* key){
   struct node *temp = head;
   while(temp != NULL) {
      if (temp->data == key) {
         return 1;
      }
      temp=temp->next;
   }
   return 0;
}

PFXNODELIST AllocList()
{
	PFXNODELIST list = (PFXNODELIST)malloc(sizeof(FXNODELIST));
	if(list)
	{
		memset(list,0,sizeof(FXNODELIST));
	}
	return list;
}

PFXNODE ListAddStart(PFXNODELIST list,void* data)
{
	PFXNODE listHead = list->head;

	PFXNODE newNode = (PFXNODE) malloc(sizeof(FXNODE));
	newNode->data = data;
	newNode->next = listHead;
	list->head = newNode;
	
	return newNode;
}

PFXNODE ListAddEnd(PFXNODELIST list,void* data)
{
	PFXNODE listHead = list->head;

	PFXNODE newNode = (PFXNODE) malloc(sizeof(struct node));
	newNode->data = data;
	newNode->next = listHead;
	list->head = newNode;

	PFXNODE linkedlist = listHead;

	// point it to old first node
	while(linkedlist->next != NULL)
	  linkedlist = linkedlist->next;

	//point first to new first node
	linkedlist->next = newNode;
	
	return newNode;
}

void VisitList(PFXNODELIST list, NodeVisit visit)
{
	PFXNODE p = list->head;
    while(p != NULL) 
	{
		visit(p);
		p = p->next;
    }
}