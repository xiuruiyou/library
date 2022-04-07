#include "book_management.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "option.c"
#include "user.h"
#define MAX 128
#define RECORD_FILE "user.txt"
#define RECORD_FILE2 "books.txt"

int load_books(FILE* file)//load the information about the file of books, it can also display all books.
{
    FILE *fp;
    char buf[100];
    linklist head, p2, last;
    head = (linklist) malloc(sizeof(Book));
    head->next = NULL;
    last = head;
    if((fp = fopen(file, "r")) == NULL){
        printf("Can not open the file.\n");
        return -1;
    }
    printf("Id      Title                     Authors              year       copies\n");
    while (1){
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
        if(feof(fp)){
            break;
        }
        printf(" %-7d %-25s %-20s %-10d %-6d\n", p2->id, p2->title, p2->authors, p2->year, p2->copies);
        last->next = p2;
        last = p2;
    }
    last->next = NULL;
    fclose(fp);
    return 0;
}

int load(FILE* file)//load the information about the file of books, it can also display all books.
{
    FILE *fp;
    char buf[100];
    linklist head, p2, last;
    head = (linklist) malloc(sizeof(Book));
    head->next = NULL;
    last = head;
    if((fp = fopen(file, "r")) == NULL){
        printf("Can not open the file.\n");
        return -1;
    }
    printf("Id      Title                     Authors              year\n");
    while (1){
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
        if(feof(fp)){
            break;
        }
        printf(" %-7d %-25s %-20s %-10d\n", p2->id, p2->title, p2->authors, p2->year);
        last->next = p2;
        last = p2;
    }
    last->next = NULL;
    fclose(fp);
    return 0;
}

int store_books(FILE *file, linklist head)//After operation the linked list of the book, store the information
{
    linklist p = head->next;
    FILE *fp;
    fp = fopen(file, "w");
    if(fp == NULL){
        printf("Can not open the file.\n");
        return -1;
    }
    while (p){
        fprintf(fp,"%d\n%s\n%s\n%d\n%d\n", p->id, p->title, p->authors, p->year, p->copies);
        p = p->next;
    }
    fclose(fp);
    return 0;
}

int store(FILE *file, linklist head)//After operation the linked list of the book, store the information
{
    linklist p = head->next;
    FILE *fp;
    fp = fopen(file, "w");
    if(fp == NULL){
        printf("Can not open the file.\n");
        return -1;
    }
    while (p){
        fprintf(fp,"%d\n%s\n%s\n%d\n", p->id, p->title, p->authors, p->year);
        p = p->next;
    }
    fclose(fp);
    return 0;
}


int add_book(linklist head)//Add the book(only librarian).
{
    printf("Please the information about the book which you want to add.\n");
    printf("Please enter the id, title, authors, year and copies:\n");
    linklist last = head, p;
    int n = 0;
    p = (linklist) malloc(sizeof(Book));
    p->authors=(char*)malloc(100*sizeof(char));
    p->title=(char*)malloc(100*sizeof(char));
    printf("Please enter the id:\n");
    scanf("%d", &p->id);
    printf("Please enter the title:\n");
    scanf("%s", p->title);
    printf("Please enter the author:\n");
    scanf("%s", p->authors);
    printf("Please enter the year:\n");
    scanf("%d", &p->year);
    printf("Please enter the copies:\n");
    scanf("%d", &p->copies);
    getchar();
    while (last->next){
        last = last->next;
        if(last->id == p->id){
            printf("The book already exists.\n");
            n = 1;
            break;
        }
    }
    if(n == 0){
        p->next = last->next;
        last->next = p;
        printf("Book was successfully added!\n");
    }
    return 0;
}

int remove_book(linklist head)
{
    linklist p = head->next ,last = head ,q=head;
    unsigned int ID;
    int n=0;
    printf("Please enter the ID to remove the book:\n");
    scanf("%d",&ID);
    getchar();
    while(q)
    {
        if(q->id == ID)
        {
            n=1;
            break;
        }
        q=q->next;
    }
    if(n==0)
    {
        printf("\n");
        printf("No result\n");
    }
    else
    {
        while(p)
        {
            if(p->id == ID)
            {
                last->next = p->next;
                free(p);
            }
            else
            {
                last=p;
                p=p->next;
            }
        }
        printf("\n");
    }
    return 0;
}

