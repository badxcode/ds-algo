#include<iostream>
using namespace std;

struct node { // Creating a node 
    int data; // variable to store the data
    node* next; // Pointer which points to the next node in memory
};
struct node* head; // head pointer keeps the first node address

struct node* getNewNode(int data) { // make a new node with given data [neso academy]
    struct node* newNode = new node();

    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}
int countingNodes() { // how many nodes do we have?
    int count = 0;
    struct node* c = head;

    while(c!=NULL) { // c == NULL means we are not pointing to any nodes
        count++;
        c = c->next;
    }

    return count;
}
void insertAtEnd(int data) { // insert data at the end of node each time [mycodeschool-5]
    struct node* temp = getNewNode(data);

    if(head==NULL) { // temp is the 1st node coz head == NULL
        head = temp; // so, temp is head
    }
    else {
        struct node* trv = head; // tev to traverse to last node
        while(trv->next!=NULL) { // trv->next == NULL means there's no node after trv so trv is the last node
            trv = trv->next;
        }
        trv->next = temp; // trv is the last node. Thus, adding temp after the last node
    }
}
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
void printRecursion(struct node* print) // prints the list using recursion [mycodeschool-10]
{   
    if(print==NULL) return; // exit condition

    cout << ' ' << print->data;
    printRecursion(print->next);
    cout << endl;
}
void printRecursionReverse(struct node *print) // prints the list in reverse order using recursion (doesn't actually reverse the list) [mycodeschool-10]
{   
    if(print==NULL) return; // exit condition
    
    printRecursionReverse(print->next);
    cout << ' ' << print->data;
}

int main()
{
    head = NULL; // making head NULL to define empty list
    int n, data, position, i;

    cout << "How many nodes do you want?: ";
    cin >> n;

    // checking the insert functions
    for(i=0; i<n; i++)
    {
        cout << "Enter the data: ";
        cin >> data;
        // cout << "Enter the position: ";
        // cin >> position;

        insertAtEnd(data);
        //insertAtBeginning(data);
        //insertAtNthPosition(data,position);
    }
    print();

    // checking recursive and print fucntions
    // cout << "The list is: ";
    // printRecursion(head);
    //reversingIterative();
    //reversingRecursion(head);
    //print();

    // cout << "The list is: ";
    // printRecursionReverse(head);

    /* checking the delete node function
    for(i=0; i<n; i++)
    {
        cout << "Enter the position to delete: ";
        cin >> position;

        deleteNode(position);
        print();
    }
    */

    /* checking the insertion in a sorted list function
    for(i=0; i<n; i++)
    {
        cout << "Enter the data to insert in sort list: ";
        cin >> data;

        insertInSortList(data);
        print();
    }
    */ 
}