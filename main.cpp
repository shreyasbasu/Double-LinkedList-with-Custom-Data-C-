#include <iostream>

using namespace std;

// Data Class : Holds all the data that goes inside the Node
class Data {
public:
    int value;
    string name;
    Data(int value, string name) {
        this->value = value;
        this->name = name;
    }
    void print() {

        cout << "[" << value << ", "<< name << "] ";
    }
    //custom EqualTo function that checks if first value is equal to second value
    bool isEqualTo(Data *d){
        return this->value == d->value && this->name == d->name;
    }
    //custom LessThan function that checks if first value is less than the second value
    //(not used but maybe can be used for future projects)
    bool isLessThan(Data *d){
        return this->value < d->value;
    }
    //custom greaterThan function that checks if first value is greater than the second value
    bool isGreaterThan(Data *d){
        return this->value > d->value;
    }
};

// Node Class : Node for the LinkedList
template <typename T> class Node {
public:
    T *value;
    Node<T> *next;
    Node<T> *prev;
    Node(T *value) {
        this->value = value;
        next = nullptr;
        prev = nullptr;
    }
    void print() { value->print(); }
};

// LinkedList Class : Container for Nodes
template <typename T> class DoubleLinkedList {
private:
    Node<T> *head;
    Node<T> *tail;
    int length;

public:
    // Constructor
    DoubleLinkedList(T *value) {
        Node<T> *newNode = new Node<T>(value);
        head = newNode;
        tail = newNode;
        length = 1;
    }

    // Destructor
    ~DoubleLinkedList() {
        Node<T> *temp = head;
        while (head) {
            head = head->next;
            delete temp;
            temp = head;
        }
    }

    void printList() {
        Node<T> *temp = head;
        while (temp != nullptr) {
            temp->print();
            temp = temp->next;
        }
    }

    // get and set
    Node<T> *getHead() {
        if (head == nullptr) {
            cout << "Head: nullptr" << endl;
        } else {
            cout << "Head: " << head->value << endl;
        }
        return head;
    }

    Node<T> *getTail() {
        if (tail == nullptr) {
            cout << "Tail: nullptr" << endl;
        } else {
            cout << "Tail: " << tail->value << endl;
        }
        return tail;
    }

    int getLength() {
        cout << "Length: " << length << endl;
        return length;
    }

    Node<T> *get(int index) {
        if (index < 0 || index >= length)
            return nullptr;
        Node<T> *temp = head;
        for (int i = 0; i < index; ++i) {
            temp = temp->next;
        }
        return temp;
    }

    bool set(int index, T *value) {
        Node<T> *temp = get(index);
        if (temp) {
            temp->value = value;
            return true;
        }
        return false;
    }

    // All insert methods
    // Insert at end
    void append(T *value) {
        Node<T> *newNode = new Node<T>(value);
        if (length == 0) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        length++;
    }

    // Insert at beginning

    void prepend(T *value) {
        Node<T> *newNode = new Node<T>(value);
        if (length == 0) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        length++;
    }

    // Insert at Index

    bool insert(int index, T *value) {
        if (index < 0 || index > length)
            return false;
        if (index == 0) {
            prepend(value);
            return true;
        }
        if (index == length) {
            append(value);
            return true;
        }
        Node<T> *newNode = new Node<T>(value);
        Node<T> *prev1 = get(index - 1);
        Node<T> *next1 = prev1->next;
        newNode->prev = prev1;
        newNode->next = next1;
        prev1->next = newNode;
        next1->prev = newNode;
        length++;
        return true;
    }

    // All delete Methods
    // Write deleteAtHead, DeleteTail & DeleteAtIndex here
    void deleteAtHead(){
        //check if list is 0 nodes long, nothing to delete
        if (length == 0) {
            cout << "List is empty. Cannot delete from an empty list." << endl;
            return;
        }
        //check if list is 1 node, delete the head (only element)
        else if(length == 1){
            delete head;
            head = nullptr;
            tail = nullptr;
            length = 0;
        }
        //all other cases
        else {
            //store head node
            Node<T>* temp = head;
            //change head node
            head = head->next;
            //make the previous pointer null because it's the new head
            head->prev = nullptr;
            //update length
            length = length - 1;
            //free up space by immediately deleting the previous head node
            delete temp;
        }
    }

    void deleteAtTail(){
        //check if list is 0 nodes long, nothing to delete
        if (length == 0) {
            cout << "List is empty. Cannot delete from an empty list." << endl;
            return;
        }
        //check if list is 1 node, delete the tail (only element)
        else if(length == 1){
            delete tail;
            head = nullptr;
            tail = nullptr;
            length = 0;
        }
        //all other cases
        else {
            //store tail
            Node<T>* temp = tail;
            //make tail previous node
            tail = tail->prev;
            //make the next pointer null because it's the new tail
            tail->next = nullptr;
            //update length
            length = length - 1;
            //free up space by immediately deleting the previous head node
            delete temp;
        }
    }

    void deleteAtIndex(int index){
        //check if list is 0 nodes long, nothing to delete
        if (length == 0) {
            cout << "List is empty. Cannot delete from an empty list." << endl;
            return;
        }
        //if index == 0 then it's head so call deleteHead function
        if (index == 0) {
            deleteAtHead();
            return;
        }
        //if index == length - 1 then it's the tail so call deleteTail function
        if (index == length - 1){
            deleteAtTail();
            return;
        }
        //create temp node pointer
        Node<T>* temp = head;
        //go through till temp is the indexed node
        for (int i = 0; i < index; ++i) {
            temp = temp->next;
        }
        //change the node before the index's next pointer to the node after index
        temp->prev->next = temp-> next;
        //change the node after the index's previous pointer to the node before index
        temp->next->prev = temp->prev;
        //delete the temp
        delete temp;
        //update length
        length--;
    }

    void sortList(){
        //initialize variables
        int swapCounter = 1;
        string tempName;
        //check for empty list
        if (length == 0) {
            cout << "List is empty. Cannot delete from an empty list." << endl;
            return;
        }
        //otherwise go into loop as long as swaps are being made
        while(swapCounter > 0){
            swapCounter = 0;
            //make temp node head
            Node<T>* temp = head;
            while (temp->next != nullptr){
                //if the first value is greater than the second one (using custom isGreaterThan) then switch
                if (temp->value->isGreaterThan(temp->next->value)){
                    //have the pointer store the next value
                    T* tempData = temp->next->value;
                    //make the next value the previous value
                    temp->next->value = temp->value;
                    //store the next value (held in temp data) in the previous spot
                    temp->value = tempData;
                    //update swapCounter var
                    swapCounter++;
                }
                //move to next node
                temp = temp->next;
            }
        }
    }

    int countMultiples(T *value){
        //initialize variables
        int counter = 0;
        Node<T>* temp = head;
        //go through the list
        while (temp != nullptr){
            //if an equal value is found then update (equal is a custom method)
            if(temp->value->isEqualTo(value)){
                counter++;
            }
            //move temp pointer
            temp = temp->next;
        }
        //return the total count
        return counter;
    }

    void reverseList(){
        //initialize variables
        Node<T>* current = head;
        Node<T>* temporary = nullptr;
        while (current != nullptr) {
            //stores current node
            temporary = current->prev;
            //swaps the two nodes
            current->prev = current->next;
            current->next = temporary;
            //moves to next node
            current = current->prev;
        }
        //update head
        if (temporary != nullptr){
            head = temporary->prev;
        }
    }

    void removeMultiples(){
        //initialize variables
        DoubleLinkedList<Data> *uniqueList = nullptr;
        int index = 0;
        bool isInitialized = false;
        Node<T>* temp = head;
        //go through loop
        while (temp != nullptr){
            //if there is something in uniqueLIst to compare and there is more than 0 iterations
            //(i.e. there has been a previous iteration in the list) then delete the value using delete index
            if(isInitialized && uniqueList->countMultiples(temp->value) > 0) {
                temp = temp->next;
                deleteAtIndex(index);
            }
            else {
                //update uniqueLIst like this every other time
                if (isInitialized) {
                    uniqueList->append(temp->value);
                }
                //for the first time make sure to update new uniqueList like this
                else {
                    isInitialized = true;
                    uniqueList = new DoubleLinkedList<T>(temp->value);
                }
                //update pointer and counter
                temp = temp->next;
                index++;
            }
        }
    }
    void evenOddSplit(){
        //if empty list then just return
        if (getLength() == 0){
            return;
        }
        //declare variable
        DoubleLinkedList<Data> *evenList (nullptr);
        //if the length is one just put the one in even list and then say the odd list is empty
        if(getLength() == 1){
            evenList = new DoubleLinkedList<T>(head->value);
            deleteAtHead();
            cout << "Even List: \n";
            evenList->printList();
            cout << "Odd list: NO LIST";
            return;
        }
        //initialize variables
        int index = 0;
        //add first item in evenlist
        evenList = new DoubleLinkedList<T>(head->value);
        //add next list in oddList
        DoubleLinkedList<Data> *oddList = new DoubleLinkedList<T>(head->next->value);
        //current node is 3rd item
        Node<T>* current = head->next->next;
        //while current can still go (until it reaches tail)
        while (current != nullptr) {
            //if the index is even add it to the evenLIst
            if (index % 2 == 0){
                evenList->append(current->value);
                deleteAtHead();
            }
            //otherwise add it to oddList
            else if (index % 2 == 1){
                oddList->append(current->value);
                deleteAtHead();
            }
            //update variables
            current = current->next;
            index++;
        }
        //print evenList and oddList using printList() function
        cout << "Even List: ";
        evenList->printList();
        cout << endl;
        cout << "Odd list: ";
        oddList->printList();
        cout << endl;
    }

};

