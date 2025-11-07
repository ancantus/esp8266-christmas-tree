import machine
import neopixel
import time

# web interactive demo at https://wokwi.com/projects/447001528860220417

NUMROWS = 5
np = neopixel.NeoPixel(machine.Pin(13), NUMROWS * NUMROWS) # D7 on NodeMCU

def sweep_color(color, duration):
	step_duration = int(duration / NUMROWS)
	for i in range(NUMROWS):
		for j in range(NUMROWS):
			np[(i * NUMROWS) + j] = color
		np.write()
		time.sleep_ms(step_duration)


def main():
	rainbow = [
		(255, 0, 0),	# red
		(255, 127, 0),	# orange
		(255, 255, 0),	# yellow
		(0, 255, 0),	# green
		(0, 0, 255),	# blue
		(75, 0, 130),	# purple
		(148, 0, 211),	# violet
	]
	
	index = 0
	while True:
		sweep_color(rainbow[index], 300)
		time.sleep_ms(1000)
		index = (index + 1) % len(rainbow)

# always include a startup sleep in case your program busy-loops
# this means it still can be recovered / troubleshooted with the py REPL
time.sleep_ms(5000)
main()