#include "layers.h"

//
// Layer
//
Layer::Layer()
{

}

void Layer::setNextLayer(std::shared_ptr<Layer> next_layer)
{
    m_next_layer = next_layer;
}

int Layer::nodes()
{
    return m_nodes;
}

Matrix Layer::getLinOutput()
{
    return m_lin_output;
}

Matrix &Layer::sigmoid(const Matrix &x)
{
    auto* ret = new Matrix(x);

    for(int i = 0; i < ret->rows(); i++) {
        for(int j = 0; j < ret->columns(); j++) {
            //ret->Set(i, j, Sigmoid(ret->Get(i, j)));
            ret->at(i, j) = sigmoid(ret->at(i, j));
        }
    }

    return *ret;
}

Matrix &Layer::sigmoidDeriv(const Matrix &x)
{
    auto* ret = new Matrix(x);

    for(int i = 0; i < ret->rows(); i++) {
        for(int j = 0; j < ret->columns(); j++) {
            //ret->Set(i, j, Sigmoid(ret->Get(i, j)));
            ret->at(i, j) = sigmoidDeriv(ret->at(i, j));
        }
    }

    return *ret;
}

float Layer::sigmoid(float x)
{
    return 1/(1 + exp(-x));
}

float Layer::sigmoidDeriv(float x)
{
    float z = sigmoid(x);
    return z*(1-z);
}






//
// FlattenLayer
//
FlattenLayer::FlattenLayer(int width, int height, std::shared_ptr<Layer> t_prev_layer): m_width(width), m_height(height)
{
    m_nodes = width*height;

    m_lin_output = Matrix(nodes(), 1);
    m_lin_output.Fill(0);

}

///
/// \brief FlattenLayer::Output starts the process of inference from this point using some precomputed input.
/// \param input
/// \return an output from the end of the model
///
Matrix FlattenLayer::output(const Matrix& input)
{
    Matrix Z(nodes(), 1);

    for(int i = 0; i < m_height; i++) {
        for(int j = 0; j < m_width; j++) {
            //Z->Set(i*m_width+j, 1, input.Get(i, j));
            Z.at(i*m_width+j, 0) = input.at(i, j);
            m_lin_output.at(i*m_width+j, 0) = input.at(i, j);
        }
    }

    // go to next layer or return output
    if (m_next_layer != nullptr) {
        return m_next_layer->output(Z);
    } else {
        return Z;
    }
}

void FlattenLayer::backPropagation(const Matrix &next_weights, const Matrix &next_sensitivity, float learning_rate)
{
    return;
}

///
/// \brief FlattenLayer::computeSensitivity
/// \param next_weights
/// \param next_sensitivity
/// \return zawsze NULL ale to tylko przy założeniu, że nie ma przed nim żadnej głębokiej warstwy.
///
Matrix FlattenLayer::computeSensitivity(const Matrix &next_weights, const Matrix &next_sensitivity)
{
    // tylko przy założeniu że to krańcowa warstwa
    m_sensitivity.Fill(0);
    return m_sensitivity;
}

void FlattenLayer::updateWeights(Matrix in, float learning_rate)
{

}





//
// DenseLayer
//
DenseLayer::DenseLayer(int size, std::shared_ptr<Layer> prev_layer)
{
    m_prev_layer = prev_layer;
    m_nodes = size;
    m_inputs = prev_layer->nodes();

    m_weights = Matrix(m_inputs, nodes());
    m_weights.FillRandom(-1,1);

    m_sensitivity = Matrix(nodes(), 1);
    m_sensitivity.Fill(0);

    m_lin_output = Matrix(nodes(), 1);
    m_lin_output.Fill(0);
}

Matrix DenseLayer::output(const Matrix &input)
{
    float sum = 0.0f;
    Matrix z(nodes(), 1);

    // go through every node
    for(int i = 0; i < nodes(); i++)
    {
        sum = 0.0f;

        // sum all (weight x input) value pair
        for(int j = 0; j < m_inputs; j++)
        {
            sum += m_weights.Get(j,i) * input.Get(j, 0);
        }
        //ret->Set(i, 1, sum);
        z.at(i, 0) = sigmoid(sum);
        m_lin_output.at(i, 0) = sum;
    }

    if (m_next_layer != nullptr) {
        return m_next_layer->output(z);
    } else {
        return z;
    }

}

