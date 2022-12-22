//
// Created by Egor Vasilkov on 21.12.22.
//

#ifndef POISLAB31__NGRAPH_H_
#define POISLAB31__NGRAPH_H_


#pragma once
#include <memory>
#include <stdexcept>
#include <iostream>

/// <summary>
/// Simulates rib structure in Graph.
/// </summary>
template <class T>
struct Rib
{
  T id;
  Rib<T>* nextRib = nullptr;
};

/// <summary>
/// Simulates node structure in Graph.
/// </summary>
template <class T>
struct Node
{
  T key;
  int ribCount = 0;
  Node<T>* next = nullptr;
  Rib<T>* nextRib = nullptr;
};

/// <summary>
/// Simulates graph via orthogonal adjacency list with nodes and ribs.
/// </summary>
template <class T, class A = std::allocator<T>>
class Graph
{
 public:
  typedef A allocator_type;
  typedef typename A::value_type value_type;
  typedef typename A::reference reference;
  typedef typename A::const_reference const_reference;
  typedef typename A::pointer pointer;

  /// <summary>
  /// Provides methods to iterate through nodes in Graph class.
  /// </summary>
  class NodeIterator
  {
   public:
    typedef std::forward_iterator_tag iterator_category;
    typedef Node<T> value_type;
    typedef ptrdiff_t difference_type;
    typedef value_type* pointer;
    typedef value_type& reference;

    NodeIterator(pointer ptr)
        :node(ptr) {}

    NodeIterator(const NodeIterator& iterator)
    {
      node = iterator.node;
    }

    NodeIterator& operator=(const NodeIterator& iterator)
    {
      node = iterator.node;
      return this;
    }

    NodeIterator& operator++()
    {
      node = node->next;
      return *this;
    }

    reference operator*() const
    {
      return *node;
    }

    pointer operator->() const
    {
      return node;
    }

    friend bool operator==(const NodeIterator& firstIterator, const NodeIterator& secondIterator)
    {
      return firstIterator.node == secondIterator.node;
    }

    friend bool operator!=(const NodeIterator& firstIterator, const NodeIterator& secondIterator)
    {
      return firstIterator.node != secondIterator.node;
    }

    NodeIterator operator++(int)
    {
      pointer a = node;
      node = node->next;
      return a;
    }

    pointer node;
  };

  /// <summary>
  /// Const modification of NodeIterator.
  /// </summary>
  class ConstNodeIterator
  {
   public:
    typedef std::forward_iterator_tag iterator_category;
    typedef Node<T> value_type;
    typedef ptrdiff_t difference_type;
    typedef const value_type* pointer;
    typedef const value_type& reference;

    ConstNodeIterator(pointer ptr)
        :node(ptr) {}
    ConstNodeIterator(const ConstNodeIterator& iterator)
    {
      node = iterator.node;
    }
    ConstNodeIterator(const NodeIterator& iterator)
    {
      node = iterator.node;
    }

    ConstNodeIterator& operator=(const ConstNodeIterator& iterator)
    {
      node = iterator.node;
      return this;
    }

    ConstNodeIterator& operator++()
    {
      node = node->next;
      return this;
    }

    reference operator*() const
    {
      return *node;
    }

    pointer operator->() const
    {
      return node;
    }

    friend bool operator==(const ConstNodeIterator& firstIterator, const ConstNodeIterator& secondIterator)
    {
      return firstIterator.node == secondIterator.node;
    }

    friend bool operator!=(const ConstNodeIterator& firstIterator, const ConstNodeIterator& secondIterator)
    {
      return firstIterator.node != secondIterator.node;
    }

    ConstNodeIterator operator++(int)
    {
      pointer a = node;
      node = node->next;
      return a;
    }

    pointer node;
  };

  /// <summary>
  /// Provides methods to iterate through ribs in Graph class.
  /// </summary>
  class RibIterator
  {
   public:
    typedef std::forward_iterator_tag iterator_category;
    typedef Rib<T> value_type;
    typedef ptrdiff_t difference_type;
    typedef value_type* pointer;
    typedef value_type& reference;

