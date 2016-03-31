# trigram-translator
program that reads files and stores trigrams (sets of three characters) and compares them to documents of "unknown" language to identify the unknown language

Created by: Teddy Laurita
Created on: 11/14/15
COMP11
Project2

Translate_main.cpp
    This function takes in a file with entries in the form of: Language filename.txt, 
prints out the file name, all the trigrams (strings of three characters)
in that file, and their frequencies, and finally, prints out, for an unknown language text file,
the percent chances, that that text file is written in any of
the other languages included in the original file.

TrigramVector
   This class reads in a file with a language and a filename
contained in it. It stores the language and opens the second
filename. It then reads all the characters from that file into a
string, replacing all non-alphabetic characters with spaces
and turning consecutive spaces into a single space.
Finally it reads through that string and stores all the trigrams
in a dynamic array of structs and counts the times that simliar
strings appear, also to be housed in the struct.

                        NOTE:
the print_freq function prints out each trigram in a
trigramvector along with its frequency. The function is called in the
run_trigrams function and is commented out during my provide to make
work with the cosine similarity easier.

Languages
    This class has a dynamic array of trigramvector
classes in it. Each trigramvector reprisents one language and stores its
own trigrams and those trigrams's content, count, and frequency. Each
trigramvector also knows its own cosine similarity compared to the "Unknown"
language file.

NOTE: The language must be read in with an uppercase, as
      the string "italian" is different than "Italian"

Operating Instructions: IMPORTANT: Pipe in a file to the
program using the "<" operator. That file must have at least
one language and another filename in the style:
            Language filename.txt

TO COMPILE (all on one line):
    clang++ -Wall -Wextra -g Translate_main.cpp TrigramVector.cpp
    Languages.cpp (optional: -o program_name)
Compiling Note: User MUST have header files (".h") in the
    current directory in order to compile and run correctly.
