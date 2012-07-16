#include <algorithm>                 // for std::for_each
#include <iostream>                  // for std::cout
#include <utility>                   // for std::pair
#include <deque>
#include <list>
#include <tuple>
#include <boost/lexical_cast.hpp>

int main(int argc, char * argv[])    
{
  // A:1 B:1 C:4 D:2 E:2 F:4 G:1 H:2 I:4 
  if (argc > 1) {
    // tuple<index, name, visited, value>
    typedef std::tuple<int, std::string, int> Vertex;
    std::deque<Vertex> vertexq;
    while(*++argv)
    {
      static int value = 0;
      static int index = 0;
      static int argv_counter = 0;
      static int mod;
      static int quotient;
      try
      {
        value = boost::lexical_cast<int>(*argv);
        if(value < 1) {
          std::cerr << "bad input" << std::endl;
        }
        // 生成名字
        std::string name;
        quotient = argv_counter;
        do {
          mod = quotient % 27;
          name += static_cast<char>('A' + mod);
          quotient /= 27;
        } while (quotient > 26);
        vertexq.push_back(Vertex(index++, name, value));        
      }
      catch(boost::bad_lexical_cast &)
      {
        std::cerr << "bad lexical cast" << std::endl;
        return -1;
      }
      ++argv_counter;
    }
    std::cout << "Vertex[]:" << std::endl;
    for(auto & vertex: vertexq) {
      std::cout << std::get<0>(vertex) << ":" << std::get<1>(vertex) << " ";
    }
    std::cout << std::endl;
    // 找出所有边
    std::cout << "Edge[]:" << std::endl;
    typedef std::pair<Vertex, Vertex> Edge;
    std::deque<Edge> edgeq;
    const size_t size = vertexq.size();
    int left = 0;
    int right = 0;
    for (auto & vertex: vertexq) {
      // 出边右
      right = (std::get<0>(vertex) + std::get<2>(vertex)) % size;
      // 出边左
      left = (std::get<0>(vertex) - std::get<2>(vertex) + size) % size;
      // 此处能用vertexq[right]的原因是, typename Vertex 的 member<0> index 是 i++
      // Vertex 用 map 可读性更好
      edgeq.push_back(Edge(vertex, vertexq[right]));
      edgeq.push_back(Edge(vertex, vertexq[left]));
    }
    // 显示边
    for (auto & edge: edgeq) {
      std::cout << std::get<1>(edge.first)
                << "->"
                << std::get<1>(edge.second)
                << " ";
    }
    std::cout << std::endl;
    // 起点，共 size 个
    std::cout << "visit begin:" << std::endl;
    // 依次从每个节点开始遍历
    for (auto & vertex: vertexq) {
      static int index;
      static int counts;
      static bool right_visited;
      static bool left_visited;
      static Vertex * current = nullptr;
      static Vertex * branch = nullptr;
      static std::deque<Vertex> branchq;
      static std::deque<Vertex> visitedq;
      current = &vertex;
      branch = &vertex;
      visitedq.push_back(*current);
      // continue;
      while(true) {
        std::cout << std::get<1>(visitedq.back()) << " ";
        right_visited = false;
        left_visited = false;
        // 先右后左
        index = std::get<0>(*current) * 2;
        current = &edgeq[index].second; // 修改当前节点,右
        branch = &edgeq[index + 1].second; // 可能的当前节点(分支当前节点),左
        // 判断current是否被访问过
        for(auto & x: visitedq) {
          if(x == *current) {
            right_visited = true;
            break; // for(Vertex & x: visitedq) {
          }
        }
        for(auto & x: visitedq) {
          if(x == *branch) {
            left_visited = true;
            break; // for(Vertex & x: visitedq) {
          }
        }
        if(right_visited) {
          if(left_visited) {
            // 都被访问过, 1 1
            // 回退
            if(not branchq.empty()) {
              std::cout << std::endl << "branchq: ";
              for(auto & x: branchq) {
                std::cout << std::get<1>(x) << " ";
              }
              std::cout << std::endl;
              counts = 0;
              while (not branchq.empty()) {
                static int tmp;
                tmp = counts;
                for (auto & x: visitedq) {
                  if (branchq.back() == x) {
                    branchq.pop_back();
                    ++counts;
                    break;
                  }
                }
                if (tmp != counts) {
                  tmp = counts;
                } else {
                  break;
                }
              }
              std::cout << "counts = " << counts << std::endl;
              while (counts--) {
                visitedq.pop_back();
              }
              visitedq.pop_back();
              for (auto & x: visitedq) {
                std::cout << std::get<1>(x) << " ";
              }
              std::cout << std::endl;
              if (branchq.empty()) {
                break;
              }
              current = &branchq.back();
              visitedq.push_back(*current);
              branchq.pop_back();
            } else {
              std::cout << std::endl;
              break; // while(true) {
            }
          } else {
            // 右被访问过，左没被访问过, 1 0
            visitedq.push_back(*branch);
            branchq.push_back(*current);
            current = branch;
          }
        } else {
          if (left_visited) {
            // 右没被访问过, 左被访问过, 0 1
            visitedq.push_back(*current);
            branchq.push_back(*branch);
          } else {
            // 都没被访问过, 0 0
            visitedq.push_back(*current);
            branchq.push_back(*branch);
          }
        }
        if(visitedq.size() == size) {
          std::cout << "found:" << std::endl;
          break; // while(true)  
        }
      } // while(true)     
      if(visitedq.size() == size) {
        for (auto & x: visitedq) {
          std::cout << std::get<1>(x) << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
          //break;
      }
      branchq.clear();
      visitedq.clear();
    } // for (Vertex & vertex: vertexq) {
  }
  return 0;
}
  