    RibIterator(NodeIterator nodeIterator)
    {
      if (nodeIterator == nullptr)
        rib = nullptr;
      else
        rib = nodeIterator->nextRib;
    }
    RibIterator(pointer ptr)
        :rib(ptr) {}
    RibIterator(const RibIterator& iterator)
    {
      rib = iterator.rib;
    }

    RibIterator& operator=(const RibIterator& iterator)
    {
      rib = iterator.rib;
      return this;
    }

    RibIterator& operator++()
    {
      rib = rib->nextRib;
      return this;
    }

    reference operator*() const
    {
      return *rib;
    }

    pointer operator->() const
    {
      return rib;
    }

    friend bool operator==(const RibIterator& firstIterator, const RibIterator& secondIterator)
    {
      return firstIterator.rib == secondIterator.rib;
    }

    friend bool operator!=(const RibIterator& firstIterator, const RibIterator& secondIterator)
    {
      return firstIterator.rib != secondIterator.rib;
    }

    RibIterator operator++(int)
    {
      pointer a = rib;
      rib = rib->nextRib;
      return a;
    }

    pointer rib;
  };

  /// <summary>
  /// Const modification of RibIterator.
  /// </summary>
  class ConstRibIterator
  {
   public:
    typedef std::forward_iterator_tag iterator_category;
    typedef Rib<T> value_type;
    typedef ptrdiff_t difference_type;
    typedef const value_type* pointer;
    typedef const value_type& reference;

    ConstRibIterator(NodeIterator nodeIterator)
    {
      if (nodeIterator == nullptr)
        rib = nullptr;
      else
        rib = nodeIterator->nextRib;
    }

    ConstRibIterator(ConstNodeIterator nodeIterator)
    {
      if (nodeIterator == nullptr)
        rib = nullptr;
      else
        rib = nodeIterator->nextRib;
    }

    ConstRibIterator(pointer ptr)
        :rib(ptr) {}

    ConstRibIterator(const ConstRibIterator& iterator)
    {
      rib = iterator.rib;
    }

    ConstRibIterator(const RibIterator& iterator)
    {
      rib = iterator.rib;
    }

    ConstRibIterator& operator=(const ConstRibIterator& iterator)
    {
      rib = iterator.rib;
      return this;
    }

    ConstRibIterator& operator++()
    {
      rib = rib->nextRib;
      return this;
    }

    reference operator*() const
    {
      return *rib;
    }

    pointer operator->() const
    {
      return rib;
    }

    friend bool operator==(const ConstRibIterator& firstIterator, const ConstRibIterator& secondIterator)
    {
      return firstIterator.rib == secondIterator.rib;
    }

    friend bool operator!=(const ConstRibIterator& firstIterator, const ConstRibIterator& secondIterator)
    {
      return firstIterator.rib != secondIterator.rib;
    }

    ConstRibIterator operator++(int)
    {
      pointer a = rib;
      rib = rib->nextRib;
      return a;
    }

    pointer rib;
  };

  RibIterator RBegin(NodeIterator nodeIterator)
  {
    return RibIterator(nodeIterator);
  }

  RibIterator REnd()
  {
    return RibIterator(nullptr);
  }

  ConstRibIterator CRBegin(NodeIterator nodeIterator) const
  {
    return ConstRibIterator(nodeIterator);
  }

  ConstRibIterator CRBegin(ConstNodeIterator nodeIterator) const
  {
    return ConstRibIterator(nodeIterator);
  }

  ConstRibIterator CREnd(NodeIterator nodeIterator) const
  {
    return ConstRibIterator(nullptr);
  }

  ConstRibIterator CREnd(ConstNodeIterator nodeIterator) const
  {
    return ConstRibIterator(nullptr);
  }

  NodeIterator begin()
  {
    return NodeIterator(Head);
  }

  NodeIterator end()
  {
    return NodeIterator(nullptr);
  }

  ConstNodeIterator Cbegin() const
  {
    return ConstNodeIterator(Head);
  }

  ConstNodeIterator Cend() const
  {
    return ConstNodeIterator(nullptr);
  }

