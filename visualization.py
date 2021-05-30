import matplotlib.pyplot as plt 
import numpy as np 

plt.style.use('seaborn-whitegrid')

x1 = np.arange(0, 5, 0.1)
y1 = [277 for x in range(50)] 

x2 = np.arange(5, 15, 0.1)
y2 = [311 for x in range(100)]

x3 = np.arange(15, 50, 0.1)
y3 = [330 for x in range(350)]

# Plot all x and y
plt.bar(x1, y1,  label='NOTE_C', color='tab:cyan')
plt.bar(x2, y2, label='NOTE_D', color='tab:olive')
plt.bar(x3, y3, label='NOTE_E', color='m')
plt.title("Ultrasonic Music Box Default Tone")
plt.legend(loc='upper right', borderaxespad=0.)
plt.ylabel("Tone")
plt.xlabel("Distance (cm)")
plt.xlim(-0.1, 55)
plt.ylim(250, 350)
plt.show()