void return_book(char *uuu, linklist head)
{
    linklist p = head->next ,last = head ,q=head;
    unsigned int ID;

    char USER[100];
    strcpy(USER, uuu);

    int n=0;
    printf("Please enter the ID to return the book:\n");
    scanf("%d",&ID);
    getchar();
    while(q)
    {
        if(q->id == ID)
        {
            n=1;
            break;
        }
        q=q->next;
    }
    if(n==0)
    {
        printf("\n");
        printf("No result\n");
    }
    else
    {
        while(p)
        {
            if(p->id == ID)
            {
                last->next = p->next;
                free(p);
            }
            else
            {
                last=p;
                p=p->next;
            }
        }
        printf("\n");
    }

    FILE *fp;
    char buf[100];
    linklist a2, p2, z2;
    a2 = (linklist) malloc(sizeof(Book));
    a2->next = NULL;
    z2 = a2;
    int cc;
    if((fp = fopen(RECORD_FILE2, "r")) == NULL){
        printf("Can not open the file.\n");
        exit(0);
    }
    while (1){
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
        if(ID == p2->id){
            printf("Returning successful!\n");
            cc = p2->copies + 1;
            p2->copies = cc;
        }
        if(feof(fp)){
            break;
        }
        z2->next = p2;
        z2 = p2;
    }
    store_books(RECORD_FILE2, a2);
    z2->next = NULL;
    fclose(fp);
}

void borrow_book(char *uuu)
{
    printf("Enter the id of the book you want to borrow:\n");
    unsigned int id;
    scanf("%d", &id);
    getchar();
    char USER[100];
    strcpy(USER, uuu);
//    strcat(USER, ".txt");

    char buf1[100];
    int check = 0;
    int check1 = 0;
    linklist a, p, z;//user linklist
    a = (linklist) malloc(sizeof(Book));
    a->next = NULL;
    z = a;
    FILE *f = fopen(USER, "a+");
    if(f == NULL){
        printf("Can't open the file.\n");
        exit(0);
    }
    while (1){
        p = (linklist) malloc(sizeof(Book));
        p->authors=(char*)malloc(100*sizeof(char));
        p->title=(char*)malloc(100*sizeof(char));
        fgets(buf1, MAX, f);
        sscanf(buf1, "%d\n", &p->id);
        fgets(buf1, MAX, f);
        sscanf(buf1, "%[^\n]s\n", p->title);
        fgets(buf1, MAX, f);
        sscanf(buf1, "%[^\n]s\n", p->authors);
        fgets(buf1, MAX, f);
        sscanf(buf1, "%d\n", &p->year);
        if(id == p->id){
            check = 1;
            printf("You have already borrowed this book!\n");
        }
        if(feof(f)){
            break;
        }
        z->next = p;
        z = p;
    }
    z->next = NULL;
    //---------------
    FILE *fp;
    char buf[100];
    linklist head, p2, last;
    head = (linklist) malloc(sizeof(Book));
    head->next = NULL;
    last = head;
    int cc;
    if((fp = fopen(RECORD_FILE2, "r")) == NULL){
        printf("Can not open the file.\n");
        exit(0);
    }
    while (1){
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
        if((id == p2->id) && (check == 0) &&(p2->copies > 0)){
            fprintf(f,"%d\n%s\n%s\n%d\n", p2->id, p2->title, p2->authors, p2->year);
            printf("Borrowing successful!\n");
            check1 = 1;
            cc = p2->copies - 1;
            p2->copies = cc;
            fclose(f);
        }
        if(feof(fp)){
            break;
        }
        last->next = p2;
        last = p2;
    }
    store_books(RECORD_FILE2, head);
    if(check1 == 0){
        printf("Borrowing failure.\n");
    }
    last->next = NULL;
    fclose(fp);
}

