#include <stdio.h>
#include <malloc.h>

#define S 25

struct student {
    char firstname[S];
    char surname[S];
    char iq[S];
    struct student* prev;
    struct student* next;
};

void show_menu () {
    printf("\n1 - add element\n");  
    printf("2 - delete element\n");  
    printf("3 - view all elements\n");  
    printf("4 - save list in the file\n");
    printf("5 - load list from the file\n");    
    printf("0 - exit\n");  
}

int is_empty (struct student* root) {

    if ((root->prev == root) && (root->next == root)) {
        return 1;
    }

    else {
        return 0;
    }

}

void view(struct student* root) {

    struct student* ptr = root->next;

    int i = 0;

    if (is_empty(root) == 1) {
        printf("List is empty");
    }

    else {

        do {

            printf("\nELEMENT #%d\n", i);

            printf("Firstname =  %s\n", ptr->firstname);
            printf("Surname =  %s\n", ptr->surname);
            printf("iq =  %s\n", ptr->iq);

            ptr = (ptr -> next);

            i++;

        }  while (ptr != root);

    }

}



void save_in_file(struct student* root) {

    FILE* f;

    struct student* ptr = root -> next;

    int i = 0;

    f = fopen("save_from_list.txt", "w");

    while(ptr != root) {

        fprintf(f, "%s\n", ptr -> firstname);
        fprintf(f, "%s\n", ptr -> surname);
        fprintf(f, "%s\n", ptr -> iq);

        ptr = ptr -> next;
    }

    fclose(f);

    printf("\nok!\n");
    

}

int symbols_in_string(char* string) {

    char symbol = 1;

    int i = 0;

    while (symbol != 0) {

        symbol = *(string + i);

        i++;

    }

    return i - 1;
}

void init_root(struct student* root) {

    (root->next) = root;

    (root->prev) = root;

}



void add_data(struct student* new_node) {
    printf("\nEnter the firstname\n");
    scanf("%s", &(new_node -> firstname));
    printf("\nEnter the surname\n");
    scanf("%s", &(new_node -> surname));
    printf("\nEnter the IQ\n");
    scanf("%s", &(new_node -> iq));
}

struct student* add_element(struct student* node1, struct student* node2) {

    struct student* new_node;

    new_node = (struct student*)malloc(sizeof(struct student));

    (node1->next) = new_node;

    (node2->prev) = new_node;

    new_node -> next = node2;

    new_node -> prev = node1;

    return new_node;

}

int serch_element(struct student* root, char* string, int symbols_in_string, char* struct_string) {

    int check = 0;

    for (int i = 0; i < symbols_in_string; i++) {

        if (string[i] == (struct_string[i])) {

            check++;

        }

        else {

            check = 0;

        }

    }

    if (check == symbols_in_string) {

        return 1;

    }

    else {

        return 0;

    }

}

void delete_element(struct student* ptr) {

    struct student* tmp;

    printf("\nElement %d has been deleted\n" , ptr);

    tmp = ptr -> next;
 
    ptr = ptr -> prev;

    free(ptr -> next);

    ptr -> next = tmp;

    tmp = ptr;

    ptr = ptr -> next;

    ptr -> prev = tmp;
    
}


void choose_delete_element(struct student* root) {

    char firstname[S];
    char surname[S];
    char iq[S];

    int key;

    struct student* ptr = root->next;
    
    printf("\n SHO UDALAT'? \n");
    printf("1 - First name \n");
    printf("2 - Surname \n");
    printf("3 - IQ \n");

    scanf("%d", &key);

    switch (key) {

    case 1:

        printf("\nEnter the firstname\n");
        scanf("%s", firstname);

        while (ptr != root) {

            if (serch_element(root, firstname, symbols_in_string(ptr->firstname), ptr->firstname) == 1) {

                delete_element(ptr);

            }

            ptr = ptr -> next;

        }

        break;

    case 2:

        printf("\nEnter the surname\n");
        scanf("%s", surname);

        while (ptr != root) {

            if (serch_element(root, surname, symbols_in_string(ptr->surname), ptr->surname) == 1) {

                delete_element(ptr);

            }

            ptr = ptr -> next;

        }

        break;

    case 3: 

        printf("\nEnter the iq\n");
        scanf("%s", iq);

        while (ptr != root) {

            if (serch_element(root, iq, symbols_in_string(ptr->iq), ptr->iq) == 1) {

                delete_element(ptr);

            }

            ptr = ptr -> next;

        }

        break;

    default:
        printf("Incorrect operation");
        break;
    }

}

int add_data_from_file(struct student* new_node, FILE* f) {

    if ( fscanf(f, "%s", new_node -> firstname) != EOF) {
        fscanf(f, "%s", new_node -> surname);
        fscanf(f, "%s", new_node -> iq);
        return 1;
    }

    else {

        printf("File is OVER!");
        delete_element(new_node);
        return 0;
        
    }

}

void delete_all_list(struct student* root) {

    struct student* ptr = root -> next;


    while (is_empty(root) != 1) {

        delete_element(ptr);

        ptr = ptr -> next;

    }

    printf("\nAll list has been deleted\n");

}


void load_from_file(FILE* f, struct student* root) {

    delete_all_list(root);

    f = fopen("load_in_list.txt", "r");

    while(add_data_from_file(add_element(root, root->next), f) != 0);

    fclose(f);
}



void main(void) {

    FILE* f;

    struct student* root;

    int key;

    root = (struct student*)malloc(sizeof(struct student));
    init_root(root);

    do {

		show_menu();

		scanf("%d", &key);

		switch (key) {

		case 1:

            add_data(add_element(root, root->next));

			break;

		case 2:
            
            if (is_empty(root) != 1) {
                choose_delete_element(root);
            }

            else {
                printf("List is empty");
            }

			break;

		case 3: 
            view(root);
			break;
		case 4:
            printf("Data has been save in the file");
            save_in_file(root);
			break;
        case 5:
            printf("Data has been loaded from the file");
            load_from_file(f, root);
            break;
        case 0:
            key = 0;
            break;

		default:
			printf("Incorrect operation");
			break;
		}

	} while (key != 0);

}

