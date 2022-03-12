// A BASELINE FOR FEATURES OF LINKED LISTS IN C LANG.

#include <stdio.h>
#include <stdlib.h>

struct n{
    int x;
    struct n * next;
};
typedef struct n node;

void print_list(node*);
node * add_new_element(node *, int); // add to end
node * add_or_insert_new_el(node *, int); // ascending sort

int main(){
    node * root; // point head of list
    root = NULL;

    // node*idx will be used to point root as index of root
    // linked lists use sequential access

    int i, new_element;
    for(i=0; i<10; i++){
        printf("enter new element: ");
        scanf("%d", &new_element);
        root = add_or_insert_new_el(root, new_element);
    }

    print_list(root);
}

void print_list(node*idx){ // send the pointer
                           // of where you want to start travel
    int i = 0;
    while(idx != NULL){ // we will travel until we reach the NULL pointer at the end
        i++;
        printf("%d. element: %d\n", i, idx -> x);
        idx = idx -> next;
    }
}


// we reach the NULL then we add new element *at the end*
node * add_new_element(node*idx, int new_element){

    if (idx == NULL){
        idx = (node*) malloc(sizeof(node));
        idx -> x = new_element;
        idx -> next = NULL;
        return idx;
    }

    // we can consider iter as i in loops
    // (use to travel to the end without changing main pointer)
    node * iter = idx; 
    while(iter -> next != NULL){
        iter = iter -> next;
    }
    
    // we create new node through next of iter (it's possible cuz we add elements to the end of list - it points null anyways)
    // we need to be careful about not losing the index of root
    iter -> next = (node*) malloc(sizeof(node));
    iter -> next -> x = new_element;
    iter -> next -> next = NULL;
    return idx;
}

node * add_or_insert_new_el(node*idx, int new_element){
    // (creating sorted linkedlist)
    // this function will be insert elements by checking whether new element is higher or lower
    // imagine that we have 3 7 2 4 as elements to add to the empty list consequitively
    // 3 will be added as root, root -> 3 -> NULL;
    // when 2 is come, 2 will point 3
    // we break root's next pointer to change it 3 to 2 | root -> 2 -> 3 -> 7
    // when 4 is come, 4 will point 7
    // we break 3's next pointer to change it to 7 to 4
    // so the latest linkedlist is root -> 2 -> 3 -> 4 -> 7

    if(idx == NULL){          // if linkedlist is empty
        idx = (node*) malloc(sizeof(node));
        idx -> x = new_element;
        idx -> next = NULL;
        return idx;
    }

    else{
        node* iter = idx;
        while(iter -> next != NULL && new_element >= iter -> next -> x)
            iter = iter -> next;
    
        // we need temporary box to not lose linkedlist at the space while changing pointers
        // we have to point the linkedlist if we break it without adding new point, we cannot reach that list again
        node * temp = (node*) malloc(sizeof(node));

        if (idx -> x > new_element){        // add element as root
            temp -> next = idx;
            temp -> x = new_element;
            return temp; // send temp as new root, it is important to update root's pointer in main
        }
        else if(iter -> next != NULL && new_element <= iter -> next -> x){     // instertion
            temp -> next = iter -> next;
            temp -> x = new_element;
            iter -> next = temp;
            return idx;
        }
        else{ // end of list
            // we have already written code to add element to the end so why we won't use it?
            idx = add_new_element(idx, new_element);
            return idx;
        }
    }
}