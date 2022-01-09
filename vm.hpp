#ifndef VM_HPP
#define VM_HPP

#include <cassert>

class VM;

struct Object {
    enum ObjType {
        T_INT,
        T_PAIR
    };

    bool marked;
    Object* next;
    ObjType type;

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
    Object* stack[MAX_STACK];
    int tos; // top of stack
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

