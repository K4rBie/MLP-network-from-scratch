#ifndef MODELDEFINITION_H
#define MODELDEFINITION_H

#include <array>
#include <vector>
#include <list>


struct ModelDefinition 
{
    int input_width {};
    int input_height {};
    std::list<int> dense_layers_sizes;
    int number_of_classes {};
};


#endif