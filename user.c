#include "user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "do_book.c"



void output_user(linklist1 head) //Put the user's account number and password into the file
{
    linklist1 p=head->next1;
    FILE *fp = fopen(RECORD_FILE, "w");
    if(fp==NULL)
    {
        printf("Can not open the file.\n");
        exit(0);
    }
    while (p)
    {
        fprintf(fp, "%s %s\n", p->username, p->password);
        p=p->next1;
    }
    fclose(fp);
}

void regi(linklist1 head) //User Registration (linked list)
{
    linklist1 last = head, p;
    int check = 0;//Check whether the username is duplicated.
    p=(linklist1) malloc(sizeof(user));
    printf("Please enter a username:");
    scanf("%s", p->username);
    getchar();
    while (last->next1)
    {
        last=last->next1;
        if(strcmp(last->username, p->username) == 0)
        {
            printf("Sorry, registration unsuccessful, the username you entered already exists.\n");
            check = 1;
            break;
        }
    }
    if(check == 0)
    {
        printf("Please enter a password:");
        scanf("%s", p->password);
        getchar();
        p->next1 = last->next1;
        last->next1 = p;
        printf("Registered library account successfully!\n");
    }
}

void login(linklist1 head) //User login.
{
    linklist1 last = head, p;
    int check = 0;
    char a[20] = "librarian";//Enter the librarian identification.
    p=(linklist1) malloc(sizeof(user));
    printf("Please enter a username:");
    scanf("%s", p->username);
    char USER[100];
    getchar();
    while (last->next1)
    {
        last = last->next1;
        if(strcmp(last->username, p->username) == 0)
        {
            strcpy(USER, p->username);
            check = 1;
            break;
        }
    }
    if(check==0)
    {
        printf("The user does not exist.\n");
    } else{
        printf("Please enter a password:");
        scanf("%s", p->password);
        getchar();
        if((strcmp(last->password, p->password) == 0) && (strcmp(last->password, a) == 0))
        {
            printf("\n(logged in as: librarian)");
            librarian_page();
        }
        else if(strcmp(last->password, p->password) == 0){
            printf("\n(logged in as: %s)", last->username);
            user_page(USER);
        } else{
            printf("Password is wrong.\n");
        }
    }
}

void librarian_page()//Enter the librarian page, librarian can add the book and remove the book.
{
    FILE *fp;
    char buf[100];
    linklist head, p2, last;
    head = (linklist) malloc(sizeof(Book));
    head->next = NULL;
    last = head;
    if((fp = fopen(RECORD_FILE2, "r")) == NULL)
    {
        printf("Can not open the file.\n");
        exit(0);
    }
    while (1)
    {
        p2 = (linklist) malloc(sizeof(Book));
        p2->authors=(char*)malloc(100*sizeof(char));
        p2->title=(char*)malloc(100*sizeof(char));
        fgets(buf, MAX, fp);
        sscanf(buf, "%d\n", &p2->id);
        fgets(buf, MAX, fp);
        sscanf(buf, "%[^\n]s\n", p2->title);
        fgets(buf, MAX, fp);
        sscanf(buf, "%[^\n]s\n", p2->authors);
        fgets(buf, MAX, fp);
        sscanf(buf, "%d\n", &p2->year);
        fgets(buf, MAX, fp);
        sscanf(buf, "%d\n", &p2->copies);
        if(feof(fp))
        {
            break;
        }
        last->next = p2;
        last = p2;
    }
    last->next = NULL;
    fclose(fp);

    int option;
    int userOpen = 1;
    while (userOpen)
    {
        printf("\n Please choose an option:\n 1) Add a book\n 2) Remove a book\n 3) Search for books\n 4) Display all books\n 5) Log out\n   Option: ");
        option = optionChoice();
        if(option == 1)
        {
//            load_books(RECORD_FILE2);
            add_book(head);
            store_books(RECORD_FILE2, head);
        }
        else if(option == 2)
        {
//            load_books(RECORD_FILE2);
            remove_book(head);
            store_books(RECORD_FILE2, head);
        }
        else if(option == 3)
        {
            search();
        }
        else if(option == 4)
        {
            load_books(RECORD_FILE2);
        }
        else if(option == 5){
            break;
        } else{
            printf("Error enter.\n");
        }
    }
}


void user_page(char *uuu)//Enter the user page, users can borrow the book and remove the book.
{
    char USER[100];
    strcpy(USER, uuu);
    strcat(USER, ".txt");
    printf("%s\n", USER);

    FILE *fp;
    char buf[100];
    linklist head, p2, last;
    head = (linklist) malloc(sizeof(Book));
    head->next = NULL;
    last = head;
    if((fp = fopen(USER, "r")) == NULL)
    {
        printf("Can not open the file.\n");
        exit(0);
    }
    while (1)
    {
        p2 = (linklist) malloc(sizeof(Book));
        p2->authors=(char*)malloc(100*sizeof(char));
        p2->title=(char*)malloc(100*sizeof(char));
        fgets(buf, MAX, fp);
        sscanf(buf, "%d\n", &p2->id);
        fgets(buf, MAX, fp);
        sscanf(buf, "%[^\n]s\n", p2->title);
        fgets(buf, MAX, fp);
        sscanf(buf, "%[^\n]s\n", p2->authors);
        fgets(buf, MAX, fp);
        sscanf(buf, "%d\n", &p2->year);
        if(feof(fp))
        {
            break;
        }
        last->next = p2;
        last = p2;
    }
    last->next = NULL;
    fclose(fp);

    int option;
    int userOpen = 1;

    while (userOpen){
        printf("\n Please choose an option:\n 1) Borrow a book\n 2) Return a book\n 3) Search for books\n 4) Display all books\n 5) Log out\n   Option: ");
        option = optionChoice();
        if(option == 1)
        {
            borrow_book(USER);
//            store_books(RECORD_FILE2, head);
        }
        else if(option == 2){
            load(USER);
            return_book(USER, head);
            store(USER, head);
        }
        else if(option == 3){
            search();
        }
        else if(option == 4){
            load_books(RECORD_FILE2);
        }
        else if(option == 5){
            break;
        } else{
            printf("Error enter.\n");
        }
    }
}

//-------------------------------------------------


