#include "godison/TreeModel.h"
#include "iostream"
using namespace godison;
struct Point {
  int x{}, y{};
};
class EObjectTreeModel : public models::TreeModel<Point> {
 public:
  EObjectTreeModel() : TreeModel() {}
  std::shared_ptr<TItem> GetRoot() { return root_; }
  virtual void AddItem(NodeType* node, std::string label, int insert_pos = -1,
                       NodeType* parent = nullptr) override {
    static std::vector<std::shared_ptr<Point>> filler_objects;
    if (!node) return;
    if (root_->IsChildObjectRecoursive(node)) return;
    TItem* parent_item = root_->FindItemByObject(parent);
    auto new_item = new TItem(node, insert_pos, parent_item);
    new_item->SetName(label);
  }
  virtual void DeleteItem(NodeType* node) {}
  bool IsInTree(NodeType* node) { return root_->IsChildObjectRecoursive(node); }
};
int main() {
  EObjectTreeModel model;
  Point a, b, c;
  model.AddItem(&a, "A");
  model.AddItem(&b, "B", -1, &a);
  model.AddItem(&c, "C", -1, &b);
  std::cout << model.Cols() << " " << model.Rows();
  return 0;
}