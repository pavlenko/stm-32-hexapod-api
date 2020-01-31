#ifndef PE_FSM_HPP
#define PE_FSM_HPP

#include <type_traits>

template <class T>
class PE_FSM;

template <class T>
using PE_FSMHandler = void (*)(PE_FSM<T> &fsm);

template <class T>
class PE_FSMState {
public:
    PE_FSMHandler<T> onEntering = nullptr;
    PE_FSMHandler<T> onDispatch = nullptr;
public:
    /**
     * Default constructor
     */
    PE_FSMState() = delete;

    /**
     * Init with only enter callback
     *
     * @param onEntering
     */
    explicit PE_FSMState(PE_FSMHandler<T> onEntering);

    /**
     * Init with enter and dispatch callback
     *
     * @param onEntering
     * @param onDispatch
     */
    explicit PE_FSMState(PE_FSMHandler<T> onEntering, PE_FSMHandler<T> onDispatch);
};

template <class T>
class PE_FSM {
private:
    T _prevState;
    T _nextState;
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
    void initialize(T &state);

    /**
     * Set new state
     *
     * @param state
     */
    void transitionTo(T &state);

    /**
     * Process change state
     */
    void dispatch();
};

#endif //PE_FSM_HPP
