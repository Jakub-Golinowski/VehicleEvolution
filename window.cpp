/*!
 * @file window.cpp
 * @author J.Golinowski, P. Sykulski
 * @date June 2017
 * @brief Window class implementation
 */

#include "window.h"
#include "evolutioncontroller.h"


Window::Window(): view_(&model_), controller_(&model_, &view_)
{
    model_.addTrack();

    numberOfEvolutionGenerationsSpinBox_.setRange(1, 50);
    numberOfEvolutionGenerationsSpinBox_.setValue(numberOfEvolutionGenerationsInt_);

    numberOfEvolutionGenerationsLabel_.setText("Liczba iteracji algorytmu:");
    numberOfEvolutionGenerationsLabel_.setBuddy(&numberOfEvolutionGenerationsSpinBox_);

    numberOfVisualizedChromosomeSpinBox_.setRange(1, EvolutionController::GENERATION_SIZE);

    numberOfVisualizedChromosomeLabel_.setText("Numer wyświetlanego chromosomu:");
    numberOfVisualizedChromosomeLabel_.setBuddy(&numberOfVisualizedChromosomeSpinBox_);

    numberOfVisualizedGenerationLabel_.setText(QString("Numer generacji: %1").arg(currentGenerationNumber_));

    randomGenerationButton.setText("Wygeneruj losową generację pojazdów");
    evolutionStartButton_.setText("Start ewolucji");
    evolutionStartButton_.setDisabled(true);

    connect(&randomGenerationButton, SIGNAL(clicked(bool)),
            this, SLOT(randomGenerationButtonClicked()));
    connect(&numberOfVisualizedChromosomeSpinBox_, SIGNAL(valueChanged(int)),
            this, SLOT(numberOfVisualizedChromosomeChanged()));
    connect(&evolutionStartButton_, SIGNAL(clicked(bool)), this, SLOT(evolutionStartButtonClicked()));

    mainLayout_.setColumnStretch(3, 1);
    mainLayout_.addWidget(&view_, 0, 0, 1, 4, Qt::AlignCenter);
    mainLayout_.addWidget(&numberOfVisualizedGenerationLabel_,1,0, Qt::AlignLeft);
    mainLayout_.addWidget(&numberOfVisualizedChromosomeLabel_, 2, 0, Qt::AlignLeft);
    mainLayout_.addWidget(&numberOfVisualizedChromosomeSpinBox_, 2, 1, Qt::AlignLeft);
    mainLayout_.addWidget(&randomGenerationButton, 3, 0, Qt::AlignLeft);
    mainLayout_.addWidget(&numberOfEvolutionGenerationsLabel_, 4, 0, Qt::AlignLeft);
    mainLayout_.addWidget(&numberOfEvolutionGenerationsSpinBox_, 4, 1, Qt::AlignLeft);
    mainLayout_.addWidget(&evolutionStartButton_, 5,0, Qt::AlignCenter);
    setLayout(&mainLayout_);

    setWindowTitle("Ewolucja pojazdów");

    connect(&evolutionWatcher, SIGNAL(finished()), this, SLOT(finishedEvolutionHandler()));

}

void Window::numberOfEvolutionGenerationsChanged()
{

}

void Window::numberOfVisualizedChromosomeChanged()
{
    if( evolutionController_.currentGeneration_.size())
    {
        numberOfVisualizedChromosome_ = EvolutionController::GENERATION_SIZE - (numberOfVisualizedChromosomeSpinBox_.value());
        model_.deleteCar();
        model_.addCarFromChromosome(evolutionController_.getChromosome(numberOfVisualizedChromosome_),
                                    EvolutionController::CAR_INITIAL_X_POSITION, EvolutionController::CAR_INITIAL_Y_POSITION);
        controller_.startSimulation(10);
    }

}

void Window::evolutionStartButtonClicked()
{
    currentGenerationNumber_ += numberOfEvolutionGenerationsSpinBox_.value();
    evolutionStartButton_.setDisabled(true);
    numberOfVisualizedChromosomeSpinBox_.setDisabled(true);
    randomGenerationButton.setDisabled(true);
    numberOfEvolutionGenerationsSpinBox_.setDisabled(true);
    // Run evolution in separate thread from GUI
    evolutionFuture = QtConcurrent::run(this, &Window::doEvolution);
    evolutionWatcher.setFuture(evolutionFuture);
}

void Window::finishedEvolutionHandler()
{
    evolutionStartButton_.setDisabled(false);
    numberOfVisualizedChromosomeSpinBox_.setDisabled(false);
    randomGenerationButton.setDisabled(false);
    numberOfEvolutionGenerationsSpinBox_.setDisabled(false);
    numberOfVisualizedGenerationLabel_.setText(QString("Numer generacji: %1").arg(currentGenerationNumber_));
    numberOfVisualizedChromosomeChanged();
}

void Window::doEvolution(){
    evolutionController_.evolution(numberOfEvolutionGenerationsInt_);
    // Evaluate so, the user can view cars in sorted order
    evolutionController_.evaluateCurrentGeneration();
}

void Window::randomGenerationButtonClicked()
{
    currentGenerationNumber_ = 1;
    numberOfVisualizedGenerationLabel_.setText(QString("Numer generacji: %1").arg(currentGenerationNumber_));
    evolutionController_.initializeRandomFirstGeneration();
    evolutionStartButton_.setDisabled(false);
    numberOfVisualizedChromosomeChanged();
}

