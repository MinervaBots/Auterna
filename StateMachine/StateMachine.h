#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <tuple>

using std::tuple;
using std::make_tuple;
using std::tie;

template<class T_INP, class T_STATE, class T_OUT = T_STATE>
class StateMachine {
public:
    StateMachine(T_STATE initialState) : _state{initialState} {}

    virtual tuple<T_STATE, T_OUT>
    getNextValues(const T_STATE &state, const T_INP &inp) const = 0;

    virtual void step(const T_INP &inp) = 0;
protected:
    T_STATE _state;
};

#endif
