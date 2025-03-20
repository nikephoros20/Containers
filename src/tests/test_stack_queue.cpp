#include "s21_tests.h"
// #include "../test_header.h"

TEST(Stack, Constructor) {
  s21::Stack<int> s21_stack;
  std::stack<int> std_stack;
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(Stack, Clear) {
  s21::Stack<int> s21_stack = {1, 2, 3, 4};
  s21_stack.clear();
  EXPECT_EQ(s21_stack.size(), size_t(0));
  EXPECT_EQ(s21_stack.empty(), true);
}

TEST(Stack, Constructor_Initializer) {
  s21::Stack<int> s21_stack = {1, 2, 3, 4};
  EXPECT_EQ(s21_stack.top(), 4);
  EXPECT_EQ(s21_stack.size(), size_t(4));
  EXPECT_EQ(s21_stack.empty(), false);
}

TEST(Stack, Constructor_Copy) {
  s21::Stack<char> s21_stack_1 = {'a', 'b', 'c', 'd'};
  s21::Stack<char> s21_stack_2 = s21_stack_1;
  s21::Stack<char> s21_stack_3 = {'a', 'b', 'c', 'd'};

  EXPECT_EQ(s21_stack_1.size(), s21_stack_2.size());

  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(s21_stack_1.top(), s21_stack_2.top());
    EXPECT_EQ(s21_stack_1.size(), s21_stack_2.size());
    s21_stack_1.pop(), s21_stack_2.pop();
  }
}

TEST(Stack, Constructor_Move) {
  s21::Stack<char> s21_stack_1 = {'a', 'b', 'c', 'd'};
  s21::Stack<char> s21_stack_2 = std::move(s21_stack_1);

  s21::Stack<char> s21_stack_3 = {'a', 'b', 'c', 'd'};

  EXPECT_EQ(s21_stack_2.size(), s21_stack_3.size());
  EXPECT_EQ(s21_stack_1.size(), size_t(0));
  EXPECT_EQ(s21_stack_1.empty(), true);
  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(s21_stack_3.top(), s21_stack_2.top());
    EXPECT_EQ(s21_stack_3.size(), s21_stack_2.size());
    s21_stack_3.pop(), s21_stack_2.pop();
  }
}

