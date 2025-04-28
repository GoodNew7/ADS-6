// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <stdexcept>

template<typename T>
class TPQueue {
 private:
  struct QueueNode {
    T queueData;
    QueueNode* nextNode;
    explicit QueueNode(const T& val) : queueData(val), nextNode(nullptr) {}
  };
  QueueNode* queueHead;

 public:
  TPQueue() : queueHead(nullptr) {}

  ~TPQueue() {
    while (queueHead) {
      QueueNode* nodeToDelete = queueHead;
      queueHead = queueHead->nextNode;
      delete nodeToDelete;
    }
  }

  void enqueue(const T& item) {
    QueueNode* newNode = new QueueNode(item);
    if (!queueHead) {
      queueHead = newNode;
      return;
    }
    if (item.prior > queueHead->queueData.prior) {
      newNode->nextNode = queueHead;
      queueHead = newNode;
      return;
    }
    QueueNode* currentNode = queueHead;
    while (currentNode->nextNode &&
           currentNode->nextNode->queueData.prior >= item.prior) {
      currentNode = currentNode->nextNode;
    }
    newNode->nextNode = currentNode->nextNode;
    currentNode->nextNode = newNode;
  }

  T dequeue() {
    if (!queueHead) {
      throw std::out_of_range("Queue is empty!");
    }
    QueueNode* nodeToRemove = queueHead;
    T tempValue = queueHead->queueData;
    queueHead = queueHead->nextNode;
    delete nodeToRemove;
    return tempValue;
  }

  void push(const T& item) {
    enqueue(item);
  }

  T pop() {
    return dequeue();
  }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_

