#ifndef HEAPNODE_H
#define HEAPNODE_H

#include "HashNode.h"

class HeapNode{
 public:

  int value, count;
  int HashIndex;
  HashNode *PTE;
  
 HeapNode(int Val, int i):value(Val),count(1),HashIndex(i),PTE(NULL){};
 HeapNode(int Val, HashNode *k):value(Val),count(1),HashIndex(-1),PTE(k){};
  ~HeapNode(){};
};

#endif
