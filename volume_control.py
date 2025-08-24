import serial
import time
from ctypes import cast, POINTER
from comtypes import CLSCTX_ALL
from pycaw.pycaw import AudioUtilities, IAudioEndpointVolume

# --- Setup Serial (change COM port to match Arduino) ---
ser = serial.Serial('COM5', 9600, timeout=1)
time.sleep(2)  # wait for Arduino reset

# --- Setup Pycaw ---
devices = AudioUtilities.GetSpeakers()
interface = devices.Activate(IAudioEndpointVolume._iid_, CLSCTX_ALL, None)
volume = cast(interface, POINTER(IAudioEndpointVolume))

print("Listening for Arduino volume values...")

while True:
    try:
        line = ser.readline().decode().strip()
        if line.isdigit():
            vol_percent = int(line)
            vol_scalar = vol_percent / 100.0  # convert to 0.0–1.0
            volume.SetMasterVolumeLevelScalar(vol_scalar, None)
            print(f"Volume set to {vol_percent}%")
    except Exception as e:
        print("Error:", e)
        break