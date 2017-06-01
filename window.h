#ifndef WINDOW_H
#define WINDOW_H

#include "view.h"
#include "controller.h"
#include "renderarea.h"
#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QPushButton>
#include <QGridLayout>
#include "evolutioncontroller.h"


//class QCheckBox;
//class QComboBox;
//class QLabel;
//class QSpinBox;

class View;

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window();
    void VisualiseChromosomeInWindow(Chromosome chomosome);
    void StartEvolution(unsigned long numberOfGenerations);

    enum evolutionInputGenerationTypeEnum{ Random = 0, FromFile = 1 };

    evolutionInputGenerationTypeEnum  evolutionInputGenerationType;
    unsigned long numberOfEvolutionGenerationsInt;

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

    QGridLayout mainLayout;
    QPushButton evolutionStartButton;

    QLabel evolutionInputGenerationTypeLabel;
    QLabel numberOfEvolutionGenerationsLabel;

    QComboBox evolutionInputGenerationTypeComboBox;
    QSpinBox numberOfEvolutionGenerationsSpinBox;

};

#endif // WINDOW_H
