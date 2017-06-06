/*!
 * @file chromosome.h
 * @author J.Golinowski, P. Sykulski
 * @date June 2017
 * @brief Header file for Chromosome class
 */

#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <array>
#include <string>
#include <Box2D/Box2D.h>
#include <boost/tokenizer.hpp>
#include "wheel.h"

/*!
 * Chromosome class is used to represent a chromosome in the contex of vehicle evolution algorithm.
 * One chromosome is a set of parameters that unequivocally identify a single two-dimensional car.
 * In that sense a two-dimensional car can be created solely with the use of the cromosome's parameters.\n\n
 *
 * There are following assumtions imposed on a two-dimensional car being subject of evolution process:\n
 * 1. The car body is an 8-vertex polygon. (that can be covex or concave)\n
 * 2. Each car has got 2 wheels. \n
 * 3. Each wheel is attached with its central point to one of car body vertices. \n\n
 *
 * The Chromosome cosists of 20 parameters in the following order:\n
 * x_1 y_1 x_2 y_2 x_3 y_3 x_4 y_4 x_5 y_5 x_6 y_6 x_7 y_7 x_8 y_8 r_1 v_1 r_2 v_2\n
 * where:\n
 * x_n is a x coordinate of n-th vertex (float)\n
 * y_n is a y coordinate of n-th vertex (flaot)\n
 * r_m is a radius of the m-th wheel (float)\n
 * v_m is an index number of the vertex to which m-th circle is attached (integer)\n
 *
 */

class Chromosome
{
public:
    /*! Constructor which initilizes Chromosome class fields from a string containing all 20 paramteres.
     * \brief Deserilizes input chromosome string.
     * \param chromosomeString: it contains all parameters seperated with spaces. For example: "-4.413066 9.602226 4.642906 -6.671811 6.875719 0.210768 2.377907 5.476480 3.196440 2.563803 9.849648 3.031129 4.178925 -4.816052 -3.388288 -6.950301 5.794323 3 0.915325 7";..
     */
    Chromosome(std::string chromosomeString);

    static const int32 NUMBER_OF_WHEELS = 2;
    static const int32 NUMBER_OF_VERTICES = 8;
    static const int32 NUMBER_OF_TOKENS = 2*NUMBER_OF_VERTICES + 2*NUMBER_OF_WHEELS; /*!< Each vertice and each wheel are described by 2 tokens. */

    typedef std::array<std::string, NUMBER_OF_TOKENS> TokenizedChromosomeString_t;
    typedef std::array<b2Vec2, NUMBER_OF_VERTICES> VerticesArray_t;
    typedef std::array<b2Vec2, 2> VerticesPair_t;
    typedef std::array<Wheel, NUMBER_OF_WHEELS> WheelsArray_t;
    typedef std::array<b2Vec2, 3> TriangleVertices_t;

    static const std::string CHROMOSOME_STRING_SEPARATOR;

    /*! Method that returns std::array of vertices representing car body polygon
     * \brief Getter for vertices_.
     * \return array of vertices representing car body polygon.
     */
    VerticesArray_t GetVerticesArray();

    /*! Method creating a TriangleVertices_t from a vertex (indicated by index param) and vertex next to it in vertices_. Third vertex provided by the user. This method is provided for convenient creation of car body triangles in Box2D.
     * \brief Used to create triangles in car body creation.
     * \param int32 index: index of the vertex in vertices_.index
     * \param thirdVertex: vertex provided by user which is a last vertex of a triangle.
     * \return
     */
    TriangleVertices_t CreateTriangleByIndexAndThridVertex(int32 index, b2Vec2 thirdVertex);

    /*!
     * \brief Getter for wheels_
     * \return WheelsArray_t: array of wheels
     */
    WheelsArray_t getWheels();
    TokenizedChromosomeString_t chromosomeTokens_;

#ifndef UNIT_TEST
    private:
#endif
    /*! Forms a pair of vertices from the vertex indicated by index and the vertex indicated by index+1 in vertices_ field.
     * \brief Creates a pair of vertex(index) and vertex(index+1)
     * \param index
     * \return pair of vertices
     */
    VerticesPair_t GetVerticesPairByIndex(int32 index);

    /*! Method that creates tokens from a space separated string describing chromosome parameters. Decimal delimiter is assumed to be a dot (.)
     * \brief Creates tokens to fill in chromosome paramteres fields.
     * \param chromosomeString: contains all parameters seperated with spaces. For example: "-4.413066 9.602226 4.642906 -6.671811 6.875719 0.210768 2.377907 5.476480 3.196440 2.563803 9.849648 3.031129 4.178925 -4.816052 -3.388288 -6.950301 5.794323 3 0.915325 7";.
     * \return it contains std::string fields, each is a string representation of one chromosome parameter.
     */
    TokenizedChromosomeString_t TokenizeChromosomeString(std::string chromosomeString);

    WheelsArray_t wheels_;
    VerticesArray_t vertices_;
    std::string chromosomeString_;
};

#endif // CHROMOSOME_H
