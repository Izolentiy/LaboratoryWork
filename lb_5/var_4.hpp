#include <string>
#include <iostream>

struct tovar {
  std::string name; // название элемента списка
  int count = 0; // количество в списке
  tovar *next = nullptr; // указатель на следующий элемент в списке
  
  tovar(std::string _name, int _count) : name(_name), count(_count) {};
};

struct list{
  tovar *first = nullptr; // указатель на первый элемент списка

  tovar *search(std::string name) {
    if (first == nullptr) return first;

    tovar* temp = first;
    while (name != temp->name) {
      if (temp->next == nullptr) return temp;

      temp = temp->next;
    }
    return temp;
  }

  // добавление товара в список
  void add_tovar(const std::string &name, int count) {
    tovar *item = new tovar(name, count);

    if (first == nullptr) {
      // список пустой, значит первым элементом
      // станет наш товар который мы добавляем
      first = item;
      return;
    }
    
    // проходимся по списку, пока не найдем товар,
    // который указывает на товар который мы хотим добавить
    // list { tomato, banana, pasta, rice }
    tovar* temp = first;
    while (name != temp->name) {
      if (temp->next == nullptr) {
        // товара в списке не оказалось, то есть мы дошли до конца
        // добавляем его в конец
        temp->next = item;
        return;
      }
      temp = temp->next;
    }

    // оказалось, что список содержит данный товар
    // значит нам нам надо увеличить его количество
    temp->count += count;
  }

  void print() {
    std::cout << "Spisok pokupok: \n\n";
    tovar *temp = first;
    while (temp != nullptr) {
      std::cout << temp->name << "  " << temp->count << '\n';
      temp = temp->next;
    }
    std::cout << "\n\n";
    
  }

  // удаление товара из списка
  void remove_tovar(const std::string &name) {
    if (first == nullptr) {
      // список пустой значит мы ничего не удаляем
      return;
    }
    
    // проходимся по списку, пока не найдем товар,
    // который указывает на товар который мы хотим добавить
    // list { tomato }
    tovar* temp = first;
    tovar* rem;
    if (temp->next == nullptr) {
      if (name == temp->name) {
        first = nullptr;
      }
      return;
    }
    if (name == temp->name) {
      first = temp->next;
      delete []temp; // <---------------
      return;
    }
    while (name != temp->next->name) {
      if (temp->next->next == nullptr) {
        // товара в списке не оказалось, то есть мы дошли до конца
        // добавляем его в конец
        return;
      }
      temp = temp->next;
    }

    // <---------------
    rem = temp->next; // указатель на удаляемый элемент
    temp->next = rem->next; // предыдущий элемент указывает на следующий
    delete []rem; // очищаем память
  }
};

int main_4() {
  // создаем наши товары
  tovar tomato("tomato", 5);
  tovar banana("banana", 2);
  tovar pasta("pasta", 6);
  tovar rice("rice", 2);
  tovar apple("apple", 5);

  list spisok;

  spisok.add_tovar("tomato", 6);
  spisok.add_tovar("banana", 3);
  spisok.print();
  spisok.remove_tovar("tomato");
  spisok.print();

}

// хотим добавить tomato
// list {  }
// first == nullptr, то есть он пустой
// first = tomato
// list { tomato }

// хотим снова добавить tomato
// list { tomato }
//           ^
// temp = first , то есть

// list { tomato, banana, pasta, rice }
//                   ^

// list { tomato, banana, pasta, rice }
//                          ^

// list { tomato, banana, pasta, rice }
//                                ^


