#include "list.h"
#include "func.h"

int main (void)
{   
      Item temp;
      List * phonebook; 
      InitList(&phonebook);
      bool cond;
      char FileName [MAX];
      if (GetFileName(FileName, MAX))
            cond = DownLoad(&phonebook, FileName);
      short ch;
      while ((ch = menu()) != 8)
      {
            switchcase(ch, &phonebook, &temp);
      }
      if (cond)
            UnLoad(&phonebook, FileName);
      DeleteList(&phonebook);
      puts("Programm is oveR!");
      return 0;
} 