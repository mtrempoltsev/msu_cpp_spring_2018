#include <iostream>

struct Node_int
{
    int64_t data_;
    Node_int* next_, *prev_;
    explicit Node_int(const int64_t data = 0):
            data_(data),
            next_(nullptr),
            prev_(nullptr)
    {}
    Node_int(const Node_int& copied):
            data_(copied.data_),
            next_(nullptr),
            prev_(nullptr)
    {
    }
    Node_int(Node_int&& moved) noexcept
    {
        data_ = moved.data_;
        moved.data_ = 0;
        next_ = moved.next_;
        moved.next_ = nullptr;
        prev_ = moved.prev_;
        moved.prev_ = nullptr;
    }
    Node_int& operator=(const Node_int& copied)
    {
        if (this == &copied)
        {
            return *this;
        }
        data_ = copied.data_;
        next_ = nullptr;
        prev_ = nullptr;
        return *this;
    }
    Node_int& operator=(Node_int&& moved) noexcept
    {
        if (this == &moved)
        {
            return *this;
        }
        data_ = moved.data_;
        moved.data_ = 0;
        next_ = moved.next_;
        moved.next_ = nullptr;
        prev_ = moved.prev_;
        moved.prev_ = nullptr;
        return *this;
    }
    friend  std::ostream& operator<<(std::ostream& os, const Node_int* node_int)
    {
//        os.width(2);
//        os.fill('0');
        os << node_int->data_;
        return os;
    }
    ~Node_int() = default;
};

