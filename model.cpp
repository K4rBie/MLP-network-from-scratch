#include "model.h"

Model::Model(int input_width, int input_height, int number_of_classes, std::vector<int> dense_layers_sizes)
    : m_input_width(input_width), m_input_height(input_height), m_classes(number_of_classes)
{
    m_input_layer = std::shared_ptr<Layer>{new FlattenLayer(input_width, input_height, nullptr)};
    std::shared_ptr<Layer> prev = m_input_layer;

    for (int size : dense_layers_sizes) {
        //auto dense = std::shared_ptr<Layer>{ new DenseLayer(dense_layers_sizes[0], m_input_layer)};
        auto dense = std::shared_ptr<Layer>{new DenseLayer(size, prev)};
        prev->setNextLayer(dense);
        prev = dense;
    }

    m_output_layer = std::shared_ptr<Layer>{new OutputLayer(number_of_classes, prev)};
    prev->setNextLayer(m_output_layer);
}

float Model::trainingEpoch(const path& training_data_path, float learning_rate)
{
    Matrix image;
    Matrix labels;
    float loss = 0.f;
    int images = 0;

    for (const auto& img_file : directory_iterator(training_data_path))
    {
        path img_path = img_file.path();

        string ext = img_path.extension();
        string jpg = ".jpg";
        string jpeg = ".jpeg";

        if ((ext==jpg || ext==jpg) && classesFileExists(img_path))
        {
            CImg<float> img(img_path.c_str());
            img.resize(m_input_width, m_input_height,1,1,3);

            image = Matrix(img);
            labels = fetchLabels(img_path);

            //cout << "labels: " << endl;
            //labels.print();

            Matrix inference = infer(image);
            backPropagation(labels, learning_rate);

            loss += calculateLoss(inference, labels);
            images++;

        }     
    }

    cout << "(obrazy: " << images << ") ";
    float average_loss = loss/(float)images;
    return average_loss;
}

void Model::train(const path& training_data_path, int epochs, float learning_rate)
{
    float previous_loss = MAXFLOAT;
    float actual_loss = MAXFLOAT;

    for (int i = 0; i < epochs; i++) {
        previous_loss = actual_loss;
        actual_loss = trainingEpoch(training_data_path, learning_rate);

        cout << "aktualna strata po " << i+1 << " epokach: " << actual_loss << endl;

        //if (actual_loss > previous_loss) break;
    }
}

void Model::evaluate(const path &eval_data_path)
{
    Matrix image;
    Matrix labels;
    float loss = 0.f;
    int images = 0;

    for (const auto& img_file : directory_iterator(eval_data_path))
    {
        path img_path = img_file.path();

        string ext = img_path.extension();
        string jpg = ".jpg";
        string jpeg = ".jpeg";

        if ((ext==jpg || ext==jpg) && classesFileExists(img_path))
        {
            CImg<float> img(img_path.c_str());
            img.resize(m_input_width, m_input_height,1,1,3);


            image = Matrix(img);
            labels = fetchLabels(img_path);

            //cout << "labels: " << endl;
            //labels.print();

            Matrix inference = infer(image);

            loss += calculateLoss(inference, labels);
            images++;

        }
    }
    cout << "ewaluacja na " << images << " obrazach." << endl;
    float average_loss = loss/(float)images;
    cout << "??rednia strata to: " << average_loss << endl;
}


bool Model::classesFileExists(const path& image_path)
{
    string config_str = image_path.parent_path().c_str() + string("/") + image_path.stem().c_str() + string(".txt");
    path config_path(config_str);

    if (std::filesystem::exists(config_path)){
        //cout << "classes path: " << config_str << " exists." << endl;
        return true;
    } else {
        cout << "brak etykiet dla obrazu: " << image_path << endl;
        return false;
    }
}

Matrix Model::fetchLabels(const path &image_path)
{
    string config_str = image_path.parent_path().c_str() + string("/") + image_path.stem().c_str() + string(".txt");
    std::fstream config_file;
    config_file.open(config_str, std::ios::in);
    Matrix classes(m_classes, 1);

    if (config_file.is_open()) {
        for (int i = 0; i < m_classes; i++){
            if(!config_file.eof()){
                config_file >> classes.at(i, 0);
            } else {
                throw;
            }
        }
    }

    config_file.close();

    return classes;
}

void Model::backPropagation(const Matrix& training_labels, float learning_rate)
{
    Matrix null_matrix(1,1);
    m_output_layer->backPropagation(null_matrix, training_labels, learning_rate);
}

float Model::calculateLoss(const Matrix& inference, const Matrix& training_labels)
{
    float loss = 0;
    float s, z;
    float epsilon = 1e-7f;

    // tu mo??e chodzi?? o liniowy output (tak rozumiem obliczenia z prezentacji),
    //ale nie jestem pewien bo b????d powinni??my liczy?? od ostatecznego wyniku
    //??
    for (int i = 0; i < inference.rows(); i++) {
        s = training_labels.at(i, 0);
        z = inference.at(i, 0);

        if (s < epsilon) s = epsilon;
        else
        if (1.f - s < epsilon) s = 1.f - epsilon;

        if (z < epsilon) z = epsilon;
        else
        if (1.f - z < epsilon) z = 1.f - epsilon;

        loss += -( s*log(z) + (1.f-s) * log(1.f-z));
    }

    return loss;
}

///
/// \brief Model::Infer Returns a Matrix of class fit probabilities
/// \param image
/// \return
///
Matrix Model::infer(Matrix image)
{

    //Matrix input(image);
    Matrix classification = m_input_layer->output(image);

    //classification.print();

    return classification;
}
