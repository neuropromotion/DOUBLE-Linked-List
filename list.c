#include "list.h"
static Item * error (Item * pi)
{
    fprintf(stderr, "Error! Nothing to delete, list is empty!\n"); 
    return pi;
}
static void AddItem (Item *pi, Node * pnode)
{
    strcpy(pnode->item.phone, pi->phone);
    strcpy(pnode->item.name, pi->name);
}
void InitList (List ** plist)
{
    if (ListIsFull())
        return;
    (*plist) = (List *) malloc(sizeof(List));
    (*plist)->head = (*plist)->tail = NULL;
    (*plist)->size = 0;
}
bool ListIsEmpty (List ** plist)
{
    return ((*plist)->size == 0) ? true : false;
}
bool ListIsFull ()
{
    Node * temp;
    temp = (Node *) malloc(sizeof(Node));
    if (temp == NULL)
    {
        fprintf(stderr, "Memory allocating error!\n");
        return true;
    }
    free(temp);
    return false;
}
unsigned int ListItemCount (List ** plist)
{
    return (*plist)->size;
}
bool AddToHead (Item * pi, List ** plist)
{
    Node * pnew; 
    if (ListIsFull())
        return false;
    pnew = (Node *) malloc (sizeof(Node));
    AddItem(pi, pnew);
    if (ListIsEmpty(plist))
    {
        pnew->prev = pnew->next = NULL;
        (*plist)->head = (*plist)->tail = pnew;
        (*plist)->size++; 
    } else
    {
        pnew->next = (*plist)->head;
        pnew->prev = NULL;
        (*plist)->head->prev = pnew;
        (*plist)->head = pnew; 
        (*plist)->size++;
    }
    return true;
}
bool AddToTail (Item * pi, List ** plist)
{
    Node * pnew;  
    if (ListIsFull())
        return false;
    pnew = (Node *) malloc (sizeof(Node));
    AddItem(pi, pnew);
    if (ListIsEmpty(plist))
    {
        pnew->prev = pnew->next = NULL;
        (*plist)->head = (*plist)->tail = pnew;
        (*plist)->size++;
    } else 
    {
        pnew->next = NULL;
        pnew->prev = (*plist)->tail;
        (*plist)->tail->next = pnew;
        (*plist)->tail = pnew;
        (*plist)->size++;
    }
    return true;
}
Item DeleteFromHead (List ** plist)
{
    Item temp_item;
    if (ListIsEmpty(plist))
        return *(error(&temp_item));
    Node * temp;
    temp = (*plist)->head; 
    temp_item = (*plist)->head->item; 
    (*plist)->head = (*plist)->head->next; 
    (*plist)->head->prev = NULL; 
    free(temp); 
    (*plist)->size--;
    return temp_item;
}
Item DeleteFromTail (List ** plist)
{
    Item temp_item;
    if (ListIsEmpty(plist))
        return *(error(&temp_item));
    Node * temp;
    temp = (*plist)->tail;
    temp_item = (*plist)->tail->item;
    (*plist)->tail = (*plist)->tail->prev;
    (*plist)->tail->next = NULL;
    free(temp);
    (*plist)->size--;
    return temp_item;
}
void DeleteList (List ** plist)
{
    unsigned int sz = (*plist)->size;
    unsigned int ctr = 0;
    Node * temp;
    while (ctr < sz)
    {
        temp = (*plist)->head;
        (*plist)->head = (*plist)->head->next;
        free(temp);
    }
}


void Traverse (List ** plist, void (*pfun)(Item item), int status)
{
    unsigned int ctr = ListItemCount(plist);
    unsigned int counter = 0;
    if (status == 0)
    {
        Node * trav = (*plist)->head;
        while (counter < ctr)
        {
            pfun(trav->item);
            trav = trav->next;
            counter++;
        }
    } else
    {
        Node * trav = (*plist)->tail;
        while (counter < ctr)
        {
            pfun(trav->item);
            trav = trav->prev;
            counter++;
        }
    }
}