#include "chromosome.h"

const std::string Chromosome::CHROMOSOME_STRING_SEPARATOR = " ";
const float Chromosome::VERTEX_PROXIMITI_LIMIT = 0.5;
 Chromosome::Chromosome(std::string chromosomeString) : chromosomeString_(chromosomeString){

    chromosomeTokens_ = TokenizeChromosomeString(chromosomeString);

    int i = 0;
    //TODO przetestować (szczególnie warunki brzegowe na i). Poprawić motyw z kołem -> wywaliż angular velocity i ustawiać to w stawie.
    for(i = 0; i < 2*NUMBER_OF_VERTICES ; ++i){
        float x = std::stof(chromosomeTokens_[i]);
        float y = std::stof(chromosomeTokens_[(i+1)]);
        vertices_[i/2] = b2Vec2(x,y);
        ++i;
    };
    int wheelsArrayIndex = 0;
    for(i; i < NUMBER_OF_TOKENS; ++i){
        float wheelRadius = std::stof(chromosomeTokens_[i]);
        int vertexIndex = std::stoi(chromosomeTokens_[i+1]);
        wheels_[wheelsArrayIndex] = Wheel(vertices_[vertexIndex], wheelRadius, vertexIndex);
        ++i;
        ++wheelsArrayIndex;
    };
}

Chromosome::TokenizedChromosomeString_t Chromosome::TokenizeChromosomeString(std::string chromosomeString){
    //TODO add tests
    TokenizedChromosomeString_t tokenizedChromosomeString;
    boost::char_separator<char> sep(" ");
    boost::tokenizer<boost::char_separator<char>> tokens(chromosomeString, sep);
    int i = 0;
    for (const auto& t : tokens) {
            tokenizedChromosomeString[i] = t;
            ++i;
        }
    return tokenizedChromosomeString;
}

Chromosome::VerticesArray_t Chromosome::GetVerticesArray(){
    return vertices_;
}

Chromosome::VerticesPair_t Chromosome::GetVerticesPairByIndex(int32 index){
    //TODO chronić zakres na index (0 do 7) czyli od 0 do NUMBER_OF_VERTICES - 1

    Chromosome::VerticesPair_t verticesPair;
    verticesPair[0] = vertices_[index];
    verticesPair[1] = vertices_[(index+1) % Chromosome::NUMBER_OF_VERTICES];

    return verticesPair;
}

Chromosome::TriangleVertices_t Chromosome::CreateTriangleByIndexAndThridVertex(int32 index, b2Vec2 thirdVertex)
{
    Chromosome::TriangleVertices_t triangleVertices;
    Chromosome::VerticesPair_t verticesPair = GetVerticesPairByIndex(index);
    triangleVertices[0] = verticesPair[0] + thirdVertex; //third Vertex is the new center of cordinate system
    triangleVertices[1] = verticesPair[1] + thirdVertex; //third Vertex is the new center of cordinate system
    triangleVertices[2] = thirdVertex;

    return triangleVertices;
}

bool Chromosome::MoveAwayIfTooClose(b2Vec2& vertex1, b2Vec2& vertex2){
    //TODO napisać testy
    bool MovedAway = false;
    if(abs(vertex1.x - vertex2.x) < Chromosome::VERTEX_PROXIMITI_LIMIT){
        MovedAway = true;
        if(vertex1.x > vertex2.x)
            vertex1.x = Chromosome::VERTEX_PROXIMITI_LIMIT + vertex2.x;
        else
            vertex2.x = Chromosome::VERTEX_PROXIMITI_LIMIT + vertex1.x;
    }
    if(abs(vertex1.y - vertex2.y) < Chromosome::VERTEX_PROXIMITI_LIMIT){
        MovedAway = true;
        if(vertex1.y > vertex2.y)
            vertex1.y = Chromosome::VERTEX_PROXIMITI_LIMIT + vertex2.y;
        else
            vertex2.y = Chromosome::VERTEX_PROXIMITI_LIMIT + vertex1.y;
    }

    return MovedAway;

}

Chromosome::WheelsArray_t Chromosome::getWheels(){
    return wheels_;
}
