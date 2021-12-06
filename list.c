#include<stdlib.h>
#include<stdio.h>
//#include"list.h"

typedef struct Node{
    int value;
    struct Node * next;
} Node;

typedef struct List{
    Node * head;
} List;

// create and returns instance of List
List * create_list(void){
    List * list = malloc(sizeof(List));         //allocate memory to a newly created list
    if(list == NULL){                           //allocation error check
        exit(1);
    }
    list->head = NULL;                          //assign NULL to the head node
    return list;
}

// releases all memory used by list, list is set to NULL
void destroy_list(List ** list){
    List * current = *list;                         //create an auxiliary 'current' list and assign  the values of 'list' dereferenced to it
    while(current->head != NULL){                   //iterate through the whole list
        Node * buffer = current->head;              //create an auxiliary node to store the current 'head' value
        current->head = current->head->next;        //change the 'head' pointer to the following node
        free(buffer);                               //free the memory of the current 'head' node contained by the buffer
    }
    List * buffer = *list;                          //setting list to null and deallocating memory
    *list = NULL;
    free(buffer);                                    
}

// return amount of elements in list
int count_elements(List * list){
    if(list->head == NULL){                     //case if the list is empty
        return 0;
    }else{
        int i=1;                                //create a counter varialbe
        Node * current = list->head;
        while(current->next != NULL){           //a while loop iterating untill the 'next' value of the last node is null
            current = current->next;            //go to the next node
            i++;                                //increment the counter variable
        }
        return i;                               //return the counter value
    }
}

// append element to list at the end
void append_to_list(List * list, int elem){
    if(list == NULL){                           //check if the list exists
        printf("The list doesn't exist!\n");
        exit(2);
    }
    Node * new_element = malloc(sizeof(Node));  //allocate memory to a new element
    if(new_element == NULL){                    //allocation error check
        exit(3);
    }

    new_element->next = NULL;                   //assign values to the new node
    new_element->value = elem;

    if(list->head == NULL){                     //if the list is empty - make 'elem' the first element
        list->head = new_element;
        return;
    }

    Node * current = list->head;                //iterate to get to the last element of the list
    while(current->next != NULL){               
        current = current->next;
    }
    current->next = new_element;                //insert the new node at the end of the list
}

// elements are indexed from 0
int get_nth_element(List * list, int index){
    if(list->head == NULL){                     //check if the list is empty
        printf("Error: the list is empty!\n");
        exit(4); 
    }
    Node * current = list->head;                //create an auxiliary 'current' node for iteration purposes
    for(int i = 0; i < index; i++){             //iterate until the 'index' value is met
        if(current->next == NULL){
            printf("Error: the value of index is too high!\n");     //error check (if 'index' is too high)
            exit(5);
        }
        current = current->next;                //go to another 'current' node
    }   
    return current->value;                      //when the loop is finished, return the value of the nth element
}

// remove nth element - indexed from 0
void remove_nth_element(List * list, int index){
    if(list->head == NULL){                                 //error check if the list is empty
        printf("Error: the list is empty!\n");
        exit(6);
    }
    if(index == 0){                                         //case for removal of the first (head) node
        Node * aux = list->head;
        list->head = list->head->next;
        free(aux);
    }else{
        Node * current = list->head;                        //creating an auxiliary node
        for(int i = 0; i <= index; i++){                    //iterating through the list to get to the indexed node
            if(index == (i+1) && current->next != NULL){    //index needs to be equal to i+1, since we're removing the 'next' node
                Node * to_remove = current->next;           //create an auxiliary 'to_remove' node
                current->next = current->next->next;        //change the pointer to the following node
                free(to_remove);                            //free the memory of removed node
                return;
            }else if(current->next == NULL){		        //action if it's the last node of the list
                free(current);
                return;
            }
        current = current->next;			                //iterate through the list
        if(current->next == NULL){			                //case if there's no such a high index
                printf("Error: index too high!\n");
                return;
            }
        }
    }    
}

// clear list - remove all elements
void clear_list(List * list){
    List * current = list;                                  //creating an auxiliary node
    while(current->head != NULL){                           
        Node * buffer = current->head;                      //creating a buffer for a node to be removed
        current->head = current->head->next;                //change head pointer to the next node
        free(buffer);                                       //deallocate memory from the buffer node
    }
    list->head = NULL;                                      //when the loop is finished, set head pointer value to NULL
}

// insert element to list at specified index,
// indexed from 0, elements are shifted
void insert_to_list(List * list, int elem, int index){
    Node * current = list->head;                //create an auxiliaty 'current' node
    Node * previous = current;                  //create another auxiliaty node to store the pointer to the previous node
    Node * new_node = malloc(sizeof(Node));     //create a new node and allocate memory to it
    if(new_node == NULL){                       //allocation error check    
        exit(7);
    }
    new_node->value = elem;                     //assign value to the new node 'value' variable
    
    if(index == 0){                             //case if index points to the first element of the lsit
        new_node->next = list->head;
        list->head = new_node;

    }else{

    for(int i=0; i<index; i++){                 //iterate over the list with a 'for' loop to get to the indexed node
        if(current == NULL){                    //each iteration checks if the 'current' node is set to NULL, if it is, the index is too high
            printf("Index too high!\n");
            exit(8);
        }
        previous = current;                     //store the 'current' node in a 'previous' node
        current = current->next;                //current gets the 'current->next' value
    }                                           //at this point: ...|previous| -> |current|... the new_node needs to be positioned in between
    new_node->next = current;                   //we need: ...|previous| -> |new_node| -> |current|...
    previous->next = new_node;                  //repositioning the nodes
    }
}

// sort elements in list
//bubble sort by changing values inside nodes
void sort_list(List * list){
    if(list->head == NULL){         //check if the list is empty
        return;
    }
    int buffer;                     //create a buffer variable
    int p = 1;                      //create a variable to check if the list is already sorted
    /*nested loop to iterate through the list and check if the value of a variable 
    inside the current node is greater than the value of a variable inside the next node*/
    for(Node * current_i = list->head; current_i != NULL; current_i = current_i->next){             
        for(Node * current_j = current_i->next; current_j != NULL; current_j = current_j->next){     
            if(current_j->value < current_i->value){            //check if current value is greater than next value
                buffer = current_j->value;                      //create a buffer variable to store the value of the variable contained by the current node
                current_j->value = current_i->value;            //switch the variables inside current and next nodes
                current_i->value = buffer;                      //get the value form buffer and assign it to the current node
                p=0;                                            //if the swap occured, change the 'p' variable to 0
            }
        }
        if(p==1){                                               //if 'p' remains unchanged - the list is already sorted
            break;
        }
    }
}

// reverse list
void reverse_list(List * list){
    Node * buffer = NULL;               //buffer for injecting every next node at the beginning
    Node * current = list->head;
    while(current != NULL){
        Node * forward = current->next; //stores 'current' without the first element
        current->next = buffer;         //on first iteration - current (first node) becomes the last node, each iteration will inject nodes at the beginning
        buffer = current;               //and store the outcome in the buffer
        current = forward;              //current now contains only unreversed nodes
    }
    list->head = buffer;                //change the list head pointer to the first node of buffer
}