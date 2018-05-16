// #include <iostream>
// #include <string>
// #include "StateMachine.h"

// class A : public StateMachine<int, int, int>{
// public:
//     A() : StateMachine(0) {}

//     int getNextValues(int state, int inp, int& outState);
//     void step(int inp);
// };

// int A::getNextValues(int state, int inp, int& outState) {
//     return outState = state + inp;
// }

// void A::step(int inp) {
//     int outState;

//     int out = this->getNextValues(this->_state, inp, outState);
//     this->_state = outState;

//     std::cout << "Out: " << out << std::endl;
// }

// int main(void) {
//     StateMachine<int, int, int>* a = new A();

//     a->step(1);
//     a->step(7);
//     a->step(-4);
//     a->step(-3);

//     return 0;
// }