  Graph();
  Graph(const Graph&);
  ~Graph();

  /// <summary>
  /// Checks if Graph has no nodes.
  /// </summary>
  /// <returns>True if empty, false if not.</returns>
  bool IsEmpty() const;

  /// <summary>
  /// Removes all ribs and nodes from Graph.
  /// </summary>
  void Clear();

  /// <summary>
  /// Checks if Graph has node with 'value' key.
  /// </summary>
  /// <param name = "value">Key to search by.</param>
  /// <returns>True if node is found, false if not.</returns>
  bool HasNode(value_type value);

  /// <summary>
  /// Checks if a rib connecting two nodes exists.
  /// </summary>
  /// <param name = "firstKey">Key to search first node by.</param>
  /// <param name = "secondKey">Key to search second node by.</param>
  /// <returns>True if rib exists, false if not.</returns>
  bool AreConnected(value_type firstKey, value_type secondKey) const;

  /// <summary>
  /// Provides amount of nodes on Graph.
  /// </summary>
  /// <returns>Amount of nodes.</returns>
  int GetNodeAmount() const;

  /// <summary>
  /// Provides amount of ribs of a node with 'key' key.
  /// </summary>
  /// <param name = "key">Key to search by.</param>
  /// <returns>Amount of ribs.</returns>
  int GetRibCount(value_type key) const;

  /// <summary>
  /// Adds another node with 'value' key.
  /// </summary>
  /// <param name = "value">Key to search by.</param>
  void AddNode(value_type value);

  /// <summary>
  /// Adds rib between two nodes.
  /// </summary>
  /// <param name = "firstKey">Key to search first node by.</param>
  /// <param name = "secondKey">Key to search second node by.</param>
  void AddRib(value_type firstKey, value_type secondKey);

  /// <summary>
  /// Deletes node from a Graph.
  /// </summary>
  /// <param name = "firstKey">Key to search node by.</param>
  void RemoveNode(value_type key);

  /// <summary>
  /// Remoces rib between two nodes.
  /// </summary>
  /// <param name = "firstKey">Key to search first node by.</param>
  /// <param name = "secondKey">Key to search second node by.</param>
  void RemoveRib(value_type firstKey, value_type secondKey);

  pointer operator[](value_type index)
  {
    Node<value_type>* node = GetNode(index);
    if (node == nullptr)
      throw std::invalid_argument("No such node found");
    value_type* valueArray = new value_type[node->ribCount];
    RibIterator ribTraveller = node->nextRib;
    for (int i = 0; i < node->ribCount; i++)
    {
      valueArray[i] = ribTraveller->id;
      ribTraveller++;
    }
    return valueArray;
  }

  Graph<value_type>& operator=(const Graph<value_type>& graph)
  {
    while (Tail != nullptr)
    {
      RemoveNode(Head->key);
    }
    Node<value_type>* nodeTraveller = graph.Head;
    for (int i = 0; i < graph.nodeAmount; i++)
    {
      this->AddNode(nodeTraveller->key);
      Rib<value_type>* ribTraveller = nodeTraveller->nextRib;
      for (int j = 0; j < nodeTraveller->ribCount; j++)
      {
        this->AttachRibToNode(new Rib<value_type>(), this->Tail, ribTraveller->id);
        ribTraveller = ribTraveller->nextRib;
      }
      nodeTraveller = nodeTraveller->next;
    }

    return *this;
  }

  bool operator==(const Graph&) const;
  bool operator!=(const Graph&) const;
  bool operator>(const Graph&) const;
  bool operator<(const Graph&) const;
  bool operator>=(const Graph&) const;
  bool operator<=(const Graph&) const;

 private:

  Node<value_type>* GetNode(value_type key) const
  {
    NodeIterator nodeFinder = Head;
    while (nodeFinder != nullptr)
    {
      if (nodeFinder->key == key)
        return nodeFinder.node;
      nodeFinder++;
    }
    return nullptr;
  }

