#include "QColor"
#include "godison/Vectors.h"
#include "iostream"
using namespace godison;
int main() {
  vectors::Vector3D a(QColor(233, 123, 42));
  std::cout << a;
}