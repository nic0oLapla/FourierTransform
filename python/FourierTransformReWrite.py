from math import e, floor, pi, sqrt
import librosa
import matplotlib.pyplot as plt

def readWav(filePath, dFreq):
    sampleRate = librosa.get_samplerate(filePath)
    soundFile = librosa.load(filePath, sr = sampleRate, mono = True)
    waveform = list(soundFile[0])
   
    return waveform, sampleRate, dFreq

def transform(inputTuple):
    
    waveform, sampleRate, dFreq = inputTuple

    maxFreq = floor(sampleRate/2)
    samples = len(waveform)
    dw = (2 * pi) / samples #superceded by sampleRate
    
    xAxis = waveform
    tAxis = []
    for i in range(0, samples):
        tAxis.append(i/sampleRate)

    XAxis = []
    wAxis = []
    
    f = dFreq
    while f <= maxFreq:
        
        sumReal = 0
        sumImag = 0

        for i in range(0, samples):
            
            frame = xAxis[i] * e**(-1j * f  * 2 * pi * tAxis[i])

            sumReal += frame.real
            sumImag += frame.imag

        magnitude = sqrt(sumReal**2 + sumImag**2)
        
        #if magnitude >= 1:
        #    print(f, magnitude)

        XAxis.append(magnitude)
        wAxis.append(f)

        f += dFreq

    return xAxis, tAxis, XAxis, wAxis

def graph(inputTuple):
    
    displacement, time, amplitude, frequency = inputTuple

    plt.subplot(1, 2, 1)
    plt.plot(time, displacement)

    plt.subplot(1, 2, 2)
    plt.plot(frequency, amplitude)
    
    plt.show()


graph(transform(readWav("C:/Users/Nicol/OneDrive/Documents/Data/EESoundFiles/test2.wav", 2*pi)))