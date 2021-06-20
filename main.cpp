#include <iostream>
#include <cmath>
#include "model.h"

int main (int argc, char *argv[]) { 
    Matrix a(2,2);
    Matrix b(2,2);
    a.Fill(1);
    b.Fill(2);
    b = a + b;
    b.At(1,1) = 1;
    b.Set(1,1,2);
    //cout << b.Get(1,1) << endl;

    //b.print();
    string training = "";
    string image_path = "";
    int epochs = 0;

    std::vector<int> dense_layers {50, 20, 7};

    Model model(100, 100, 6, dense_layers);

    cout << "wybierz folder z danymi treningowymi: ";
    cin >> training;
    cout << endl;

    cout << "wybierz ilość epok: ";
    cin >> epochs;
    cout << endl;

    model.train(training, epochs, 0.1f);

    cout << "uczenie zakończone" << endl;

    while (true) {
        cout << "wybierz obraz do analizowania: ";
        cin >> image_path;
        cout << endl;

        if(image_path == "q") break;

        CImg<float> img(image_path.c_str());

        Matrix image(img);
        //image.print();


        Matrix result = model.infer(image);
        result.print();
    }







 }
