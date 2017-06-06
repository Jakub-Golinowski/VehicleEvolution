/*!
 * @file view.h
 * @author J.Golinowski, P. Sykulski
 * @date June 2017
 * @brief Header file for View class
 */

#ifndef VIEW_H
#define VIEW_H

#include <QWidget> 
#include <QFrame>
#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>
#include "model.h"
#include "spawn.h"

/*! The View class is used as a canvas to paint cars and tarack. The view is aware of model from which it takes date needed to draw car and track.
 * \brief The View class is used as a canvas to paint cars and tarack.
 */

class View : public QWidget
{
    Q_OBJECT
public:
    /*! View constructor. It initializes the model_ with given pointer to model.
    * \brief View constructor.
    * \param model
    */
    View(Model * model);
    /*!
     * \brief Sets the minimum size of the canvas hint.
     * \return suggested minimum size of the canvas.
     */
    QSize minimumSizeHint() const override;
    /*!
     * \brief Sets the size of the canvas hint.
     * \return suggested size of the canvas.
     */
    QSize sizeHint() const override;

protected:
    /*! Paints the most up-to-date state of the model_. It is responsible for proper scaling of the model data and centering the view on the car.
     * \brief Paints the most up-to-date state of the model_.
     * \param event unused. Warning silenced by Q_UNUSED(event);
     */
    void paintEvent(QPaintEvent *event);

private:
    Model * model_;

    static const float32 DRAWING_SCALE;
    static const int PEN_WIDTH;
    static const float32 ORIGINAL_PIXEL_SIZE;
    static const float DISTANCE_STRING_PROPER_PLACEMENT_COEFFICIENT;
};

#endif // VIEW_H
