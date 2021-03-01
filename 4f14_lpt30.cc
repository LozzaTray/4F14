#include <iostream>
#include <thread>
using namespace std;

int random_integer(int lower_cutoff, int upper_cutoff);

class LinkNode
{
private:
    string data;
    LinkNode *prev;
    LinkNode *next;

public:
    LinkNode(string x)
    {
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

    void populate()
    {
        const int num_nodes = 140;
        const int min_length = 3;
        const int max_length = 10;

        const string alphabet = "abcdefghijklmnopqrstuvwxyz";
        const int alphabet_length = alphabet.length();

        for (int i = 0; i < num_nodes; i++)
        {
            int data_length = random_integer(min_length, max_length);
            string data = "";
            
            for (int j = 0; j < data_length; j++)
            {
                int index = random_integer(0, alphabet_length);
                char character = alphabet[index];
                data += character;
            }

            this->insert(data);
        }
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

    void print()
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

int random_integer(int lower_cutoff, int upper_cutoff)
{
    int offset = rand() % (upper_cutoff - lower_cutoff);
    return lower_cutoff + offset;
}

int main()
{
    cout << "4F14 - Doubly Linked List CW - Multi-Threading" << endl
         << endl;
    LinkedList *ll = new LinkedList();
    ll->populate();
    ll->print();
}