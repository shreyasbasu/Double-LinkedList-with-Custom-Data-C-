#Written by 
Shreyas Basu
# Double-LinkedList-with-Custom-Data-C-
A double linked list with a custom data type. Methods use pointers to manipulate data in different ways.

#Brief Description of the Project
This is a Double Linked List Manipulator equipped with an easy-to-use menu and several custom functions that work.

#File Structure of the project submitted
  Main.cpp
  README.pdf
  
#How to get started?
  Describe the input required from the user
  Start by creating list (option 1)
  Once created any functions can be used (CAUTION: recalling the create list creates a brand new list again and deletes previous list)
  EvenOddSplit function and the exit button terminates program
#Describe what function is called by each input and briefly describe each function.
1. Creates a list using the given data. Essentially calls constructor
2. Calls destructor that destroys the list
3. Uses prepend function to add given data to head or beginning of the list
4. Uses append function to add given data to tail or end of the list
5. Uses insert function to add given data to certain index of the list
6. Uses delete at head function to delete the head
7. Uses delete at tail function to delete the tail
8. Uses delete at index function to delete at certain index
9. Uses reverseList function to reverse the list
10. Uses sortList function to sort the list
11. Uses countMultiples to count certain number of multiples of a specific data
12. Uses removeMultiples method to remove multiples of certain data
13. Uses evenOddSplit to split up data into two sets of even and odd indices
14. Exits the program

#Runtime: The Big 0 of each function
printLIst: O(n)
getHead O(1)
getTail O(1)
getLength: O(1)
get: O(n)
set: O(n)
append: O(1)
prepend: O(1)
insert: O(n)
deleteAtHead: O(1)
deleteAtTail: O(1)
deleteAtIndex: O(n)
sortList: O(n^2)
countMultiples: O(n)
reverseList: O(n)
removeMultiples: O(n^2)
evenOddSplit: O(n)
