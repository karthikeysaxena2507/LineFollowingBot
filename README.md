# LINE-FOLLOING-BOT
The bot follows a black line on a plane white background. The working of the bot, principles used and equipments required have been discussed below.

 <h3>Equipments Required</h3>
1. Arduino genuino uno board </br>
2. Motor Driver (L298N) </br>
3. Pololu qtr 8rc sensor </br>
4. Castor wheel </br>
5. L clamps </br>
6. Motors (200rpm) (2) </br>
7. Jumper wires </br> 
8. An adapter </br>

<h3> Working of bot </h3>
1. The bot actually works on the priciple of light's property to reflect white light completely and absorb black light completely. For this purpose we use 
   pololu qre 8rc sensor which has 8 IR sensors which is used to take input and pass it to arduino. </br>
2. The arduino is tha brain of our bot. It processes the input received from the sensor and converts the digital signal to analog with the help of pulse 
   width modulation technique. </br>
3. The modified signal is then sent by arduino to the motor driver which is responsible to move the wheels according to the input received from arduino. </br>
4. The motor driver is then connected to our 2 motors attached to wheels which move the bot. </br>

