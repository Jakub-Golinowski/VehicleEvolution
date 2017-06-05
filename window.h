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

/*! The Window class is a main application window. It is responsible for collecting user input and managing evolution and its visualisation.
 * \brief The Window class is a main application window.
 */

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window();

signals:

private slots:
    /*! Handles request for random generation creation. Randomly creates first generation and signals it to user by displaying generation number. Displays first car from new generation.
     * \brief Handles request for random generation creation.
     */
    void randomGenerationButtonClicked();
    /*! Handles request for changing number of evolutions generations. Sets the field that holds the number of generations to new value.
     * \brief Handles request for changing number of evolutions generations.
     */
    void numberOfEvolutionGenerationsChanged();
    /*! Handles request for changing currently visualized chromosome. Deletes old car and creates new one. Starts new simulation.
     * \brief Handles request for changing currently visualized chromosome.
     */
    void numberOfVisualizedChromosomeChanged();
    /*! Starts the process of evolution in separate thread. Current generation is taken as an input generation. The evolution will be done as many times as stated by user.
     * \brief Starts the process of evolution in separate thread.
     */
    void evolutionStartButtonClicked();
    /*! Executes when separate thread finishes evolution. Enables buttons. Displays number of current generation and visualizes (by default the best) car from current generation.
     * \brief Executes when separate thread finishes evolution.
     */
    void finishedEvolutionHandler();

private:
    /*! Execute evolution algorithm on current generation. This is a wrapper on evolution controller class method to perform evolution that calls it with the current generation as input argument.
     * \brief Execute evolution algorithm on current generation.
     */
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
