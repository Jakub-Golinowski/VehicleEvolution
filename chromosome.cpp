#include "chromosome.h"

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
        wheels_[wheelsArrayIndex] = Wheel(vertices_[vertexIndex],wheelRadius, 10);
        ++i;
        ++wheelsArrayIndex;
    };
}

Chromosome::TokenizedChromosomeString_Type Chromosome::TokenizeChromosomeString(std::string chromosomeString){
    //TODO add implementation
    TokenizedChromosomeString_Type ret = {"0.1", "0.2", "0.3", "0.4", "0.5", "0.6", "0.7", "0.8", "0.9", "0.10", "0.11", "0.12", "0.13", "0.14", "0.15", "0.16", "0.17", "1", "0.19", "2"};
    return ret;
}

