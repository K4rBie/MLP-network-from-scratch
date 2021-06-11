#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <array>
#include <vector>

class Perceptron
{
public:
  Perceptron(int number_of_inputs);

  float Output(std::vector<float> inputs);

private:
    int m_inputs;
    std::vector<float> m_weights;
    float Sigmoid(float x);
};

#endif