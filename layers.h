#ifndef LAYERS_H
#define LAYERS_H

#include <vector>
#include <memory>
#include <cmath>
#include <iostream>

#include "matrix.h"

using std::cout; using std::cin;
using std::endl; using std::string;

class Layer 
{
public:
    Layer();
    ~Layer(){};
    virtual Matrix output(const Matrix&) = 0;
    void setNextLayer(std::shared_ptr<Layer> next_layer);
    virtual int nodes();
    virtual Matrix computeSensitivity(const Matrix &next_weights, const Matrix &next_sensitivity) = 0;
    virtual void backPropagation(const Matrix& next_weights, const Matrix& next_sensitivity, float learning_rate) = 0;
    Matrix getLinOutput();


protected:
    static float sigmoid(float x);
    static Matrix& sigmoid(const Matrix& x);
    static float sigmoidDeriv(float x);
    static Matrix &sigmoidDeriv(const Matrix &x);

    virtual void updateWeights(Matrix in, float learning_rate) = 0;

    std::weak_ptr<Layer> m_prev_layer;
    std::shared_ptr<Layer> m_next_layer = nullptr;
    int m_nodes = 0;
    int m_inputs = 0;
    Matrix m_lin_output;
    Matrix m_sensitivity;
    Matrix m_weights;


};

class FlattenLayer: public Layer
{
public:
    FlattenLayer(int width, int height, std::shared_ptr<Layer> t_prev_layer);
    Matrix output(const Matrix &input);
    void backPropagation(const Matrix& next_weights, const Matrix& next_sensitivity, float learning_rate);

private:
    Matrix computeSensitivity(const Matrix &next_weights, const Matrix &next_sensitivity);
    void updateWeights(Matrix in, float learning_rate);
    int m_neurons_count;
    int m_width;
    int m_height;


};

class DenseLayer: public Layer
{
public:
    DenseLayer(int size, std::shared_ptr<Layer> prev_layer);
    Matrix output(const Matrix &input);
    void backPropagation(const Matrix& next_weights, const Matrix& next_sensitivity, float learning_rate);

private:
    void updateWeights(Matrix in, float learning_rate);
    Matrix computeSensitivity(const Matrix &next_weights, const Matrix &next_sensitivity);


};


class OutputLayer: public Layer
{
public:
    OutputLayer(int size, std::shared_ptr<Layer> prev_layer);
    Matrix output(const Matrix &input);
    void backPropagation(const Matrix &next_weights, const Matrix &next_sensitivity, float learning_rate);

private:
    Matrix computeSensitivity(const Matrix&, const Matrix &next_sensitivity);
    void updateWeights(Matrix in, float learning_rate);
    Matrix m_weights;
    Matrix m_sensitivity;
    int m_neurons_count;

};

#endif
