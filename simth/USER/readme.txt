1、STM32作为CPU1，TM4作为CPU2；（STM32用的F103ZET6）
2、如需修改PID参数，在keyboard中修改；
（如果按键弄好了可以直接用按键修改，本程序设了四个按键：选参数，选量程，加、减）
3、simth文件中为传递函数部分
4、controler中为控制部分
5、关于归一化：程序中是归一化的电压，因为ad受参考电压影响较大
	Yt预设为-10——10；将电压归统一为0——3V，（-10——0对应0——1.5V;0——10对应1.5——3.0V）
	ad采集到的电压可能损耗较大，可以根据自己板子的实际情况进行补偿