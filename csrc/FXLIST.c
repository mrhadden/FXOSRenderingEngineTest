#include "FXLIST.h"

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
   struct node *temp = head, *prev = NULL;
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
   return AllocNamedList(NULL);
}

PFXNODELIST AllocNamedList(const char* name)
{
	PFXNODELIST list = (PFXNODELIST)malloc(sizeof(FXNODELIST));
	if(list)
	{
		memset(list,0,sizeof(FXNODELIST));
      if(name)
         list->name = name;
	}
	return list;
}

void ListClear(PFXNODELIST list)
{
	if(list)
	{
		memset(list,0,sizeof(FXNODELIST));
	}	
}

void DeallocNode(PFXNODE node)
{
	if(node)
	{
		memset(node,0,sizeof(FXNODE));
		free(node);
	}
}

void DeallocList(PFXNODELIST list)
{
	if(list)
	{
		memset(list,0,sizeof(FXNODELIST));
		free(list);
	}
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
	PFXNODE newNode = (PFXNODE) malloc(sizeof(FXNODE));
	newNode->data = data;
   newNode->next = NULL;
	PFXNODE linkedlist = list->head;

	// point it to old first node
	while(linkedlist->next != NULL)
	  linkedlist = linkedlist->next;

	//point first to new first node
	linkedlist->next = newNode;
	
	return newNode;
}

PFXNODE ListRemove(PFXNODELIST list,void* data)
{
   PFXNODE temp = list->head;
   PFXNODE prev = NULL;
   if(temp != NULL && temp->data == data) 
   {
      list->head = temp->next;
      return temp;
   }

   // Find the key to be deleted
   while(temp != NULL && temp->data != data) 
   {
      prev = temp;
      temp = temp->next;
   }

   // If the key is not present
   if(temp == NULL) 
	   return NULL;

   // Remove the node
   prev->next = temp->next;
   
   return temp;
   
}

PFXNODE ListSearch(PFXNODELIST list,void* key)
{
   PFXNODE temp = list->head;
   while(temp != NULL) 
   {
      if(temp->data == key) 
      {
         return temp;
      }
      temp=temp->next;
   }
   return NULL;   
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