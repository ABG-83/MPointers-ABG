#ifndef MPOINTERLIST_H
#define MPOINTERLIST_H

class MPointerNode {
public:
    int id;
    void* ptr;
    int refCount; // Nuevo atributo para el conteo de referencias
    MPointerNode* next;

    MPointerNode(int id, void* ptr)
        : id(id), ptr(ptr), refCount(1), next(nullptr) {}
};

class MPointerList {
public:
    MPointerNode* getHead() const
    {
        return head;
    }
    MPointerList() : head(nullptr), tail(nullptr) {}

    ~MPointerList() {
        clear();
    }

    void add(int id, void* ptr) {
        MPointerNode* newNode = new MPointerNode(id, ptr);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    MPointerNode* find(int id) {
        MPointerNode* current = head;
        while (current != nullptr) {
            if (current->id == id) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
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
