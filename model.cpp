#include "model.h"
#include <algorithm>

Model::Model(int input_width, int input_height, int number_of_classes, std::vector<int> dense_layers_sizes)
{
    m_input_layer = std::shared_ptr<Layer>{new FlattenLayer(input_width, input_height, nullptr)};
    std::shared_ptr<Layer> prev = m_input_layer;


    for (int size : dense_layers_sizes) {
        //auto dense = std::shared_ptr<Layer>{ new DenseLayer(dense_layers_sizes[0], m_input_layer)};
        auto dense = std::shared_ptr<Layer>{new DenseLayer(dense_layers_sizes[size], prev)};
        prev->SetNextLayer(dense);
        prev = dense;
    }

    m_output_layer = std::shared_ptr<Layer>{new OutputLayer(number_of_classes, prev)};

}

int Model::Infer(float **image)
{

    Matrix input(image);
    m_input_layer->Output(input);




}
