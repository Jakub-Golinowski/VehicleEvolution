#ifndef WINDOW_H
#define WINDOW_H

#include "view.h"
#include "controller.h"
#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QPushButton>
#include <QGridLayout>
#include "evolutioncontroller.h"

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window();
    void StartEvolution(unsigned long numberOfGenerations);

    enum evolutionInputGenerationTypeEnum{ RANDOM = 0, FROMFILE = 1 };

    evolutionInputGenerationTypeEnum  evolutionInputGenerationType;
    unsigned int numberOfEvolutionGenerationsInt_ = 5;
    unsigned int numberOfVisualizedChromosome_ = 0;

signals:

private slots:
    void randomGenerationButtonClicked();
    void fromFileButtonButtonClicked();
    void numberOfEvolutionGenerationsChanged();
    void numberOfVisualizedChromosomeChanged();
    void evolutionStartButtonClicked();

private:

    EvolutionController evolutionController_;

    Model model_;
    View view_;
    Controller controller_;

    QGridLayout mainLayout_;
    QPushButton evolutionStartButton_;

    QPushButton randomGenerationButton;
    QPushButton fromFileButton;
    QLabel numberOfEvolutionGenerationsLabel_;
    QLabel numberOfVisualizedChromosomeLabel_;

    QComboBox evolutionInputGenerationTypeComboBox_;
    QSpinBox numberOfEvolutionGenerationsSpinBox_;
    QSpinBox numberOfVisualizedChromosomeSpinBox_;

};

#endif // WINDOW_H
