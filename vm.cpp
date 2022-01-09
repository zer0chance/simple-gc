#include "vm.hpp"

void Object::mark() {
    // Checking if object was marked before to prevent recursive marking.
    if (marked) return;

    marked = true;
    if (type == T_PAIR) {
        first->mark();
        second->mark();
    }
}

void VM::sweep() {
    Object* current = head;
    while (current != nullptr) {
        if (current->marked) {
            current->marked = false;
            current = current->next;
        } else {
            Object* garbage = current;
            current = garbage->next;
            delete garbage;
        }
    }
}

void VM::pushInt(int intValue) {
    Object* object = new Object(Object::T_INT);
    object->value = intValue;
    push(object);
}

Object* VM::pushPair() {
    Object* object = new Object(Object::T_PAIR);
    object->first = pop();
    object->second = pop();

    push(object);
    return object;
}
