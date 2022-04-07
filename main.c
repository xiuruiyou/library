#include <stdio.h>
#include <stdlib.h>
#include "user.h"
#include "user.c"



int main(int argc, char **argv)
{
//    if(argc != 3){
//        printf("Error.\n");
//        exit(0);
//    } else{
//        char user_file[100];
//        char book_file[100];
//        strcpy(book_file, argv[1]);
//        strcpy(user_file, argv[2]);
//    }

    int libraryOpen = 1;
    int option;
    FILE *fp;
    linklist1 head, p2, last;
    head = (linklist1) malloc(sizeof(user));
    head->next1 = NULL;
//    last = (linklist1) malloc(sizeof(user));
    last = head;
    if((fp = fopen(RECORD_FILE, "r")) == NULL)
    {
        printf("Can not open the file.\n");
        exit(0);
    }
    while (1)
    {
        p2 = (linklist1) malloc(sizeof(user));
        fscanf(fp, "%s %s", p2->username, p2->password);
        if(feof(fp))
        {
            break;
        }
        last->next1 = p2;
        last = p2;
    }
    last->next1 = NULL;
    fclose(fp);


    //The system main page is displayed.
    while( libraryOpen )
    {
        printf("\n Please choose an option:\n 1) Register an account\n 2) Login\n 3) Search for books\n 4) Display all books\n 5) Quit\n   Option: ");
        option = optionChoice();
        //User registration.
        if( option == 1 )
        {
            regi(head);
            output_user(head);
        }
        //A user logs in to the system page of the user.
        else if( option == 2 )
        {
            login(head);
        }
        //Search for books.
        else if( option == 3 )
        {
            printf("You have to register or log in to use this function.\n");
        }
        //show all books.
        else if( option == 4 )
        {
            load_books(RECORD_FILE2);
        }
        //Exit the program.
        else if( option == 5 )
        {
            libraryOpen = 0;
            printf("\nClosing\n");
            exit(0);
        }
        else
            printf("\nSorry, the option you entered was invalid, please try again.\n");
    }
//    if(ret != 0){
//        return ret;
//    }
//    ret = load_books(RECORD_FILE2);
//    return ret;
}




