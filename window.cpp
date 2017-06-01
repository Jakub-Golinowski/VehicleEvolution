#include "window.h"
#include "evolutioncontroller.h"

#include <QtWidgets>

const int IdRole = Qt::UserRole;

Window::Window(): view_(&model_), controller_(&model_, &view_)
{
    std::string chromosomeString = "-4.413066 9.602226 4.642906 -6.671811 6.875719 0.210768 2.377907 5.476480 3.196440 2.563803 9.849648 3.031129 4.178925 -4.816052 -3.388288 -6.950301 5.794323 3 0.915325 7";
    Chromosome chromosome(chromosomeString);


    model_.addTrack();
    model_.addCarFromChromosome(chromosome, EvolutionController::CAR_INITIAL_X_POSITION, EvolutionController::CAR_INITIAL_Y_POSITION);
    view_.setGeometry(0,0,800,600);
    controller_.startSimulation(5);


    evolutionInputGenerationTypeComboBox_.addItem(tr("Losowe"), evolutionInputGenerationTypeEnum::Random);
    evolutionInputGenerationTypeComboBox_.addItem(tr("Plik"), evolutionInputGenerationTypeEnum::FromFile);

    evolutionInputGenerationTypeLabel_.setText("Źródło nowej generacji:");
    evolutionInputGenerationTypeLabel_.setBuddy(&evolutionInputGenerationTypeComboBox_);

    numberOfEvolutionGenerationsSpinBox_.setRange(1, 20);

    numberOfEvolutionGenerationsLabel_.setText("Numer generacji:");
    numberOfEvolutionGenerationsLabel_.setBuddy(&numberOfEvolutionGenerationsSpinBox_);

    evolutionStartButton_.setText("Start ewolucji");

    connect(&evolutionInputGenerationTypeComboBox_, SIGNAL(activated(int)),
            this, SLOT(evolutionInputGenerationTypeChanged()));
    connect(&numberOfEvolutionGenerationsSpinBox_, SIGNAL(valueChanged(int)),
            this, SLOT(numberOfEvolutionGenerationsChanged()));
    connect(&evolutionStartButton_, SIGNAL(clicked(bool)), this, SLOT(evolutionStartButtonClicked()));

    mainLayout_.setColumnStretch(0, 1);
    mainLayout_.setColumnStretch(3, 1);
    mainLayout_.addWidget(&view_, 0, 0, 1, 4, Qt::AlignCenter);
    mainLayout_.addWidget(&evolutionInputGenerationTypeLabel_, 1, 0, Qt::AlignLeft);
    mainLayout_.addWidget(&evolutionInputGenerationTypeComboBox_, 1, 1, Qt::AlignLeft);
    mainLayout_.addWidget(&numberOfEvolutionGenerationsLabel_, 2, 0, Qt::AlignLeft);
    mainLayout_.addWidget(&numberOfEvolutionGenerationsSpinBox_, 2, 1, Qt::AlignLeft);
    mainLayout_.addWidget(&evolutionStartButton_, 3,0, Qt::AlignCenter);
    setLayout(&mainLayout_);

    evolutionInputGenerationTypeChanged();
    numberOfEvolutionGenerationsChanged();

    setWindowTitle("Ewolucja pojazdów");
}

void Window::evolutionInputGenerationTypeChanged()
{
   evolutionInputGenerationType= evolutionInputGenerationTypeEnum(evolutionInputGenerationTypeComboBox_.currentIndex());
}

void Window::numberOfEvolutionGenerationsChanged()
{
    numberOfEvolutionGenerationsInt_ = numberOfEvolutionGenerationsSpinBox_.value();
}

void Window::evolutionStartButtonClicked()
{
    //TODO: add checking evolutionInputGenerationType and reading from file
    evolutionController_.evolution(numberOfEvolutionGenerationsInt_);
}

void Window::VisualiseChromosomeInWindow(Chromosome chomosome)
{
/*    drawer_ = new QB2Draw(QRect(0,0,800,600));
    drawer_.SetFlags(0x0001);
    model_ = new Model(0.0f,-10.f, drawer);
    model_.addTrack();
    model_.addCarFromChromosome(chromosome, CAR_INITIAL_X_POSITION, CAR_INITIAL_Y_POSITION);
    view_ = new View(model, drawer);
    view_.setGeometry(0,0,800,600);
    view_.a ;
    controller_ = new Controller(model, view);
    controller_.startSimulation(5);*/
}

