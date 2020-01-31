#include "PE_FSM.hpp"

template<class T>
PE_FSMState<T>::PE_FSMState(PE_FSMHandler<T> onEntering):
onEntering(onEntering)
{}

template<class T>
PE_FSMState<T>::PE_FSMState(PE_FSMHandler<T> onEntering, PE_FSMHandler<T> onDispatch):
onEntering(onEntering),
onDispatch(onDispatch)
{}

template<class T>
PE_FSM<T>::PE_FSM():
_prevState(nullptr),
_nextState(nullptr)
{}

template<class T>
void PE_FSM<T>::initialize(T &state) {
    _prevState = _nextState = state;

    if (_prevState.onEntering) {
        _prevState.onEntering();
    }
}

template<class T>
void PE_FSM<T>::transitionTo(T &state) {
    _nextState = state;
}

template<class T>
void PE_FSM<T>::dispatch() {
    if (_prevState != _nextState) {
        _prevState = _nextState;

        if (_prevState.onEntering) {
            _prevState.onEntering(*this);
        }
    }

    if (_prevState.onDispatch) {
        _prevState.onDispatch(*this);
    }
}
