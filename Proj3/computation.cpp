#include "computation.h"

#include <latch>

#include "actions.h"

namespace {

// a=6 b=5 c=8 d=5 e=8 f=9 g=4 h=5 i=6 k=4
std::latch done_a(6), done_b(5), done_c(8), done_d(5), done_e(8),
    done_g(4), done_h(5), done_i(6), done_k(4);

void act_a(int i) { f('a', i); done_a.count_down(); }
void act_b(int i) { f('b', i); done_b.count_down(); }
void act_e(int i) { done_a.wait(); f('e', i); done_e.count_down(); }
void act_g(int i) { done_a.wait(); f('g', i); done_g.count_down(); }
void act_h(int i) { done_b.wait(); f('h', i); done_h.count_down(); }
void act_i(int i) { done_b.wait(); f('i', i); done_i.count_down(); }
void act_k(int i) { done_e.wait(); f('k', i); done_k.count_down(); }
void act_c(int i) { done_g.wait(); done_h.wait(); f('c', i); done_c.count_down(); }
void act_d(int i) { done_i.wait(); f('d', i); done_d.count_down(); }
void act_f(int i) { done_k.wait(); done_c.wait(); done_d.wait(); f('f', i); }

void worker0() {
    act_a(1); act_a(6); act_b(5); act_h(1); act_g(1); act_e(6);
    act_k(1); act_i(4); act_d(1); act_c(3); act_c(8); act_f(1); act_f(6);
}

void worker1() {
    act_a(2); act_b(1); act_e(1); act_h(2); act_g(2); act_e(7);
    act_k(2); act_i(5); act_d(2); act_c(4); act_f(2); act_f(7);
}

void worker2() {
    act_a(3); act_b(2); act_e(2); act_h(3); act_g(3); act_e(8);
    act_k(3); act_i(6); act_d(3); act_c(5); act_f(3); act_f(8);
}

void worker3() {
    act_a(4); act_b(3); act_e(3); act_h(4); act_g(4); act_i(1);
    act_k(4); act_c(1); act_d(4); act_c(6); act_f(4); act_f(9);
}

void worker4() {
    act_a(5); act_b(4); act_e(4); act_h(5); act_e(5); act_i(2);
    act_i(3); act_c(2); act_d(5); act_c(7); act_f(5);
}

}  // namespace

void worker(int id) {
    switch (id) {
        case 0: worker0(); break;
        case 1: worker1(); break;
        case 2: worker2(); break;
        case 3: worker3(); break;
        case 4: worker4(); break;
    }
}
