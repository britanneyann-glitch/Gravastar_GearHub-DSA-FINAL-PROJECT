#ifndef UNDO_STACK_H
#define UNDO_STACK_H

struct UndoRecord {
    int productId;
    int quantity;
};

class UndoStack {
private:
    struct Node {
        UndoRecord data;
        Node* next;
        Node(const UndoRecord& value, Node* link) : data(value), next(link) {}
    };
    Node* topNode;

public:
    UndoStack();
    ~UndoStack();
    UndoStack(const UndoStack&) = delete;
    UndoStack& operator=(const UndoStack&) = delete;

    void push(const UndoRecord& record);
    bool pop(UndoRecord& record);
    bool empty() const;
};

#endif
