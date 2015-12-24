If you've found this repo, you're interested in adding internal electronics to your BB8 Dome.
<div align=center"><img src="https://scontent-iad3-1.xx.fbcdn.net/hphotos-xfp1/v/t1.0-9/10603798_10153226422607761_3631755225023624732_n.jpg?oh=16adb8e8d58f0730d4804b3a3ccf2d0d&oe=5714BCDA" width=320></div>


All of the options I'd seen involved using every single pin of an arduino to light the logic panels on the dome.  Unfortunately, that removed the ability to do anything more interesting with the lighting, because you'd very quickly run out of PWM capable pins. So, I decided to create a version that utilizes shift registers to extend the capabilities a bit.

I've created a parts list if you'd like to grab the components yourself.

<a href="https://docs.google.com/spreadsheets/d/1KzJZGZxBMD4uZg5txSiHm7NLZ_BNpFicUeiCb588h9Q/edit#gid=0">Google Sheets Parts List for BB8 Internals</a>

Within that parts list, you'll see that I'm offering parts kits for sale.  This parts kit includes everything you'd need to create the board that drives the lights, with some instructions on assembly.  It does not include the arduino or any of the components to tie the two together.

Once you've got your lighting board set up, you'll need to download the arduino sketch included here, along with the following libraries:

ShiftPWM
ArduinoThread
LogicBoard

LogicBoard is the code I'm writing to handle the different lighting modes and interactions in this version of the software.
