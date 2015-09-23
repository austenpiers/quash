#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "Quash.h"
#include "HeapNode.h"
#include "HashNode.h"
using namespace std;

//QUASH CONSTRUCTOR
Quash::Quash(){
  //initializing Hash Table
  for(int i = 0; i<43; i++)
    this->Table[i] = NULL;
}

//QUASH DESTRUCTOR
Quash::~Quash(){
  //deleting Hash Table
  for(int i = 0; i<43; i++){
    while(this->Table[i] != NULL)
      {
	HashNode *current = this->Table[i];
	do{
	  HashNode *tmp = current;
	  current = current->Next;
	  delete tmp;
	}while(current != NULL);
      }
  }
}

//HASH FUNCTION
int Quash::hashFunction(int input){
  int index = input%(43);
  if (index < 0)
    index += 43;
  return index;
}

//INSERTION OF NODE
void Quash::InsertHashNode(int key){	
	
  //find initial index
  int index = this->hashFunction(key);
  HashNode *Location = (this->Table[index]);
  
  //Base case, index is empty
  if(Location == NULL){
    this->Table[index] = new HashNode(key);
    cout << "item successfully inserted, count = 1" << endl;
    this->Table[index]->HeapVal = HeapInsertNode(key, index);
    return;
  }
  
  //while there is no spot available, keep looking
  while(Location != NULL ){
    //the item already exists, increment count
    if((Location->Value)==key){
      (Location->Count)++;
      (Heap[Location->HeapVal]->count)++;
      cout << "item already present, new count = " << Location->Count << endl;
      return;
    }
    //when we hit the end, create a new Node, insert to hash and heap
    if((Location->Next) == NULL){
      (Location->Next) = new HashNode(key);
      cout << "item successfully inserted, count = 1" << endl;
      (Location->Next->HeapVal) = (HeapInsertNode(key, Location));
      return;
    }
  }
}

//INSERT NODE INTO HEAP /hash-node is root
int Quash::HeapInsertNode(int key, int index){
  HeapNode *nwNode = new HeapNode(key, index);
  this->Heap.push_back(nwNode);
  return(percolateUp(Heap.size() - 1));
}
//INSERT NODE INTO HEAP /hash-node in separate chain
int Quash::HeapInsertNode(int key, HashNode *index){
  HeapNode *nwNode = new HeapNode(key, index);
  this->Heap.push_back(nwNode);
  return(percolateUp(Heap.size() - 1));
}

//PERCULATE UP
int Quash::percolateUp(int i){
  if(Heap.size() == 1)
    return 0;
  int swtch = i;
  HeapNode* temp;
  int parent = (i/2); //set the key of the parent node
	
  //if there is a left child and its less than parent
  if (Heap[parent]->value > Heap[i]->value)
    swtch = parent;

  //if parent is greater than
  if (i != swtch){
    //switch them
    if(Heap[swtch]->HashIndex == -1)
      (Heap[swtch]->PTE->Next->HeapVal) = i;
    else
      (Table[Heap[swtch]->HashIndex]->HeapVal) = i;

    temp = (Heap[swtch]);
    Heap[swtch] = Heap[i];
    Heap[i] = temp;
    //percolate up from the one we just switched to
    return (percolateUp(swtch));
  }
  else
    return i;
}

//HASHTABLE IMPLEMENTED LOOKUP
void Quash::lookup(int key){
  int index = this->hashFunction(key);
  HashNode *Location = (this->Table[index]);

  //search through list for key or NULL
  while(Location != NULL){ 
      // Found
      if((Location->Value) == key){
	cout << "item found, count = " << Location->Count << endl;
	return;
      }
      Location = Location->Next;
    }
  //not found
  cout << "item not found" << endl;
  return;
}

