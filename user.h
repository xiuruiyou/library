#ifndef CWK1_USER_H
#define CWK1_USER_H

typedef struct _User
{
    char username[50];
    char password[50];
    struct _User *next1;
}user, *linklist1;


void login(linklist1 head);
void regi(linklist1 head);
void output_user(linklist1 head);
void user_page(char *uuu);
void librarian_page();

void borrow_book(char *uuu);


#endif //CWK1_USER_H
