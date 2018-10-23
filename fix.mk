
all-fix:
	@echo make fix

fix:
	sudo stty -F /dev/ttyACM0 -hupcl
