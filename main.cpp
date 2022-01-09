#include "vm.hpp"

int main() {
    VM vm;
    
    vm.pushInt(1);
    vm.pushInt(2);
    vm.pushPair();
    vm.pushInt(4);
    vm.pop();
    vm.pop();
    vm.pushInt(5);
    
    vm.gc();
}
