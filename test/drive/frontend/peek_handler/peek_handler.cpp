#include <cstdlib>
#include <memory>
#include <vector>

#include "gtest/gtest.h"
#include "peek_handler.hpp"
#include "test_params.hpp"
#include "test_utils.hpp"

#define INVOKE_PEEK_HANDLER_IMPL(context)                               \
  peek_handler_impl(                                                    \
      &context.returned_credits, context.return_credit_num_queue.get(), \
      context.peek_req_queue.get(), context.peek_resp_queue.get())

struct PeekHandlerContext {
  unsigned short returned_credits = 0;
  std::unique_ptr<ST_Queue<unsigned short>> return_credit_num_queue;
  std::unique_ptr<ST_Queue<unsigned int>> peek_req_queue;
  std::unique_ptr<ST_Queue<unsigned int>> peek_resp_queue;

  PeekHandlerContext() {
    return_credit_num_queue.reset(new ST_Queue<unsigned short>(128));
    peek_req_queue.reset(new ST_Queue<unsigned int>(128));
    peek_resp_queue.reset(new ST_Queue<unsigned int>(128));
  }
};

TEST(peek_handler_impl, correct) {
  PeekHandlerContext context;
  std::vector<unsigned int> real_peek_resp_queues;

  context.peek_req_queue->write(Tag::NEXT_TAG_TO_USE);
  RUN_METHOD(1, INVOKE_PEEK_HANDLER_IMPL(context));
  drain_queue(context.peek_resp_queue.get(), &real_peek_resp_queues);
  ASSERT_EQ(real_peek_resp_queues.size(), 0);
  real_peek_resp_queues.clear();

  context.peek_req_queue->write(Tag::RETURNED_CREDITS_TAG);
  RUN_METHOD(1, INVOKE_PEEK_HANDLER_IMPL(context));
  drain_queue(context.peek_resp_queue.get(), &real_peek_resp_queues);
  ASSERT_EQ(real_peek_resp_queues.size(), 1);
  ASSERT_EQ(real_peek_resp_queues[0], 0);
  real_peek_resp_queues.clear();

  int expected_peek_resp = 0;
  for (int i = 0; i < 4; i++) {
    context.return_credit_num_queue->write(i);
    expected_peek_resp += i;
  }
  RUN_METHOD(3, INVOKE_PEEK_HANDLER_IMPL(context));
  context.peek_req_queue->write(Tag::RETURNED_CREDITS_TAG);
  RUN_METHOD(1, INVOKE_PEEK_HANDLER_IMPL(context));
  drain_queue(context.peek_resp_queue.get(), &real_peek_resp_queues);
  ASSERT_EQ(real_peek_resp_queues.size(), 1);
  ASSERT_EQ(real_peek_resp_queues[0], expected_peek_resp);
  real_peek_resp_queues.clear();

  context.peek_req_queue->write(Tag::RETURNED_CREDITS_TAG);
  RUN_METHOD(1, INVOKE_PEEK_HANDLER_IMPL(context));
  drain_queue(context.peek_resp_queue.get(), &real_peek_resp_queues);
  ASSERT_EQ(real_peek_resp_queues.size(), 1);
  ASSERT_EQ(real_peek_resp_queues[0], 0);
  real_peek_resp_queues.clear();
}
