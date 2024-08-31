#ifndef MPOINTERLIST_H
#define MPOINTERLIST_H

class MPointerNode {
public:
    int id;
    void* ptr;
    MPointerNode* next;
};

class MPointerList {
public:
    MPointerList() : head(nullptr), tail(nullptr) {}

    ~MPointerList() {
        clear();
    }

    void add(int id, void* ptr) { // Cambia el tipo a void*
        MPointerNode* newNode = new MPointerNode{id, ptr, nullptr};

        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void remove(int id) {
        MPointerNode* current = head;
        MPointerNode* previous = nullptr;

        while (current != nullptr && current->id != id) {
            previous = current;
            current = current->next;
        }

        if (current != nullptr) {
            if (previous == nullptr) {
                head = current->next;
            } else {
                previous->next = current->next;
            }

            if (current == tail) {
                tail = previous;
            }

            delete current;
        }
    }

    void clear() {
        MPointerNode* current = head;
        while (current != nullptr) {
            MPointerNode* temp = current;
            current = current->next;
            delete temp;
        }
        head = tail = nullptr;
    }

private:
    MPointerNode* head;
    MPointerNode* tail;
};

#endif // MPOINTERLIST_H
