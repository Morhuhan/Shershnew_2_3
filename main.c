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
    printf("4 - load list in the file\n");
    printf("5 - load list from the file\n");    
    printf("0 - exit\n");  
}

// Проверяет, пуст ли список
int is_empty (struct student* root) {

    if (root == NULL) {
        return 1;
    }

    else {
        return 0;
    }

}


// Просмотреть весь список
void view(struct student* root) {

    struct student* ptr = root;

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

// Заполняет указанный элемент данными
void add_data(struct student* new_node) {
    printf("\nEnter the firstname\n");
    scanf("%s", &(new_node -> firstname));
    printf("\nEnter the surname\n");
    scanf("%s", &(new_node -> surname));
    printf("\nEnter the IQ\n");
    scanf("%s", &(new_node -> iq));
}

// Добавляет элемент в список
void add_element(struct student* node1, struct student* node2) {

    struct student* new_node;

    new_node = (struct student*)malloc(sizeof(struct student));

    (node1->next) = new_node;

    (node2->prev) = new_node;

    new_node -> next = node2;

    new_node -> prev = node1;

    add_data(new_node);

}

// Считает и возвращает колличество символов в строке
int symbols_in_string(char* string) {

    char symbol = 1;

    int i = 0;

    while (symbol != 0) {

        symbol = *(string + i);

        i++;

    }

    return i - 1;
}

// Проверяет, есть ли такой элемент в списке, у которого поле struct_string схоже с заданной string
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

// Удаляет элемент, на который указывает ptr
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

// Позволяет выбрать по какому полю структуры student произвести удаление, возвращает новый root в main если старый был удален
struct student* choose_delete_element(struct student* root) {

    char firstname[S];
    char surname[S];
    char iq[S];

    int key;
    int flag = 0;
    int root_del_flag = 0;
    struct student* old_root = root;

    struct student* ptr = root;
    
    printf("\n SHO UDALAT'? \n");
    printf("1 - First name \n");
    printf("2 - Surname \n");
    printf("3 - IQ \n");

    scanf("%d", &key);

    switch (key) {

    case 1:

        printf("\nEnter the firstname\n");
        scanf("%s", firstname);

        while (flag != 1) {

            if (serch_element(root, firstname, symbols_in_string(ptr->firstname), ptr->firstname) == 1) {

                if (ptr != root) {
                    delete_element(ptr);
                }

                else {
                    root_del_flag = 1;
                    printf("ok!");
                }

            }

            if (ptr -> next != root) {
                ptr = ptr -> next;
            }

            else {
                flag = 1;
            }

        }

        if (root_del_flag == 1) {

            ptr = root -> next;

            if (ptr -> next != ptr) {
                old_root = root;
                root = ptr;
                delete_element(old_root);
            }

            else {
                delete_element(root);
                root = NULL;
            }

        }

        break;

    case 2:

        printf("\nEnter the surname\n");
        scanf("%s", surname);

        while (flag != 1) {

            if (serch_element(root, surname, symbols_in_string(ptr->surname), ptr->surname) == 1) {

                if (ptr != root) {
                    delete_element(ptr);
                }

                else {
                    root_del_flag = 1;
                    printf("ok!");
                }

            }

            if (ptr -> next != root) {
                ptr = ptr -> next;
            }

            else {
                flag = 1;
            }

        }

        if (root_del_flag == 1) {

            ptr = root -> next;

            if (ptr -> next != ptr) {
                old_root = root;
                root = ptr;
                delete_element(old_root);
            }

            else {
                delete_element(root);
                root = NULL;
            }

        }

        break;

    case 3: 

        printf("\nEnter the iq\n");
        scanf("%s", iq);

        while (flag != 1) {

            if (serch_element(root, iq, symbols_in_string(ptr->iq), ptr->iq) == 1) {

                if (ptr != root) {
                    delete_element(ptr);
                }

                else {
                    root_del_flag = 1;
                    printf("ok!");
                }

            }

            if (ptr -> next != root) {
                ptr = ptr -> next;
            }

            else {
                flag = 1;
            }

        }

        if (root_del_flag == 1) {

            ptr = root -> next;

            if (ptr -> next != ptr) {
                old_root = root;
                root = ptr;
                delete_element(old_root);
            }

            else {
                delete_element(root);
                root = NULL;
            }

        }

        break;

    default:
        printf("Incorrect operation");
        break;
    }

    return root;

}


// Заполняет элемент данными из файла, возвращает 0 если достигнут конец файла (аналог add_data)
int add_data_from_file(struct student* new_node, FILE* f) {

    if ( fscanf(f, "%s", new_node -> firstname) != EOF) {
        fscanf(f, "%s", new_node -> surname);
        fscanf(f, "%s", new_node -> iq);
        return 1;
    }

    else {
        return 0;
    }

}

// Получает 2 указателя на элементы, создает между ними новый, заполняет его данными из файла и связывает список (аналог как add_element())
int add_element_from_file(struct student* node1, struct student* node2, FILE* f) {

    struct student* new_node;

    new_node = (struct student*)malloc(sizeof(struct student));

    if (add_data_from_file(new_node, f) == 0) {

        free(new_node);

        return 0;
    }

    else {

        (node1->next) = new_node;

        (node2->prev) = new_node;

        new_node -> next = node2;

        new_node -> prev = node1;

        return 1;

    }
}

// Загружает элементы списка в файл load_from_list.txt
void load_from_list(struct student* root) {

    FILE* f;

    struct student* ptr = root;

    f = fopen("load_from_list.txt", "w");

    while(ptr -> next != root) {

        fprintf(f, "%s\n", ptr -> firstname);
        fprintf(f, "%s\n", ptr -> surname);
        fprintf(f, "%s\n", ptr -> iq);

        ptr = ptr -> next;
    }

    fclose(f);
}


void main(void) {

    FILE* f;

    struct student* root = NULL;

    int key;
    int flag = 0;

    do {

		show_menu();

		scanf("%d", &key);

		switch (key) {

		case 1:

            if (is_empty(root) == 1) {

                root = (struct student*)malloc(sizeof(struct student));

                add_data(root);

                root -> prev = root;

                root -> next = root;

            }

            else {

                add_element(root, root -> next);

            }

			break;

        case 2: 

            if (is_empty(root) != 1) {
               root = choose_delete_element(root);
            }

            else {
                printf("List is empty");
            }

            break;

        case 3: 
            view(root);
        break;

		case 4:
            printf("\nData has been loaded from list in the file\n");
            load_from_list(root);
			break;

        case 5:

            printf("\nData has been loaded from file in the list\n");

            f = fopen("load_in_list.txt", "r");
            
            while(flag != 1) {

                if (is_empty(root) == 1) {

                    root = (struct student*)malloc(sizeof(struct student));

                    if (add_data_from_file(root, f) == 0) {
                        free(root);
                        root = NULL;
                        flag = 1;   // Проверка на то, есть ли в файле символы  
                    }

                    else {
                        root -> prev = root;
                        root -> next = root;
                    }

                }

                else {

                    if (add_element_from_file(root, root->next, f) == 0) {
                        flag = 1;
                    }

                }
            }

            flag = 0;

            fclose(f);

            break;

        case 0:
            break;

		default:
			printf("Incorrect operation");
			break;
		}

	} while (key != 0);

}