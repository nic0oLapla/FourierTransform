#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <cmath>
#include <utility>
#include <tuple>
#include <vector>
#include <complex>
#include <stdlib.h>
#include "AudioFile-1.1.0/AudioFile.h"


std::vector<float> readWav(std::string fileName) {

    AudioFile<float> wav;
    wav.load(fileName);

    int numSamples = wav.getNumSamplesPerChannel();

    std::vector<float> samples;
    for (int i = 0; i < numSamples; i++) {
        samples.push_back(wav.samples[0][i]);
    }

    return samples;

}

std::tuple< std::vector<float>, std::vector<float>, std::vector<float>, std::vector<float> > transform(const std::vector<float> & displacement, double dFrequency, int samplingFrequency) {
    
    //number of samples
    size_t numSamples = displacement.size();

    //nyquist limit
    int maxFrequency = samplingFrequency/2;
    
    //fundamental frequency
    //currently unused - practically replaced by dFrequency
    double fundFrequency = (2*M_PI)/numSamples;

    //define and populate time (input) axis
    std::vector<float> time;
    for (size_t i = 0; i < numSamples; i++) {
        time.push_back(static_cast<float>(i)/samplingFrequency);
    }
    
    //define output axes
    std::vector<float> frequency;
    std::vector<float> amplitude;
    
    for (float f = dFrequency; f < maxFrequency; f += dFrequency) {

        //reset sums
        double sumReal = 0;
        double sumImag = 0;

        for (size_t i = 0; i < numSamples; i++) {
            
            //rewrite as complex variables
            std::complex<double> complexDisplacement(displacement[i], 0);
            std::complex<double> complexArg(0, -1*f*2*M_PI*time[i]);
            
            //the actual transform
            std::complex<double> frame = complexDisplacement * std::__complex_exp(complexArg);

            //add to sum of complex vectors
            sumReal += std::real(frame);
            sumImag += std::imag(frame);
            
        }

        //magnitude of complex vectors
        float magnitude = sqrt(sumReal*sumReal + sumImag*sumImag);

        //if (magnitude >= 1) {
        //    std::cout << f << ", " << magnitude << std::endl;
        //}

        //add to output axes
        frequency.push_back(f);
        amplitude.push_back(magnitude);
  
    }

    return std::make_tuple(displacement, time, frequency, amplitude);

}

void fileOutput(const std::vector<float> & displacement, const std::vector<float> & time, const std::vector<float> & frequency, const std::vector<float> & amplitude) {

    std::ofstream file1("axes1CSV.txt");

    for (size_t i = 0; i < time.size(); i++) {
        file1 << displacement[i] << "," << time[i] << std::endl;
    }
    
    std::ofstream file2("axes2CSV.txt");

    for (size_t i = 0; i < amplitude.size(); i++) {
        file2 << frequency[i] << "," << amplitude[i] << std::endl;
    }

}


int main() {

auto sampleVec = readWav("C:/Users/Nicol/OneDrive/Documents/Data/EESoundFiles/test2.wav");
std::cout << "file read" << std::endl;

auto[disp, time, freq, amp] = transform(sampleVec, 2*M_PI, 44100);
std::cout << "transform performed" << std::endl;

fileOutput(disp, time, freq, amp);
std::cout << "output to file" << std::endl;

std::cout << "graphing with python" << std::endl;
system("python C:/Users/Nicol/OneDrive/Documents/Code/C++/FT/CSVtoGraph.py");

}