//DELETE MINIMUM ELEMENT
void Quash::deleteMin(){

  if(this->Heap.size() == 0){
    cout << "min item not present since table is empty" << endl; return;}
    

  //store minimum
  HeapNode* min = (this->Heap[0]);
  //setting potential index of min in HashTable
  int potInd = min->HashIndex;

  // if there is more than one of the min elements, just minus the count
  if((min->count) > 1){
      (min->count)--;
      cout << "min item = " << min->value << ", count decremented, new count = " << min->count << endl;
      if(potInd == -1)
	(min->PTE->Next->Count)--;
      else
	(this->Table[potInd]->Count)--;
      return;
    }

  //take the last element and put it at the root
  this->Heap[0] = this->Heap[Heap.size() - 1];
  this->Heap.pop_back();

  //Percolate Down and update HashTable's Node pointing to the perviously last element 
  if((this->Heap[0]->HashIndex) == -1)
    (this->Heap[0]->PTE->Next->HeapVal) = percolateDown(0);
  else
    (this->Table[Heap[0]->HashIndex]->HeapVal) = percolateDown(0);
  
  //Delete the min in HashTable
  HashNode *tmp;
  if(potInd == -1){
    tmp = min->PTE->Next;
    min->PTE->Next = tmp->Next;
  }
  else{
    tmp = this->Table[potInd];
    this->Table[potInd] = tmp->Next;
  }

  //print standard output
  cout << "min item " << tmp->Value << " successfully deleted" << endl;
  delete tmp;
  delete min;
  return;
}


//PERCULATE DOWN
int Quash::percolateDown(int i){
  if(Heap.size() == 1)
    return i;
  int swtch = i;
  HeapNode* temp;

  int left = 2*i + 1; //set the key of the left node
  int right = 2*i + 2; //set the key of the right node
	
  //if there is a left child and its less than parent
  if (left < (Heap.size()) && Heap[left]->value < Heap[i]->value)
    swtch = left;
  //if there is a right child and its less than either the parent or the left node
  else if(right < (Heap.size()) && Heap[right]->value < Heap[swtch]->value)
    swtch = right;

  //if a switch must be made
  if (i != swtch){
    //switch them
    if(Heap[swtch]->HashIndex == -1)
      Heap[swtch]->PTE->Next->HeapVal = i;
    else
      Table[Heap[swtch]->HashIndex]->HeapVal = i;

    temp = (Heap[swtch]);
    Heap[swtch] = Heap[i];
    Heap[i] = temp;

    //percolate down from the one we just switched to
    return percolateDown(swtch);
  }
  else
    return i;
}

//DELETING A SPECIFIC INDEX IN THE HASH TABLE
void Quash::deleteNode(int key){
  int index = this->hashFunction(key);
  HashNode *tmp = this->Table[index];
  while(tmp != NULL){
    if(tmp->Value == key){
      this->deleteMin(tmp->HeapVal);
      cout << "item successfully deleted" << endl;
      tmp = tmp->Next;
      return;
    }
  }
  cout << "item not present in the table" << endl;
}

//DELETE SPECIFIC ELEMENT
void Quash::deleteMin(int i){
  //store minimum
  HeapNode* min = (this->Heap[i]);
  //setting potential index of min in HashTable
  int potInd = min->HashIndex;

  // if there is more than one of the min elements, just minus the count
  if((min->count) > 1){
      (min->count)--;
      if(potInd == -1)
	(min->PTE->Next->Count)--;
      else
	(this->Table[potInd]->Count)--;
      return;
    }

  //take the last element and put it at the root
  this->Heap[i] = this->Heap[Heap.size() - 1];
  this->Heap.pop_back();

  //Percolate Down and update HashTable's Node pointing to the perviously last element 
  if((this->Heap[i]->HashIndex) == -1)
    (this->Heap[i]->PTE->Next->HeapVal) = percolateDown(i);
  else
    (this->Table[Heap[i]->HashIndex]->HeapVal) = percolateDown(i);
  
  //Delete the min in HashTable
  HashNode *tmp;
  if(potInd == -1){
    tmp = min->PTE->Next;
    min->PTE->Next = tmp->Next;
  }
  else{
    tmp = this->Table[potInd];
    this->Table[potInd] = tmp->Next;
  }

  //print standard output
  delete tmp;
  delete min;
  return;
}

void Quash::print(){

  for(int iter = 0; iter < this->Heap.size(); iter++)
    cout << Heap[iter]->value << " ";
  cout << endl;
}
