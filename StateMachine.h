template<class T_INP, class T_STATE, class T_OUT>
class StateMachine{
   public:
   StateMachine (int initialState):
   _state(initialState) {};
  
  virtual int getNextValues(int state, int inp, int& outState) {};
  virtual void step(int inp) {};  
  
  protected:
    int _state;   
};

