//
// Created by chaomaer on 2023/1/31.
//

#include "thread.h"

Frame *Thread::new_frame(Method* method) {
    return new Frame(this, method);
}

void Thread::push_frame(Frame *frame) {
    stack.push(frame);
}

Frame *Thread::pop_frame() {
    auto frame = stack.top();
    stack.pop();
    return frame;
}

Frame *Thread::top_frame() {
    return stack.top();
}

bool Thread::empty_frame() {
    return stack.size() == 0;
}