  Rib<value_type>* FindRib(value_type firstKey, value_type secondKey) const
  {
    RibIterator ribFinder = GetNode(firstKey)->nextRib;
    while (ribFinder != nullptr)            // ����� �����
    {
      if (ribFinder->id == secondKey)
        return ribFinder.rib;
      ribFinder++;
    }
    return nullptr;
  }

  void AttachRibToNode(Rib<value_type>* rib, Node<value_type>* node, value_type key)
  {
    rib->id = key;
    rib->nextRib = node->nextRib;         // ���������� �����
    node->nextRib = rib;
    node->ribCount++;
  }

  void DettachRibFromNode(Node<value_type>* node, value_type key)
  {
    RibIterator firstRibFinder = node->nextRib;
    Rib<value_type>* previousRib = nullptr;
    while (firstRibFinder->id != key)
    {
      previousRib = firstRibFinder.rib;                       // ����� ����� � ������������
      firstRibFinder++;
    }
    if (previousRib == nullptr)                             // �������� �����
    {
      Rib<value_type>* temp = firstRibFinder->nextRib;
      delete node->nextRib;
      node->nextRib = temp;
    }
    else
    {
      Rib<value_type>* temp = firstRibFinder->nextRib;
      delete previousRib->nextRib;
      previousRib->nextRib = temp;
    }
    node->ribCount--;
  }

  Node<value_type>* Head;
  Node<value_type>* Tail;

  friend std::ostream& operator<< (std::ostream& out, const Graph& graph)
  {
    for (ConstNodeIterator nodeTraveller = graph.Cbegin(); nodeTraveller != graph.Cend(); nodeTraveller++)
    {
      out << nodeTraveller->key << " ";
    }

    return out;
  }

  int nodeAmount;
};

template<class T, class A>
inline Graph<T, A>::Graph()
{
  Head = nullptr;
  Tail = nullptr;
  nodeAmount = 0;
}

template<class T, class A>
inline Graph<T, A>::Graph(const Graph& graph)
{
  Node<value_type>* nodeTraveller = graph.Head;
  for (int i = 0; i < graph.nodeAmount; i++)
  {
    this->AddNode(nodeTraveller->key);
    Rib<value_type>* ribTraveller = nodeTraveller->nextRib;
    for (int j = 0; j < nodeTraveller->ribCount; j++)
    {
      Rib<value_type>* newRib = new Rib<value_type>();
      this->AttachRibToNode(newRib, this->Tail, ribTraveller->id);
      ribTraveller = ribTraveller->nextRib;
    }
    nodeTraveller = nodeTraveller->next;
  }
}


template<class T, class A>
inline Graph<T, A>::~Graph()
{
  Clear();
}

template<class T, class A>
inline bool Graph<T, A>::IsEmpty() const
{
  return nodeAmount == 0;
}

template<class T, class A>
inline void Graph<T, A>::Clear()
{
  while (Tail != nullptr)
  {
    RemoveNode(Head->key);
  }
}

template<class T, class A>
inline bool Graph<T, A>::HasNode(value_type value)
{
  return GetNode(value) != nullptr;
}

template<class T, class A>
inline bool Graph<T, A>::AreConnected(value_type firstKey, value_type secondKey) const
{
  return FindRib(firstKey, secondKey) != nullptr;
}

template<class T, class A>
inline int Graph<T, A>::GetNodeAmount() const
{
  return nodeAmount;
}

template<class T, class A>
inline int Graph<T, A>::GetRibCount(value_type key) const
{
  if (!HasNode(key))
  {
    return 0;
  }
  Node<value_type>* nodeFinder = GetNode(key);

  return nodeFinder->ribCount;
}

template<class T, class A>
inline void Graph<T, A>::AddNode(value_type value)
{
  if (HasNode(value))
  {
    throw std::invalid_argument(value + " node already exists");
  }

  Node<value_type>* newNode = new Node<value_type>();
  newNode->key = value;
  newNode->ribCount = 0;
  if (nodeAmount == 0)
  {
    Head = newNode;
    Tail = newNode;
  }
  else
  {
    Tail->next = newNode;
    Tail = newNode;
  }

  nodeAmount++;
}

