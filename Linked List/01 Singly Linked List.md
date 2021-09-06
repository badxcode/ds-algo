# 01 Singly Linked List

Created: 03-09-2021 14:54     
Home: [Index](../README.md)    
Previous: [00 Linked List](00%20Linked%20List.md)  
Next: [02 Doubly Linked List](02%20Doubly%20Linked%20List.md)  
Source: [mycodeschool (5-11)](https://www.youtube.com/playlist?list=PL2_aWCzGMAwI3W_JlcBbtYTwiQSsOTa6P)    

---

Singly linked list are the basic linked list that we talked about earlier. It has a data part which stores the value and a pointer which points to the next node. The navigation or linking is only forward.

We first create a node like this:

```C++
struct node {
	int data; // data part
	struct node* next; // pointer to point to the next node
};
```

We then create a node every time we insert a value in the heap memory section. We can perform this locally inside any function we like. Alternatively, we  can  also create an external function and call it from other functions to reduce repetitiveness like this:

```C++
struct node* getNewNode(int data) { // make a new node with given data
    
	struct node* newNode = new node();
    newNode->data = data;
    newNode->next = NULL;
	
    return newNode;
}
```

This function will create a node in the heap memory and will return the memory address of that allocated space. Which we can later use to perform the following operations:

one more thing before we dive into the operations, we know that for linked list we only keep the address of the head node, which is the 1st node in our list. We can declare a pointer in the `main()` but then we have to pass this `head` address in every function we may call afterwards. That's why we declare a pointer variable globally to keep the 1st node address. Initially we assign it to `NULL` because we don't have anything in our list at the beginning like so:

```C++
//Global area
struct node* head = NULL;
```

###### Insertion at the end of the list:

```C++
void insertAtEnd(int data) { // insert data at the end of node each time [mycodeschool-5]
    struct node* temp = getNewNode(data);

    if(head==NULL) { // temp is the 1st node coz head == NULL
        head = temp; // so, temp is head
    }
    else {
        struct node* trv = head; // trv to traverse to last node
        while(trv->next!=NULL) { // trv->next == NULL means there's no node after trv so trv is the last node
            trv = trv->next;
        }
        trv->next = temp; // trv is the last node. Thus, adding temp after the last node
    }
}
```
 
 ###### Insertion at the beginning of the list:
 
 ```C++
 void insertAtBeginning(int data) { // insert at the beginning (at 1st position) each time [mycodeschool-6]
    struct node* temp = getNewNode(data);

    if(head==NULL) { // temp is the 1st node coz head == NULL
        head = temp; // so, temp is head
    }
    else {
        temp->next = head; // making old head(1st) node to 2nd node
        head = temp; // making temp as the head(1st) node thus inserting at beginning
    }
}
```

###### Inserting at a given position: 

```C++
void insertAtNthPosition(int data, int position) { // inserting at a given positoin [mycodeschool-7]

    if(head==NULL && position!=1) { //there's 0 node and position > 1 so can't insert
        cout << "Invalid position. The list is empty." << endl;
        return;
    }
    if(position<=0) { //positoin less than or equal to 0 doesn't exists
        cout << "Invalid position." << endl;
        return;
    }

    int count = countingNodes(); // number of nodes we have
    if(position<=count+1) { // count+1 coz if we have 4 nodes we can insert at position 5
        
        struct node *temp1 = getNewNode(data);

        if(position==1) { // inserting at 1st position
            temp1->next = head; // making the old head(1st)node 2nd node
            head = temp1; // making the new node 1st node
            return;
        }
        struct node *temp2 = head;
        // traversing to point to (position-1) node
        for(int i=1; i<position-1; i++) // loop will run (position-2) times coz (position-2)->next = (position-1)
            temp2 = temp2->next;
        
        temp1->next = temp2->next; //linking (new node)->next = position node [{(position-1)->next = position}]
        temp2->next = temp1; // linking (new node) after (position-1) node. Making (new node) the position node and old position node to (position+1) node
    }
    else {
        cout << "Invalid position. The last position is " << count << endl;
    }
}
```

If we have 5 nodes, we can insert at node 6 but we cannot insert at node 7 or higher. That's why we have to count how many nodes we have to determine if the requested position is valid or not.

####### Counting Nodes:
```C++
int countingNodes() { // how many nodes do we have?
    int count = 0;
    struct node* c = head;

    while(c!=NULL) { // c == NULL means we are not pointing to any nodes
        count++;
        c = c->next;
    }

    return count;
}
```

###### Deleting a node:

For deletion also, we can't delete nodes that we don't have. Like we have 5 nodes, we can't delete nodes at position 6 or higher. That's why we are also counting nodes here using the previous function.

```C++
void deleteNode(int position) { // delete a specific node [mycodeschool-8]
    if(head==NULL) { // head == NULL means empty list
        cout << "The list is already empty. Nothing to delete." << endl;
        return;
    }

    int count = countingNodes();
    if(position<=0 || position>count) { // invalid positions
        cout << "Invalid position." << endl;
        return;
    }

    struct node* temp1 = head;
    if(position==1) {
        head = head->next; // making the 2nd node as head node
        delete temp1; // delete 1st node
    }
    else {
        for(int i=1; i<position-1; i++) { // temp1 points to (positon-1) node
            temp1 = temp1->next;
        }
        struct node* temp2 = temp1->next; // temp2 = positon node
        temp1->next = temp2->next; // linking (position+1) node with (positoin-1) node

        delete temp2; // delete position node
    }
}
```

###### Inserting node in a sorted list:

In a sort list, we have to insert values in a way so that we don't break the sort. Like if we have a list like: `10 20 30 40` and we enter 15, we have to enter it after 10 like, `10 15 20 30 40`. So that it remains a sorted list even after our insertion.

```C++
void insertInSortList(int data) { // inserts data in a sorted list [neso academy-96]
    struct node* newNode = getNewNode(data);
    struct node* temp = head;
    int key = data;

    if(head==NULL || key < head->data) { // head == NULL is empty node || key < head->data means new node must be the 1st node
        newNode->next = head;
        head = newNode;

        return;    
    }
    /*
        temp->next==NULL  means there's no node after temp so we have to insert node after temp
        temp->next->data < key means we are comparing the given data with (position+1) data while staying at position node
        thus if it's true we can point to position node with temp and add the given node at (position+1) node
    */
    while(temp->next!=NULL && temp->next->data < key) {
        temp = temp->next;
    }
    newNode->next = temp->next; //linking (new node)->next = position node [{(position-1)->next = position}]
    temp->next = newNode; // linking (new node) after (position-1) node. Making (new node) the position node and old position node to (position+1) node
}
```

###### Reversing a list (iterative method):

```C++
void reversingIterative() { // reverses linked list iteratively (without recursion) [mycodeschool-9]
    struct node *current, *prev, *next; // current = current node, prev = previous node of current node, next = next node after current node
    current = head; // initialy, current = head
    prev = NULL; // no node before head

    while(current!=NULL) // current = NULL means the traversal and reversing complete
    {
        next = current->next; // next stores the next node after current node
        current->next = prev; // making link of current next  node with previous node of current
        prev = current; // previous will point to current 
        current = next; // current changes to the next node
    }
    /*  prev = last node (which is 1st node after reversing)
        next = NULL
        current = NULL
    */
    head = prev; // head = newly 1st node
}
```

###### Reversing a list (recursion method):

```C++
void reversingRecursion(struct node* p) { // reverse linked list using recursion [mycodeschool-11]
    if(p->next==NULL) { // p->next == NULL means p is the last node
        head = p; // last node is 1st node after reversing but here linking with other happens too
        return; // exit condition
    }
    reversingRecursion(p->next); // recursion callilng
    // draw the stack and each step :) 
    struct node* q = p->next;
    q->next = p;
    p->next = NULL;
}
```

###### Printing a list:

```c++
void print() // prints the list normally [mycodeschool]
{
    struct node* print = head;
    
    cout << "The list is: ";
    while(print!=NULL) // print has traversed all the nodes and now pointing to NULL
    {
        cout << ' ' << print->data;
        print = print->next;
    }
    cout << endl;
}
```

###### Printing a list (recursion):

```C++
void printRecursion(struct node* print) // prints the list using recursion [mycodeschool-10]
{   
    if(print==NULL) return; // exit condition

    cout << ' ' << print->data;
    printRecursion(print->next);
    cout << endl;
}
```

###### Printing a list in reverse: 

Here, we are just printing list in reverse. The list stays the same internally.

```C++
void printRecursionReverse(struct node *print) // prints the list in reverse order using recursion (doesn't actually reverse the list) [mycodeschool-10]
{   
    if(print==NULL) return; // exit condition
    
    printRecursionReverse(print->next);
    cout << ' ' << print->data;
}
```


