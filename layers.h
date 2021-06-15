#ifndef LAYERS_H
#define LAYERS_H

#include <vector>
#include "matrix.h"
#include <memory>
#include <cmath>

class Layer 
{
public:
    Layer();
    ~Layer(){};
    virtual Matrix& Output(const Matrix&) = 0;
    void SetNextLayer(std::shared_ptr<Layer> next_layer);
    int Nodes();
    static float Sigmoid(float x);
    static Matrix& Sigmoid(const Matrix& x);

protected:
    std::weak_ptr<Layer> m_prev_layer;
    std::shared_ptr<Layer> m_next_layer = nullptr;
    int m_nodes = 0;
    int m_inputs = 0;


};

class FlattenLayer: public Layer
{
public:
    FlattenLayer(int width, int height, std::shared_ptr<Layer> t_prev_layer);
    Matrix& Output(const Matrix &input);


private:
    int m_neurons_count;
    int m_width;
    int m_height;


};

class DenseLayer: public Layer
{
public:
    DenseLayer(int size, std::shared_ptr<Layer> prev_layer);
    Matrix& Output(const Matrix &input);
    Matrix Sensitivity();

private:
    Matrix m_weights;
    Matrix m_sensitivity;
};


class OutputLayer: public Layer
{
public:
    OutputLayer(int size, std::shared_ptr<Layer> prev_layer);
    Matrix& Output(const Matrix &input);
    Matrix Sensitivity();

private:
    Matrix m_weights;
    Matrix m_sensitivity;
    int m_neurons_count;

};

#endif
