template<class T_INP, class T_STATE, class T_OUT>
class StateMachine{
public:
  StateMachine (T_STATE initialState):
    _state(initialState) {};
  
  virtual T_OUT getNextValues(T_STATE state, T_INP inp, T_STATE& outState) = 0;
  virtual void step(T_INP inp) = 0;  

protected:
  T_STATE _state;   
};

