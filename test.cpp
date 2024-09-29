#include <gtest/gtest.h>

#include <experimental/random>
#include "headers/Object.h"

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
    result = new CountObjectsInContainerTask(con);
    break;
  case 2:
    result = new CountTasksWithResultTask(con);
    break;
  default:
    result = new CountObjectsTask();
    break;
  }
  return result;
}

TEST(Add, Simple) {
  Container<Task *> *conteiner = new Container<Task *>();
  int n = 10;
  for (int i = 0; i < n; ++i) {
    conteiner->pushBack(
        generateTask(std::experimental::randint(0, 4), conteiner));
  }

  EXPECT_EQ(conteiner->getLength(), 10);  
}

TEST(Clear, Simple) {
  Container<Task *> *conteiner = new Container<Task *>();
  int n = 10;
  for (int i = 0; i < n; ++i) {
    conteiner->pushBack(
        generateTask(std::experimental::randint(0, 4), conteiner));
  }
  Container<Task *>::Iterator it = conteiner->first();
  for (;it != conteiner->last(); it++) {
    Task *t = conteiner->peekFront();
    t->execute();
  }
  conteiner->clear();
  EXPECT_EQ(Object::getObjectCount(), 0);
}

TEST(AreEmpty, Simple) {
    Container<Task *> *conteiner = new Container<Task *>();
  int n = 10;
  for (int i = 0; i < n; ++i) {
    conteiner->pushBack(
        generateTask(std::experimental::randint(0, 4), conteiner));
  }
  Container<Task *>::Iterator it = conteiner->first();
  for (;it != conteiner->last(); it++) {
    Task *t = conteiner->peekFront();
    t->execute();
  }
  conteiner->clear();
  EXPECT_EQ(conteiner->isEmpty(), true);
}