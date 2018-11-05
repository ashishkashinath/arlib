/**
 * @file penalty.cpp
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

#include "penalty.hpp"

#include <exception>
#include <string_view>

ARReturnType penalty(std::string_view path_or_graph, long unsigned int source,
                     long unsigned int target, int k, double theta, double p,
                     double r, int max_nb_updates, int max_nb_steps,
                     arlib::routing_kernels kernel, Graphs gtype) {
  switch (gtype) {
  case Graphs::AdjListInt:
    return details::penalty<GrAdjListInt>(path_or_graph, source, target, k,
                                          theta, p, r, max_nb_updates,
                                          max_nb_steps, kernel);
  case Graphs::AdjListFloat:
    return details::penalty<GrAdjListFloat>(path_or_graph, source, target, k,
                                            theta, p, r, max_nb_updates,
                                            max_nb_steps, kernel);
  default:
    throw std::invalid_argument{"Unknown Graph enum value."};
  }
}