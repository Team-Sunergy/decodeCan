// typedef struct Node
// {
//     Node* next;     // next node
//     int64_t data;   // holds data
// } Node;

// typedef struct LinkedList
// {
//     Node* head;
// } LinkedList;

// LinkedList initList() {
//     LinkedList list;
//     list.head = NULL;
//     return list;
// }

// Node createNode(int64_t data) {
//     Node newNode;        // create node
//     newNode.data = data; // add data
//     newNode.next = NULL; // declare next to null
//     return newNode;
// }

// void add(LinkedList list, Node node) {
//     if(list == NULL) { // Case 1, no list exists
//         printf("list doesnt exist\n");
//         // you can create list with initList
//         return;
//     }

//     if(node == NULL) { // Case 1.5
//         printf("this node is null, create a node");
//         return;
//     }

//     if(list.head == NULL) { // Case 2, list has no items
//         list.head = &node;  // make node the head
//         return;
//     }

//     Node* current = list.head; // save head for traversing
//     while(current->next != NULL) { // Case 3, list has items.
//         current = current->next; // traverse to end of list
//     }

//     // we reached the end of list
//     current->next = node;   // set node at end of list to next node
// }