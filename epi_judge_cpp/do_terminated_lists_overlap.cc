#include <memory>

#include "list_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::shared_ptr;

void AdvanceListByK(int k, shared_ptr<ListNode<int>>& L) {
    for (int i = 0; i < k; ++i) {
        L = L->next;
    }
}

int Length(const shared_ptr<ListNode<int>>& L) {
    int count = 0;
    auto ptr = L;
    while (ptr) {
        ptr = ptr->next;
        ++count;
    }  
    return count;
}

shared_ptr<ListNode<int>> OverlappingNoCycleLists(shared_ptr<ListNode<int>> l0,
                                                  shared_ptr<ListNode<int>> l1) {
    int count_l0 = Length(l0), count_l1 = Length(l1);

    int diff = count_l0 - count_l1;
    AdvanceListByK(abs(diff), diff < 0 ? l1 : l0);

    while (l1 && l0 && l1 != l0) {
        l1 = l1->next, l0 = l0->next;
    }
    return l1;
}

void OverlappingNoCycleListsWrapper(TimedExecutor& executor,
                                    shared_ptr<ListNode<int>> l0,
                                    shared_ptr<ListNode<int>> l1,
                                    shared_ptr<ListNode<int>> common) {
  if (common) {
    if (l0) {
      auto i = l0;
      while (i->next) {
        i = i->next;
      }
      i->next = common;
    } else {
      l0 = common;
    }

    if (l1) {
      auto i = l1;
      while (i->next) {
        i = i->next;
      }
      i->next = common;
    } else {
      l1 = common;
    }
  }

  auto result = executor.Run([&] { return OverlappingNoCycleLists(l0, l1); });

  if (result != common) {
    throw TestFailure("Invalid result");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "l0", "l1", "common"};
  return GenericTestMain(
      args, "do_terminated_lists_overlap.cc", "do_terminated_lists_overlap.tsv",
      &OverlappingNoCycleListsWrapper, DefaultComparator{}, param_names);
}
