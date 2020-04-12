#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"

using std::vector;
using std::rotate;
using std::length_error;

class Queue {
public:
  explicit Queue(size_t capacity) : arr_(capacity), head_index_(0), 
    tail_index_(0), curr_size_(0) { 
    // Do nothing
  }
  void Enqueue(int x) {
    if (curr_size_ == arr_.size()) {
      rotate(arr_.begin(), arr_.begin() + head_index_, arr_.end());
      head_index_ = 0, tail_index_ = curr_size_;
      arr_.resize(arr_.size() * 2);
    }
    arr_[tail_index_] = x;
    tail_index_ = (tail_index_ + 1) % arr_.size();
    ++curr_size_;
  }
  int Dequeue() noexcept(false) {
    if (!curr_size_) {
      throw length_error("Empty Queue");
    }
    --curr_size_;
    int rv = arr_[head_index_];
    head_index_ = (head_index_ + 1) % arr_.size();
    return rv;
  }
  size_t Size() const {
    return curr_size_;
  }
private:
  size_t head_index_, tail_index_, curr_size_;
  vector<int> arr_;
};

struct QueueOp {
  enum class Operation { kConstruct, kDequeue, kEnqueue, kSize } op;
  int argument;

  QueueOp(const std::string& op_string, int arg) : argument(arg) {
    if (op_string == "Queue") {
      op = Operation::kConstruct;
    } else if (op_string == "dequeue") {
      op = Operation::kDequeue;
    } else if (op_string == "enqueue") {
      op = Operation::kEnqueue;
    } else if (op_string == "size") {
      op = Operation::kSize;
    } else {
      throw std::runtime_error("Unsupported queue operation: " + op_string);
    }
  }

  void execute(Queue& q) const {
    switch (op) {
      case Operation::kConstruct:
        // Hack to bypass deleted assign operator
        q.~Queue();
        new (&q) Queue(argument);
        break;
      case Operation::kDequeue: {
        int result = q.Dequeue();
        if (result != argument) {
          throw TestFailure("Dequeue: expected " + std::to_string(argument) +
                            ", got " + std::to_string(result));
        }
      } break;
      case Operation::kEnqueue:
        q.Enqueue(argument);
        break;
      case Operation::kSize: {
        int s = q.Size();
        if (s != argument) {
          throw TestFailure("Size: expected " + std::to_string(argument) +
                            ", got " + std::to_string(s));
        }
      } break;
    }
  }
};

namespace test_framework {
template <>
struct SerializationTrait<QueueOp> : UserSerTrait<QueueOp, std::string, int> {};
}  // namespace test_framework

void QueueTester(const std::vector<QueueOp>& ops) {
  Queue q(0);
  for (auto& op : ops) {
    op.execute(q);
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"ops"};
  return GenericTestMain(args, "circular_queue.cc", "circular_queue.tsv",
                         &QueueTester, DefaultComparator{}, param_names);
}
