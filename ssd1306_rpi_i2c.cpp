#include "ssd1306_rpi_i2c.h"
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <unistd.h>
#include <bitset>
#include <algorithm>
#include <iostream>
#include "symbols_set.h"

namespace ssd1306_rpi {

SSD1306_RPI_I2C::SSD1306_RPI_I2C():fd_i2c(0), addressI2C(0x3C), draw_mode_(Draw_Mode::Draw_immediately)
{

}

SSD1306_RPI_I2C::~SSD1306_RPI_I2C()
{
    close_i2c();
}

bool SSD1306_RPI_I2C::open_i2c(std::string_view device_name, uint8_t address_i2c)
{
    bool result=false;
    device_name_i2c = device_name;
    addressI2C = address_i2c;

    if ((fd_i2c = open(device_name_i2c.c_str(), O_RDWR)) < 0)
    {
        perror("error opening I2C\n");
    }
    else
    {
        if (ioctl(fd_i2c, I2C_SLAVE, addressI2C) < 0)
        {
            perror("Error at ioctl\n");
        }
        else
        {
            result=true;
        }
    }
    return result;
}

void SSD1306_RPI_I2C::close_i2c()
{
    if(fd_i2c > 0)
    {
        close(fd_i2c);
    }
}

void SSD1306_RPI_I2C::display()
{
    update();
    clear();
}

void SSD1306_RPI_I2C::set_draw_mode(Draw_Mode mode)
{
    draw_mode_ = mode;
}

void SSD1306_RPI_I2C::clear()
{
    clear_buffer();
    clear_display_lines();
}

void SSD1306_RPI_I2C::draw_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
    if(x1 == x2 && y1 == y2)
    {
        lcd_display[y1][x1]=1;
    }
    else
    {
//        // соединить две точки (Алгоритм Брезенхайма) https://ru.wikibooks.org/wiki/Реализации_алгоритмов/Алгоритм_Брезенхэма#Реализация_на_C++
//        const int deltaX = abs(x2 - x1);
//        const int deltaY = abs(y2 - y1);
//        const int signX = x1 < x2 ? 1 : -1;
//        const int signY = y1 < y2 ? 1 : -1;
//        //
//        int error = deltaX - deltaY;
//        //
//        lcd_display[y2][x2] = 1;

//        while(x1 != x2 || y1 != y2)
//        {
//            lcd_display[y1][x1] = 1;
//            const int error2 = error * 2;
//            //
//            if(error2 > -deltaY)
//            {
//                error -= deltaY;
//                x1 += signX;
//            }
//            if(error2 < deltaX)
//            {
//                error += deltaX;
//                y1 += signY;
//            }
//        }
        draw_line_(x1, y1, x2, y2);
    }
    lcd_display_to_display_lines();
    if(draw_mode_== Draw_Mode::Draw_immediately)
    {
        display();
    }
}

void SSD1306_RPI_I2C::draw_circle(uint8_t x_center, uint8_t y_center, uint8_t radius)
{
    if(radius<1)
        return;

    // Рисование круга. Алгоритм Брезенхайма. https://ciplusplussnachala.wordpress.com/2012/08/17/c-для-начинающих-рисование-окружности/

    int8_t x1,y1,yk = 0;
    int8_t sigma,delta,f;

    x1 = 0;
    y1 = radius;
    delta = 2*(1-radius);

    do
    {
        lcd_display[y_center+y1][x_center+x1]=1;
        lcd_display[y_center+y1][x_center-x1]=1;
        lcd_display[y_center-y1][x_center+x1]=1;
        lcd_display[y_center-y1][x_center-x1]=1;

        f = 0;
        if (y1 < yk)
            break;
        if (delta < 0)
        {
            sigma = 2*(delta+y1)-1;
            if (sigma <= 0)
            {
                x1++;
                delta += 2*x1+1;
                f = 1;
            }
        }
        else
            if (delta > 0)
            {
                sigma = 2*(delta-x1)-1;
                if (sigma > 0)
                {
                    y1--;
                    delta += 1-2*y1;
                    f = 1;
                }
            }
        if (!f)
        {
            x1++;
            y1--;
            delta += 2*(x1-y1-1);
        }
    }
    while(1);

    lcd_display_to_display_lines();
    if(draw_mode_ == Draw_Mode::Draw_immediately)
    {
        display();
    }
}

void SSD1306_RPI_I2C::draw_rect(uint8_t left, uint8_t top, uint8_t right, uint8_t bottom)
{
    if(left==right && top==bottom)
        return;
    draw_line_(left, top, right, top);
    draw_line_(left, top, left, bottom);
    draw_line_(right, top, right, bottom);
    draw_line_(left, bottom, right, bottom);
    lcd_display_to_display_lines();
    if(draw_mode_ == Draw_Mode::Draw_immediately)
    {
        display();
    }
}