// Main Program

int main() {
    //declare variables
    int inputOptionNum;
    int entryInt;
    int index;
    bool initialized = false;
    string entryString;
    Data *d1 = nullptr;
    DoubleLinkedList<Data> *ll1 (nullptr);
    //formatting
    cout << "This is a DLL Manipulator. Please enter the number option that you wish to choose" << endl;
    //if 14 then exit and it's supposed to exit after evenOdd, until that happens continue the loop
    while (inputOptionNum != 14 && inputOptionNum != 13) {
        //if a list is not initialized then put no list formed, once initialized print whole list
        if (initialized){
            cout << ll1->getLength();
            cout << "( ";
            ll1->printList();
            cout << ")" << endl;
        }
        else{
            cout << "No List Formed Currently" << endl;
        }
        //Prompt the menu
        cout << "1. Create a List" << endl;
        cout << "2. Delete a List" << endl;
        cout << "3. Insert at Head" << endl;
        cout << "4. Insert at Tail" << endl;
        cout << "5. Insert at Index" << endl;
        cout << "6. Delete at Head" << endl;
        cout << "7. Delete at Tail" << endl;
        cout << "8. Delete at Index" << endl;
        cout << "9. Reverse List" << endl;
        cout << "10. Sort List" << endl;
        cout << "11. Count Multiples" << endl;
        cout << "12. Delete Multiples" << endl;
        cout << "13. Split List Even Odd" << endl;
        cout << "14. Exit" << endl;
        //Take input
        cin >> inputOptionNum;
        //use a switch for each of the cases
        switch (inputOptionNum) {
            case 1:
                //get the data
                cout << "Enter an integer" << endl;
                cin >> entryInt;
                cout << "Enter a string" << endl;
                cin >> entryString;
                //put data into data structure
                d1 = new Data(entryInt, entryString);
                //add that data to a linked list
                ll1 = new DoubleLinkedList<Data>(d1);
                //set initialized to true so it can start printing list in output
                initialized = true;
                break;
            case 2:
                //use destructor to delete the list and updated initialized accordingly
                delete ll1;
                initialized = false;
                break;
            case 3:
                //get inputs
                cout << "Enter an integer" << endl;
                cin >> entryInt;
                cout << "Enter a string" << endl;
                cin >> entryString;
                //use prepend function to prepend a data structure with given data
                ll1->prepend(new Data(entryInt, entryString));
                break;
            case 4:
                //get inputs
                cout << "Enter an integer" << endl;
                cin >> entryInt;
                cout << "Enter a string" << endl;
                cin >> entryString;
                //use append function to append a data structure with given data
                ll1->append(new Data(entryInt, entryString));
                break;
            case 5:
                //get inputs
                cout << "Enter an integer" << endl;
                cin >> entryInt;
                cout << "Enter a string" << endl;
                cin >> entryString;
                cout << "Enter the index for the new item" << endl;
                cin >> index;
                //use insert function to insert a data structure with given data at a certain index
                ll1->insert(index, new Data(entryInt, entryString));
                break;
            case 6:
                //call deleteAtHead function to delete at head
                ll1->deleteAtHead();
                break;
            case 7:
                //call deleteAtTail function to delete at tail
                ll1->deleteAtTail();
                break;
            case 8:
                //get input
                cout << "Which index would you like to delete at?" << endl;
                cin >> index;
                //call deleteAtIndex function to delete at index
                ll1->deleteAtIndex(index);
                break;
            case 9:
                //call reverseLIst function to reverse the list
                ll1->reverseList();
                break;
            case 10:
                //call sortList to sort the function
                ll1->sortList();
                break;
            case 11:
                //enter inputs
                cout << "Enter an integer" << endl;
                cin >> entryInt;
                cout << "Enter a string" << endl;
                cin >> entryString;
                //output total multiples using countMultiples method
                cout << "Total Number of multiples: "<< ll1->countMultiples(new Data(entryInt, entryString)) << endl;
                break;
            case 12:
                //remove multiples using removeMultiples method
                ll1->removeMultiples();
                break;
            case 13:
                //split into even and odd using evenOddSplit function
                ll1->evenOddSplit();
                //free up memory that is not being used
                delete ll1;
                break;
            case 14:
                //free up memory that is not being used
                delete ll1;
                break;
            default:
                //otherwise invalid input ask for another prompt
                cout << "Invalid Input. Re-enter a valid number option. Your options will show up again after you input any integer and press enter." << endl;
                cin >> inputOptionNum;
                break;
        }
    }





    return 0;
}
