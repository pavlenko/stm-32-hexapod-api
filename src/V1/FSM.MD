# Usage

```c++
#include <FSM.hpp>

// Create specific state class
class StateB: public FSMState<StateB> {
public:
    explicit StateB(FSMHandler<StateB> onEntering): FSMState(onEntering) {}
}; 

// Create FSM
FSM<StateA> fsm = FSM<StateA>();

// Create state handlers
void handlerA(FSM<StateA> &fsmImpl) {}
void handlerB(FSM<StateA> &fsmImpl) {}

// Create states
StateA state1 = StateA(handlerA);
StateA state2 = StateA(handlerA);

// Use fsm
void main() {
    while (true) {
        if (a) {
            fsm.transitionTo(state1);
        }  
        if (b) {
            fsm.transitionTo(state2);
        }

        fsm.dispatch();
    }    
}
```