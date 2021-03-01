#include <iostream>
#include <thread>
#include <chrono>
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
    LinkNode *tail;
    int length;

public:
    LinkedList()
    {
        length = 0;
        head = new LinkNode("HEAD");
        tail = new LinkNode("TAIL");
        
        head->set_prev(NULL);
        head->set_next(tail);

        tail->set_prev(head);
        tail->set_next(NULL);
    }

    int get_length()
    {
        return length;
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
        LinkNode *current = new LinkNode(x);
        LinkNode *next = head->get_next();

        current->set_next(next);
        if (next != NULL)
            next->set_prev(current);
        
        head->set_next(current);
        current->set_prev(head);
        
        length++;
    }

    void remove(LinkNode *node)
    {
        // assume that node is in the list
        LinkNode *prev = node->get_prev();
        LinkNode *next = node->get_next();

        prev->set_next(next);
        next->set_prev(prev);

        length--; 
    }

    void remove_at_random()
    {
        int index = random_integer(0, length);
        LinkNode *node = head->get_next();
        for(int i = 0; i < index; i++)
        {
            node = node->get_next();
        }
        remove(node);
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

    string concatenate_data()
    {
        LinkNode *node = head->get_next();
        string repr = "";
        while (node != tail)
        {
            repr += node->get_data();
            node = node->get_next();
        }
        return repr;
    }

};

int random_integer(int lower_cutoff, int upper_cutoff)
{
    int offset = rand() % (upper_cutoff - lower_cutoff);
    return lower_cutoff + offset;
}

LinkedList *ll;

void period_print()
{
    int millis = 1000;
    while (ll->get_length() > 0)
    {
        this_thread::sleep_for(chrono::milliseconds(millis));
        string repr = ll->concatenate_data();
        cout << repr << endl << endl;
    }
    cout << "Exiting printing thread" << endl;
}

void period_delete()
{
    int millis = 100;
    while (ll->get_length() > 0) {
        this_thread::sleep_for(chrono::milliseconds(millis));
        ll->remove_at_random();
    }
    cout << "Exiting deletion thread" << endl;
}

int main()
{
    cout << "4F14 - Doubly Linked List CW - Multi-Threading" << endl
         << endl;
    ll = new LinkedList();
    ll->populate();

    thread print_thread(period_print);
    thread delete_thread(period_delete);

    print_thread.join();
    delete_thread.join();
}