template<class T, class A>
inline void Graph<T, A>::AddRib(value_type firstKey, value_type secondKey)
{
  if (!HasNode(firstKey))
  {
    throw std::invalid_argument(firstKey + " node doesn't exist");
  }
  else if (!HasNode(secondKey))
  {
    throw std::invalid_argument(secondKey + " node doesn't exist");
  }
  else if (AreConnected(firstKey, secondKey))
  {
    std::cout << firstKey << " and " << secondKey << " are already connected\n";
  }
  else
  {
    Node<value_type>* firstNode = GetNode(firstKey);

    Rib<value_type>* newRib = new Rib<value_type>();
    AttachRibToNode(newRib, firstNode, secondKey);

    Node<value_type>* secondNode = GetNode(secondKey);

    newRib = new Rib<value_type>();
    AttachRibToNode(newRib, secondNode, firstKey);
  }
}

template<class T, class A>
inline void Graph<T, A>::RemoveNode(value_type key)
{
  if (!HasNode(key))
  {
    throw std::invalid_argument(key + " node doesn't exist");
  }
  Node<value_type>* prevNode = nullptr;
  NodeIterator nodeFinder = Head;
  while (nodeFinder->key != key)                      // ����� ���� � ������������
  {
    prevNode = nodeFinder.node;
    nodeFinder++;
  }
  Rib<value_type>* rib = nodeFinder->nextRib;
  while (nodeFinder->ribCount != 0)
  {
    RemoveRib(nodeFinder->key, rib->id);            // �������� ����
    rib = nodeFinder->nextRib;
  }
  delete rib;
  if (prevNode == nullptr)
  {
    Head = Head->next;
  }
  else
  {
    prevNode->next = nodeFinder->next;
  }

  if (nodeFinder->next == nullptr)
    Tail = prevNode;
  delete nodeFinder.node;
  nodeAmount--;
}

template<class T, class A>
inline void Graph<T, A>::RemoveRib(value_type firstKey, value_type secondKey)
{
  if (!HasNode(firstKey))
  {
    throw std::invalid_argument(firstKey + " node doesn't exist");
  }
  else if (!HasNode(secondKey))
  {
    throw std::invalid_argument(secondKey + " node doesn't exist");
  }
  else
  {
    Node<value_type>* firstNodeFinder = GetNode(firstKey);
    DettachRibFromNode(firstNodeFinder, secondKey);

    Node<value_type>* secondNodeFinder = GetNode(secondKey);
    DettachRibFromNode(secondNodeFinder, firstKey);
  }
}

template<class T, class A>
inline bool Graph<T, A>::operator==(const Graph& graph) const
{
  if (graph.nodeAmount != this->nodeAmount)
    return false;

  NodeIterator nodeTraveller = graph.Head;
  for (int i = 0; i < graph.nodeAmount; i++)
  {
    Node<value_type>* foundNode = GetNode(nodeTraveller->key);
    if (foundNode == nullptr)
      return false;
    RibIterator ribTraveller = nodeTraveller->nextRib;
    if (nodeTraveller->ribCount != foundNode->ribCount)
      return false;
    for (int j = 0; j < nodeTraveller->ribCount; j++)
    {
      if (!AreConnected(ribTraveller->id, nodeTraveller->key))
        return false;
      ribTraveller++;
    }
    nodeTraveller++;
  }
  return true;
}

template<class T, class A>
inline bool Graph<T, A>::operator!=(const Graph& graph) const
{
  return !operator==(graph);
}

template<class T, class A>
inline bool Graph<T, A>::operator>(const Graph& graph) const
{
  return this->nodeAmount > graph.nodeAmount;
}

template<class T, class A>
inline bool Graph<T, A>::operator<(const Graph& graph) const
{
  return this->nodeAmount < graph.nodeAmount;
}

template<class T, class A>
inline bool Graph<T, A>::operator>=(const Graph& graph) const
{
  return operator>(graph) || operator==(graph);
}

template<class T, class A>
inline bool Graph<T, A>::operator<=(const Graph& graph) const
{
  return operator<(graph) || operator==(graph);
}

#endif //POISLAB31__NGRAPH_H_
