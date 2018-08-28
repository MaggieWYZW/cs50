// Helper functions for music

#include <cs50.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // extract nemerator and denominator from the fraction string
    // assume each is a charactor seperated by a slash
    double numerator = atof(&fraction[0]);
    double denominator = atof(&fraction[2]);
    double dur = numerator/denominator;
    return (int) round(dur / (1.0 / 8));
}

int count_steps(string note)
{
    int steps;
    // Notes in an octave
    const string NOTES[] = {"C", "C#", "D", "D#", "E",
                            "F", "F#", "G", "G#", "A", "A#", "B"
                            };

    for(int i = 0, n=sizeof(NOTES) / sizeof(NOTES[0]); i < n; i++)
    {
        if (strcmp(NOTES[i], note) == 0)
        {
            steps = i - 9;
        }
    }
    //printf("steps are %i\n", steps);
    return steps;
}

// Calculates frequency (in Hz) of a note
int frequency(string fullnote)
{
    int freq = 0;

    // full notes
    if (strlen(fullnote) == 2)
    {
        //printf("%s!!!", fullnote);
        char note[1];
        sprintf(note, "%c", fullnote[0]);
        double octave = atof(&fullnote[1]);

        double step = (double) count_steps(note);
        double base_freq = 440 * pow(2, (octave - 4));
        freq = (int) round(base_freq * pow(2, step / 12));
    }
    // notes with sharp/flat
    else if (strlen(fullnote) == 3)
    {
        char note[2];
        char tmp = fullnote[0];
        double octave = atof(&fullnote[2]);
        if (fullnote[1] == 'b')
        {
            switch (tmp)
            {
                case 'D':sprintf(note, "%c%c", 'C','#'); break;
                case 'E': sprintf(note, "%c%c", 'D','#'); break;
                case 'F': sprintf(note, "%c", 'E'); break;
                case 'G': sprintf(note, "%c%c", 'F','#'); break;
                case 'A': sprintf(note, "%c%c", 'G','#'); break;
                case 'B': sprintf(note, "%c%c", 'A','#'); break;
                case 'C': sprintf(note, "%c", 'B'); octave--; break;
            }
        }
        else
        {
            sprintf(note, "%c%c", fullnote[0], fullnote[1]);
        }

        double step = (double) count_steps(note);
        double base_freq = 440 * pow(2, (octave - 4));
        freq = (int) round(base_freq * pow(2, step / 12));
    }

    return freq;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    //
    if (!strcmp(s, ""))
    {
        //printf("It is a rest!");
        return 1;
    }
    else
    {
        return 0;
    }

}
