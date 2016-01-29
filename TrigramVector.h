#include <fstream>
#include <iostream>
using namespace std;


struct TrigramFrequency
{
  int count;
  string trigram;
  double trigram_frequency;
};


class TrigramVector
{
  public:
    TrigramVector();

    TrigramFrequency *trigram_data;

    void set_language_and_filename(string new_language, string new_filename);
    void set_cosine(double cos);
    int get_file_length();
    int get_vector_length();
    string get_filename();
    string get_language();
    int get_total_trigrams();
    double get_cosine();

    void calculate_trigram_frequency();
    void expand_frequency_array();
    void run_trigrams();
    void run_separate_trigrams();

  private:
    string language;
    string filename;
    string file_characters;
    int file_length;
    int vector_length;
    int total_trigrams;
    double cosine;

    void to_lowercase();
    void open_new_file();
    void seperate_trigrams();
    bool if_already_seen(int used, string new_trigram);
    void print_freq();

};
