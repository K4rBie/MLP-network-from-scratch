#ifndef MODEL_H
#define MODEL_H

#include <array>
#include <list>
#include <vector>
#include <iostream>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include "CImg.h"

#include "layers.h"

using std::cout; using std::cin;
using std::endl; using std::string;
using std::filesystem::directory_iterator;
using std::filesystem::path;
using std::shared_ptr;
using cimg_library::CImg;

class Model 
{
public:
    Model(int input_width, int input_height,
          int number_of_classes,
          std::vector<int> dense_layers_sizes);
    void train(const std::filesystem::__cxx11::path &training_data_path, int epochs, float learning_rate);
    Matrix infer(Matrix image);
    

private:
    bool classesFileExists(const path& image_path);
    Matrix trainingLabels(const path& image_path);
    void backPropagation(const Matrix& training_labels, float learning_rate);
    float calculateLoss(const Matrix& inference, const Matrix &training_labels);
    float trainingEpoch(const path &training_data_path, float learning_rate);

    shared_ptr<Layer> m_input_layer = nullptr;
    shared_ptr<Layer> m_output_layer = nullptr;

    int m_input_width;
    int m_input_height;
    int m_classes;
    path m_training_data_path;

};


#endif
