/**
 * MIT License
 *
 * Copyright (c) 2023 Dora Ltd
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

#pragma once

#include <driver/gpio.h>
#include <esp_log.h>

class MuxHC4067 {
public:
    MuxHC4067(gpio_num_t s0, gpio_num_t s1, gpio_num_t s2, gpio_num_t s3, gpio_num_t sig, gpio_num_t en = GPIO_NUM_NC);
    ~MuxHC4067();

    bool get(int channel);
    void set(int channel, bool state);

    void enable();
    void disable();

private:
    void selectChannel(int channel);

    gpio_num_t s0, s1, s2, s3;
    gpio_num_t sig, en;

    bool enable_status = false;
};