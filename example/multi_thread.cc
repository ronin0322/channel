/*
 * @Author: ronin0322
 * @Date: 2022-09-10 19:25:17
 * @LastEditors: ronin0322
 * @LastEditTime: 2022-09-10 23:14:08
 * @FilePath: /channel/example/multi_thread.cc
 * @Description:
 *
 * Copyright (c) 2022 by ronin0322, All Rights Reserved.
 */

#include "../include/ronin/channel.hpp"
#include <iostream>
#include <thread>
void ReadThreadTask(ronin::Channel<int> *ch)
{
    std::cout << "ch->Read()" << ch->Read() << std::endl;
}
void WriteThreadTask(ronin::Channel<int> *ch, int val)
{
    ch->Write(val);
    std::cout << "ch->Write(" << val << ")" << std::endl;
}
int main()
{
    int threads_num = 10;
    ronin::Channel<int> ch;
    std::thread read_threads[threads_num];

    std::thread write_threads[threads_num];
    for (int i = 0; i < threads_num; i++)
        write_threads[i] = std::thread(WriteThreadTask, &ch, i);

    for (int i = 0; i < threads_num; i++)
        read_threads[i] = std::thread(ReadThreadTask, &ch);

    for (auto &x : read_threads)
        x.join();
    for (auto &x : write_threads)
        x.join();
    return 0;
}