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
    void VisualiseChromosomeInWindow(Chromosome chomosome);
    void StartEvolution(unsigned long numberOfGenerations);

    enum evolutionInputGenerationTypeEnum{ Random = 0, FromFile = 1 };

    evolutionInputGenerationTypeEnum  evolutionInputGenerationType;
    unsigned long numberOfEvolutionGenerationsInt_;

signals:

private slots:
    void evolutionInputGenerationTypeChanged();
    void numberOfEvolutionGenerationsChanged();
    void evolutionStartButtonClicked();

private:

    EvolutionController evolutionController_{};

    Model model_;
    View view_;
    Controller controller_;

    QGridLayout mainLayout_;
    QPushButton evolutionStartButton_;

    QLabel evolutionInputGenerationTypeLabel_;
    QLabel numberOfEvolutionGenerationsLabel_;

    QComboBox evolutionInputGenerationTypeComboBox_;
    QSpinBox numberOfEvolutionGenerationsSpinBox_;

};

#endif // WINDOW_H
