#pragma once
#include <stack>
#include "iterator.h"
class OctreeIterator : public Iterator {
public:
    OctreeIterator(Node* node);	
    Node* next();
    Node* current();
    bool is_end();

public:
	std::stack<Node*> stack;
};

