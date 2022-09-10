/*
 * @Author: ronin0322
 * @Date: 2022-09-10 19:14:59
 * @LastEditors: ronin0322
 * @LastEditTime: 2022-09-10 20:52:32
 * @FilePath: /channel/include/ronin/channel.hpp
 * @Description:
 *
 * Copyright (c) 2022 by ronin0322, All Rights Reserved.
 */

#include <atomic>
#include <condition_variable>
#include <iostream>
#include <queue>
namespace ronin
{
    template <typename T>
    class Channel
    {
    public:
        Channel()
        {
            is_closed_.store(false);
        }
        Channel(int cap) : cap_(cap)
        {
            is_closed_.store(false);
        }
        void Write(T val)
        {
            if (is_closed_.load())
                throw std::runtime_error("cannot write on closed channel");
            std::unique_lock<std::mutex> lck(mtx_);
            while (cap_ > 0 && queue_.size() >= cap_)
            {
                cnd_.wait(lck);
            }
            std::cout << "Write wake up" << std::endl;
            queue_.push(val);
            cnd_.notify_one();
        }
        T Read()
        {
            if (is_closed_.load() && queue_.empty())
            {
                return T();
            }
            std::unique_lock<std::mutex> lck(mtx_);
            while (queue_.size() == 0 && !is_closed_.load())
            {
                cnd_.wait(lck);
            }
            std::cout << "Read wake up" << std::endl;
            auto val = queue_.front();
            queue_.pop();
            cnd_.notify_one();
            return val;
        }

    private:
        std::size_t cap_;
        std::queue<T> queue_;
        std::condition_variable cnd_;
        std::mutex mtx_;
        std::atomic<bool> is_closed_;
    };
}