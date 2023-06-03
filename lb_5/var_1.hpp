#pragma once

#include <iostream>
#include "stdint.h"

#define BUS_CAPACITY 12
#define PASSANGER_COUNT 5

const char tab[] = "  ";

struct passanger {
  passanger* next = nullptr;
  char name[10] = "";
  uint8_t in; // остановка на которой сел
  uint8_t out; // остановка на которой выходит
};

struct bus {
  passanger *last = nullptr; // последний вошедший пассажир
  uint8_t capacity = BUS_CAPACITY;
  uint8_t pass_count = 0;
};

void insert(bus &b, passanger &p);
void remove(bus &b, passanger &p);
void remove_first(bus &b);
void move_to_exit(bus &b, passanger &p);
void print_status(passanger &p, char *);
void print_status(char *);

/**
 * Bus:
 * 
 * in -> | 0, 1, 2, 3, 4 | -> out
 *         ^           ^
 *        last       first
 */
void happy_bus() {
  // создание объектов
  passanger passangers[PASSANGER_COUNT] = {
    { nullptr, "Denis", 1, 2 },
    { nullptr, "Andrey", 2, 6 },
    { nullptr, "Badma", 4, 5 },
    { nullptr, "Ivan", 3, 4 },
    { nullptr, "Bair", 2, 7 }
  };
  bus busy_bus;

  // имитация работы автобуса
  for (uint8_t stop = 1; stop <= 10; ++stop) {
    // печатаем номер остановки
    std::cout << "Stop #" << (int)stop << std::endl;
    for (uint8_t i = 0; i < PASSANGER_COUNT; ++i) {
      if (passangers[i].in == stop) {
        insert(busy_bus, passangers[i]);
      }
      if (passangers[i].out == stop) {
        remove(busy_bus, passangers[i]);
      }
    }
    std::cout << '\n';
  }
}

void insert(bus &b, passanger &p) {
  if (b.pass_count == b.capacity) {
    print_status("bus is full.");
    return;
  }
  p.next = b.last;
  b.last = &p;
  b.pass_count += 1;
  print_status(p, " entered the bus.");
}

void remove(bus &b, passanger &p) {
  if (b.pass_count == 0) {
    print_status("bus is empty.");
    return;
  }
  passanger *temp = b.last;
  if (temp == &p) { // only one
    b.last = p.next;
  } else {
    while (temp->next != &p) {
      if (temp->next == nullptr) return; // no passanger
      temp = temp->next;
    }
    temp->next = p.next;
    p.next = nullptr;
  }
  b.pass_count -= 1;
  print_status(p, " left the bus.");
}

void remove_first(bus &b) {
  passanger *temp = b.last;
  if (temp == nullptr) return; // no passanger
  if (temp->next == nullptr) { // only one
    b.last = nullptr;
  } else {
    while (temp->next->next != nullptr) {
      temp = temp->next;
    }
    temp->next = nullptr;
  }
  b.pass_count -= 1;
}

void move_to_exit(bus &b, passanger &p) {
  passanger *temp = b.last;
  if (temp == nullptr) return; // no passanger
  if (temp == &p) return; // only one
  while (temp->next != &p) {
    if (temp->next == nullptr) return; // no such passanger
    temp = temp->next;
  }
  temp->next = p.next;
  p.next = nullptr;
  while (temp->next != nullptr) {
    temp = temp->next;
  }
  temp->next = &p;
}

void print_status(passanger &p, char* msg) {
  std::cout << tab << p.name << msg << std::endl;
}

void print_status(char *msg) {
  std::cout << tab << msg << std::endl;
}