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
  //  controller_.startSimulation(5);


    evolutionInputGenerationTypeComboBox.addItem(tr("Losowe"), evolutionInputGenerationTypeEnum::Random);
    evolutionInputGenerationTypeComboBox.addItem(tr("Plik"), evolutionInputGenerationTypeEnum::FromFile);

    evolutionInputGenerationTypeLabel.setText("Źródło nowej generacji:");
    evolutionInputGenerationTypeLabel.setBuddy(&evolutionInputGenerationTypeComboBox);

    numberOfEvolutionGenerationsSpinBox.setRange(1, 20);

    numberOfEvolutionGenerationsLabel.setText("Numer generacji:");
    numberOfEvolutionGenerationsLabel.setBuddy(&numberOfEvolutionGenerationsSpinBox);

    evolutionStartButton.setText("Start ewolucji");

    connect(&evolutionInputGenerationTypeComboBox, SIGNAL(activated(int)),
            this, SLOT(evolutionInputGenerationTypeChanged()));
    connect(&numberOfEvolutionGenerationsSpinBox, SIGNAL(valueChanged(int)),
            this, SLOT(numberOfEvolutionGenerationsChanged()));
    connect(&evolutionStartButton, SIGNAL(clicked(bool)), this, SLOT(evolutionStartButtonClicked()));

    mainLayout.setColumnStretch(0, 1);
    mainLayout.setColumnStretch(3, 1);
    mainLayout.addWidget(&view_, 0, 0, 1, 4, Qt::AlignCenter);
    mainLayout.addWidget(&evolutionInputGenerationTypeLabel, 1, 0, Qt::AlignLeft);
    mainLayout.addWidget(&evolutionInputGenerationTypeComboBox, 1, 1, Qt::AlignLeft);
    mainLayout.addWidget(&numberOfEvolutionGenerationsLabel, 2, 0, Qt::AlignLeft);
    mainLayout.addWidget(&numberOfEvolutionGenerationsSpinBox, 2, 1, Qt::AlignLeft);
    mainLayout.addWidget(&evolutionStartButton, 3,0, Qt::AlignCenter);
    setLayout(&mainLayout);

    evolutionInputGenerationTypeChanged();
    numberOfEvolutionGenerationsChanged();

    setWindowTitle("Ewolucja pojazdów");
}

void Window::evolutionInputGenerationTypeChanged()
{
   evolutionInputGenerationType= evolutionInputGenerationTypeEnum(evolutionInputGenerationTypeComboBox.currentIndex());
}

void Window::numberOfEvolutionGenerationsChanged()
{
    numberOfEvolutionGenerationsInt = numberOfEvolutionGenerationsSpinBox.value();
}

void Window::evolutionStartButtonClicked()
{
    //TODO: add checking evolutionInputGenerationType and reading from file
    evolutionController_.evolution(numberOfEvolutionGenerationsInt);
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

