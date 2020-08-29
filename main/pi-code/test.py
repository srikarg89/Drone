import pigpio

pi = pigpio.pi()
#pi.set_PWM_range(4, 100)

while True:
   inp = input()
   pi.set_PWM_dutycycle(4, int(inp))

