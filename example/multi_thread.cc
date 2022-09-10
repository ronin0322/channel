/*
 * @Author: ronin0322
 * @Date: 2022-09-10 19:25:17
 * @LastEditors: ronin0322
 * @LastEditTime: 2022-09-10 20:46:43
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
    std::cout << "ch->Write(" << val << ")" << std::endl;
    ch->Write(val);
}
int main()
{
    int threads_num = 2;
    ronin::Channel<int> ch(1);
    std::thread read_threads[threads_num];

    for (int i = 0; i < threads_num; i++)
        read_threads[i] = std::thread(ReadThreadTask, &ch);

    std::thread write_threads[threads_num];
    for (int i = 0; i < threads_num; i++)
        write_threads[i] = std::thread(WriteThreadTask, &ch, i);

    for (auto &x : read_threads)
        x.join();
    for (auto &x : write_threads)
        x.join();
    return 0;
}