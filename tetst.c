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

struct student* init_first_element(struct student* root) {

struct student* ptr;

ptr = (struct student*)malloc(sizeof(struct student));

root = ptr;

ptr -> next = ptr;

ptr -> prev = ptr;

}

void main(void) {

    FILE* f;

    struct student* root = NULL;

    int key;

    do {

		show_menu();

		scanf("%d", &key);

		switch (key) {

		case 1:

            if ( root == NULL) {

               root = init_first_element(root);

            }

            else {

                add_element(root, root -> next);

            }

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