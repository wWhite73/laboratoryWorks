#pragma once

class Tree {
private:
    int size;
    int value;
    Tree* childeren;

public:
    Tree();
    Tree(int size);
    Tree(int size, int value);
    Tree(const Tree&);

    virtual ~Tree();

    int getValue() const;
    int getSize() const;
    Tree* getChilderen() const;

    void setValue(int value);

    Tree& operator=(const Tree& tree);

    bool operator==(const Tree& tree) const;
    bool operator!=(const Tree& tree) const;

    friend const Tree operator+(const Tree& tree1, const Tree& Tree2);

    void print() const;
    void printr(int prefix) const;

};

class Leaf : public Tree {
public:
    Leaf();
    Leaf(const int value);
};
