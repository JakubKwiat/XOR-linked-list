#include <iostream>
#include <string>
using namespace std;
struct Node
{
    int data;
    Node* link;
};
Node* beg, * end1, * act, * previous, * next1;
Node* XOR(Node* prev, Node* next)
{
    return(Node*)((uintptr_t)(prev) ^ (uintptr_t)(next));  
}
void Add_beg(int& number_beg) {
    int data;
    cin >> data;
    Node* newNode;
    newNode = new Node;
    newNode->data = data;
    if (beg == NULL) {
        newNode->link = NULL;
        previous = newNode;
        next1 = newNode;
        beg = newNode;
        end1 = newNode;
        act = newNode;
    }
    else {
        if (number_beg == 0) {
            newNode->link = XOR(NULL, beg);
            beg->link = XOR(newNode,beg->link);
            beg = newNode;
            previous = beg;
            number_beg++;
        }
        else {
            newNode->link = XOR(NULL, beg);
            beg->link = XOR(newNode,beg->link);
            beg = newNode;
        }
    }
}
void Add_end(int& number_end) {
    int data;
    cin >> data;
    Node* newNode;
    newNode = new Node;
    newNode->data = data;
    if (end1 == NULL) {
        newNode->link = NULL;
        previous = newNode;
        next1 = newNode;
        beg = newNode;
        end1 = newNode;
        act = newNode;
    }
    else {
        if (number_end == 0) {
            newNode->link = XOR(end1, NULL);
            end1->link = XOR(newNode,end1->link);
            end1 = newNode;
            next1 = end1;
            number_end++;
        }
        else {
            newNode->link = XOR(end1, NULL);
            end1->link = XOR(newNode,end1->link);
            end1 = newNode;
        }
    }
}
void Add_act(int &number_beg,int &number_end) {
    int data;
    cin >> data;
    Node* newNode;
    newNode = new Node;
    newNode->data = data;
    if (act == NULL) {
        newNode->link = NULL;
        previous = newNode;
        next1 = newNode;
        beg = newNode;
        end1 = newNode;
        act = newNode;
    }
    else {
        if (act == beg) {
            newNode->link = XOR(NULL, beg);
            beg->link = XOR(newNode, next1);
            beg = newNode;
            previous = newNode;
            number_beg = 1;
        }
        else if (act==end1){
            newNode->link = XOR(end1,previous);
            end1->link = XOR(newNode, NULL);
            Node* temp;
            temp = XOR(previous->link, act);
            previous->link = XOR(temp, newNode);
            act->link = XOR(newNode, next1);
            previous = newNode;
            number_end = 1;
        }
        else {
            newNode->link = XOR(previous, act);
            Node* temp;
            temp = XOR(previous->link, act);
            previous->link = XOR(temp, newNode);
            act->link = XOR(newNode, next1);
            previous = newNode;
        }
    }
}
void Del_beg(int& number_beg, int& number_end) {
    if ((act == beg) && (act == end1)) {
        next1 = beg = previous = act = end1 = NULL;
        number_beg = 0;
        number_end = 0;
    }   
    else if (act != NULL) {
        if ((act != beg) && (previous!=beg)) {
            Node* temp;
            temp = beg;
            beg = XOR(beg->link, NULL);
            beg->link = XOR(beg->link, temp);
            previous = NULL;
        }
        else if (previous == beg) {
            Node* temp;
            temp = beg;
            beg = XOR(beg->link, NULL);
            beg->link = XOR(beg->link, temp);
            previous = NULL;
        }
        else if (act == beg) {
                Node* temp;
                temp = beg;
                beg = XOR(beg->link, NULL);
                beg->link = XOR(beg->link, temp);
                act = end1;
                next1 = NULL;
                previous = XOR(end1->link, NULL);
        }
    }
}
void Del_end(int& number_beg, int& number_end) {
    if ((act == beg) && (act == end1)) {
        next1 = beg = previous = act = end1 = NULL;
        number_beg = 0;
        number_end = 0;
    }
     else if (act != NULL) {
        if ((act != end1) && (next1 != end1)) {
            Node* temp;
            temp = end1;
            end1 = XOR(end1->link, NULL);
            end1->link = XOR(end1->link, temp);
        }
        else if (next1 == end1) {
            Node* temp;
            temp = end1;
            end1 = XOR(end1->link, NULL);
            end1->link = XOR(end1->link, temp);
            next1 = NULL;
        }
        else if (act == end1) { 
                Node* temp;
                temp = end1;
                end1 = XOR(end1->link, NULL);
                end1->link = XOR(end1->link, temp);
                act = end1;
                next1 = NULL;
                previous=XOR(end1->link,NULL);
        }
    }
}
void Del_act(int &number_beg,int &number_end) {
    if ((act == beg) && (act == end1)) {
        next1 = beg = previous = act = end1 = NULL;
        number_beg = 0;
        number_end = 0;
    }
    else if (act != NULL) {
        if (act == beg) {
            Del_beg(number_beg,number_end);
        }
        else if (act == end1) {
            Del_end(number_beg, number_end);
        }
        else {
            Node* temp = XOR(previous->link, act);
            Node* temp1 = XOR(next1->link, act);
            act = previous;
            previous = temp;
            act->link = XOR(previous, next1);
            next1->link = XOR(act, temp1);
        }
    }
}
void Del_val(int &number_beg,int &number_end) {
    int value;
    cin >> value;
    Node* start = beg;
    Node* prev2 = NULL;
    Node* next2 = NULL;
    while (start != NULL) {
        start = beg;
        prev2 = NULL;
        while (start != NULL) {
            if (start->data == value) {
                if (start == beg) {
                    Del_beg(number_beg, number_end);
                }
                else if (start == end1) {
                    Del_end(number_beg, number_end);
                }
                else if (start == act) {
                    Del_act(number_beg, number_end);
                }
                else {
                    next2 = XOR(start->link, prev2);
                    Node* temp_prev = XOR(prev2->link, start);
                    Node* temp_next = XOR(next2->link, start);
                    start = prev2;
                    prev2 = temp_prev;
                    start->link = XOR(prev2, next2);
                    next2->link = XOR(start, temp_next);
                }
                break;
            }
            else {
                next2 = XOR(prev2, start->link);
                prev2 = start;
                start = next2;
            }
        }
    }
}
void Actual() {
    if (act == NULL) {
        cout << "NULL" << endl;
    }
    else {
        cout << act->data << endl;
    }
}
void Next() {
    if (act == NULL) {
        cout << "NULL" << endl;
    }
    else {
            if (act == end1) {
                act = beg;
                previous = NULL;
                next1 = XOR(act->link, previous);
            }
            else {
                Node* temp;
                temp = next1;
                next1 = XOR(next1->link, act);
                act = temp;
                previous = XOR(act->link, next1);
            }  
        cout << act->data << endl;
    }
}
void Prev() {
    if (act == NULL) {
        cout << "NULL" << endl;
    }
    else {
        if (act == beg) {
            act = end1;
            next1 = NULL;
            previous = XOR(act->link,next1);
        }
        else {
            Node* temp;
            temp = previous;
            previous = XOR(previous->link, act);
            act = temp;
            next1 = XOR(act->link, previous);
        }
        cout << act->data << endl;
    }
}
void Print_forward() {
    Node* start = beg;
    Node* prev2 = NULL;
    Node* next2 = NULL;
    while (start != NULL) {
        cout << start->data << " ";
        next2 = XOR(prev2, start->link);
        prev2 = start;
        start = next2;
    }
    if (act == NULL) {
        cout << "NULL";
    }
    cout << endl;
}
void Print_backward() {
    Node* start = end1;
    Node* prev2 = NULL;
    Node* next2 = NULL;
    while (start != NULL) {
        cout << start->data << " ";
        prev2 = XOR(next2, start->link);
        next2 = start;
        start = prev2;
    }
    if (act == NULL) {
        cout << "NULL";
    }
    cout << endl;
}
int main() {
    int number_beg = 0;
    int number_end = 0;
    string command;
    while (std::cin>>command) {
        if (command == "ADD_BEG") {
            Add_beg(number_beg);
        }
        if (command == "ADD_END") {
            Add_end(number_end);
        }
        if (command == "ADD_ACT") {
            Add_act(number_beg,number_end);
        }
        if (command == "PRINT_FORWARD") {
            Print_forward();
        }
        if (command == "PRINT_BACKWARD") {
            Print_backward();
        }
        if (command == "NEXT") {
            Next();
        }
        if (command == "PREV") {
            Prev();
        }
        if (command == "ACTUAL") {
            Actual();
        }
        if (command == "DEL_BEG") {
            Del_beg(number_beg, number_end);
        }
        if (command == "DEL_END") {
            Del_end(number_beg, number_end);
        }
        if (command == "DEL_ACT") {
            Del_act(number_beg,number_end);
        }
        if (command == "DEL_VAL") {
            Del_val(number_beg,number_end);
        }
    }
    return 0;
}