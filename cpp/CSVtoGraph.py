import matplotlib.pyplot as plt

with open("C:/Users/Nicol/OneDrive/Documents/Code/C++/FT/axes1CSV.txt", "r") as file:
    lines = []
    
    for line in file:
        lines.append(line.strip())

    displacement = [0] * len(lines)
    time = [0] * len(lines)

    for i in range(len(lines)):
        displacement[i], time[i] = lines[i].split(",")
        displacement[i] = float(displacement[i])
        time[i] = float(time[i])

    plt.subplot(1, 2, 1)
    plt.plot(time, displacement)  

with open("C:/Users/Nicol/OneDrive/Documents/Code/C++/FT/axes2CSV.txt", "r") as file:
    
    lines = []
    
    for line in file:
        lines.append(line.strip())

    frequency = [0] * len(lines)
    amplitude = [0] * len(lines)

    for i in range(len(lines)):
        frequency[i], amplitude[i] = lines[i].split(",")
        frequency[i] = float(frequency[i])
        amplitude[i] = float(amplitude[i])

    plt.subplot(1, 2, 2)
    plt.plot(frequency, amplitude)  
    
plt.show()


