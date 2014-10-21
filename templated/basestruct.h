#ifndef BSTRUCT_H
#define BSTRUCT_H




/**
 * \class List
 *
 * @brief The Graph class
 */
class Bstruct
{
  private:

    std::forward_list<int>* data;
    int nVertices, x, y, mEdges, maximumDegree;
    float degreeSum;
    int* vertDegree;
    int* degrees;
  public:
    /**
     * @brief Graph Default constructor
     */
    Bstruct(){}

    virtual void pushString(std::string* line) = 0;

    virtual int maxDegree() = 0;

    virtual void empiricalDistribution(std::string* target) = 0;

    virtual float meanDegree() = 0;

    ~Bstruct(){}

protected:



};

#endif // BSTRUCT_H