TEST(Stack, Push) {
  s21::Stack<int> s21_stack;
  std::stack<int> std_stack;
  s21_stack.push(5);
  s21_stack.push(0);
  std_stack.push(5);
  std_stack.push(0);
  EXPECT_EQ(s21_stack.top(), std_stack.top());
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(Stack, Pop) {
  s21::Stack<int> s21_stack;
  std::stack<int> std_stack;
  s21_stack.push(5);
  s21_stack.push(0);
  std_stack.push(5);
  std_stack.push(0);
  s21_stack.pop();
  s21_stack.pop();
  std_stack.pop();
  std_stack.pop();
  s21_stack.push(15);
  s21_stack.push(10);
  std_stack.push(15);
  std_stack.push(10);
  s21_stack.pop();
  std_stack.pop();
  EXPECT_EQ(s21_stack.top(), std_stack.top());
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(Stack, Swap) {
  s21::Stack<std::string> s21_stack_1 = {"aqua", "school", "terra", "sun"};
  s21::Stack<std::string> s21_stack_2 = {"Kazan", "container", "project"};
  s21::Stack<std::string> s21_stack_3 = {"aqua", "school", "terra", "sun"};
  s21::Stack<std::string> s21_stack_4 = {"Kazan", "container", "project"};

  s21_stack_1.swap(s21_stack_2);

  EXPECT_EQ(s21_stack_1.size(), s21_stack_4.size());
  EXPECT_EQ(s21_stack_2.size(), s21_stack_3.size());
  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(s21_stack_3.top(), s21_stack_2.top());
    EXPECT_EQ(s21_stack_3.size(), s21_stack_2.size());
    s21_stack_3.pop(), s21_stack_2.pop();
  }
  for (auto i = 0; i < 3; i++) {
    EXPECT_EQ(s21_stack_1.top(), s21_stack_4.top());
    EXPECT_EQ(s21_stack_1.size(), s21_stack_4.size());
    s21_stack_1.pop(), s21_stack_4.pop();
  }
}

TEST(Stack, Move_assignment) {
  s21::Stack<int> stack7;
  s21::Stack<int> stack6;
  stack6.push(1);
  stack6.push(1);
  stack7.push(1);
  stack7 = std::move(stack6);
  EXPECT_EQ(stack7.size(), 2);
}

TEST(insert_many, stack_1) {
  s21::Stack<int> s21_stack;
  s21_stack.push(1);
  s21_stack.push(2);
  s21_stack.insert_many_back(3, 4);
  EXPECT_EQ(s21_stack.size(), 4);
  EXPECT_EQ(s21_stack.top(), 4);
}

TEST(insert_many, stack_2) {
  s21::Stack<int> s21_stack;
  s21_stack.push(1);
  s21_stack.push(2);
  s21_stack.insert_many_back();
  EXPECT_EQ(s21_stack.size(), 2);
  EXPECT_EQ(s21_stack.top(), 2);
}

TEST(insert_many, stack_3) {
  s21::Stack<int> s21_stack;
  s21_stack.push(1);
  s21_stack.push(2);
  s21_stack.insert_many_back(3, 4);
  s21_stack.pop();
  EXPECT_EQ(s21_stack.top(), 3);
}

TEST(insert_many, stack_4) {
  s21::Stack<int> s21_stack;
  s21_stack.push(1);
  s21_stack.push(2);
  s21_stack.insert_many_back(
      3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22,
      23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
      41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58,
      59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76,
      77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94,
      95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110,
      111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125,
      126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140,
      141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155,
      156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170,
      171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185,
      186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
      201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215,
      216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230,
      231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245,
      246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 256, 257);
  EXPECT_EQ(s21_stack.top(), 257);
  EXPECT_EQ(s21_stack.size(), 257);
}

TEST(insert_many, stack_5) {
  s21::Stack<int> s21_stack;
  s21_stack.push(1);
  s21_stack.push(2);
  s21_stack.insert_many_back(3);
  EXPECT_EQ(s21_stack.size(), 3);
  EXPECT_EQ(s21_stack.top(), 3);
}

TEST(insert_many, stack_6) {
  s21::Stack<int> s21_stack;
  s21_stack.push(1);
  s21_stack.push(2);
  s21_stack.insert_many_back(3, 4);
  s21_stack.insert_many_back(5, 6);
  EXPECT_EQ(s21_stack.size(), 6);
  EXPECT_EQ(s21_stack.top(), 6);
  s21_stack.pop();
  s21_stack.pop();
  EXPECT_EQ(s21_stack.size(), 4);
  EXPECT_EQ(s21_stack.top(), 4);
}

TEST(insert_many, stack_7) {
  s21::Stack<int> s21_stack;
  s21_stack.push(1);
  s21_stack.push(2);
  int i = 4;
  s21_stack.insert_many_back(3, i);
  EXPECT_EQ(s21_stack.size(), 4);
  EXPECT_EQ(s21_stack.top(), 4);
}

// QUEUE

TEST(queue, Constructor_Initializer) {
  s21::Queue<int> s21_queue = {1, 2, 3, 4};
  EXPECT_EQ(s21_queue.front(), 1);
  EXPECT_EQ(s21_queue.back(), 4);
  EXPECT_EQ(s21_queue.size(), size_t(4));
  EXPECT_EQ(s21_queue.empty(), false);
}

TEST(queue, Clear) {
  s21::Queue<int> s21_queue = {1, 2, 3, 4};
  s21_queue.clear();
  EXPECT_EQ(s21_queue.size(), size_t(0));
  EXPECT_EQ(s21_queue.empty(), true);
}

TEST(queue, Constructor) {
  s21::Queue<int> s21_queue;
  std::queue<int> std_queue;
  EXPECT_EQ(s21_queue.size(), std_queue.size());
  EXPECT_EQ(s21_queue.empty(), std_queue.empty());
}

TEST(queue, Copy) {
  s21::Queue<char> s21_queue_1 = {'a', 'b', 'c', 'd'};
  s21::Queue<char> s21_queue_2 = s21_queue_1;

  EXPECT_EQ(s21_queue_1.size(), s21_queue_2.size());

  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(s21_queue_1.front(), s21_queue_2.front());
    EXPECT_EQ(s21_queue_1.size(), s21_queue_2.size());
    s21_queue_1.pop(), s21_queue_2.pop();
  }
}

TEST(queue, Constructor_Move) {
  s21::Queue<char> s21_queue_1 = {'a', 'b', 'c', 'd'};
  s21::Queue<char> s21_queue_2 = std::move(s21_queue_1);
  s21::Queue<char> s21_queue_3 = {'a', 'b', 'c', 'd'};

  EXPECT_EQ(s21_queue_2.size(), s21_queue_3.size());
  EXPECT_EQ(s21_queue_1.size(), size_t(0));
  EXPECT_EQ(s21_queue_1.empty(), true);
  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(s21_queue_3.front(), s21_queue_2.front());
    EXPECT_EQ(s21_queue_3.size(), s21_queue_2.size());
    s21_queue_3.pop(), s21_queue_2.pop();
  }
}

TEST(queue, Push) {
  s21::Queue<int> s21_queue;
  std::queue<int> std_queue;
  s21_queue.push(5);
  s21_queue.push(0);
  std_queue.push(5);
  std_queue.push(0);
  EXPECT_EQ(s21_queue.front(), std_queue.front());
  EXPECT_EQ(s21_queue.back(), std_queue.back());
  EXPECT_EQ(s21_queue.size(), std_queue.size());
  EXPECT_EQ(s21_queue.empty(), std_queue.empty());
}

