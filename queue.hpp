#include <memory>
#include <string>
#include <iostream>
using namespace std;

template<typename T>
class Queue {

    public:
        explicit Queue(int capacity = 10) : head_{-1}, tail_{-1}, size_{0}, capacity_{capacity}, data_{make_unique<T[]>(capacity)} {}

        Queue(const Queue<T> &other) {
            int other_size = other.size_;
            capacity_ = other.capacity_;
            unique_ptr<T[]> new_data(new T[capacity_]);
            head_ = 0;
            tail_ = other_size - 1;
            size_ = 0;

            for(int i = 0; i < other_size; i++)
                enqueue(other.data_[i]);
            data_ = move(new_data);
        }
        Queue<T> &operator=(const Queue<T> &other) {
            if(this != &other) {
                int other_size = other.size_;
                capacity_ = other.capacity_;
                unique_ptr<T[]> new_data(new T[capacity_]);
                head_ = 0;
                tail_ = other_size - 1;
                size_ = 0;

                for(int i = 0; i < other.size_; i++)
                    enqueue(other.data_[i]);
            }
            return *this;
        }
        Queue(Queue<T> &&other) noexcept {
            data_ = move(other.data_);
            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;
            capacity_ = other.capacity_;

            other.head_ = 0;
            other.tail_ = 0;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        Queue<T> &operator=(const Queue<T> &&other) noexcept {
            if(this != &other) {
                data_ = move(other.data);
                head_ = other.head_;
                tail_ = other.tail_;
                size_ = other.size_;
                capacity_ = other.capacity_;

                other.head_ = 0;
                other.tail_ = 0;
                other.size_ = 0;
                other.capacity_ = 0;
            }
            return *this;
        } 

        void enqueue(const T& element) {
            if(isFull())
                throw runtime_error("Queue is Full");
            if(isEmpty()) {
                tail_ = head_ = 0;
            } else {
                tail_ = (tail_ + 1) % capacity_;
            }
            data_[tail_] = element;
            size_++;
            //cerr << "head = " << head_ << endl;
            //cerr << "tail = " << tail_ << endl;
        }

        T dequeue() {
            if(isEmpty()) {
                throw runtime_error("Queue is Empty");
            }
            T elem = data_[head_];

            if(head_ == tail_) {
               head_ = tail_ = -1; 
            } else {
                head_ = (head_ + 1) % capacity_;
            }
            size_--;
            //cerr << "head = " << head_ << endl;
            //cerr << "tail = " << tail_ << endl;
            return elem;
        }
        T& front() {
            if(isEmpty())
                throw runtime_error("Queue is empty");
            return data_[head_];
        }
        bool isEmpty() const {
            return head_ == -1 && tail_ == -1;
        }
        
        bool isFull() const {
            return (tail_ + 1) % capacity_ == head_;
        }

        int size() const {
            return size_;
        }

    void print() const {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return;
        }
        int i = head_;
        do {
            cout << data_[i] << " ";
            i = (i + 1) % capacity_;
        } while (i != (tail_ + 1) % capacity_);
        cout << endl;
    }


    private:
        int head_;
        int tail_;
        int size_;
        int capacity_;
        unique_ptr<T[]> data_; 
};

