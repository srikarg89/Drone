import tkinter as tk
from tkinter import messagebox
import serial

ser = serial.Serial("COM5", 9600)

MIN_SPEED, MAX_SPEED = 0, 100

def send(speed):
    to_send = int(speed * 255 / MAX_SPEED)
    ser.write([to_send])

class Example(tk.Frame):
    def __init__(self, parent):
        tk.Frame.__init__(self, parent, width=400,  height=400)

        self.label = tk.Label(self, text="Speed: 0", width=20)
        self.label.pack(fill="both", padx=100, pady=100)

        self.label.bind("<w>", self.on_press)
        self.label.bind("<s>", self.on_press)
        self.label.bind("<a>", self.on_press)

        # give keyboard focus to the label by default, and whenever
        # the user clicks on it
        self.label.focus_set()
        self.label.bind("<1>", lambda event: self.label.focus_set())
        self.speed = 0


    def on_press(self, event):
        if event.keysym == 'a':
            # Safety switch, automatically turns off motors when pressed
            self.speed = 0
            send(self.speed)
        elif event.keysym == 'w':
            self.speed += 1
            self.speed = min(self.speed, MAX_SPEED)
            send(self.speed)
        elif event.keysym == 's':
            self.speed -= 1
            self.speed = max(self.speed, MIN_SPEED)
            send(self.speed)

        print(self.speed)
        self.label.configure(text="Speed: " + str(self.speed))


def on_closing():
    if messagebox.askokcancel("Quit", "Do you want to quit?"):
        send(0)
        ser.close()
        root.destroy()

if __name__ == "__main__":
    root = tk.Tk()
    root.protocol("WM_DELETE_WINDOW", on_closing)
    Example(root).pack(fill="both", expand=True)
    root.mainloop()
