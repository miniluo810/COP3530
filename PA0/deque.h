#include <memory>
#include <exception>

namespace cop3530 {

template <typename T>
class deque {
    
    struct node {
        T data;
        node *prev;
        node *next;
        // something to point to the next node
        // something to point to the previous node
        // something to hold a value of type T
    };

    // something to hold the head of the list
    // something else?

    public:
        node* head;
        node* tail;
        size_t count1;
        deque();
        void push_front(T data);
        void push_back(T data);
        void pop_front();
        void pop_back();
        T front();
        T back();
        size_t size();
        bool empty();
};

template <typename T>
deque<T>::deque() {
    head= nullptr;
    tail= nullptr;
    count1=0;
}

template <typename T>
void deque<T>::push_front(T data) {
    node *addNode=new node;
    addNode->data = data;
    if(head!= nullptr){
        addNode->next= head;
        addNode->prev= nullptr;
        head->prev=addNode;
        if (count1==0){
            tail->prev=addNode;
        }
        head=addNode;
    }else{
        head=addNode;
        tail=addNode;
    }
    count1++;

}

template <typename T>
void deque<T>::push_back(T data) {
    node *addNode = new node;
    addNode->data = data;
    addNode->next= nullptr;
    addNode->prev= tail;
    if(tail!= nullptr){
        //addNode->prev= tail;
        //addNode->next= nullptr;
        tail->next=addNode;
        if (count1==1){
            head->next=addNode;
            addNode->prev=head;
        }
        tail=addNode;
    }else{
        head=addNode;
        addNode->prev= nullptr;
        tail=addNode;
        addNode->next= nullptr;
    }
    count1++;

}

template <typename T>
void deque<T>::pop_front() {
    node *temp=head;
    if (count1 == 0) {
        throw std::runtime_error("Error");
    } else if (count1==1) {
        delete temp;
        count1--;
        head= nullptr;
        tail= nullptr;
   } else {
        head=temp->next;
        head->prev= nullptr;
        delete temp;
        count1--;
        //head=temp;
    }


}

template <typename T>
void deque<T>::pop_back() {
    node*temp2=tail;
    if (count1 == 0) {
        throw std::runtime_error("Error");
    } else if (tail->prev == nullptr) {
        delete tail;
        count1--;
        head= nullptr;
        tail= nullptr;
    } else {
       tail=temp2->prev;
       tail->next= nullptr;
       delete temp2;
        count1--;
    }
    
}

template <typename T>
T deque<T>::front() {
    if (count1 == 0) {
        throw std::runtime_error("Error");
    }
    return head->data;
}

template <typename T>
T deque<T>::back() {
    if (count1 == 0) {
        throw std::runtime_error("Error");
    }
    return tail->data;
    
}

template <typename T>
size_t deque<T>::size() {
    return count1;
}

template <typename T>
bool deque<T>::empty() {
    if(count1==0){
        return true;
    }else{
        return false;
    }
}

}