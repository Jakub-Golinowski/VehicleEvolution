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
#include <QtConcurrent/QtConcurrent>
#include "evolutioncontroller.h"

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window();

signals:

private slots:
    void randomGenerationButtonClicked();
    void numberOfEvolutionGenerationsChanged();
    void numberOfVisualizedChromosomeChanged();
    void evolutionStartButtonClicked();
    void finishedEvolutionHandler();

private:

    void StartEvolution(unsigned long numberOfGenerations);
    void doEvolution();

    unsigned int numberOfEvolutionGenerationsInt_ = 5;
    unsigned int numberOfVisualizedChromosome_ = 0;
    unsigned int currentGenerationNumber_ = 1;

    EvolutionController evolutionController_;

    Model model_;
    View view_;
    Controller controller_;

    QGridLayout mainLayout_;
    QPushButton evolutionStartButton_;

    QPushButton randomGenerationButton;
    QLabel numberOfEvolutionGenerationsLabel_;
    QLabel numberOfVisualizedChromosomeLabel_;
    QLabel numberOfVisualizedGenerationLabel_;

    QComboBox evolutionInputGenerationTypeComboBox_;
    QSpinBox numberOfEvolutionGenerationsSpinBox_;
    QSpinBox numberOfVisualizedChromosomeSpinBox_;

    QFuture<void> evolutionFuture;
    QFutureWatcher<void> evolutionWatcher;

};

#endif // WINDOW_H
