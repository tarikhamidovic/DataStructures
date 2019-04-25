#ifndef _TODOTASK_HPP_
#define _TODOTASK_HPP_

#include<string>
#include<iostream>

class ToDoTask {
  public:
    ToDoTask() : id_{0}, priority_{0}, description_{"none"}, title_{"none"} {}
    ToDoTask(std::string title, std::string description, int priority) : title_{title}, description_{description}, priority_{priority}, id_{generateId()} {}
    bool operator<(const ToDoTask& other) {
      return priority_ < other.priority_;
    }
    bool operator>(const ToDoTask& other) {
      return priority_ > other.priority_;
    }
    bool operator==(int other) const {
      return id_ == other;
    }
    friend std::ostream& operator<<(std::ostream& out, const ToDoTask& task) {
      out << "Naziv: " << task.title_ << std::endl << "Opis: " << task.description_ << std::endl << "Prioritet: " << task.priority_ << std::endl << "ID: " << task.id_;
      return out;
    }
    ~ToDoTask() {}
  private:
    int id_, priority_;
    std::string description_, title_;
    int generateId() {
      static int counter = 0;
      return ++counter;
    }
};

#endif
