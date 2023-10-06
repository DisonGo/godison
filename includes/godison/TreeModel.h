#ifndef TreeModel_H
#define TreeModel_H

#include <memory>
#include <string>
#include <vector>

namespace godison {
namespace models {
template <class T>
class TreeItem {
 public:
  using NodeType = T;
  TreeItem(NodeType* object, int insert_pos = -1, TreeItem* parent = nullptr)
      : node_(object), parent_item_(parent) {
    if (!parent) return;
    parent->AddChild(this, insert_pos);
  };
  void AddChild(TreeItem* child, int insert_pos = -1) {
    if (child == nullptr) return;
    if (child == this) return;
    if (IsChild(child)) return;
    if (insert_pos == -1) {
      child_items_.push_back(child);
    } else {
      insert_pos = std::min(ChildCount(), insert_pos + 1);
      child_items_.insert(child_items_.cbegin() + insert_pos, child);
    }
    child->SetParent(this);
  }
  void RemoveChild(TreeItem* child) {
    if (!IsChild(child)) return;
    child_items_.erase(child_items_.cbegin() + ChildIndex(child));
    child->SetParent(nullptr);
  }
  int ChildCount() { return child_items_.size(); }
  bool HasChild() { return ChildCount(); }
  int ChildCountRecoursive() {
    int count = ChildCount();
    for (auto& item : child_items_) count += item->ChildCountRecoursive();
    return count;
  }
  // Does not add/delete widget to/of parent's child list
  TreeItem* GetParent() { return parent_item_; }
  void SetParent(TreeItem* parent) { parent_item_ = parent; }
  bool IsChild(TreeItem* child) { return ChildIndex(child) != -1; }
  bool IsChildRecoursive(TreeItem* child) {
    if (IsChild(child)) return true;
    for (auto item : child_items_)
      if (item->IsChildRecoursive(child)) return true;
    return false;
  }
  bool IsChildObject(NodeType* object) {
    if (!object) return false;
    for (auto item : child_items_)
      if (item->node_ == object) return true;
    return false;
  }
  bool IsChildObjectRecoursive(NodeType* object) {
    if (IsChildObject(object)) return true;
    for (auto item : child_items_)
      if (item->IsChildObjectRecoursive(object)) return true;
    return false;
  }
  TreeItem* FindItemByObject(NodeType* object) {
    if (object == node_) return this;
    for (auto item : child_items_) {
      auto ptr = item->FindItemByObject(object);
      if (ptr) return ptr;
    };
    return nullptr;
  }
  bool IsRoot() { return (parent_item_ == nullptr); }
  void SetName(std::string name) { name_ = name; }
  const std::string& GetName() { return name_; }
  TreeItem* operator[](size_t index) {
    if (index >= child_items_.size()) return nullptr;
    return child_items_[index];
  }
  int ChildIndex(TreeItem* child) {
    int i = 0;
    for (auto& item : child_items_) {
      if (item == child) return i;
      ++i;
    }
    return -1;
  }
  NodeType* GetNode() { return node_; }
  int ChildGensCount() {
    int max_gen_count = 0;
    for (auto item : child_items_) {
      max_gen_count = std::max(item->ChildGensCount() + 1, max_gen_count);
    }
    return max_gen_count;
  }
  const std::vector<TreeItem*>& GetChildItems() { return child_items_; }
  ~TreeItem() {
    for (auto item : child_items_)
      if (item) delete item;
  }

 protected:
  std::string name_{};
  TreeItem* parent_item_{};
  NodeType* node_{};
  std::vector<TreeItem*> child_items_;
};
template <class T>
class TreeModel {
 public:
  using NodeType = T;
  using TItem = TreeItem<NodeType>;
  TreeModel() { root_ = std::make_shared<TItem>(nullptr); }
  virtual int Rows() {
    if (!root_) return 0;
    return root_->ChildCount();
  }
  virtual int Cols() {
    if (!root_) return 0;
    return root_->ChildGensCount();
  }
  std::shared_ptr<TItem> GetRoot() { return root_; }
  virtual void AddItem(NodeType* node, std::string label, int insert_pos = -1,
                       NodeType* parent_node = nullptr) = 0;
  virtual void DeleteItem(NodeType* node) = 0;
  bool IsInTree(NodeType* node) { return root_->IsChildObjectRecoursive(node); }

 protected:
  std::shared_ptr<TItem> root_;
};
}  // namespace models

}  // namespace godison

#endif  // TreeModel_H