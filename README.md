// ROAD MAP //

Version 1.0 - Complete
Version 2.0 - Sound Module - Will include randomized sounds that play at randomized intervals.  Perhaps integrate an external power switch.
Version 3.0 - External stimulus for sound module - Considering IR, zigbee, wifi, raspberry pi interface, others.
Version 4.0 - Likely final - Will provide open ends for communication with external components (body, other network devices)... Perhaps moving the audio out of the dome into the body.



//
UPDATE 2015-12-27

For whatever reason, git desktop decided not to push up the stl's and the png that contains the breadboard layout version of the schematic.  I corrected that and those files are now available.  A couple of things about the breadboard layout:

* - Don't use 220ohm resistors on the entire RGB LED.  Every RGB LED I've seen uses something different.  Mine took 100ohm resistors on the green and blue pins.  Just check the data sheet for whatever you buy.
* - The diagram also doesn't show the power indicator LED.  This is totally optional, but I like being able to verify that the board is getting power.
* - This can be compressed significantly, using the board I show in the parts list. Look at either of the Board images in the images folder for an example.  Board2 is the latest approach, and allows you to create a wiring harness with the common cathode pin glued to the anodes.  This way, you can just plug in the entire block and not have to fiddle with it.  This version also requires less soldering.  I'll put up a picture of the solder points shortly.
* - Last but not least... just wanted to add a quick note that you probably shouldn't run this off the 5v pin. I do.. and my LEDs are BRIGHT.  But I have no idea what that's going to do to the life of my LEDs.  I imagine they will burn out quicker, but I run my board infrequently enough that I won't mind printing and replacing the LED harnesses eventually. Anyway, just wanted to drop a note about that consideration.

//

If you've found this repo, you're interested in adding internal electronics to your BB8 Dome.
<img src="https://scontent-iad3-1.xx.fbcdn.net/hphotos-xfp1/v/t1.0-9/10603798_10153226422607761_3631755225023624732_n.jpg?oh=16adb8e8d58f0730d4804b3a3ccf2d0d&oe=5714BCDA" width=320>


All of the options I'd seen involved using every single pin of an arduino to light the logic panels on the dome.  Unfortunately, that removed the ability to do anything more interesting with the lighting, because you'd very quickly run out of PWM capable pins. So, I decided to create a version that utilizes shift registers to extend the capabilities a bit.

<img src="https://scontent-iad3-1.xx.fbcdn.net/hphotos-xfa1/t31.0-8/920727_10153226421547761_8605656006124651485_o.jpg" width=320>

I’ve finally finished version 1.0 of my standalone lighting for the dome. I’ve had a lot of people ask me to post schematics, code, and parts lists… and I finally feel like it’s at a good point to do so. 

Regarding the schematic - The schematic shows 220ohm resistors for ALL of the LEDs. This is incorrect. The green and blue legs for the RGB LEDs generally use a lower value resistor. In my case, they’re using 100ohm resistors. Please check your spec sheets for whatever RGB LEDs you get.

Regarding the program - The program requires three libraries (included in the archive). ShiftPWM, which allows you to extend the number of addressable LEDs using shift registers. Arduino Thread, which facilitates (or simulates anyway) multi-threaded operation, and LogicBlock, which is custom code that I’m writing. The sketch itself, along with the LogicBlock library, are the two components of this that I’ve written from the ground up, and will be modifying over time. In future releases, I’ll only be including those two components.

Regarding the parts list (<a href="https://docs.google.com/spreadsheets/d/1KzJZGZxBMD4uZg5txSiHm7NLZ_BNpFicUeiCb588h9Q/edit#gid=0">Google Sheets Parts List for BB8 Internals</a>)- So, full disclosure: I’m VERY impatient. I buy everything on Amazon Prime, because I’m going to get whatever it is in two days, in most cases. So the links I’ve included in the parts sheet are all to amazon prime pages. You CAN find these parts cheaper elsewhere.. you can also likely find them in smaller quantities… for what it’s worth, I found that you’re really only saving a couple bucks elsewhere… but you might have better sources than me. I’ve been really happy with the quality of the parts I’ve ordered.

As a result of my Amazon purchase history, I have a surplus of parts… and as such, I’m willing to put together parts kits for those of you that are willing/able to solder your own setup. I’ve broken down the cost per part for everything I used in my build, and listed that out in the parts sheet. Just to be totally clear, I’m not marking up the price of each part, but I am charging a couple of bucks “handling” for getting everything bagged in anti-static container and organized into envelopes/packages.

I’ve also designed an enclosure to house all of this and keep it looking nice inside my dome. I’ll be happy to share the STLs for that if anyone is interested… but it’s pretty purpose specific to the board I’ve designed.

All of that said, there have been several people that have asked me if I would build this for them, and I’m willing to do that. I’ve included a few options for how that can happen (purchasing arduinos, optional parts, etc) in the parts list spreadsheet. If you think that’s something you might be interested in, feel free to reach out and we can discuss what you might need.

TO DO
-----
* Write up assembly instructions
* Update schematic to reflect 100 ohm resistors, and include power indicator led
* Continue working on v2 (sound add-on)

