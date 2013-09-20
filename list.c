 record Node {
    data; // The data being stored in the node
    Node next // A reference to the next node, null for last node
 }
 record List {
     Node firstNode // points to first node of list; null for empty list
 }

/*
Traversal of a singly linked list is simple, 
beginning at the first node and following each next link until we come to the end:

 node := list.firstNode
 while node not null
     (do something with node.data)
     node := node.next
*/
