/*!
 * @file controller.h
 * @author J.Golinowski, P. Sykulski
 * @date June 2017
 * @brief Header file for Controller class
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QTimer>
#include "model.h"
#include "view.h"

/*!
 * \brief The Controller class is used to control the proces of box2D simulation that is being visualized.
 */

class Controller : public QObject
{
    Q_OBJECT
public:
    /*! Controller constructor that initilizes model_ and view_ fields with given pointers.
     * \brief Controller constructor.
     * \param model pointer to model object.
     * \param view pointer to a view object.
     */
    Controller(Model * model, View * view);

    /*! Starts the simulation of a single car by initilizing a timer and assigning a SLOT for its timeout.
     * \brief startSimulation starts single car visual simulation.
     * \param interval simulation intercal in milliseconds.
     */
    void startSimulation(unsigned long interval);

private:
    Model  * model_;
    View  * view_;
    QTimer timer_;

public slots:
    /*! Slot called when simulation timer times out.
     * \brief Executes box2D simulation step and draws the result.
     */
    void simulateAndDraw();
};

#endif // CONTROLLER_H
