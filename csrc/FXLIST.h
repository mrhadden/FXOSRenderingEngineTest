#ifndef __LIST__
#define __LIST__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node 
{
   void* data;
   struct node *next;
   struct node *previous;
}FXNODE;

typedef FXNODE* PFXNODE;

typedef struct node_list 
{
	PFXNODE head;
	PFXNODE current;
	int 	size;
	int		max;
	const char* name;
}FXNODELIST;
typedef FXNODELIST* PFXNODELIST;

typedef void (*NodeVisit)(PFXNODE);
typedef int (*NodeVisitCtx)(PFXNODE,void*);

extern struct node *head;
extern struct node *current;

//insertion at the beginning
void insertatbegin(void* data);
void insertatend(void* data);
void insertafternode(struct node *list, void* data);
void deleteatbegin();
void deleteatend();
void deletenode(void* key);
int  searchlist(void* key);

PFXNODELIST AllocList();
PFXNODELIST AllocNamedList(const char* name);
PFXNODELIST AllocListMax(const char* name, int maxSize);
void ListClear(PFXNODELIST list);

PFXNODE ListAddStart(PFXNODELIST list,void* data);
PFXNODE ListAddEnd(PFXNODELIST list,void* data);

PFXNODE ListRemoveEnd(PFXNODELIST list);
PFXNODE ListRemove(PFXNODELIST list,void* data);

int ListSize(PFXNODELIST list);
PFXNODE ListSearch(PFXNODELIST list,void* data);

void DeallocNode(PFXNODE node);
void DeallocList(PFXNODELIST list);

void VisitList(PFXNODELIST list, NodeVisit visit);
int VisitListCtx(PFXNODELIST list, NodeVisitCtx visit, void* ctx);

#endif