void search()//The search page, you can search the book through one of the three attributes.
{
    //for find
    char TITLE[100];
    char AUTHOR[100];
    unsigned int YEAR;

    char buf[100];
    FILE *fp;
    linklist head, p2, last;
    head = (linklist) malloc(sizeof(Book));
    head->next = NULL;
    last = head;
    if ((fp = fopen(RECORD_FILE2, "r")) == NULL) {
        printf("Can not open the file.\n");
        exit(0);
    }
    while (1) {
        p2 = (linklist) malloc(sizeof(Book));
        p2->authors = (char *) malloc(100 * sizeof(char));
        p2->title = (char *) malloc(100 * sizeof(char));
        fgets(buf, MAX, fp);
        sscanf(buf, "%d\n", &p2->id);
        fgets(buf, MAX, fp);
        sscanf(buf, "%[^\n]s\n", p2->title);
//        printf("%s\n", p2->title);
        fgets(buf, MAX, fp);
        sscanf(buf, "%[^\n]s\n", p2->authors);
        fgets(buf, MAX, fp);
        sscanf(buf, "%d\n", &p2->year);
        fgets(buf, MAX, fp);
        sscanf(buf, "%d\n", &p2->copies);
        if (feof(fp)) {
            break;
        }
        last->next = p2;
        last = p2;
    }
    last->next = NULL;
    fclose(fp);

    int option;
    int libraryOpen = 1;
    printf("\nLoading search menu...\n");
    while (libraryOpen){
        printf("\nPlease choose an option:\n");
        printf("1) Find books by title\n");
        printf("2) Find books by author\n");
        printf("3) Find books by year\n");
        printf("4) Return to previous menu\n");
        printf("Option: ");
        option = optionChoice();
        if(option == 1)//Search the book by title.
        {
            printf("Please enter title:");
            scanf("%[^\n]s", TITLE);
            find_book_by_title(TITLE, head);
        }
        else if(option == 2)//Search the book by author.
        {
            printf("Please enter author:");
            scanf("%[^\n]s", AUTHOR);
            find_book_by_author(AUTHOR, head);
        }
        else if(option == 3)//Search the book by author.
        {
            printf("Please enter year:");
            scanf("%d", &YEAR);
            find_book_by_year(YEAR, head);
        }
        else if(option == 4)
        {
            break;
        } else
        {
            printf("Invalid inputs.\n");
        }
    }
}

BookList find_book_by_title (const char *title, linklist head)//Search the book by title.
{
    linklist p = head;
    BookList list1;
    int n = 0;
    getchar();
    while (p)
    {
//        printf("%s %s\n", p->title, title);
        if(strcmp(p->title, title) == 0)
        {
            n = 1;
            break;
        }
        p = p->next;
    }
    if(n == 0)
    {
        printf("No result.\n");
    } else{
        printf("Id      Title                     Authors              year       copies\n");
        n = 0;
        while (p)
        {
            if(strcmp(p->title, title) == 0){
                printf(" %-7d %-25s %-20s %-10d %-6d\n", p->id, p->title, p->authors, p->year, p->copies);
                n += 1;
            }
            p = p->next;
        }
    }
    list1.length = n;
    list1.list->title = title;
    return list1;
}

BookList find_book_by_author (const char *author, linklist head)//Search the book by author.
{
    linklist p = head;
    BookList list1;
    int n = 0;
    getchar();
    while (p->next!=NULL){
        p = p->next;
//        printf("%s %s\n", p->authors, author);
        if(strcmp(p->authors, author) == 0)
        {
            n = 1;
            break;
        }
    }
    if(n == 0)
    {
        printf("No result.\n");
    } else{
        printf("Id      Title                     Authors              year       copies\n");
        n = 0;
        while (p)
        {
            if(strcmp(p->authors, author) == 0){
                printf(" %-7d %-25s %-20s %-10d %-6d\n", p->id, p->title, p->authors, p->year, p->copies);
                n += 1;
            }
            p = p->next;
        }
    }
    list1.length = n;
    list1.list->authors = author;
    return list1;
}

BookList find_book_by_year (unsigned int year, linklist head)//Search the book by year.
{
    linklist p = head;
    BookList list1;
    int n = 0;
    getchar();
    while (p->next!=NULL)
    {
        p = p->next;
        if(p->year == year){
            n = 1;
            break;
        }
    }
    if(n == 0)
    {
        printf("No result.\n");
    } else{
        printf("Id      Title                     Authors              year       copies\n");
        n = 0;
        while (p)
        {
            if(p->year == year){
                printf(" %-7d %-25s %-20s %-10d %-6d\n", p->id, p->title, p->authors, p->year, p->copies);
                n += 1;
            }
            p = p->next;
        }
    }
    list1.length = n;
    list1.list->year = year;
    return list1;
}
