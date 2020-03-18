/*
 * 2016, Vladislav Tananaev
 * tananaev@cs.uni-freiburg.de
 */
#pragma once
#include <cstdlib>  // EXIT_SUCESS, EXIT_FAILURE
#include <iomanip>
#include <iostream>
#include <string>
#include <opencv2/core.hpp>

namespace bm4d_gpu {

struct Parameters {
  std::string input_filename;
  std::string output_filename;
  float sim_th{2500.0f};  // Similarity threshold for the first step
  float hard_th{2.7f};    // Hard schrinkage threshold

  // Can be changed but not advisable
  int window_size{5};  // Search window, barely affects the results [Lebrun M., 2013]
  int step_size{3};    // Reasonable values {1,2,3,4}
                       // Significantly (exponentially) affects speed,
                       // slightly affect results
  int gpu_device{0};

  // Fixed in current implementation
  // TODO: check what's up here
  const int patch_size{4};  // Patch size
  const int maxN{16};       // Maximal number of the patches in one group

  bool parse(const int argc, const char* const* const argv, int* ret_val) {
    const cv::String keys =
      "{help h usage ?           |        | Print help message}"
      "{@input                   | <none> | Input file path (tiff/avi)}"
      "{@output                  |        | Output file path}"
      "{similarity-threshold     | 2500.  | Similarity threshold }"
      "{hard-shrinkage-threshold | 2.7    | Similarity threshold }"
      "{window-size              | 5      | Window size }"
      "{step-size                | 3      | Step size }"
      "{gpu-index                | 0      | GPU index }"
    ;
    cv::CommandLineParser parser(argc, argv, keys);

    if (parser.has("help")) {
      parser.printMessage();
      *ret_val = EXIT_SUCCESS;
      return false;
    }

    if (!parser.check()) {
      parser.printErrors();
      *ret_val = EXIT_FAILURE;
      return false;
    }

    input_filename = parser.get<cv::String>("@input");
    output_filename = parser.get<cv::String>("@output");
    sim_th = parser.get<float>("similarity-threshold");
    hard_th = parser.get<float>("hard-shrinkage-threshold");
    window_size = parser.get<int>("window-size");
    step_size = parser.get<int>("step-size");
    gpu_device = parser.get<int>("gpu-index");

    return true;
  }

  void printParameters() const {
    std::cout << "Parameters:" << std::endl;
    std::cout << "            input file: " << input_filename << std::endl;
    std::cout << "           output file: " << output_filename << std::endl;
    std::cout << "  similarity threshold: " << std::fixed << std::setprecision(3) << sim_th
              << std::endl;
    std::cout << "        hard threshold: " << std::fixed << std::setprecision(3) << hard_th
              << std::endl;
    std::cout << "           window size: " << window_size << std::endl;
    std::cout << "             step size: " << step_size << std::endl;
    std::cout << "  max cubes in a group: " << maxN << std::endl;
    std::cout << "            patch size: " << patch_size << std::endl;
  }
};
}  // namespace bm4d_gpu
