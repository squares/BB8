If you've found this repo, you're interested in adding internal electronics to your BB8 Dome.

All of the options I'd seen involved using every single pin of an arduino to light the logic panels on the dome.  Unfortunately, that removed the ability to do anything more interesting with the lighting, because you'd very quickly run out of PWM capable pins. So, I decided to create a version that utilizes shift registers to extend the capabilities a bit.

I've created a parts list if you'd like to grab the components yourself.

https://docs.google.com/spreadsheets/d/1KzJZGZxBMD4uZg5txSiHm7NLZ_BNpFicUeiCb588h9Q/edit#gid=0

Within that parts list, you'll see that I'm offering parts kits for sale.  This parts kit includes everything you'd need to create the board that drives the lights, with some instructions on assembly.  It does not include the arduino or any of the components to tie the two together.

Once you've got your lighting board set up, you'll need to download the arduino sketch included here, along with the following libraries:

ShiftPWM
ArduinoThread
LogicBoard

LogicBoard is the code I'm writing to handle the different lighting modes and interactions in this version of the software.
