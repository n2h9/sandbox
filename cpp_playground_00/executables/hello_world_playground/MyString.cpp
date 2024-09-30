#pragma once

#include <string.h>

#include <cstdint>
#include <iostream>

class MyString {
 public:
  MyString() = default;

  MyString(const char* string) : m_Size(strlen(string)) {
    m_Data = new char[m_Size];
    memcpy(m_Data, string, m_Size);
    printf("MyString created!\n");
  }

  MyString(const MyString& other) {
    m_Size = other.m_Size;
    m_Data = new char[m_Size];
    memcpy(m_Data, other.m_Data, m_Size);
    printf("MyString copied!\n");
  }

  MyString(MyString&& other) {
    m_Size = other.m_Size;
    m_Data = other.m_Data;

    other.m_Size = 0;
    other.m_Data = nullptr;
    printf("MyString moved!\n");
  }

  void Print() {
    for (auto i = 0; i < m_Size; i++) {
      printf("%c", m_Data[i]);
    }
    printf("\n");
  }

  ~MyString() {
    delete m_Data;
    printf("MyString deleted!\n");
  }

 private:
  char* m_Data;
  int m_Size;
};

class Entity {
 public:
  Entity() = default;
  explicit Entity(const MyString& name) : m_Name(name) {
    printf("Entity created! MyString passed by reference \n");
  }

  explicit Entity(MyString&& name) : m_Name(std::move(name)) {
    printf("Entity created! MyString passed by move \n");
  }

  void PrintName() { m_Name.Print(); }

  ~Entity() { printf("Entity deleted!\n"); }

 private:
  MyString m_Name;
};