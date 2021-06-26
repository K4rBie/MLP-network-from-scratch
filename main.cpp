#include <iostream>
#include <cstring>
#include <cmath>
#include "model.h"

int main (int argc, char *argv[]) { 
    string training = "";
    string eval = "";
    string image_path = "";
    string epochs_str = "";
    string height_str = "";
    string width_str = "";
    string out_str = "";

    string lr_str = "";
    string layer_size_str = "";
    int layer_size = 0;
    int epochs = 0;
    float lr = 0.1f;
    int height = 0;
    int width = 0;
    int out = 0;
    std::vector<int> dense_layers {};


    cout << "BUDOWANIE SIECI" << endl;


    cout << "podaj wysokość zdjęcia (dom. 100): ";
    std::getline(std::cin, height_str);
    if (height_str == "") height = 100;
    else height = std::stoi(height_str);

    cout << "podaj szerokość zdjęcia (dom. 100): ";
    std::getline(std::cin, width_str);
    if (width_str == "") width = 100;
    else width = std::stoi(width_str);


    cout << "wprowadź dowolną ilość warstw gęstych podając pojedynczo ich rozmiary (integer)." << endl;
    cout << "Naciśnij q aby zakończyć wprowadzanie rozmiarów warstw. Lista nie może być pusta." << endl;

    while (true)
    {
        std::getline(std::cin, layer_size_str);
        if (layer_size_str == "q" && !dense_layers.empty()) break;
        dense_layers.push_back(std::stoi(layer_size_str));
    }
    out = dense_layers.back();
    dense_layers.pop_back();

    cout << endl;
    cout << "UCZENIE SIECI" << endl;
    Model model(width, height, out, dense_layers);

    cout << "wybierz folder z danymi treningowymi (dom. train): ";
    std::getline(std::cin, training);
    //cin >> training;
    if (training == "") training = "train";

    cout << "wybierz folder z danymi ewaluacyjnymi (dom. eval): ";
    std::getline(std::cin, eval);
    if (eval == "") eval = "eval";

    cout << "wybierz ilość epok (dom. 50): ";
    std::getline(std::cin, epochs_str);
    if (epochs_str == "") epochs = 50;
    else epochs = std::stoi(epochs_str);

    cout << "wybierz learning rate (dom. 0.1): ";
    std::getline(std::cin, lr_str);
    if (lr_str == "") lr = 0.1f;
    else lr = std::stoi(lr_str);

    cout << endl;
    cout << "uczenie rozpoczęte" << endl;
    model.train(training, epochs, lr);

    cout << "uczenie zakończone" << endl;

    model.evaluate(eval);


    while (true) {
        cout << "wybierz obraz do analizowania: ";
        cin >> image_path;
        cout << endl;

        path path(image_path);

        if(image_path == "q") break;
        if(!std::filesystem::exists(path)) continue;

        CImg<float> img(image_path.c_str());
        img.resize(width, height,1,1,3);

        Matrix image(img);
        //image.print();


        Matrix result = model.infer(image);
        result.print();
    }

 }
