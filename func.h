#ifndef _FUNC_H_
#define _FUNC_H_
#include "list.h"
#include <inttypes.h>
#include <ctype.h>
#include <unistd.h>
#define DELIMITER "*********************"
void buff ();
short menu ();
void switchcase (short ch, List ** plist, Item * pi);
void GetItem (Item * pi); 
void show (Item item);
char * s_gets (char * st, int sz);
bool DownLoad (List ** plist, char * file_name);
bool UnLoad (List ** plist, char * file_name);
bool GetFileName (char * st, int sz);
void AddFromFile (List ** plist, Node * pnew);
#endif