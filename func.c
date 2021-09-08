#include "list.h"
#include "func.h"


short menu ()
{
    short ch;
    char temp [MAX];
    puts(DELIMITER);
    puts("1) Add name in front              2) Add name in back");
    puts("3) Delete name from front         4) Delete name from back");
    puts("5) Show list from front to back   6)Show list from back to front");
    puts("7) Show quantity of names         8) Exit");
    puts(DELIMITER);
    printf("Choose appripriate number: ");
    while (fgets(temp, MAX, stdin) != NULL)
    {
        if (strlen(temp) > 2)
        {
            puts("Incorrect data! Try again!");
            continue;
        }
        ch = atoi(temp);
        if ((ch < 9) && (ch > 0))
            break;
        puts("Incorrect data! Try again!");
    }
    return ch;
}
void buff ()
{
    while(getchar() != '\n')
        continue;
}

void switchcase (short ch, List ** plist, Item * pi)
{
    Item * temp;
    switch(ch)
    {
        case 1:
            GetItem(pi);
            AddToHead(pi, plist);
            break;
        case 2: 
            GetItem(pi);
            AddToTail(pi, plist);
            break;
        case 3: 
            printf("[%s] was deleted from list!\n", DeleteFromHead(plist).name);
            break;
        case 4:
            printf("[%s] was deleted from list!\n", DeleteFromTail(plist).name);
            sleep(2);
            break;
        case 5:
            if (ListIsEmpty(plist))
            {
                puts("List is Empty. Nothing to display!");
                sleep(2);
            }else
            {
                Traverse(plist, show, 0);
                sleep(2);
            } 
            break;
        case 6:
            if (ListIsEmpty(plist))
            {
                puts("List is Empty. Nothing to display!");
                sleep(2);
            }else
            {
                Traverse(plist, show, 1);
                sleep(2);
            } 
            break;
        case 7:
            printf("Quantity of names in list: %u\n", ListItemCount(plist));
            sleep(2);
            break;
        case 8:
            return;
    }
}
void GetItem (Item * pi)
{
    puts("Enter name:");
    strcpy(pi->name, s_gets(pi->name, MAX));
    puts("Enter phone number:");
    strcpy(pi->phone, s_gets(pi->phone, MAX)); 
}

void show (Item item)
{
      printf("Name: [%s], Phone: [%s]\n", item.name, item.phone); 
}

char * s_gets (char * st, int sz)
{
    char * ret_val;
    char * find;
    ret_val = fgets(st, sz, stdin);
    if (ret_val)
    {
        find = strchr(st, '\n');
        if (find)
        {
            *find = '\0';
        }
    }
    return ret_val;
}

bool DownLoad (List ** plist, char * file_name)
{
    uint32_t size = 0;
    uint32_t ctr = 0;
    FILE * fptr;
    Node * temp;
    if ((fptr = fopen(file_name, "rb")) == NULL)
    {
        fprintf(stderr, "ERROR: File did not open!\n");
        return false;
    }
    fread(&size, sizeof(uint32_t), 1, fptr);
    while (ctr < size)
    {
        if(ListIsFull())
        {
            fprintf(stderr, "ERROR: Downloading from file crashed");
            return false;
        }
        temp = (Node*)malloc(sizeof(Node));
        fread(temp, sizeof(Node), 1, fptr);
        puts("ERR");
        AddFromFile(plist, temp);
        ctr++;
    }
    fclose(fptr);
    return true;
}
bool UnLoad (List ** plist, char * file_name)
{
    uint32_t size = ListItemCount(plist);
    uint32_t ctr = 0;
    Node * temp = (*plist)->head;
    FILE * ptr;
    if ((ptr = fopen(file_name, "wb")) == NULL)
    {
        fprintf(stderr, "ERROR: Downloading from file crashed");
        return false;
    } else
    {
        fwrite (&size, sizeof(uint32_t), 1, ptr);
        while (ctr < size)
        {
            fwrite(temp, sizeof(Node), 1, ptr);
            temp = temp->next;
            ctr++;
        }
    }
    fclose(ptr);
    return true;
}
bool GetFileName (char * st, int sz)
{
    puts("If you want to download data from file, enter file's name or empty string otherwise");
    s_gets(st, sz);
    if (st[0] == '\0')
        return false;
    return true;
}



void AddFromFile (List ** plist, Node * pnew)
{
    if (ListIsEmpty(plist))
    {
        pnew->next = pnew->prev = NULL;
        (*plist)->head = (*plist)->tail = pnew;
        (*plist)->size++;
    } else
    {
        pnew->prev = (*plist)->tail;
        pnew->next = NULL;
        (*plist)->tail->next = pnew;
        (*plist)->tail = pnew;
        (*plist)->size++;
    }
}