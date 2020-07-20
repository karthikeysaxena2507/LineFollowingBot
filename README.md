# LINE-FOLLOING-BOT
The bot follows a black line on a plane white background. The working of the bot, priciples used and materials required have been discussed below.

 <h3>Equipments Required</h3>
1. Arduino genuino uno board
2. Motor Driver (L298N) 
3. Pololu qtr 8rc sensor 
4. Castor wheel
5. L clamps
6. Motors (200rpm) (2)
7. Jumper wires
8. An adapter

<h3> Working of bot </h3>
1. The bot actually works on the priciple of light's property to reflect white light completely and absorb black light completely. For this purpose we use 
   pololu qre 8rc sensor which has 8 IR sensors which is used to take input and pass it to arduino.
2. The arduino is tha brain of our bot. It processes the input received from the sensor and converts the digital signal to analog with the help of pulse 
   width modulation technique.
3. The modified signal is then sent by arduino to the motor driver which is responsible to move the wheels according to the input received from arduino.
4. The motor driver is then connected to our 2 motors attached to wheels which move the bot.

