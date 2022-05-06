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

		//show_menu();

		scanf("%d", &key);

		switch (key) {

		case 1:

            if (root == NULL) {

                root = (struct student*)malloc(sizeof(struct student));

                root -> prev = root;

                root -> next = root;

                printf("root = %d\n", root);
                printf("root -> next = %d\n", root -> next);
                printf("root -> prev = %d\n", root -> prev);

                // Заполнить значениями

            }

            else {

                root -> next = (struct student*)malloc(sizeof(struct student));

                root -> prev = root -> next;

                printf("root = %d\n", root);
                printf("root -> next = %d\n", root -> next);
                printf("root -> prev = %d\n", root -> prev);

                //add_element(root, root -> next);

            }

			break;


		default:
			printf("Incorrect operation");
			break;
		}

	} while (key != 0);

}