#ifndef LAYERS_H
#define LAYERS_H

#include <vector>
#include "matrix.h"

class Layer 
{
public:
    Layer();
    ~Layer();
    virtual std::vector<float> Output() = 0;
    int Size();
    virtual Matrix Sensitivity() = 0;

protected:
    Layer* m_prev_layer; //sharedptr
    Layer* m_next_layer;
    int m_size;
    Matrix m_weights;
    Matrix m_sensitivity;

};

class InputLayer: Layer 
{
public:
    InputLayer(float size);
    std::vector<float> Output();

private:
    

};

class DenseLayer: Layer 
{
public:
    DenseLayer(float size);
    std::vector<float> Output();

private:

};



class FlattenLayer: Layer 
{
public:
    FlattenLayer(float size, Layer* t_prev_layer);
    std::vector<float> Output();

private:
    

};

class OutputLayer: Layer 
{
public:
    OutputLayer(float size);
    std::vector<float> Output();

private:
    

};

#endif