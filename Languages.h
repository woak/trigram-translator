#include <iostream>
using namespace std;
#include <fstream>
#include "TrigramVector.h"

class Languages
{
  public:
    Languages();

    int get_documents_length();

    void expand_documents();
    double calculate_cosine(int i, int j);
    int find_unknown_document();
    void calculate_all_cosines();

    TrigramVector *documents;

  private:
    int documents_length;
};
