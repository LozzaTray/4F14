#include <iostream>
#include <thread>
using namespace std;

class LinkNode
{
private:
    string data;
    LinkNode *prev;
    LinkNode *next;

public:
    LinkNode(string x){
        this->data = x;
    }

    string get_data()
    {
        return this->data;
    }

    void set_prev(LinkNode *node)
    {
        prev = node;
    }

    void set_next(LinkNode *node)
    {
        next = node;
    }

    LinkNode *get_prev()
    {
        return this->prev;
    }

    LinkNode *get_next()
    {
        return this->next;
    }
};

class LinkedList
{
private:
    LinkNode *head;
    int length;

public:
    LinkedList()
    {
        length = 0;
        head = new LinkNode("");
        head->set_prev(NULL);
        head->set_next(NULL);
    }

    void insert(string x)
    {
        // Insertion done at front of the list
        LinkNode *n = new LinkNode(x);
        n->set_next(head->get_next());
        if (head->get_next() != NULL)
            (head->get_next())->set_prev(n);
        head->set_next(n);
        n->set_prev(NULL);
        length++;
    }

    void print_nodes()
    {
        LinkNode *node = head->get_next();
        cout << "HEAD <--> ";
        while (node != NULL)
        {
            cout << node->get_data() << " <--> ";
            node = node->get_next();
        }
        cout << "TAIL";
        cout << endl;
    }
};


int main()
{
    cout << "4F14 - Doubly Linked List CW - Multi-Threading" << endl << endl;
    LinkedList *ll = new LinkedList();
    ll->insert("a");
    ll->insert("b");
    ll->print_nodes();
}