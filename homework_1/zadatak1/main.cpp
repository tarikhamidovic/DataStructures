#include<iostream>
#include"list.hpp"
#include"todotask.hpp"
#include<string>

int main(int argc, char *argv[])
{
  std::cout << "************Notes************" << std::endl;
  List<ToDoTask> mylist;
  bool programRunning = true;
  while (programRunning) {
    std::cout << "1 - Unos nove obaveze" << std::endl;
    std::cout << "2 - Prikaz trenutnih obaveza" << std::endl;
    std::cout << "3 - Oznacavanje obaveze kao zavrsene" << std::endl;
    std::cout << "0 - Kraj programa" << std::endl;
    std::cout << "Unesite opciju: ";
    int menu;
    std::cin >> menu;
    std::cout << "------------------------------------" << std::endl;
    switch (menu) {
      case 1: {
        std::cout << "Unesite naslov: ";
        std::string title;
        std::cin >> title;
        std::cin.ignore();
        std::cout << "Unesite opis: ";
        std::string description;
        std::getline(std::cin, description);
        std::cout << "Unesite prioritet(1 -> high, 2 -> medium, 3 -> low): ";
        int priority;
        std::cin >> priority;
        mylist.add(ToDoTask(title, description, priority));
        std::cout << "Nova obaveza uspjesno unesena!" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        break;
        }
      case 2: {
        if (mylist.size() == 0) {
          std::cout << "Vasa lista sa obavezama je prazna!" << std::endl;
          std::cout << "------------------------------------" << std::endl;
        }
        mylist.print();
        break;
      }
      case 3: {
        if (mylist.size() == 0) {
          std::cout << "Vasa lista sa obavezama je prazna!" << std::endl;
          std::cout << "------------------------------------" << std::endl;
          break;
        }
        std::cout << "Unesite ID obaveze koju zelite obrisati: ";
        int id;
        std::cin >> id;
        auto lambda = [=] (const ToDoTask& task) {
          return task == id;
        };
        auto it = mylist.find(lambda);
        if (it == mylist.end()) {
          std::cout << "Obaveza sa datim ID-om ne postoji!" << std::endl;
        }
        else {
          mylist.remove(it);
          std::cout << "Obaveza sa ID: " << id  << " uspijesno obrisana!"<< std::endl;
        }
        std::cout << "------------------------------------"  << std::endl;
        break;
      }
      case 0: {
        programRunning = false;
        break;
      }
      default:
        std::cout << "Pogresan unos!" << std::endl;
    }
  }
  return 0;
}
