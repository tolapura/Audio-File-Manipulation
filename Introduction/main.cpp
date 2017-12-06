#include <iostream>
#include <cmath>
#include "AudioFile.h"  //numChannels = 1, sampleRate = 44100, bitDepth = 16, audioLength *varies

using namespace std;

void writeAudioFile(int freq) {
    AudioFile<float> audioFile;
    audioFile.setSampleRate (44100);
    audioFile.setBitDepth (16);
    audioFile.setAudioBufferSize (1, 44100 * 10);
    for (int i = 0; i < audioFile.getNumSamplesPerChannel(); i++) {
        float sample = sinf ((float)(2.0 * M_PI * ((float)i/44100) * freq));
        for (int k = 0; k < audioFile.getNumChannels(); k++)
            audioFile.samples[k][i] = sample * 0.5f;
    }
    string fileName = "sine-" + to_string(freq) + ".wav";
    audioFile.save(fileName);
    cout << "Pure tone generated and saved to \"" << fileName << '\"';
}

void writeTwelveTone(int freq) {
    AudioFile<float> audioFile;
    audioFile.setSampleRate (44100);
    audioFile.setBitDepth (16);
    audioFile.setAudioBufferSize(1, 44100 * 25);
    float a =  1.059463;
    for (int i = 0; i < audioFile.getNumSamplesPerChannel(); i++) {
        double div = i / 44100.0;
        bool isDecimal = (div * 44100 - floor(div) * 44100) != 0;
        bool isEven = ((int)div % 2 == 0);
        if (!isDecimal || isEven) {
            float sample = sinf((float)(2.0 * M_PI * div * freq * pow(a, (int)div/2)));
            for (int k = 0; k < audioFile.getNumChannels(); k++) {
                audioFile.samples[k][i] = sample * 0.5f;
            }
        }
    }
    string fileName = "12-TET-" + to_string(freq) + ".wav";
    audioFile.save(fileName);
    cout << "Tuning sequence saved to \"" << fileName << '\"';
}

void writeJustIntonation(int freq) {
    AudioFile<float> audioFile;
    audioFile.setSampleRate (44100);
    audioFile.setBitDepth (16);
    audioFile.setAudioBufferSize(1, 44100 * 15);
    float foo[8] = {1.00, 1.125, 1.25, 1.33, 1.50, 1.67, 1.88, 2.00};
    for (int i = 0; i < audioFile.getNumSamplesPerChannel(); i++) {
        double div = i / 44100.0;
        bool isDecimal = (div * 44100 - floor(div) * 44100) != 0;
        bool isEven = ((int)div % 2 == 0);
        if (!isDecimal || isEven) {
            float sample = sinf((float) (2.0 * M_PI * div * freq * foo[(int)div/2]));
            for (int k = 0; k < audioFile.getNumChannels(); k++)
                audioFile.samples[k][i] = sample * 0.5f;
        }
    }
    string fileName = "just-intonation-" + to_string(freq) + ".wav";
    audioFile.save(fileName);
    cout << "Tuning sequence saved to \"" << fileName << '\"';
}

int main() {
    int i;
    cout << "1. Generate a Pure Tone\n2. Generate Tuning Sequence\n";
    do {
        cout << "Choose a feature: ";
        cin >> i;
    } while (i > 2 || i < 1);
    if (i == 1) {
        int freq;
        cout << "Frequency of the pure tone in Hertz: ";
        cin >> freq;
        while (!cin || freq < 1) {
            cout << "Frequency of the pure tone in Hertz: ";
            cin >> freq;
        }
        writeAudioFile(freq);
    } else {
        cout << "1. Just Intonation\n2. 12-Tone Equal Temperament\n";
        do {
            cout << "Choose a Tuning System: ";
            cin >> i;
        } while (i > 2 || i < 1);
        int freq;
        if (i == 1) {
            do {
                cout << "Frequency of “Do” in Hertz: ";
                cin >> freq;
            } while (freq < 20);
            writeJustIntonation(freq);
        } else {
            do {
                cout << "Frequency of Unison in Hertz: ";
                cin >> freq;
            } while (freq < 20);
            writeTwelveTone(freq);
        }
    }
    cout << endl << "Press Enter to exit..." << endl;
    char in;
    do {
        cin.clear();
        cin.ignore();
        cin >> in;
    } while (cin.get() == '\n');
    return 0;
}

