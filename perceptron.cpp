#include "perceptron.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>

Perceptron::Perceptron(int number_of_inputs) : m_inputs(number_of_inputs) 
{
    m_weights.reserve(m_inputs+1);
    //srand((unsigned int)std::time(NULL));
    
    float max = 1;
    float min = -1;

    for (int i = 0; i <= m_inputs; i++){
        m_weights.push_back(min + (float)std::rand()/(float)RAND_MAX*(max - min));
    }
    //assign random values 0 to 1


}

float Perceptron::Output(std::vector<float> inputs)
{
    float sum = 0;

    for (int i = 0; i < inputs.size(); i++) {
        sum += m_weights[i]*inputs[i];
    }

    sum -= m_weights[m_weights.size()-1];


    return sum;
}


float Perceptron::Sigmoid(float x) {
    //return 1/(1+exp());

    //int o = exp();
}

// a może lepiej to wszystko na wielkich macierzach? wtedy przechodzę z obliczeniami przez kolejne 