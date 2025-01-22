#pragma once
#include "AdventurePoint.h"
#include "Hall.h"


template <typename T>
class TreeNode
{
public:
    TreeNode* left;
    TreeNode* right;
    T data;
    

    TreeNode(T Data, TreeNode* _left = nullptr, TreeNode* _right = nullptr)
    {
        data = Data;
        left = _left;
        right = _right;
    }

    // ~TreeNode()
    // {
    //     delete left;
    //     delete right;
    // }
};

class BinaryTree
{
public:
    TreeNode<AdventurePoint>* Root;
    BinaryTree(TreeNode<AdventurePoint>* root)
    {
        Root = root;
    }
    ~BinaryTree()
    {
        Clear(Root);
        Root = nullptr;
    }

    void Clear(const TreeNode<AdventurePoint>* node)
    {
        if (node == NULL)
        {
            return;
        }
        Clear(node->left);
        Clear(node->right);
        delete node;
    }
};

class Adventure
{
public:
    string name;
    BinaryTree* AdventureTree;
    TreeNode<AdventurePoint>* RootNode;
    TreeNode<AdventurePoint>* CurrentNode;
    int gold;

    Adventure(const string& name, TreeNode<AdventurePoint>* root)
        : name(name)
    {
        
        RootNode = root;
        AdventureTree = new BinaryTree(RootNode);
        CurrentNode = AdventureTree->Root;
        gold = 0;
    }

    // ~Adventure()
    // {
    //     //delete CurrentNode;
    //     delete AdventureTree;
    // }
};

