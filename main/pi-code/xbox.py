import os, time
import pigpio
import socket

#os.system('sudo pigpiod')

ESC = 4
pi = pigpio.pi()
pi.set_servo_pulsewidth(ESC, 0)

GS_IP, GS_PORT = '192.168.0.34', 5005
MAX_VALUE = 2000
MIN_VALUE = 700

ARMED = False
SPEED = 1000

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((GS_IP, GS_PORT))


def arm():
    global ARMED
#    print("Plug battery in and press enter")
#    input()
    pi.set_servo_pulsewidth(ESC, 0)
    time.sleep(1)
    pi.set_servo_pulsewidth(ESC, MAX_VALUE)
    time.sleep(1)
    pi.set_servo_pulsewidth(ESC, MIN_VALUE)
    time.sleep(1)
    print("Motor is armed")
    ARMED = True


def control(speed):
    if not ARMED:
        return
    pi.set_servo_pulsewidth(ESC, speed)
    SPEED = speed


def disarm():
    global ARMED
    pi.set_servo_pulsewidth(ESC, 0)
#    pi.stop()
    ARMED = False


def run():
    while True:
        inp = sock.recv(1024).decode()
        print("Received:", inp)
        if inp == "A":
            arm()
        elif inp == "D":
            disarm()
        elif inp == "Q":
            if ARMED:
                print("Can't kill program while motor is armed")
                continue
            pi.stop()
            return
        elif inp.isdigit():
            speed = int(inp)
            if speed < 950 or speed > 1700:
                print("Speed (" + inp  + ") is not in the range 950-1700")
            control(speed)
        else:
            print("Unknown command received", inp)
        print("Sending back confirmation")
        sock.send("CONFIRMATION".encode())


if __name__ == '__main__':
    disarm()
    run()

print("GG Game over boys")