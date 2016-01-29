#include "TrigramVector.h"


// TrigramVector constructor
// takes in nothing
// returns nothing
TrigramVector::TrigramVector()
{
        language = "";
        filename = "";
        file_characters = "";
        file_length = 0;
        total_trigrams = 0;
        vector_length = 10;
        cosine = 0.0;
        trigram_data = new TrigramFrequency[vector_length];
        // once we know how long the file is we can initilize yo
        for (int i = 0; i < vector_length; i++) {
                trigram_data[i].count = 0;
                trigram_data[i].trigram = "";
                trigram_data[i].trigram_frequency = 0.0;
        }
}

// expand_frequency_array doubles the size of the frequency
// array
// takes in nothing
// returns nothing but allocates more space for frequency
void TrigramVector::expand_frequency_array()
{
        // expand
        TrigramFrequency *bigger_array =
        new TrigramFrequency[vector_length * 2];
        // copy elements
        for (int i = 0; i < vector_length; i++) {
                bigger_array[i] = trigram_data[i];
        }
        // delete original allocation
        delete[] trigram_data;
        // point the array to the bigger array
        trigram_data = bigger_array;
        // initilize new counts and frequencies
        for (int i = vector_length; i < vector_length*2; i++) {
                trigram_data[i].count = 0;
                trigram_data[i].trigram_frequency = 0.0;
        }
        // update capacity
        vector_length = vector_length * 2;
}

// set_language_and_filename sets the language and
// filename variables
// takes in nothing
// returns nothing
void TrigramVector::set_language_and_filename(string new_language,
                                              string new_filename)
{
        language = new_language;
        filename = new_filename;
}

// get_vector_length gets the vector_Length variable
// takes nothing
// returns an int that's the vector_legnth
int TrigramVector::get_vector_length()
{
        return vector_length;
}

// get_file_length gets the file_length variable
// takes nothing
// returns the file_length int variable
int TrigramVector::get_file_length()
{
        return file_length;
}

// get_filename gets the filename variable
// takes nothing
// returns the filename variable (string)
string TrigramVector::get_filename()
{
        return filename;
}

// get_language gets the language variable
// takes nothing
// returns the language variable: a string
string TrigramVector::get_language()
{
        return language;
}

// get_total_trigrams gets the total_trigrams var
// takes nothing
// returns nothing
int TrigramVector::get_total_trigrams()
{
        return total_trigrams;
}

// set_cosine sets the cosine var
// takes the cosine as a double
// returns nothing
void TrigramVector::set_cosine(double cos)
{
        cosine = cos;
}

// get_cosine gets the cosine var
// takes nothing
// returns the cosine var: a double
double TrigramVector::get_cosine()
{
        return cosine;
}

// open_new_file opens the file, replaces non alphabetic
// characters with spaces, and minimizes multispaces
// to a single space
// takes in nothing
// returns nothing but changes file_characters and file_length
void TrigramVector::open_new_file()
{
        ifstream finput;
        char c;

        finput.open(filename.c_str());


        while (finput.get(c)) {
                if (isalpha(c) == false) {
                        c = ' ';
                }
                if (!(c == ' ' and file_characters[file_length-1] == ' ')) {
                        file_characters += c;
                        file_length++;
                }
        }

        finput.close();
}


// to_lowercase turns all the characters in a file to lowercase
// takes in the filename
// returns nothing
void TrigramVector::to_lowercase()
{
        for (int i = 0; i < file_length; i++) {
                file_characters[i] = tolower(file_characters[i]);
        }
}

// seperate_trigrams splits the file_characters string
// into trigrams and stores the frequency of those trigrams
// in an array
// takes in nothing
// returns nothing but changes the frequency array
void TrigramVector::seperate_trigrams()
{

        // read until length-2 bc the last trigram starts
        // at legnth-2
        for (int i = total_trigrams; i < file_length-2; i++) {
                if (i == vector_length) {
                        expand_frequency_array();
                }
                string new_trigram = "";
                new_trigram += file_characters[i];
                new_trigram += file_characters[i+1];
                new_trigram += file_characters[i+2];
                if (if_already_seen(i, new_trigram) == false) {
                        trigram_data[i].trigram = new_trigram;
                        trigram_data[i].count++;
                }
                // if the trigram already exists find first iteration
                // and increase frequency
                else {
                        for (int j = 0; j < i-1; j++) {
                                if (trigram_data[j].trigram == new_trigram) {
                                        trigram_data[j].count++;
                                }
                        }
                }
                total_trigrams++;
        }
}

// if_already_seen checks to see whether the trigram
// has already been read in from the file
// takes in and int: the position in file string
// returns true if found, false if not
bool TrigramVector::if_already_seen(int i, string new_trigram)
{
        for (int j = 1; j < i-1; j++) {
        string trigram_seen = "";
        trigram_seen += file_characters[j];
        trigram_seen += file_characters[j+1];
        trigram_seen += file_characters[j+2];
                if (trigram_seen == new_trigram) {
                        return true;
                }
        }
        return false;
}

// run_trigrams runs the functions necessary for finding
// the frequency of trigrams in a file
// takes in nothing
// returns nothing but changes the structs
void TrigramVector::run_trigrams()
{
        calculate_trigram_frequency();
        //print_freq();
}

// run_seperate_trigrams seperates the trigrams from the characters take in
// takes nothing
// returns nothing
void TrigramVector::run_separate_trigrams()
{
        open_new_file();
        to_lowercase();
        seperate_trigrams();
}

// calculate_trigram_frequency finds the trigram frequency
// for each trigram as compared to all the trigrams in the file
// takes nothing
// returns nothing but changes trigram_frequency var
void TrigramVector::calculate_trigram_frequency()
{
        for (int i = 0; i < file_length; i++) {
                trigram_data[i].trigram_frequency =
                trigram_data[i].count / (double) total_trigrams;
        }
}

// print_freq prints out trigrams with their frequencies
// takes nothing
// returns nothing but prints to screen
// NOTE checks to see whether trigramvector is empty before couting
void TrigramVector::print_freq()
{
        if (language != "") {
                cout << "Frequency for " << language << endl;
        }
        // ends file_length-2 bc the last trigram starts two from the end
        for (int j = 0; j < file_length-2; j++) {
                if (trigram_data[j].trigram != "") {
                        cout << trigram_data[j].trigram_frequency << " " <<
                        trigram_data[j].trigram << endl;
                }
        }
        if (total_trigrams > 0) {
                cout << "Total trigrams " << total_trigrams << endl;
        }
}
