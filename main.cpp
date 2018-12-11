/* SDT-example-pwm-robotArm
 *
 * Copyright (c) 2018 Sigma Delta Technologies Inc.
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

 #include "mbed.h"

/* Serial */
Serial serial_pc(USBTX, USBRX, 9600);

/* Servo motor */
PwmOut pwmOut_servo0(PWM0);    // GPIO2
PwmOut pwmOut_servo1(PWM1);    // GPIO3
PwmOut pwmOut_servo2(PWM2);    // GPIO0
PwmOut pwmOut_servo3(PWM3);    // GPIO1
PwmOut* pPwmOut_servo = &pwmOut_servo2;

float duty = 0.100;
bool flag = false;

int main(void) {
    serial_pc.printf("< Sigma Delta Technologies Inc. >\n\r");

    /* Servo motor 주기 설정 */
    pwmOut_servo0.period_ms(20);    // 주기는 20ms로 설정
    pwmOut_servo1.period_ms(20);
    pwmOut_servo2.period_ms(20);
    pwmOut_servo3.period_ms(20);

    /* Servo motor 초기 각도 설정 */
    pwmOut_servo0.write(0.100);    // write()에 들어가는 값의 단위는 배수다
    pwmOut_servo1.write(0.100);    // 0.050 ~ 0.100 사이의 값만 가능
    pwmOut_servo2.write(0.100);
    pwmOut_servo3.write(0.100);
    wait(2);

    while(true) {
        pPwmOut_servo->write(duty);

        if(flag) {
            duty = duty + 0.001f;
            if(duty >= 0.100) {
                flag = false;
            }
        }
        else {
            duty = duty - 0.001f;
            if(duty <= 0.050) {
                flag = true;
            }
        }
        
        wait_ms(150);
    }
}
