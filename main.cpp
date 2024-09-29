#include "headers/Object.h"
#include <experimental/random>
#include <iostream>

Task *generateTask(int n, Container<Task *> *con) {
  Task *result;
  std::uniform_real_distribution<double> unif(-1000000, 1000000);
  std::default_random_engine re;

  int k = std::experimental::randint(0, 3);
  BinaryOperator op = (k == 0) ? ADD : (k == 1) ? SUB : (k == 2) ? MUL : DIV;
  switch (n) {
  case 0:
    result = new BinaryOperation(op, unif(re), unif(re), "Name1");
    break;
  case 1:
    result = new AddToContainerTask(
        con, generateTask(std::experimental::randint(0, 4), con));
    break;
  case 2:
    result = new CountObjectsInContainerTask(con);
    break;
  case 3:
    result = new CountTasksWithResultTask(con);
    break;
  default:
    result = new CountObjectsTask();
    break;
  }

  return result;
}

int main() {
  Container<Task *> *conteiner = new Container<Task *>();
  int n = 10;
  for (int i = 0; i < n; ++i) {
    conteiner->pushBack(
        generateTask(std::experimental::randint(0, 4), conteiner));
  }
  std::cout<<Object::getObjectCount() << '\n';
  Container<Task *>::Iterator it = conteiner->first();
  for (;it != conteiner->last(); it++) {
    Task *t = conteiner->peekFront();
    t->execute();
  }   
  conteiner->clear();
  std::cout<<Object::getObjectCount() << '\n';
  return 0;
}