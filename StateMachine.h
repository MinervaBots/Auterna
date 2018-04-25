template<class T_INP, class T_STATE, class T_OUT>
class StateMachine{
   public:
   StateMachine (T_STATE initialState):
   _state(initialState) {};
  
  virtual int getNextValues(T_STATE state, T_INP inp, T_STATE& outState) {};
  virtual void step(T_INP inp) {};  
  
  protected:
    T_STATE _state;   
};

