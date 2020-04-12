#include <iostream>
#include "ssd1306_rpi_i2c.h"
#include <thread>

int main(int argc, char *argv[])
{
    static_cast<void>(argc);
    static_cast<void>(argv);
    ssd1306_rpi::SSD1306_RPI_I2C oled;
    if(oled.open_i2c("/dev/i2c-1", 0x3C))
    {
        std::cout << "OLED i2C opened!" << std::endl;
        oled.init_display();
        //oled.draw_text("W#12", 23,16);
        //oled.draw_line(10,12,25,12);
    }
    oled.set_draw_mode(ssd1306_rpi::Draw_Mode::On_call_display);
    oled.draw_text("Hello-world", 10,10);
    //oled.draw_text("Hello", 30,20);
    oled.display();
    oled.inverse_display(true);
    //oled.scroll_right();


//    bool inv=true;
//    for(;;)
//    {
//        oled.inverse_display(inv);
//        inv = !inv;
//        std::this_thread::sleep_for(std::chrono::milliseconds(100));
//    }



//    for(uint i=0; i<50; ++i)
//    {
//        std::string str("Temp=");
//        str.append(std::to_string(i));
//        oled.draw_text(str, 20, 32);
//        oled.draw_line(5, i, 100,i);
//        oled.display();
//        std::this_thread::sleep_for(std::chrono::milliseconds(50));
//    }


//    oled.draw_text("ABBBBBCCCCC", 20, 20);
//    oled.display();
//    uint16_t contrast=0;
//    bool up=true;
//    for(;;)
//    {
//        if(up)
//        {
//            ++contrast;
//            if(contrast>=0x7F)
//                up=false;
//        }
//        else
//        {
//            --contrast;
//            if(contrast==0)
//                up=true;
//        }
//        std::cout << "contrast: " << contrast << std::endl;
//        oled.set_contrast(contrast);
//        std::this_thread::sleep_for(std::chrono::milliseconds(10));
//    }

    return 0;
}
