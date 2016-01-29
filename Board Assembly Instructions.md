_THIS IS A (MOSTLY COMPLETE) WORK IN PROGRESS FOR ASSEMBLY INSTRUCTIONS_

_I CAN'T BE HELD RESPONSIBLE IF YOU BURN YOUR HOUSE DOWN. USE COMMON SENSE_

# BOARD ASSEMBLY INSTRUCTIONS

## Parts Needed:
* [Google Sheet Parts List](https://docs.google.com/spreadsheets/d/1KzJZGZxBMD4uZg5txSiHm7NLZ_BNpFicUeiCb588h9Q/edit?usp=sharing)

## Tools Needed:
* Soldering iron with a fine tip
* Solder
* Helping Hands tool
* Multi-meter
* Hot glue gun
* Probably some kind of magnification or really good eyeballs.
* Light
* Time
* Patience

## GENERAL NOTES BEFORE WE START: 
* These instructions assume you have at least a moderate knowledge of soldering.  You're working with relatively small soldering points.
* It's further assumed that you should be testing your connections as you go to verify that current is passing correctly.
* I will refer to the "Top", "Bottom", "Left" and "Right" of the board in these instructions.  These terms will almost always refer to looking at the chip-side of the  board straight on, unless otherwise noted.
* In these instructions, I describe WHAT to do, and in general, WHY to do it that way, for practical purposes.  I don't describe HOW to solder... or WHY this all works.  I'm happy to discuss those issues in separate conversations, but I think it would make these instructions the size of a novel to get into that depth.
* For the purposes of clarity, I talk about the socket pins in terms of pin numbers in relation to their final position in the board.  With the socket placed horizontally with the top surface facing you, pin 1 is in the top left... counting across to pin 8.  Pin 9 is in the bottom left, and pin 16 is in the bottom right.  This is how I've always thought of them when soldering, so that's how I'll write it out here.  Hopefully that's not too confusing.

(insert drawing with numbered pins).

* Read through ALL of the instructions first, to make sure you understand everything before starting.  If you have any questions, feel free to reach out and ask and I will try to clarify. I've had to desolder major sections of boards before because I didn't realize something, and that sucks.




## With that out of the way, lets DO THIS!

**Step 1:**

Solder the three sockets to the board.  Why do we use sockets? Well, the truth is that these guys MIGHT be getting a little more power than they're spec'd for.  I've been running mine for many, many hours without issue... but it's POSSIBLE that they may get burnt out over time. Hell, everything gets burnt out over time... but we want the shift registers to be as easy to replace as possible, since they are doing most of the work.

![Step 1 - Sockets in board](https://raw.githubusercontent.com/squares/BB8/master/images/Step1.jpg)

The first socket should be in the 7th hole.  I have another version where the first socket is in the 5th hole, but I found the 7th hole to involve less soldering down the road.

The sockets should be soldered with one space between them. 

![Step 1C - Sockets in board - Soldered](https://raw.githubusercontent.com/squares/BB8/master/images/Step1C.jpg)

**Step 2:**

This is one of the most annoying things to solder...  The 74hc595 shift register uses the second pin on the top side of the IC to control the 0th output. Thus, the reason we left a space between the sockets.  We're going to take a short length of wire, and bend it around the left side of the socket, so that it ends one pin to the left of the socket's 9th pin.

![Step 2 - 0th LED wire](https://raw.githubusercontent.com/squares/BB8/master/images/Step2.jpg)
![Step 2 - 0th LED wire](https://raw.githubusercontent.com/squares/BB8/master/images/Step2B.jpg)

Now that this it out of the way, everything else is relatively easy.

**Step 3:**

For this board, we're using the second top rail as the power rail.  You'll want to solder two short wires connecting pin 1 and pin 7 of each of the sockets  to the power rail. To save as much space later for wiring, connect them from the absolute top position of the terminal strip.

![Step 3 - Power Connection](https://raw.githubusercontent.com/squares/BB8/master/images/Step2B.jpg)

NOTE:  It's really easy to get mixed up with positions in this sort of work. Always double check that you're running a wire to the correct start and end position before soldering. Unsoldering is a pain in the ass.

**Step 4:**

Each socket is grounded from the 4th pin.  For this layout, we're using the absolute top rail of the board as the common ground.  So run a wire from the top terminal strip position on the 4th pin, to the ground rail for each socket.

![Step 4 - Ground Connection](https://raw.githubusercontent.com/squares/BB8/master/images/Step3-4.jpg)

**Step 5:**

Shift registers are awesome, and you can daisy chain them together infinitely, provided you have enough power to drive them safely... which I guess means it's not infinite, but WHATEVER.  So we're going to chain these sockets together.  The three terms you want to remember are "data", "clock", and "latch". I won't go into what each of those are right now... but suffice to say, these are the three lines that will control the way the LEDs turn on and off.

For my boards, I like to keep all of the data, clock and latch connections the same color.  This helps me troubleshoot later should something stop working. The data INPUT pin on the chip is the 3rd pin across the top side of the board, and it is being output on the 8th pin on that same side.

So, starting with the rightmost socket, connect the 3rd pin on socket 3, to the 8th pin of socket 2.  This will overlap the 0th LED pin. Just make sure that there are no exposed wires touching.  Alternatively, you can get fancy and have it curve around the top.  Whatever you think looks better :)

Repeat this from the 2nd to the 1st socket.

![Step 5 - Data Connections](https://raw.githubusercontent.com/squares/BB8/master/images/Step5.jpg)

**Step 6:**

Now for the "clock" line.  All of the ICs use the same pin to manage the clock.  This is the 6th pin.  So we're going to solder a wire from the 6th pin of the socket 3 to the 6th on the socket 2, and then repeat that from socket 2 to socket 1.

![Step 6 - Clock Connections](https://raw.githubusercontent.com/squares/BB8/master/images/Step6.jpg)

Notice, that for these connections, I'm shifting one hole up as I go from socket 3 to socket 2.  This lets me drop down one hole in that same terminal strip for that same pin, and keeps things looking nice and tidy.

**Step 7:**
The "latch" line is last, and like the clock line, it occupies the same pin on each of the sockets.  This time, we're connecting the 5th pin of the socket 3 to the 5th of the socket 2. Then repeat this to socket 1.

![Step 7 - Latch Connections](https://raw.githubusercontent.com/squares/BB8/master/images/Step7.jpg)

**Step 8:**
Solder one .1uf capacitor to the board for each of the sockets, connecting the 5th terminal strip to ground.  This shares the same terminal strip as the latch line, for reference.

![Step 8 - Capacitor Connections](https://raw.githubusercontent.com/squares/BB8/master/images/Step8.jpg)

**Step 9 (OPTIONAL STEP):**

I personally like to have a power indicator light on my board... if you have one of the parts kits, this explains the extra resistor and green LED ("BB-8 doesn't have any green LEDs... wtf?").  Solder the resistor at the top right of the board at the absolute end of the power rail.  Then solder the LED from where the resistor terminates, back to the ground rail.  Tadaaa... power indicator.

![Step 9 - Power Indicator Connections](https://raw.githubusercontent.com/squares/BB8/master/images/Step9.jpg)

The top half of the board is now complete.  Take some time to stretch or a nap or something :)

**Step 10:**

We need to get a common ground to the bottom of the board.  The prototyping board I reference in my parts list, has three rails across the bottom. For this layout, we're going to use the topmost of those three bottom rails.

To connect this to ground, you will need to use three very short wires, as shown in this photo:

![Step 10 - Common Ground Connections](https://raw.githubusercontent.com/squares/BB8/master/images/Step10.jpg)

**Step 11:**

Each of the sockets will be connected to ground from the 16th pin. Run a very short connection from the bottom of that terminal strip to the ground rail immediately below. On the solder-side of the board, use a sharpie to draw a line between the socket pin and the ground pin that you just soldered.  This will be referenced later.

![Step 11 - Ground Connections](https://raw.githubusercontent.com/squares/BB8/master/images/Step11.jpg)

**Step 12:**
Resistor time!  We want to use the bottommost hole of the terminal strip for a header socket... so we need to bend the resistors in a way that allows them to only span 3 holes.  I like to leave one leg straight, and bend down the other leg until it can fit in there correctly.  Also, as a matter of personal preference, I like to bend and place all of the resistors at the same time, and then tape them in place so they all line up nicely. Then, I go through and solder them all in a row.  

![Step 12 - Resistor Connections](https://raw.githubusercontent.com/squares/BB8/master/images/Step12.jpg)

![Step 12B - Resistor Connections](https://raw.githubusercontent.com/squares/BB8/master/images/Step12B.jpg)

Solder one set of 8-pin resistors per the photo... then flip the board over for the next step.

**Step 13:**

VERY IMPORTANT STEP.  I guess they're all very important... but this is one, where if not taken... can ruin your build when you plug it in. 

We all know that current takes the path of least resistance... and we want our current running through resistors... not the terminal strips. If we left the board like it is, then your LEDs would light up briefly at full blast, and probably burn out within a second. So we need to modify our board a little bit.  I usually wait until this point, so I can reference the solder points we made in step 12.  We need to sever the terminal strip between the resistor pins.  To do so, I use a little pointy file, and scrape them, until a test with a multi-meter proves that the connection has been severed there.  I like this board because it doesn't take too much to make this happen, and it's hard to screw up.  Just take it slow and be careful, and don't cut the connection to the ground from step 11 (the sharpie-line!).

![Step 13 - BOARD MODIFICAIONS](https://raw.githubusercontent.com/squares/BB8/master/images/Step13.jpg)

Once you've identified where the right terminal strip cuts should go, you can repeat this across the next sets of 8... JUST BE SURE TO AVOID THE BLACK LINE YOU DREW WITH THE SHARPIE. We need that connection to the ground.

![Step 13B - BOARD MODIFICAIONS](https://raw.githubusercontent.com/squares/BB8/master/images/Step13B.jpg)
![Step 13C - BOARD MODIFICAIONS](https://raw.githubusercontent.com/squares/BB8/master/images/Step13C.jpg)

Turn the board back over, and repeat the resistor soldering in step 12 for the next two sets of headers.  NOTE:  The RGB LEDs used in my parts list require a different resistor for the green and blue pins.  As such, you can see in the photos that I've left spaces for those, and installed them facing the opposite direction, just so I can clearly see where they sit.

![Step 13D - BOARD MODIFICAIONS](https://raw.githubusercontent.com/squares/BB8/master/images/Step13D.jpg)
![Step 13E - BOARD MODIFICAIONS](https://raw.githubusercontent.com/squares/BB8/master/images/Step13E.jpg)
![Step 13F - BOARD MODIFICAIONS](https://raw.githubusercontent.com/squares/BB8/master/images/Step13F.jpg)

**Step 14:**

We're going to use 6, 8-pin headers.  If you bought the bag of headers from my parts list, then you've got a bunch of 40 pin headers to cut into 8-pin sections.  We're shooting for two rows of 8-pins for each section. There are a ton of ways to ensure that your headers go in straight and aligned.  I personally take some male header pins, and connect the tops of the female headers together... then tape that flat to the board... then solder.  I've had good luck with that method.

![Step 14 - BOARD MODIFICAIONS](https://raw.githubusercontent.com/squares/BB8/master/images/Step14.jpg)

NOTE: Why 8 pin connections when the dome lights are either 1, 3, 4, or 5 pins?  Well, for me, it's more about the outputs of the ICs. I like knowing that for a given block of 8 header sockets, that one shift register is driving those.  That way, I can more easily troubleshoot a problem.  Also, it allows for me to more easily make changes in the future.  If I want to move all of my wiring harnesses around, and have the 5-pin logic lens first, I can do that.  If you decided that this is going to be the last time you deal with this particular board, and you want to do groups of headers that are the exact size of the lights you're going to plug in, then do them in this order:
4 pins, 5 pins, 2 pin, 5 pins, 3 pins, 3 pins, 2 pins.

**Step 15:**

The board is complete!  Now we just need to create connections for the arduino! For these wires, I've used jumper wires with one male end and one female end.  You will need 5 wires, and I recommend using red and black for the power and ground, and match the colors you used in step 5 for data, latch, and clock for the other three. 

Cut the female end off of each wire, and strip a few millimeters of shielding off to expose the wire, then tin that with solder.

Solder the data wire to an available hole in the terminal strip for pin 3 of Socket 1.

Solder the latch wire to an available hole in the terminal strip for pin 5 of Socket 1.

Solder the clock wire to an available hole in the terminal strip for pin 6 of Socket 1.

Solder the power (red) wire to the leftmost hole in the power rail.

Solder the ground (black) wire to the leftmost hole in the ground rail.

![Step 15 - Completed soldering](https://raw.githubusercontent.com/squares/BB8/master/images/Step15.jpg)

NOTE: These connections are VERY fragile.  We'll address that in a second... but this is probably a great point to test out at least the power connections. You can take the red and black pins, and plug them into your arduino's 3.3v and ground connections respectively. Then power up the arduino.  Your power indicator SHOULD light up, and you can scream out "IT'S ALIVE" and freak out anyone that's around you.

**Step 16: **

![Step 16 - Completed soldering](https://raw.githubusercontent.com/squares/BB8/master/images/Step16.jpg)

Remove all power to the board, if you happened to test it in the previous step.  Those wires are fragile, so let's hot glue all of the connections we just made in Step 15 to keep them from ripping out. I like to zip tie the wires together, so I know they're all going to end up coming out of the same spot on the board, and then just glob down some glue where they connect to the board. Be careful not to get any hot glue into the socket, or you're going to have a bad day.

**Step 17:**

Again, making sure you don't have any power to the board, and also making sure that your hot glue has cooled... plug in the 74hc595's!  
![Step 17 - Completed soldering](https://raw.githubusercontent.com/squares/BB8/master/images/Step17.jpg)

Your board is now complete.  You can safely power it back up.

## To test:
Install the domelights arduino sketch onto your arduino.  Connect the data wire to digital pin 4. Clock to 5. Latch to 8. Power to 3.3v and Ground to ... ground.

Take a 3.3v LED, and put the anode into the top row of the header... the cathode into the bottom row.  (Anode is the long pin... cathode is the short one).

Your LED should immediately start either dimming or flicking on and off (it depends on which part of the animation cycle it's in when you make the connection).


## Troubleshooting:

* - Power indicator isn't lighting up:  

This could happen for a couple of reasons.  The first is that there's no power coming in from the arduino.  test that the arduino has power, and that the connections are good.  You'll need to test your solder points to ensure they're solid and current is flowing. 

If you're SURE the arduino has power... and that your board is getting power... and that the wires are connected to the correct rails of the board.  Then it's possible your LED is in backwards.  this is tricky to troubleshoot if you've already cut the legs off of it... you can run jumper wires from a digital out set to high and the ground, to the pins of the LED, and see if it turns on if you swap them.  It's also possible that the LED is just burnt out.  It's best to test every LED before putting it in the board, but it can happen.

* - Lights come on, but there's no animation:
This has happened to me a few times.  First, reset the arduino with everything plugged in.  If the lights stay on, and don't change... there's a problem with the data, clock, or latch.  Make sure those wires are connected correctly on both the arduino side, and the board side.  Most of the time, it's just that one of them is plugged in to the wrong pin on the arduino side.

Failing that, double check that you've soldered them to the correct location.  The data wire should be soldered to pin 3 of the first socket.  The latch should be soldered to pin 5, and the clock to pin 6.

If all of those are correct, make sure that the connections between socket 1, 2 and 3 are all correct.

If all of the above is correct, you likely have a short in your soldering job somewhere.  You're going to need to take a very good look at the solder points between pins to make sure that there are no points where one terminal strip is connected to another.

 
* - Lights come on, and there IS animation, but it's weird:

First, let's describe what "weird" is.  When you first power on the board (assuming you have it connected to the arduino, and have successfully uploaded the code)... The logic lights should pulse two to three times (fade from dark to light and back).  The radar eye should be solid red... and the holo and psi should be on solid.  After about 2-3 seconds, the logic lens lights should randomly shift to different animations.  These could either be random lights lighting up, or fading, or some combination of those.  The radar eye should still be solid.  The PSI will either be blue or white... and the holo will be slowly fading through random colors.

See something different?  Are the lights all flickering in unison?  Is the holo solid red(or green or blue), and not changing? Is the PSI red or green? IS THE RED RADAR LED FLICKING OR FADING (that's a big one).  If any of the previous are true, this can be considered "weird". 99.99999999% of the time, this is due to a short in the soldering.  If you've followed the instructions precisely, and all of the wires are connected to the right parts of the shift registers, then it's almost definite that you have a short between solder points.  The only way to fix this (sadly), is to take out a magnifying glass and go from point to point ensuring that things that SHOULD be connected ARE connected, and things that SHOULDN'T be connected AREN'T. It's also helpful to review the points to ensure you have a good solder joint.

For more on common issues with soldering, check out this helpful guide:
https://learn.adafruit.com/adafruit-guide-excellent-soldering/common-problems

Again... this is relatively small work, and it requires a steady hand and clean soldering work.

* - LEDs don't come on:

Any issue with the LED not coming on is going to be a problem with soldering or grounding.  Step through each path that current is supposed to flow, and verify that there is a solid solder connection.  Also, make sure that everything is grounded correctly, and that all of the common ground rails are connected.

* - Other:

Throw me an email at strong.s@gmail.com and we can try to work through it.  The schematic and parts I have are exactly what I've used to make this work, so it should be easy to sort something out quickly over a skype call.











