#include "PE_FSM.hpp"

PE_FSM::PE_FSM():
_prevState(nullptr),
_nextState(nullptr)
{}

void PE_FSM::initialize(PE_FSMState *state) {
    _prevState = _nextState = state;

    if (_prevState->onEntering) {
        _prevState->onEntering(*this);
    }
}

void PE_FSM::transitionTo(PE_FSMState *state) {
    _nextState = state;
}

void PE_FSM::dispatch() {
    if (_prevState != _nextState) {
        _prevState = _nextState;

        if (_prevState->onEntering) {
            _prevState->onEntering(*this);
        }
    }

    if (_prevState->onDispatch) {
        _prevState->onDispatch(*this);
    }
}
