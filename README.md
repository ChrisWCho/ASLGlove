# ASL (American Sign Language) Glove

When I was younger I was apart of a summercamp where I was taught the alphabet in ASL (American Sign Language) and in the summer of 2021, I had an inspiration to use my knowledge of arduino micro processors, C programming language, and my memory of American Sign Language to challenge myself to design and develop a glove that allows its user to use these hand signals to output the expected letters of the alphabet.

This project allowed me to use an arduino nano, a GY521 MPU6050 accelerometer/gyroscope, and a LCD module to display the letters.
I first used flex sensors to determine in the attempt to use its variable resistance on each finger to determine the combination for a expected letters, but soon came to a realization that instead, I can use digital inputs instead and use 0's and 1's at the bend of each knuckle which provides a more accurate combination input as the flex sensors are very unpredictable.

So in the end, I was able to use this to develop a combination of finger placements along the gyroscope to determine the letters and display them correctly, while also using the accelerometer to erase the message when I shake my hand rapidly.
<!--
<img src="https://github.com/user-attachments/assets/bc800d42-9adb-4809-be05-e38c3c93ba8e" alt="Project 2" style="width:30%; height:auto;">
![image(1)](https://github.com/user-attachments/assets/f880b5e6-2788-4496-b092-7125fbbaed09)
![image(2)](https://github.com/user-attachments/assets/6273ce74-02b9-4fa0-beaa-7033ea060721)
![image(3)](https://github.com/user-attachments/assets/314c030d-0c0a-4a4a-beb4-09ce89c00d66)
![image(4)](https://github.com/user-attachments/assets/be20855d-7166-431e-89bf-32c3756bcbcc)
![image(5)](https://github.com/user-attachments/assets/8422ddc5-5532-44f9-9815-91e6bd85c082)
![image](https://github.com/user-attachments/assets/51b997f4-8c57-42fc-bdbe-be575b2d8972)

https://youtube.com/shorts/agsWuEC8VSQ
-->
## Picture of the ASL Glove Prototype.
<img src="https://github.com/user-attachments/assets/e441385b-d8f0-4e1b-9706-6823a24ae4e1" alt="Project 2" style="width:30%; height:auto;">
