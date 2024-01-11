#include "../include/octree_iterator.h"

OctreeIterator::OctreeIterator(Node* node) {
    if (node != nullptr) {
        stack.push(node);
    }
}
Node* OctreeIterator::next() {
    if (stack.empty()) {
        return nullptr;
    }
    Node* current = stack.top();
    stack.pop();
    for (int i = 7; i >= 0; --i) {
        if (current->children[i] != nullptr) { stack.push(current->children[i]); }
    }
    return current;
}
Node* OctreeIterator::current() {
    return stack.empty() ? nullptr : stack.top();
}
bool OctreeIterator::is_end() {
    return stack.empty();
}