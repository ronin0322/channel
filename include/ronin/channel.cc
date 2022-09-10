/*
 * @Author: ronin0322
 * @Date: 2022-09-10 19:14:59
 * @LastEditors: ronin0322
 * @LastEditTime: 2022-09-10 19:24:07
 * @FilePath: /channel/include/channel.cc
 * @Description:
 *
 * Copyright (c) 2022 by ronin0322, All Rights Reserved.
 */

#include <iostream>

template <typename T>
class Channel
{
public:
    void Write(T val)
    {
        queue_.push(val);
    }
    T Read()
    {
        auto val = queue.top();
        queue_.pop();
        return val;
    }

private:
    std::size_t cap_;
    std::queue<T> queue_;
    std::condition_variable cnd;
};