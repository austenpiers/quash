#ifndef QUASH_H
#define QUASH_H
#include <vector>
#include "HeapNode.h"

class Quash {
 public:
  HashNode *Table[43];
  std::vector<HeapNode*> Heap;

  Quash();
  ~Quash();

  void insert(int i);
  int hashFunction(int);
  void InsertHashNode(int);
  int HeapInsertNode(int,int);
  int HeapInsertNode(int,HashNode*);
  int percolateUp(int i);
  void lookup(int key);
  void deleteMin();
  int percolateDown(int i);
  void deleteNode(int key);
  void deleteMin(int i);
  void print();

};

#endif