Matrix DenseLayer::computeSensitivity(const Matrix& next_weights, const Matrix& next_sensitivity)
{
    m_sensitivity.Fill(0);

    float sum = 0.0f;

    for (int i = 0; i < m_nodes; i++) {
        sum = 0.0f;
        for (int j = 0; j < next_sensitivity.rows(); j ++) {
            // i,j bo bieżemy i-tą wagę z każdego node'a następnej warstwy
            sum += next_weights.at(i,j) * next_sensitivity.at(j, 0);
        }
        m_sensitivity.at(i, 0) = sigmoidDeriv(m_lin_output.at(i, 0)) * sum;
    }
    //cout << endl << "sensitivity: " << endl;
    //m_sensitivity.print();

    return m_sensitivity;
}

void DenseLayer::backPropagation(const Matrix& next_weights, const Matrix& next_sensitivity, float learning_rate)
{
    computeSensitivity(next_weights, next_sensitivity);

    // to przed zmianami w wagach, żeby nie wpływały błędnie na poprzednie warstwy.
    auto prev_layer = m_prev_layer.lock();

    prev_layer->backPropagation(m_weights, m_sensitivity, learning_rate);

    // policz zmianę na wagach
    updateWeights(prev_layer->getLinOutput(), learning_rate);

}

void DenseLayer::updateWeights(Matrix in, float learning_rate)
{
    //cout << "output from previous layer: " << endl;
    //in.print();
    for (int i = 0; i < m_nodes; i++)
    {
        for (int j = 0; j < m_inputs; j++)
        {
            m_weights.at(j, i) -= learning_rate * sigmoid(in.at(j,0))*m_sensitivity.at(i, 0);
        }
    }
}





///
/// \brief OutputLayer::OutputLayer
/// \param size
/// \param prev_layer
///
OutputLayer::OutputLayer(int size, std::shared_ptr<Layer> prev_layer)
{
    m_prev_layer = prev_layer;
    m_nodes = size;
    m_inputs = prev_layer->nodes();

    m_weights = Matrix(m_inputs, nodes());
    m_weights.FillRandom(-1,1);

    m_sensitivity = Matrix(nodes(), 1);
    m_sensitivity.Fill(0);

    m_lin_output = Matrix(nodes(), 1);
    m_lin_output.Fill(0);
}

Matrix OutputLayer::output(const Matrix &input)
{
    float sum = 0.0f;
    Matrix z(nodes(), 1);

    //m_weights.print();
    //input.print();
    // go through every node
    for(int i = 0; i < nodes(); i++)
    {
        sum = 0.0f;

        // sum all (weight x input) value pair
        for(int j = 0; j < m_inputs; j++)
        {
            sum += m_weights.Get(j,i) * input.Get(j, 0);
        }
        //ret->Set(i, 1, sum);
        m_lin_output.at(i, 0) = sum;
        z.at(i, 0) = sigmoid(sum);
    }

    if (m_next_layer != nullptr) {
        return m_next_layer->output(z);
    } else {
        return z;
    }
}

Matrix OutputLayer::computeSensitivity(const Matrix &, const Matrix &classification)
{
    // z-s to sensitivity już przy sigmoidzie

    m_sensitivity = sigmoid(m_lin_output) - classification;

    return m_sensitivity;
}

void OutputLayer::updateWeights(Matrix in, float learning_rate)
{
    for (int i = 0; i < m_nodes; i++)
    {
        for (int j = 0; j < m_inputs; j++)
        {
            m_weights.at(j, i) -= sigmoid(in.at(j,0))*m_sensitivity.at(i, 0);
        }
    }
}

void OutputLayer::backPropagation(const Matrix &next_weights, const Matrix &next_sensitivity, float learning_rate) //????????????????????????????
{
    computeSensitivity(next_weights, next_sensitivity);

    // to przed zmianami w wagach, żeby nie wpływały błędnie na poprzednie warstwy.
    auto prev_layer = m_prev_layer.lock();

    prev_layer->backPropagation(m_weights, m_sensitivity, learning_rate);

    // policz zmianę na wagach
    updateWeights(prev_layer->getLinOutput(), learning_rate);
}
