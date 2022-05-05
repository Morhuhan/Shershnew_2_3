#include <stdio.h>
#include <malloc.h>

struct student {
    char firstname[S];
    char surname[S];
    char iq[S];
    struct student* prev;
    struct student* next;
};

struct student* add_element(struct student* node1, struct student* node2) {

    struct student* new_node;

    new_node = (struct student*)malloc(sizeof(struct student));

    (node1->next) = new_node;

    (node2->prev) = new_node;

    new_node -> next = node2;

    new_node -> prev = node1;

    return new_node;

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

                root = add_element();

                init_first_element(root);

            }

            else {

                add_element(find_last_element());

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
