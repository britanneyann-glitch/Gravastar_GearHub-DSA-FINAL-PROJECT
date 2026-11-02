#include "UndoStack.h"

UndoStack::UndoStack() : topNode(nullptr) {}
UndoStack::~UndoStack() {
    UndoRecord ignored;
    while (pop(ignored)) {}
}

void UndoStack::push(const UndoRecord& record) {
    topNode = new Node(record, topNode);
}

bool UndoStack::pop(UndoRecord& record) {
    if (!topNode) return false;
    Node* oldTop = topNode;
    record = oldTop->data;
    topNode = oldTop->next;
    delete oldTop;
    return true;
}

bool UndoStack::empty() const { return topNode == nullptr; }
