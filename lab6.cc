/*************************************************************************
     Lab Assignment 6: This is another lab assignment in working with 
     linked lists. We will be using a struct node, for its simplicity,
     and working with non-member functions here. The main point is to 
     work with the logic of a linked list. Do not be afraid to make 
     drawings on scrap paper.
     The prototypes for the functions that you are to implement are
     included. You should uncomment them when you are ready to write 
     the implementation.
           John Dolan				Spring 2014
           Patricia Lindner             Fall 2021
*************************************************************************/
// Hunter Stout 2/25/2022
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct node{
     int data;
     node* next;
};


// These are the three I have implemented for you
void build_list(node*& head);  // note that we are passing by reference
void show_list(const node* head);
int size(const node* head);

//These are the two that you are to write, as described in the 
//instructions page.

void remove_repeats(node*& head);
void split_list(node* original, node*& lesser, node*& greater, int split_value);



int main(){
     int start, stop;
     int split;
     node* head = NULL;
     node* lesser;
     node* greater;

     //Original list.
     start = time(NULL);
     build_list(head);
     stop = time(NULL);
     cout << "Time to build list = " << stop - start << "seconds.\n";
     start = time(NULL);
     show_list(head);
     stop = time(NULL);
     cout << "Time to print list = " << stop - start << "seconds.\n";
     cout << "Size of the list = " << size(head) << endl;

     //Removes Repeats.
     remove_repeats(head);
     show_list(head);
     cout << "Time to print list = " << stop - start << "seconds.\n";
     cout << "Size of the list = " << size(head) << endl;

     //Splits list.
     cout << "Enter value to split list: ";
     cin >> split;
     split_list(head, lesser, greater, split);
     cout << endl << "Data under the split: " << endl;
     show_list(lesser);
     cout << endl << "Data over the split: " << endl;
     show_list(greater);

     return 0;
}

// builds a linked list of 2000 random integers, all in the range 1 - 500
void build_list(node*& head){
     node* cursor;

     head = new node;
     head -> data = rand()%500 + 1;

     cursor = head;
     for(int i = 0; i < 2000; ++i){
	cursor -> next = new node;
        cursor = cursor -> next;
        cursor -> data = rand()%500 + 1;
     }
     cursor -> next = NULL;
}

// outputs the contents of a linked list to the screen
void show_list(const node* head){
     const node* cursor = head;

     while(cursor !=  NULL){
          cout << cursor -> data << "  ";
          cursor = cursor -> next;
     }
     cout << endl;
}

// returns the number of nodes in a linked list
int size(const node* head){
	const node* cursor = head;
	int count = 0;
	while(cursor != NULL){
  	    count++;
	    cursor = cursor -> next;
	}
	return count;
}

void remove_repeats(node*& head) {
     node *current;
     node *placeholder;
     node *previous;
     current = head;

     while (current != NULL) {
          //Flips through list.
          placeholder = current -> next;
          previous = current;

          while (placeholder != NULL) {
               //Checks to make sure that the value is not identical.
               if (placeholder -> data == current -> data) {
                    previous -> next = placeholder -> next;
                    delete placeholder;
                    placeholder = previous -> next;
               }
               //If not flips to the next.
               else {
                    previous = placeholder;
                    placeholder = placeholder -> next;
               }
          }
          //Updates each passage.
          current = current -> next;
     }
     cout << endl << "Removed Identicals" << endl;
}

void split_list(node* original, node*& lesser, node*& greater, int split_value) {
     node* placeholder = new node;
     lesser = placeholder;

     //Flips until end of the list, sets starter point as original.
     for (node* temp = original; temp != NULL; temp = temp -> next) {
          //Updates placeholder with original data, sets new pointer, then moves next pointer.
          placeholder -> data = temp -> data;
          placeholder -> next = new node;
          placeholder = placeholder -> next;
          placeholder -> next = NULL;
          //Saves split if data is at checkpoint.
          if (temp -> data == split_value) {
               placeholder = new node;
               greater = placeholder;
          }
     }
}