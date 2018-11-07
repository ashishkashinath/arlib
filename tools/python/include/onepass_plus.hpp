/**
 * @file onepass_plus.hpp
 * @author Leonardo Arcari (leonardo1.arcari@gmail.com)
 * @version 0.0.1
 * @date 2018-10-28
 *
 * @copyright Copyright (c) 2018 Leonardo Arcari
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#ifndef ARLIB_PYTHON_ONEPASS_PLUS_HPP
#define ARLIB_PYTHON_ONEPASS_PLUS_HPP

#include "graph_types.hpp"
#include "arlib_utils.hpp"

#include <arlib/graph_utils.hpp>
#include <arlib/multi_predecessor_map.hpp>
#include <arlib/onepass_plus.hpp>
#include <arlib/type_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>

#include <filesystem>
#include <exception>
#include <vector>

ARReturnType onepass_plus(std::string_view path_or_graph,
                          long unsigned int source, long unsigned int target,
                          int k, double theta, Graphs gtype);

namespace details {
template <typename Graph>
ARReturnType onepass_plus(Graph const &G, arlib::vertex_of_t<Graph> source,
                          arlib::vertex_of_t<Graph> target, int k,
                          double theta) {
  using Vertex = arlib::vertex_of_t<Graph>;
  auto predecessors = arlib::multi_predecessor_map<Vertex>{};
  arlib::onepass_plus(G, predecessors, source, target, k, theta);
  const auto alt_paths = arlib::to_paths(G, predecessors, source, target);

  return to_py_paths(alt_paths, source, target);
}

template <typename Graph>
ARReturnType
onepass_plus(std::string_view path_or_graph, arlib::vertex_of_t<Graph> source,
             arlib::vertex_of_t<Graph> target, int k, double theta) {
  // Check if path_or_graph is a file path
  namespace fs = std::filesystem;
  auto path = fs::path{path_or_graph};
  if (fs::is_regular_file(path)) {
    auto G = arlib::read_graph_from_file<Graph>(path_or_graph);
    if (!G) {
      throw std::invalid_argument{"Error while reading graph file."};
    }
    return details::onepass_plus(*G, source, target, k, theta);
  } else {
    auto G = arlib::read_graph_from_string<Graph>(std::string{path_or_graph});
    return details::onepass_plus(G, source, target, k, theta);
  }
}
} // namespace details

#endif