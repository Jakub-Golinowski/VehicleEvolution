#include "window.h"
#include "evolutioncontroller.h"


Window::Window(): view_(&model_), controller_(&model_, &view_)
{
    model_.addTrack();

    evolutionInputGenerationTypeComboBox_.addItem(tr("Losowe"), evolutionInputGenerationTypeEnum::RANDOM);
    evolutionInputGenerationTypeComboBox_.addItem(tr("Plik"), evolutionInputGenerationTypeEnum::FROMFILE);

    numberOfEvolutionGenerationsSpinBox_.setRange(1, 20);

    numberOfEvolutionGenerationsLabel_.setText("Liczba iteracji algorytmu:");
    numberOfEvolutionGenerationsLabel_.setBuddy(&numberOfEvolutionGenerationsSpinBox_);

    numberOfVisualizedChromosomeSpinBox_.setRange(1, EvolutionController::GENERATION_SIZE);

    numberOfVisualizedChromosomeLabel_.setText("Numer wyświetlanego chromosomu:");
    numberOfVisualizedChromosomeLabel_.setBuddy(&numberOfVisualizedChromosomeSpinBox_);

    randomGenerationButton.setText("Wygeneruj losową generację pojazdów");
    fromFileButton.setText("Wczytaj generację pojazdów z pliku");
    evolutionStartButton_.setText("Start ewolucji");

    connect(&randomGenerationButton, SIGNAL(clicked(bool)),
            this, SLOT(randomGenerationButtonClicked()));
    connect(&fromFileButton, SIGNAL(clicked(bool)),
            this, SLOT(fromFileButtonButtonClicked()));
    connect(&numberOfVisualizedChromosomeSpinBox_, SIGNAL(valueChanged(int)),
            this, SLOT(numberOfVisualizedChromosomeChanged()));
    connect(&evolutionStartButton_, SIGNAL(clicked(bool)), this, SLOT(evolutionStartButtonClicked()));

    view_.setFrameShape( view_.Box);
    view_.setLineWidth(3);

    mainLayout_.setColumnStretch(0, 1);
    mainLayout_.setColumnStretch(3, 1);
    mainLayout_.addWidget(&view_, 0, 0, 1, 4, Qt::AlignCenter);
    mainLayout_.addWidget(&numberOfVisualizedChromosomeLabel_, 1, 0, Qt::AlignLeft);
    mainLayout_.addWidget(&numberOfVisualizedChromosomeSpinBox_, 1, 1, Qt::AlignLeft);
    mainLayout_.addWidget(&randomGenerationButton, 2, 0, Qt::AlignLeft);
    mainLayout_.addWidget(&fromFileButton, 2, 1, Qt::AlignLeft);
    mainLayout_.addWidget(&numberOfEvolutionGenerationsLabel_, 3, 0, Qt::AlignLeft);
    mainLayout_.addWidget(&numberOfEvolutionGenerationsSpinBox_, 3, 1, Qt::AlignLeft);
    mainLayout_.addWidget(&evolutionStartButton_, 4,0, Qt::AlignCenter);
    setLayout(&mainLayout_);

    numberOfEvolutionGenerationsChanged();

    setWindowTitle("Ewolucja pojazdów");

    connect(&evolutionWatcher, SIGNAL(finished()), this, SLOT(finishedEvolutionHandler()));


}

void Window::numberOfEvolutionGenerationsChanged()
{
    numberOfEvolutionGenerationsInt_ = numberOfEvolutionGenerationsSpinBox_.value();
}

void Window::numberOfVisualizedChromosomeChanged()
{
    if( evolutionController_.currentGeneration_.size())
    {
        numberOfVisualizedChromosome_ = numberOfVisualizedChromosomeSpinBox_.value()-1;
        model_.deleteCar();
        model_.addCarFromChromosome(evolutionController_.getChromosome(numberOfVisualizedChromosome_),
                                    EvolutionController::CAR_INITIAL_X_POSITION, EvolutionController::CAR_INITIAL_Y_POSITION);
        controller_.startSimulation(7);
    }

}

void Window::evolutionStartButtonClicked()
{
    evolutionStartButton_.setDisabled(true);
    // Run evolution in separate thread from GUI
    evolutionFuture = QtConcurrent::run(this, &Window::doEvolution);
    evolutionWatcher.setFuture(evolutionFuture);
}

void Window::finishedEvolutionHandler()
{
    evolutionStartButton_.setDisabled(false);
}

void Window::doEvolution(){
    //TODO: add checking evolutionInputGenerationType and reading from file
    evolutionController_.evolution(numberOfEvolutionGenerationsInt_);
    // Evaluate so, the user can view cars in sorted order
    evolutionController_.evaluateCurrentGeneration();
}

void Window::randomGenerationButtonClicked()
{
    evolutionController_.initializeRandomFirstGeneration();
}

void Window::fromFileButtonButtonClicked()
{

}

