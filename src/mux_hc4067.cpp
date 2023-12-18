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

#include "mux_hc4067.hpp"

#include <driver/gpio.h>
#include <inttypes.h>

/**
 * @brief Construct a new MuxHC4067
 *
 * @param s0 Select pin 0
 * @param s1 Select pin 1
 * @param s2 Select pin 2
 * @param s3 Select pin 3
 * @param sig SIG pin
 * @param en Enable pin
 */
MuxHC4067::MuxHC4067(gpio_num_t s0, gpio_num_t s1, gpio_num_t s2, gpio_num_t s3, gpio_num_t sig, gpio_num_t en)
    : s0(s0), s1(s1), s2(s2), s3(s3), sig(sig), en(en)
{
    gpio_reset_pin(this->s0);
    gpio_reset_pin(this->s1);
    gpio_reset_pin(this->s2);
    gpio_reset_pin(this->s3);
    gpio_reset_pin(this->sig);

    gpio_set_direction(this->s0, GPIO_MODE_OUTPUT);
    gpio_set_direction(this->s1, GPIO_MODE_OUTPUT);
    gpio_set_direction(this->s2, GPIO_MODE_OUTPUT);
    gpio_set_direction(this->s3, GPIO_MODE_OUTPUT);
    gpio_set_direction(this->sig, GPIO_MODE_INPUT_OUTPUT);

    gpio_set_level(this->s0, 0);
    gpio_set_level(this->s1, 0);
    gpio_set_level(this->s2, 0);
    gpio_set_level(this->s3, 0);

    if (this->en != GPIO_NUM_NC)
    {
        gpio_set_direction(this->en, GPIO_MODE_OUTPUT);
        this->disable();
    }
}

/**
 * @brief Destroy the MuxHC4067
 */
MuxHC4067::~MuxHC4067()
{
    gpio_set_direction(this->s0, GPIO_MODE_DISABLE);
    gpio_set_direction(this->s1, GPIO_MODE_DISABLE);
    gpio_set_direction(this->s2, GPIO_MODE_DISABLE);
    gpio_set_direction(this->s3, GPIO_MODE_DISABLE);
    gpio_set_direction(this->sig, GPIO_MODE_DISABLE);
}

/**
 * @brief Select channel
 *
 * @param channel Channel num
 */
void MuxHC4067::selectChannel(int channel)
{
    this->disable();

    uint8_t mask = 0x08;
    uint8_t i = 3;

    gpio_num_t select_pins[] = {
        this->s0,
        this->s1,
        this->s2,
        this->s3
    };

    while (mask)
    {
        gpio_num_t pin = select_pins[i--];
        gpio_set_level(pin, !!(mask & (channel & 0x0F)));
        mask >>= 1;
    }

    this->enable();
}

/**
 * @brief Enables the connection of the SIG pin with a channel that was set earlier
 */
void MuxHC4067::enable()
{
    if (this->en != GPIO_NUM_NC)
    {
        this->enable_status = true;
        gpio_set_level(this->en, 0);
    }
}

/**
 * @brief Disables the connection of the SIG pin with a channel that was set earlier
 */
void MuxHC4067::disable()
{
    if (this->en != GPIO_NUM_NC)
    {
        this->enable_status = false;
        gpio_set_level(this->en, 1);
    }
}

/**
 * @brief Get channel level
 *
 * @param channel Channel num
 * @return true
 * @return false
 */
bool MuxHC4067::get(int channel)
{
    this->selectChannel(channel);
    return gpio_get_level(this->sig);
}

/**
 * @brief Set state in channel
 *
 * @param channel Channel num
 * @param state State
 */
void MuxHC4067::set(int channel, bool state)
{
    this->selectChannel(channel);
    gpio_set_level(this->sig, state);
}
