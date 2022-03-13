// A BASELINE FOR FEATURES OF LINKED LISTS IN C LANG.

#include <stdio.h>
#include <stdlib.h>

struct n{
    int x;
    struct n * next;
};
typedef struct n node;

// normal linked list which ends with the null
void print(node *); // display the list elements
node * add(node *, int); // adding to the end without sorting
node * insert(node *, int); // adding with ascending sort
node * delete(node *, int);   // deleting an element from linked list


int main(){
    node * root; // pointer for holding the head of list
    root = NULL;

    // node*idx will be used to point root, can be considered as [index] of root
    // linked lists use sequential access

    int i, new_element;
    root = delete(root, 1);
    for(i=0; i<4; i++){
        printf("enter new element: ");
        scanf("%d", &new_element);
        root = insert(root, new_element);
    }
    print(root);

    root = delete(root, 3);
    root = delete(root, 7);
    root = delete(root, 2);
    root = delete(root, 5);

    print(root);
}

void print(node*idx){
    int i = 0;
    while(idx != NULL){ // we will travel until we reach the NULL at the end
        i++;
        printf("%d. element: %d\n", i, idx -> x);
        idx = idx -> next;
    }
}


// after we reach the NULL, we add the new element *at the end*
node * add(node*idx, int new_element){

    if (idx == NULL){
        idx = (node*) malloc(sizeof(node));
        idx -> x = new_element;
        idx -> next = NULL;
        return idx;
    }

    // we can consider iter as i in loops
    // (we will travel on the list through iter without changing head pointer)
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

node * insert(node*idx, int new_element){
    // (creating sorted linkedlist)
    // this function will be insert elements by checking whether new element is higher or lower
    // imagine that we have 3 7 2 4 as elements to add to the empty list consequitively
    // 3 will be added as root, root -> 3 -> NULL
    // 7 goes end to be settled, root -> 3 -> 7 -> NULL
    // when 2 is come, 2 will point 3
    // we break root's next pointer to change it 3 to 2 | root -> 2 -> 3 -> 7
    // when 4 is come, 4 will point 7
    // we break 3's next pointer to change it 7 to 4
    // so the latest linkedlist is root -> 2 -> 3 -> 4 -> 7

    if(idx == NULL){          // if linkedlist is empty
        idx = add(idx, new_element);
        return idx;
    }

    else{
        node* iter = idx;
        while(iter -> next != NULL && new_element >= iter -> next -> x)
            iter = iter -> next;
    
        // we need temporary box to not lose linked list at the space while changing pointers
        // we have to point the linked list if we break it without adding new point, we cannot reach that list again
        node * temp = (node*) malloc(sizeof(node));

        if (idx -> x > new_element){        // add element as root
            temp -> next = idx;
            temp -> x = new_element;
            return temp; // send temp as new root, it is important to update root's pointer in main
        }
        else if(iter -> next != NULL && iter -> next -> x >= new_element){     // instertion
            temp -> next = iter -> next;
            temp -> x = new_element;
            iter -> next = temp;
            return idx;
        }
        else{ // end of list
            // we have already written code to add element to the end so why we won't use it?
            idx = add(idx, new_element);
            return idx;
        }
    }
}

node * delete(node*idx, int element){

    if(idx == NULL){
        printf("There is no element to remove. List has 0 element.\n");
        return idx;
    }
    else if(idx -> x == element){ // if the root equals to element we search (in other words first element of the list)
        node * tmp = idx;
        idx = idx -> next;
        free(tmp);
        return idx;      
    }
    else{
        node * iter = idx;
        while(iter -> next != NULL && iter -> next -> x != element)
            iter = iter -> next;

        if(iter -> next == NULL){
            printf("There is no such element in the list.\n");
            return idx;
        }

        node * tmp = iter -> next;
        iter -> next = iter -> next -> next;
        free(tmp);
        return idx;
    }
}