TEST(queue, Pop) {
  s21::Queue<int> s21_queue;
  std::queue<int> std_queue;
  s21_queue.push(5);
  s21_queue.push(0);
  std_queue.push(5);
  std_queue.push(0);
  s21_queue.pop();
  std_queue.pop();
  EXPECT_EQ(s21_queue.front(), std_queue.front());
  EXPECT_EQ(s21_queue.back(), std_queue.back());
  EXPECT_EQ(s21_queue.size(), std_queue.size());
  EXPECT_EQ(s21_queue.empty(), std_queue.empty());
}

TEST(queue, Swap) {
  s21::Queue<std::string> s21_queue_1 = {"aqua", "school", "terra", "sun"};
  s21::Queue<std::string> s21_queue_2 = {"Kazan", "container", "project"};
  s21::Queue<std::string> s21_queue_3 = {"aqua", "school", "terra", "sun"};
  s21::Queue<std::string> s21_queue_4 = {"Kazan", "container", "project"};

  s21_queue_1.swap(s21_queue_2);

  EXPECT_EQ(s21_queue_1.size(), s21_queue_4.size());
  EXPECT_EQ(s21_queue_2.size(), s21_queue_3.size());
  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(s21_queue_3.front(), s21_queue_2.front());
    EXPECT_EQ(s21_queue_3.size(), s21_queue_2.size());
    s21_queue_3.pop(), s21_queue_2.pop();
  }
  for (auto i = 0; i < 3; i++) {
    EXPECT_EQ(s21_queue_1.front(), s21_queue_4.front());
    EXPECT_EQ(s21_queue_1.size(), s21_queue_4.size());
    s21_queue_1.pop(), s21_queue_4.pop();
  }
}

TEST(insert_many, queue_1) {
  s21::Queue<int> s21_queue;
  s21_queue.push(1);
  s21_queue.push(2);
  s21_queue.insert_many_back(3, 4);
  EXPECT_EQ(s21_queue.size(), 4);
  EXPECT_EQ(s21_queue.back(), 4);
}

TEST(insert_many, queue_2) {
  s21::Queue<int> s21_queue;
  s21_queue.push(1);
  s21_queue.push(2);
  s21_queue.insert_many_back();
  EXPECT_EQ(s21_queue.size(), 2);
  EXPECT_EQ(s21_queue.back(), 2);
}

TEST(insert_many, queue_3) {
  s21::Queue<int> s21_queue;
  s21_queue.push(1);
  s21_queue.push(2);
  s21_queue.insert_many_back(3);
  EXPECT_EQ(s21_queue.size(), 3);
  EXPECT_EQ(s21_queue.back(), 3);
}

TEST(insert_many, queue_4) {
  s21::Queue<int> s21_queue;
  s21_queue.push(1);
  s21_queue.push(2);
  s21_queue.insert_many_back('a', 4);
  EXPECT_EQ(s21_queue.size(), 4);
  EXPECT_EQ(s21_queue.back(), 4);
}

TEST(insert_many, queue_5) {
  s21::Queue<int> s21_queue;
  s21_queue.push(1);
  s21_queue.push(2);
  s21_queue.insert_many_back(-2147483648);
  EXPECT_EQ(s21_queue.size(), 3);
  EXPECT_EQ(s21_queue.back(), -2147483648);
}

TEST(insert_many, queue_6) {
  s21::Stack<int> s21_queue;
  s21_queue.push(1);
  s21_queue.push(2);
  s21_queue.insert_many_back(
      3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22,
      23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
      41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58,
      59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76,
      77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94,
      95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110,
      111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125,
      126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140,
      141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155,
      156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170,
      171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185,
      186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
      201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215,
      216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230,
      231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245,
      246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 256, 257);
  EXPECT_EQ(s21_queue.top(), 257);
  EXPECT_EQ(s21_queue.size(), 257);
}

TEST(insert_many, queue_7) {
  s21::Queue<int> s21_queue;
  s21_queue.push(1);
  s21_queue.push(2);
  s21_queue.insert_many_back(3, 4);
  EXPECT_EQ(s21_queue.size(), 4);
  EXPECT_EQ(s21_queue.front(), 1);
}

TEST(insert_many, queue_8) {
  s21::Queue<int> s21_queue;
  s21_queue.push(1);
  s21_queue.push(2);
  s21_queue.insert_many_back(3, 4);
  s21_queue.insert_many_back(5, 6);
  EXPECT_EQ(s21_queue.size(), 6);
  EXPECT_EQ(s21_queue.back(), 6);
  s21_queue.pop();
  s21_queue.pop();
  EXPECT_EQ(s21_queue.size(), 4);
  EXPECT_EQ(s21_queue.front(), 3);
}

TEST(insert_many, queue_9) {
  s21::Queue<int> s21_queue;
  s21_queue.push(1);
  s21_queue.push(2);
  int i = 4;
  s21_queue.insert_many_back(3, i);
  EXPECT_EQ(s21_queue.size(), 4);
  EXPECT_EQ(s21_queue.back(), 4);
}

TEST(queue, move_assignment) {
  s21::Queue<int> queue7;
  s21::Queue<int> queue6;
  queue6.push(1);
  queue6.push(1);
  queue7.push(1);
  queue7 = std::move(queue6);
  EXPECT_EQ(queue7.size(), 2);
}
