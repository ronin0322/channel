###
 # @Author: ronin0322
 # @Date: 2022-07-05 00:00:32
 # @LastEditors: ronin0322
 # @LastEditTime: 2022-09-10 20:43:40
 # @FilePath: /channel/build.sh
 # @Description: 
 # 
 # Copyright (c) 2022 by ronin0322, All Rights Reserved. 
### 
g++ example/multi_thread.cc -o output/multi_thread -std=c++11 -pthread
# ./output/multi_thread