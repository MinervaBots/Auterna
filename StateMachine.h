template<class T_OUT, class T_STATE, class T_INP>
class StateMachine{
   public:
   StateMachine (T_STATE initialState):
   _state(initialState);
  
  virtual T_OUT getNextValues(T_STATE state, T_INP inp);
  virtual void step(T_INP inp);  
  
  private:
    T_STATE _state;
       
   
}

