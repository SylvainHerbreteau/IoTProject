from sense_hat import SenseHat

sense = SenseHat()
temperatur= sense.get_temperature()
humidity = sense.get_humidity()
pressure= sense.get_pressure()


f= open("StationMeteo.txt","w+")

f.write("%f\n" % temperature)
f.write("%f\n" % humidity)
f.write("%f\n" % pressure)

f.close()
