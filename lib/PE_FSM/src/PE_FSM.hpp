#ifndef PE_FSM_HPP
#define PE_FSM_HPP

class PE_FSM;

typedef void (*PE_FSMHandler)(PE_FSM &fsm);

class PE_FSMState {
public:
    PE_FSMHandler onEntering = nullptr;
    PE_FSMHandler onDispatch = nullptr;
public:
    /**
     * Default constructor
     */
    //PE_FSMState() = default;

    PE_FSMState(PE_FSMHandler onEntering, PE_FSMHandler onDispatch);

//    PE_FSMState &setOnEntering(PE_FSMHandler handler) {
//        onEntering = handler;
//        return *this;
//    }
//
//    PE_FSMState &setOnDispatch(PE_FSMHandler handler) {
//        onDispatch = handler;
//        return *this;
//    }
};

class PE_FSM {
private:
    PE_FSMState *_prevState;
    PE_FSMState *_nextState;
public:
    /**
     * Default constructor
     */
    PE_FSM();

    /**
     * Set initial state
     *
     * @param state
     */
    void initialize(PE_FSMState *state);

    /**
     * Set new state
     *
     * @param state
     */
    void transitionTo(PE_FSMState *state);

    /**
     * Process change state
     */
    void dispatch();
};

#endif //PE_FSM_HPP
