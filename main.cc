#include "QColor"
#include "QVector3D"
#include "godison/Vectors.h"
#include "iostream"
using namespace godison;
int main() {
  const vectors::Vector3D a(1, 2, 3);
  auto qvec = a.ToQVector3D();
  return 0;
}