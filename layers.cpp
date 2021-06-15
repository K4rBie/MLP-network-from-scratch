#include "layers.h"

//
// Layer
//
Layer::Layer()
{

}

void Layer::SetNextLayer(std::shared_ptr<Layer> next_layer)
{
    m_next_layer = next_layer;
}

int Layer::Nodes()
{
    return m_nodes;
}

Matrix &Layer::Sigmoid(const Matrix &x)
{
    auto* ret = new Matrix(x);

    for(int i = 0; i < ret->Rows(); i++) {
        for(int j = 0; j < ret->Columns(); j++) {
            //ret->Set(i, j, Sigmoid(ret->Get(i, j)));
            ret->At(i, j) = Sigmoid(ret->At(i, j));
        }
    }

    return *ret;
}

float Layer::Sigmoid(float x)
{
    return 1/(1 + exp(-x));
}

//
// FlattenLayer
//
FlattenLayer::FlattenLayer(int width, int height, std::shared_ptr<Layer> t_prev_layer): m_width(width), m_height(height)
{
    m_nodes = width*height;
}

///
/// \brief FlattenLayer::Output starts the process of inference from this point using some precomputed input.
/// \param input
/// \return an output from the end of the model
///
Matrix& FlattenLayer::Output(const Matrix& input)
{
    auto* Z = new Matrix(Nodes(), 1);

    for(int i = 0; i < m_height; i++) {
        for(int j = 0; j < m_width; j++) {
            //Z->Set(i*m_width+j, 1, input.Get(i, j));
            Z->At(i*m_width+j, 1) = input.At(i, j);
        }
    }
    //return *Z;
    if (m_next_layer != nullptr) {
        return m_next_layer->Output(*Z);
    } else {
        return *Z;
    }

}


//
// DenseLayer
//
DenseLayer::DenseLayer(int size, std::shared_ptr<Layer> prev_layer)
{
    m_prev_layer = prev_layer;
    m_nodes = size;
    m_inputs = prev_layer->Nodes();

    m_weights = Matrix(m_inputs, Nodes());
    m_weights.FillRandom(-1,1);

    m_sensitivity = Matrix(m_inputs, Nodes());
    m_sensitivity.Fill(0);
}

Matrix& DenseLayer::Output(const Matrix &input)
{
    float sum = 0.0f;
    auto* z = new Matrix(Nodes(), 1);

    // go through every node
    for(int i = 0; i < Nodes(); i++)
    {
        sum = 0.0f;

        // sum all (weight x input) value pair
        for(int j = 0; j < m_inputs; j++)
        {
            sum += m_weights.Get(j,i) * input.Get(j, 1);
        }
        //ret->Set(i, 1, sum);
        z->At(i, 1) = Sigmoid(sum);
    }

    if (m_next_layer != nullptr) {
        return m_next_layer->Output(*z);
    } else {
        return *z;
    }

}

Matrix DenseLayer::Sensitivity()
{

}

//
// OutputLayer
//

OutputLayer::OutputLayer(int size, std::shared_ptr<Layer> prev_layer)
{

}

Matrix &OutputLayer::Output(const Matrix &input)
{

}

Matrix OutputLayer::Sensitivity()
{

}
