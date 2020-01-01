#pragma once
#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include"headers.h"

typedef struct node ListNode;
typedef ListNode * LinkList;
void InitList(LinkList &L);
void DestroyList(LinkList &L);
int ListLength(LinkList L);
bool GetElem(LinkList L, int i, ElemType &e);
int LocateElem(LinkList L, ElemType e, bool(*compare)(ElemType, ElemType));
bool PriorElem(LinkList L, ElemType cur_e, ElemType &pre_e);
void ListTraverse(LinkList L,bool(*visit)(LinkList));
bool ListInsert(LinkList &L, int i, ElemType e);
bool compare(ElemType a, ElemType b);
bool visit(LinkList e);
bool ListDelete(LinkList &L, int i, ElemType &e);

#endif // DECLARATION_H_INCLUDED