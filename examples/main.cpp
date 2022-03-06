#include <iostream>
#include "../ssd1306_rpi_i2c.h"
#include <thread>

void example_text()
{
    std::cout << "Running example_text..." << std::endl;
    ssd1306_rpi::SSD1306_RPI_I2C oled;
    if(oled.open_i2c("/dev/i2c-1", 0x3C))
    {
        std::cout << "OLED i2C opened!" << std::endl;
        oled.init_display();
        oled.set_draw_mode(ssd1306_rpi::Draw_Mode::On_call_display);
        oled.draw_text("Hello, world!", 20,20);
        oled.draw_text("Hello, world!", 30,30);
        oled.draw_text("Hello, world!", 100,50);
        oled.display();
    }
}

void example_circle()
{
    std::cout << "Running example_circle..." << std::endl;
    ssd1306_rpi::SSD1306_RPI_I2C oled;
    if(oled.open_i2c("/dev/i2c-1", 0x3C))
    {
        std::cout << "OLED i2C opened!" << std::endl;
        oled.init_display();
        oled.set_draw_mode(ssd1306_rpi::Draw_Mode::On_call_display);
        oled.draw_circle(30, 30, 20);
        oled.draw_circle(50, 30, 20);
        oled.draw_circle(100, 30, 10);
        oled.display();
    }
}

void example_move_text_line_circle()
{
    std::cout << "Running example_move_text_line_circle..." << std::endl;
    ssd1306_rpi::SSD1306_RPI_I2C oled;
    if(oled.open_i2c("/dev/i2c-1", 0x3C))
    {
        std::cout << "OLED i2C opened!" << std::endl;
        oled.init_display();
        oled.set_draw_mode(ssd1306_rpi::Draw_Mode::On_call_display);

        static uint16_t j=0;
        for(j; j<30; ++j)
        {
            std::string str("Counter down=");
            str.append(std::to_string(j));
            oled.draw_text(str, 15, 30);
            oled.draw_line(5, j, 80,j);
            oled.draw_circle(100, 5+j, 5);
            oled.display();
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

        if(j>=30)
        {
            for(j; j>0; --j)
            {
                std::string str("Counter up=");
                str.append(std::to_string(j));
                oled.draw_text(str, 15, 30);
                oled.draw_line(5, j, 80,j);
                oled.draw_circle(100, 5+j, 5);
                oled.display();
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
        }
    }
}

void example_contrast()
{
    std::cout << "Running example_contrast..." << std::endl;
    ssd1306_rpi::SSD1306_RPI_I2C oled;
    if(oled.open_i2c("/dev/i2c-1", 0x3C))
    {
        std::cout << "OLED i2C opened!" << std::endl;
        oled.init_display();
        oled.set_draw_mode(ssd1306_rpi::Draw_Mode::On_call_display);

        oled.draw_text("ABBBBBCCCCC", 20, 20);
        oled.display();
        uint16_t contrast=0;
        bool up=true;
        for(uint16_t i=0; i<1024; ++i)
        {
            if(up)
            {
                ++contrast;
                if(contrast>=0x7F)
                    up=false;
            }
            else
            {
                --contrast;
                if(contrast==0)
                    up=true;
            }
            oled.set_contrast(contrast);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
}

void example_inverse_draw()
{
    std::cout << "Running example_inverse_draw..." << std::endl;
    ssd1306_rpi::SSD1306_RPI_I2C oled;
    if(oled.open_i2c("/dev/i2c-1", 0x3C))
    {
        std::cout << "OLED i2C opened!" << std::endl;
        oled.init_display();
        oled.set_draw_mode(ssd1306_rpi::Draw_Mode::On_call_display);
        oled.draw_text("Hello, world!", 20,20);
        oled.draw_text("Hello, world!", 30,30);
        oled.draw_rect(30,40,50,60);
        oled.display();
        oled.inverse_display(true);
        std::this_thread::sleep_for(std::chrono::seconds(4));
        oled.inverse_display(false);
    }
}

void example_points()
{
    std::cout << "Running example_points..." << std::endl;
    ssd1306_rpi::SSD1306_RPI_I2C oled;
    if(oled.open_i2c("/dev/i2c-1", 0x3C))
    {
        std::cout << "OLED i2C opened!" << std::endl;
        oled.init_display();
        oled.set_draw_mode(ssd1306_rpi::Draw_Mode::On_call_display);
        oled.draw_point(10,10);
        oled.draw_point(20,20);
        oled.draw_point(64,32);
        oled.display();
    }
}

void help()
{
    std::cout << "Send to example soft value from 0 to 5 for choose example:" << std::endl;
    std::cout << "0 - example_text" << std::endl;
    std::cout << "1 - example_circle" << std::endl;
    std::cout << "2 - example_move_text_line_circle" << std::endl;
    std::cout << "3 - example_contrast" << std::endl;
    std::cout << "4 - example_inverse_draw" << std::endl;
    std::cout << "5 - example_points" << std::endl;
}

int main(int argc, char *argv[])
{
    if(argc<2)
    {
        help();
        return 0;
    }

    uint8_t num=0;
    try
    {
        num = std::stoi(argv[1]);
        switch(num)
        {
            case 0:
            {
                example_text();
                break;
            }
            case 1:
            {
                example_circle();
                break;
            }
            case 2:
            {
                example_move_text_line_circle();
                break;
            }
            case 3:
            {
                example_contrast();
                break;
            }
            case 4:
            {
                example_inverse_draw();
                break;
            }
            case 5:
            {
                example_points();
                break;
            }
            default:
            {
                help();
            }
        }
    }
    catch (std::exception &e)
    {
        std::cout << "Unsupported symbol" << std::endl;
        help();
    }

    return 0;
}
