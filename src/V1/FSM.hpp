//
// Created by master on 30.01.20.
//

#ifndef FSM_HPP
#define FSM_HPP

#include <type_traits>
#include <climits>

template <class T>
class FSM;

template <class T>
using FSMHandler = void (*)(FSM<T> &fsm);

template <class T>
class FSMState {
public:
    FSMHandler<T> onEntering;
    FSMHandler<T> onDispatch;
public:
    FSMState() = default;
    explicit FSMState(FSMHandler<T> onEntering): onEntering(onEntering), onDispatch(nullptr) {}
    explicit FSMState(FSMHandler<T> onEntering, FSMHandler<T> onDispatch): onEntering(onEntering), onDispatch(onDispatch) {}
};

template <class T>
class FSM {
private:
    T _prevState;
    T _nextState;
public:
    FSM(): _prevState(nullptr), _nextState(nullptr) {};
    void initialize(T &state);
    void transitionTo(T &state);
    void dispatch();
};

class StateA: public FSMState<StateA> {
public:
    explicit StateA(FSMHandler<StateA> onEntering): FSMState(onEntering) {}
};

class StateB: public FSMState<StateB> {
public:
    explicit StateB(FSMHandler<StateB> onEntering): FSMState(onEntering) {}
};

FSM<StateA> fsm = FSM<StateA>();

void handlerA(FSM<StateA> &fsmImpl) {}
void handlerB(FSM<StateB> &fsmImpl) {}

StateA stateA = StateA(handlerA);
StateB stateB = StateB(handlerB);

void test() {
    fsm.transitionTo(stateA);
    fsm.transitionTo(stateA);
}

#endif //FSM_HPP
