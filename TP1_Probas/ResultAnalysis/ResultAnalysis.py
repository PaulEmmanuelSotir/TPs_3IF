from ggplot import *
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from io import StringIO
import warnings
import subprocess
warnings.filterwarnings("ignore")

def bitfield(n, size):
    if n >= 0:
        bits = np.array([int(digit) for digit in bin(n)[2:]])
        return np.lib.pad(bits, (size - int(n).bit_length(), 0), 'constant', constant_values=(0, 0))
    else:
        n += 1
        inverted = [-int(digit) + 1 for digit in bin(n)[3:]]
        inverted = np.lib.pad(inverted, (size - int(n).bit_length(), 0), 'constant', constant_values=(1, 1))
        return inverted

def plot_bit_sequence_fft(data, bits_count):
    # use ggplot style sheet
    from matplotlib import style
    style.use('ggplot')
    # Get bit sequence fft and plot it using matplot lib
    bitset = np.array([float(2 * b - 1) for d in data for b in bitfield(d, bits_count)])
    t = np.arange(bitset.size)
    sp = np.fft.fft(bitset)
    freq = np.fft.fftfreq(t.shape[-1])
    sp[0] = 0 # remove 0's high value
    plt.suptitle('Spectral test (DFT of monobit sequence)', fontsize = 16)
    plt.xlabel('frequency')
    plt.ylabel('amplitude')
    plt.plot(freq, sp.real, freq, sp.imag)
    plt.show()#Spectral Test
    
def width(data, bins):
    return abs((max(data['values']) - min(data['values']))/bins)
