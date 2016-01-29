#include "Languages.h"
#include <cmath>

// constructor sets the language vars to original values
// takes in nothing
// returns nothing
Languages::Languages()
{
        documents_length = 1;
        documents = new TrigramVector[documents_length];

}

// get_documents_length gets the documents_length var
// takes nothing
// returns documents_length
int Languages::get_documents_length()
{
        return documents_length;
}

// expand_documents expands the documents
// array when it gets full
// takes in nothing
// returns new nothing but changes documents array
void Languages::expand_documents()
{
        // expand
        TrigramVector *bigger_array =
        new TrigramVector[documents_length * 2];
        // copy elements
        for (int i = 0; i < documents_length; i++) {
                bigger_array[i] = documents[i];
        }
        // delete original allocation
        delete[] documents;
        // point the array to the bigger array
        documents = bigger_array;
        // update capacity
        documents_length *= 2;
}

// calculate_all_cosines runs calculate cosine on all the documents
// compared to the unknown document
// takes nothing
// returns nothing but prints out cosines
void Languages::calculate_all_cosines()
{
        int unknown = find_unknown_document();
        cout << documents[unknown].get_filename() << endl;
        for (int i = 0; i < documents_length; i++) {
                if (i != unknown and documents[i].get_total_trigrams() > 0) {
                        documents[i].set_cosine(calculate_cosine(i, unknown));
                }
        }
}

// calculate_cosine calculates the cosine similarity
// for two weights or frequencies
// takes document numbers to compare
// returns the cosine similarity between the two documents
double Languages::calculate_cosine(int doc, int unknown)
{
        double numer = 0.0, denom_a = 0.0, cosine = 0.0, denom_b = 0.0;
        double denominator = 0.0;
        for (int i = 0; i < documents[doc].get_vector_length(); i++) {
                for (int j = 0; j < documents[unknown].get_vector_length();
                     j++) {
                        if (documents[unknown].trigram_data[j].trigram ==
                            documents[doc].trigram_data[i].trigram) {
                                numer +=
                                (documents[unknown]
                                .trigram_data[j].trigram_frequency*
                                documents[doc].trigram_data[i].
                                trigram_frequency);
                // keeps track of two summations of denominator
                                denom_a +=
                                documents[doc].trigram_data[i].
                                trigram_frequency * documents[doc].
                                trigram_data[i].trigram_frequency;
                                denom_b +=
                                documents[unknown].trigram_data[j].
                                trigram_frequency * documents[unknown].
                                trigram_data[j].trigram_frequency;
                        }
                }
        }
        denom_a = sqrt(denom_a);
        denom_b = sqrt(denom_b);
        denominator = denom_a * denom_b;
        cosine = numer/denominator;
        return cosine;
}

// find_unknown_trigram searches through the trigramvectors for the vector
// with the unkown trigrams in it
// takes nothing
// returns the index of the unknown document else -1
int Languages::find_unknown_document()
{
        for (int i = 0; i < documents_length; i++) {
                if (documents[i].get_language() == "Unknown") {
                        return i;
                }
        }
        return -1;


}
