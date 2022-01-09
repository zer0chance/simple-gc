#ifndef VM_HPP
#define VM_HPP

#include <cassert>

class VM;

struct Object {
    enum ObjType {
        T_INT,
        T_PAIR
    };

    // Setted to true if object is reachable.
    bool marked;

    // Objects are stored as linked list. See comments in VM class.
    Object* next;

    // Object's type.
    ObjType type;

    // Object in VM can be an integer or a pair.
    union {
        // INT
        int value;

        // PAIR
        struct {
            struct Object* first;
            struct Object* second;
        };
    };

    void mark();

private:
    Object(ObjType t) : marked(false), next(nullptr), type(t) {}
    ~Object() = default;
    friend VM;
};

#define MAX_STACK 256

class VM {
    // VM operates on stack as many of real VM's does.
    Object* stack[MAX_STACK];
    int tos; // top of stack

    // VM tracks all created object t collect garbage objects when they
    // becomes unreachable. All created objects stored in linked list.
    Object* head;

    void push(Object* value) {
        assert(tos < MAX_STACK); // Stack overflow
        stack[tos++] = value;

        value->next = head;
        head = value;
    }

    void mark() {
        for (int i = 0; i < tos; i++) stack[i]->mark();
    }

    void sweep();

public:
    VM() : tos(0), head(nullptr) {}
    ~VM() = default;

    void    pushInt(int intValue);
    Object* pushPair();

    Object* pop() {
        assert(tos > 0); // Stack underflow
        return stack[--tos];
    }

    void gc() {
        mark();
        sweep();
    }
};

#endif