class List {
private:
    size_t size_;
    Node_int* head_, *tail_;
    void destroy()
    {
        while(head_)
        {
            tail_ = head_->next_;
            delete head_;
            head_ = tail_;
        }
    }
public:
    List():
            head_(nullptr),
            tail_(nullptr),
            size_(0)
    {}
    explicit List(const int64_t data):
        size_(1)
    {
        head_ = new Node_int(data);
        tail_ = head_;
    }
    List(const List& copied):
            size_(copied.size_)
    {
        if (copied.head_)
        {
            head_ = new Node_int(*copied.head_);
            auto curr_copied = copied.head_->next_;
            auto curr_node = head_;
            Node_int* prev_node = nullptr;
            while(curr_copied)
            {
                curr_node->next_ = new Node_int(*curr_copied);
                curr_copied = curr_copied->next_;
                prev_node = curr_node;
                curr_node = curr_node->next_;
                curr_node->prev_ = prev_node;

            }
            tail_ = curr_node;
        } else
        {
            head_ = nullptr;
            tail_ = nullptr;
        }
    }
    List(List&& moved) noexcept
    {
        size_ = moved.size_;
        head_ = moved.head_;
        tail_ = moved.tail_;
        moved.head_ = nullptr;
        moved.tail_ = nullptr;
        moved.size_ = 0;
    }
    List& operator=(const List& copied)
    {
        if (this == &copied)
        {
            return *this;
        }
        destroy();
        if (copied.head_)
        {
            head_ = new Node_int(*copied.head_);
            auto curr_copied = copied.head_->next_;
            auto curr_node = head_;
            Node_int* prev_node;
            while(curr_copied)
            {
                curr_node->next_ = new Node_int(*curr_copied);
                curr_copied = curr_copied->next_;
                prev_node = curr_node;
                curr_node->prev_ = prev_node;
                curr_node = curr_node->next_;

            }
            tail_ = curr_node;
        } else
        {
            head_ = nullptr;
            tail_ = nullptr;
        }
        return *this;
    }
    List& operator=(List&& moved) noexcept
    {
        if (this == &moved)
        {
            return *this;
        }
        destroy();
        size_ = moved.size_;
        head_ = moved.head_;
        tail_ = moved.tail_;
        moved.size_ = 0;
        moved.head_ = nullptr;
        moved.tail_ = nullptr;
        return *this;
    }
    void push_front(const int64_t data)
    {
        size_ +=1;
        auto tmp = new Node_int(data);
        tmp->next_ = head_;
        if (head_)
        {
            head_->prev_ = tmp;
            head_ = tmp;
        } else
        {
            head_ = tmp;
            tail_ = head_;
        }
    }
    void push_back(const int64_t data)
    {
        size_ +=1;
        auto tmp = new Node_int(data);
        if (tail_)
        {
            tmp->prev_ = tail_;
            tail_->next_ = tmp;
            tail_ = tmp;
        } else
        {
            tail_ = tmp;
            head_ = tail_;
        }
    }
    void print_back() const
    {
        auto curr_node = tail_;
        if (!curr_node)
        {
            std::cout << "List is empty";
        }
        while (curr_node) {
            std::cout << curr_node;
            curr_node = curr_node->prev_;
        }
        std::cout << std:: endl;
    }
    int64_t& operator[](size_t size) {
        if (size < size_) {
            auto curr_node = head_;
            for (int i = 0; i < size; ++i) {
                curr_node = curr_node->next_;
            }
            return curr_node->data_;
        } else {
            throw std::out_of_range("");
        }
    }
    const int64_t& operator[](size_t size) const {
        if (size < size_) {
            auto curr_node = head_;
            for (int i = 0; i < size; ++i) {
                curr_node = curr_node->next_;
            }
            return curr_node->data_;
        } else {
            std::cout << "Out of range in List";
            throw std::out_of_range("");
        }
    }
    void print_front() const
    {
        auto curr_node = head_;
        if (!curr_node)
        {
            std::cout << "List is empty";
        }
        while (curr_node) {
            std::cout << curr_node;
            curr_node = curr_node->next_;
        }
        std::cout << std:: endl;
    }
    size_t get_size() const
    {
        return size_;
    }
    void pop_front()
    {
        if (head_)
        {
            --size_;
            auto tmp = head_;
            head_ = head_->next_;
            delete tmp;
            if (head_)
            {
                head_->prev_ = nullptr;
            } else
            {
                tail_ = head_;
            }
        }
    }
    void pop_back()
    {
        if (tail_)
        {
            --size_;
            auto tmp = tail_;
            tail_ = tail_->prev_;
            delete tmp;
            if (tail_)
            {
                tail_->next_ = nullptr;
            } else
            {
                head_ = tail_;
            }
        }
    }
    friend  std::ostream& operator<<(std::ostream& os, const List& list)
    {
        auto curr_node = list.tail_;
        if (!curr_node)
        {
            os << "List is empty";
        }
        while (curr_node) {
            os << curr_node;
            curr_node = curr_node->prev_;
        }
        os << std:: endl;
        return os;
    }
    bool operator==(const List &list) const
    {
        if (this == &list) {
            return true;
        }
        if (size_ != list.size_)
        {
            return false;
        }
        auto cur_1 = tail_;
        auto cur_2 = list.tail_;
        for (int i = 0; i < size_; ++i)
        {
            if(cur_1->data_ != cur_2->data_)
            {
                return false;
            }
            cur_1 = cur_1->prev_;
            cur_2 = cur_2->prev_;
        }
        return true;
    }
    bool operator!=(const List &list) const
    {
        return !(*this == list);
    }
    bool operator>=(const List &list) const
    {
        if (this == &list) {
            return true;
        }
        if (size_ > list.size_)
        {
            return true;
        } else if(size_ < list.size_)
        {
            return false;
        }
        auto cur_1 = tail_;
        auto cur_2 = list.tail_;
        for (int64_t i = 0; i < size_; ++i)
        {
            if(cur_1->data_ > cur_2->data_)
            {
                return true;
            } else if(cur_1->data_ < cur_2->data_)
            {
                return false;
            }
            cur_1 = cur_1->prev_;
            cur_2 = cur_2->prev_;
        }
        return true;
    }
    bool operator>(const List &list) const
    {
        if (this == &list) {
            return false;
        }
        if (size_ > list.size_)
        {
            return true;
        } else if(size_ < list.size_)
        {
            return false;
        }
        auto cur_1 = tail_;
        auto cur_2 = list.tail_;
        for (int64_t i = 0; i < size_; ++i)
        {
            if(cur_1->data_ > cur_2->data_)
            {
                return true;
            } else if(size_ < list.size_)
            {
                return false;
            }
            cur_1 = cur_1->prev_;
            cur_2 = cur_2->prev_;
        }
        return false;
    }
    ~List()
    {
        destroy();
    }
};
