// Created by: Teddy Laurita
// Modified on: 11/14/15
// Please see readme.txt

#include <iostream>
using namespace std;
#include <fstream>
#include <iomanip>
#include "Languages.h"


// declarations
void extract_trigrams(Languages *L);
void read_original_file(Languages *L);
void print_cosines(Languages *L);
int expand_cosines(double *cosines, int cosines_length);
void fill_cosines(double *cosines, Languages *L, int cosines_length);


int main()
{
        Languages *language = new Languages;

        extract_trigrams(language);

        return 0;
}



// extract_trigrams reads in the file, and extracts the
// trigrams while in the meantime taking out extra spaces
// takes in nothing
// returns TODO for phase 1
void extract_trigrams(Languages *L)
{
        //double top = 1.0; // will be used for printing cosine similarities
        read_original_file(L);

        // calculate frequencies and print out
        for (int i = 0; i < L->get_documents_length(); i++) {
                L->documents[i].run_trigrams();
        }
        L->calculate_all_cosines();
        print_cosines(L);
}

// read_original_file opens the file inputted by the user
// and split the lines of input into arrays of classes
// NOTE if a language has already been read in, the funtion sends the filename
// to the first trigramvector it's occurred
// takes in file_entries array
// returns nothing but fills an array of TrigramVector classes
void read_original_file(Languages *L)
{
        string language, filename;
        int count_documents = 0;
        while (cin >> language >> filename) {
                bool added = false;
                if (count_documents == L->get_documents_length()) {
                        L->expand_documents();
                }
                if (count_documents == 0) {
                        L->documents[0].set_language_and_filename
                                        (language, filename);
                        L->documents[0].run_separate_trigrams();
                }
                // checks whether language has been seen so far
                for (int i = 0; i < count_documents; i++) {
                        if (language == L->documents[i].get_language()) {
                                L->documents[i]
                                .set_language_and_filename(language,
                                                           filename);
                                L->documents[i].run_separate_trigrams();
                                added = true;
                        }
                }
                if (added == false) {
                        L->documents[count_documents].
                                set_language_and_filename(language, filename);
                        L->documents[count_documents].run_separate_trigrams();
                }
                count_documents++;
        }
}

void print_cosines(Languages *L)
{
        double max = 0.0, prev_max = 0.0;
        int max_pos = 0, temp = 0;
        // higher than possible
        max = 1.1;
        for (int j = 0; j <  L->get_documents_length(); j++) {
                prev_max = max;
                max = 0.0;
                for (int i = 0; i < L->get_documents_length(); i++) {
                        if (L->documents[i].get_cosine() > max and
                            L->documents[i].get_cosine() < prev_max) {
                                max = L->documents[i].get_cosine();
                                temp = i;
                        }
                        else if (L->documents[i].get_cosine() == prev_max and
                                i != max_pos) {
                                        max = L->documents[i].get_cosine();
                                        max_pos = i;
                        }
                }
                if (max != 0.0) {
                        cout << setw(18);
                        cout << L->documents[temp].get_language() << ": "
                        << max << endl;
                }
                max_pos = temp;
        }
}

// fill_cosines puts the cosines into the cosines array
// takes cosines pointer and a languages
// returns nothing but changes cosines
void fill_cosines(double *cosines, Languages *L, int cosines_length)
{
        for (int i = 0; i < L->get_documents_length(); i++) {
                if (i == cosines_length) {
                        cosines_length = expand_cosines(cosines,
                                                        cosines_length);
                }
                cosines[i] = L->documents[i].get_cosine();
        }
        // set first max
        cosines[0] = L->documents[0].get_cosine();
}

// expand_cosines expands the cosines array
// takes nothing
// returns nothing
int expand_cosines(double *cosines, int cosines_length)
{
        // expand
        double *bigger_array =
        new double[cosines_length * 2];
        // copy elements
        for (int i = 0; i < cosines_length; i++) {
                bigger_array[i] = cosines[i];
        }
        // delete original allocation
        delete[] cosines;
        // point the array to the bigger array
        cosines = bigger_array;
        // update capacity
        cosines_length *= 2;
        return cosines_length;
}