void SSD1306_RPI_I2C::draw_point(uint8_t x, uint8_t y)
{
    if(x > DISPLAY_COLS || y > DISPLAY_ROWS)
    {
        std::cout << "Unsupported coordinates: x=" << x << " y=" << y << std::endl;
        return;
    }

    lcd_display[y][x] = 1;
    lcd_display_to_display_lines();
    if(draw_mode_ == Draw_Mode::Draw_immediately)
    {
        display();
    }

}

void SSD1306_RPI_I2C::draw_text(std::string_view text, uint8_t x_begin, uint8_t y_begin)
{
    if(x_begin > DISPLAY_COLS || y_begin > DISPLAY_ROWS)
        return;
    uint16_t counter=0;
    uint16_t sum_x_counter=x_begin;
    for(const auto &c : text)
    {
        if(sum_x_counter >=DISPLAY_COLS)
        {
            break;
        }
        uint8_t ascii_code_symbol = static_cast<uint8_t>(c);
        auto it_vec_bytes=symbols.find(ascii_code_symbol);
        if(it_vec_bytes != symbols.end())
        {
            for(const auto el : it_vec_bytes->second)
            {
                if(sum_x_counter >=DISPLAY_COLS)
                {
                    break;
                }
                std::bitset<8> bset(el);
                for(uint8_t i=0; i<bset.size(); ++i)
                {
                    lcd_display[y_begin+i][x_begin+counter] = bset.test(i);
                }
                ++counter;
                sum_x_counter=x_begin+counter;
            }
        }
        //добавим пробел
        lcd_display[y_begin][x_begin+counter] = 0x00;
        ++counter;
        sum_x_counter=x_begin+counter;
    }
    lcd_display_to_display_lines();
    if(draw_mode_ == Draw_Mode::Draw_immediately)
    {
        display();
    }
}

void SSD1306_RPI_I2C::set_contrast(uint8_t value)
{
    if(value <= 0xFF)
    {
        unsigned char cmd[3];
        cmd[0] = 0x1;
        cmd[1] = 0x81;
        cmd[2] = value;
        write_to_i2c(cmd, std::size(cmd));
    }
}

void SSD1306_RPI_I2C::write_to_i2c(const unsigned char *data, size_t length)
{
    if(fd_i2c>0)
        write(fd_i2c, data, length);
}

void SSD1306_RPI_I2C::init_display()
{
    write_to_i2c(initSequence, std::size(initSequence));
}

void SSD1306_RPI_I2C::inverse_display(bool inverse)
{
    unsigned char cmd[3];
    unsigned char c=inverse ? 0xA7 : 0xA6;
    cmd[0] = 0x1;
    cmd[1] = c;
    cmd[2] = c;
    write_to_i2c(cmd, std::size(cmd));
}

void SSD1306_RPI_I2C::update()
{
    for(uint8_t line=0; line<8; line++)
    {
        unsigned char buffer[129] = {0};
        buffer[0] = 0x40;
        for(uint8_t i=0; i<128; i++)
        {
            buffer[1 + i] = displayLines[line][i];
        }
        write_to_i2c(buffer, 129);
    }
}

void SSD1306_RPI_I2C::clear_display_lines()
{
    for(auto &el : displayLines)
    {
        std::fill(std::begin(el), std::end(el), 0);
    }
}

void SSD1306_RPI_I2C::clear_buffer()
{
    for(auto &el : lcd_display)
    {
        std::fill(std::begin(el), std::end(el), 0);
    }
}

void SSD1306_RPI_I2C::lcd_display_to_display_lines()
{
    for(uint8_t k=0; k<DISPLAY_COLS; ++k) //128
    {
        for(uint8_t j=0; j<DISPLAY_ROWS; j+=8) //64
        {
            std::bitset<8> l={0};

            for(uint8_t i=j, bit_cntr=0; i<j+8, bit_cntr<8; ++i, ++bit_cntr)
            {
                l[bit_cntr] = lcd_display[i][k];
            }
            uint8_t idx_y=j/8;
            displayLines[idx_y][k] = static_cast<unsigned char>(l.to_ulong());
        }
    }
}

void SSD1306_RPI_I2C::draw_line_(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{

    // соединить две точки (Алгоритм Брезенхайма) https://ru.wikibooks.org/wiki/Реализации_алгоритмов/Алгоритм_Брезенхэма#Реализация_на_C++
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    //
    int error = deltaX - deltaY;
    //
    lcd_display[y2][x2] = 1;

    while(x1 != x2 || y1 != y2)
    {
        lcd_display[y1][x1] = 1;
        const int error2 = error * 2;
        //
        if(error2 > -deltaY)
        {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX)
        {
            error += deltaX;
            y1 += signY;
        }
    }
}

} // namespace ssd1306_rpi
