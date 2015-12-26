# ATtiny

Выполнил студент ФКН БПМИ142 Петроченко Даниил

Эмулятор микроконтроллера семейства AVR ATtiny13A, поддерживающий набор определенных команд. Программа, на вход которой подается код, полученный на ассемблере AVR, выполняющая этот код, а также позволяющая писать программы на ассемблере.

В процессе создания эмулятора были реализованы арифметические операции над регистрами общего назначения, эмулятор умеет выполнять простейшие программы, полученные с помощью компилятора AVRA.

Не была реализована обработка EEPROM-памяти, также поддерживается не полный список команд.

Для того, чтобы собрать и запустить эмулятор нужно:
    1. перейти в директорию /testing
    2. написать программу на ассемблере в файле testing.asm
    3. ввести команду в командной строке "make"
    4. перейти в директорию /resources.
    5. ввести в командной строке команду "cmake ."
    6. ввести команду "make"
    7. ввести команду "./Attiny ../testing/testing.hex"
    Начнется выполнение эмулятора с выводом выполненных команд. Для того, чтобы прервать выполнение эмулятора в командной строке нажмите сочетание клавишь "Ctrl + C".


Список реализованных команд:

nop
adc - sum with carry
add - sum
inc - increment
sub - sub between registers
sbc - sub between registers with carry
subi - sub between register and const
sbci - sub between registers and const with carry
ldi - Load Immediate
mov - Move Between Registers
sbi - Set Bit in I/O Register
cp - Сompare Register with Register
cpi - Compare Register with Immediate
sec - set carry flag
sen - set negative flag
sez - set zero flag
sei - global interrapt enable
ses - set signed test fag
sev - set two’s complement overflow
set - set T in SREG
seh - set half carry flag
rjmp - Relative Jump