#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED
#include <iostream>
#include <vector>


template <typename KeyType, typename ValueType>
class TreeMultimap
{
  private:
    struct Node {
        KeyType key;
        ValueType value;
        Node* left;
        Node* right;
        Node(const KeyType& k, const ValueType& v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };
    Node* root;

    void clear(Node* root) {
        if (root != nullptr)
        {
            clear(root->left);
            clear(root->right);
            delete root; // must do pot process to delete tree from leaf nodes up to root
        }
    }
    void insert(const KeyType& key, const ValueType& value, Node*& node)
    {
        if (node == nullptr)
        {
            node = new Node(key, value);
            return;
        }
        if (key < node->key)
        {
            insert(key, value, node->left);
        }
        else
            insert(key, value, node->right);
    }
    void find(Node* node, std::vector<Node*>& nodes, const KeyType& key) const
    {
        if (node)
        {
            if (key == node->key)
                nodes.push_back(node);
            find(node->right, nodes, key);
            find(node->left, nodes, key);
        }
    }
  public:
      class Iterator
      {
      public:
          Iterator(std::vector<Node*> nodes)
              : nodes(nodes), index(0)
          {
          }

          ValueType& get_value() const
          {
              if (!is_valid()) {
                  std::cout << "invalid: try again " << std::endl;
              
              }
              return nodes[index]->value;
          }

          bool is_valid() const
          {
              // Check if the index is within the bounds of the vector.
              if (index >= 0 && index < nodes.size())
                  return true;
              else
                  return false;
          }

          void advance()
          {
              if (!is_valid())
                  throw std::runtime_error("Invalid iterator cannot advance");

              index++;
          }

      private:
          std::vector<Node*> nodes; // assume this is a list of Nodes in the TreeMultimap that have the same key and have been constructed based on traversing the search tree
          int index;
      };


    TreeMultimap()
        : root(nullptr)
    {}

    ~TreeMultimap()
    {
        clear(root);
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        insert(key, value, root);//uses the private definition for insert as helper
    }

    Iterator find(const KeyType& key) const
    {
        std::vector<Node*> nodes;
        find(root , nodes, key);//uses the private definition for find as helper
        return Iterator(nodes);
    }
};

#endif // TREEMULTIMAP_INCLUDED
