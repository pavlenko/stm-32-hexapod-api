//
// Created by master on 30.01.20.
//

#include "FSM.hpp"

template<class T>
void FSM<T>::initialize(T &state) {
    _prevState = _nextState = state;

    if (_prevState.onEntering) {
        _prevState.onEntering();
    }
}

template<class T>
void FSM<T>::transitionTo(T &state) {
    _nextState = state;
}

template<class T>
void FSM<T>::dispatch() {
    if (_prevState != _nextState) {
        _prevState = _nextState;

        if (_prevState.onEntering) {
            _prevState.onEntering(this);
        }
    }

    if (_prevState.onDispatch) {
        _prevState.onDispatch(this);
    }
}
