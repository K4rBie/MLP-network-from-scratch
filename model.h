#ifndef MODEL_H
#define MODEL_H

#include <array>
#include <list>
#include <vector>

#include "layers.h"

class Model 
{
public:
    Model(int input_width, int input_height, int number_of_classes, std::vector<int> dense_layers_sizes);
    void Train();
    int Infer(float** image);

private:
    std::shared_ptr<Layer> m_input_layer = nullptr;
    std::shared_ptr<Layer> m_output_layer = nullptr;

};


#endif
