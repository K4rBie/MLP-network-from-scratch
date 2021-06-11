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
    int Infer();

private:
    std::list<Layer> m_layers; //pointers?

};


#endif