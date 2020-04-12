#ifndef SSD1306_RPI_I2C_H
#define SSD1306_RPI_I2C_H
#include <string_view>
#include <string>

namespace ssd1306_rpi {

constexpr uint8_t DISPLAY_ROWS=64;
constexpr uint8_t DISPLAY_COLS=128;

/**
 * @brief The Draw_Mode enum - режим отрисовки
 */
enum class Draw_Mode : uint8_t
{
    Draw_immediately=0, ///< Отрисовывать немедленно (установлен по умолчанию)
    On_call_display ///< Отрисовывать только по вызову метода display()
};

/**
 * @brief The SSD1306_RPI_I2C class - класс для взаимодействия с OLED-дисплеем на базе контроллера SSD1306.
 */
class SSD1306_RPI_I2C
{
public:

    SSD1306_RPI_I2C();
    ~SSD1306_RPI_I2C();

    bool open_i2c(std::string_view device_name, uint8_t address_i2c);
    void close_i2c();
    void display();
    void set_draw_mode(Draw_Mode mode);
    void clear();

    void draw_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
    void draw_circle(uint8_t x_center, uint8_t y_center, uint8_t radius);
    void draw_rect(uint8_t left, uint8_t top, uint8_t right, uint8_t bottom);
    void draw_point(uint8_t x, uint8_t y);

    /**
     * @brief draw_text - отображает текст на дисплее в заданных координатах.
     * @param text - текст для отображения
     * @param x_begin - x-координата начала текста
     * @param y_begin - y-координата начала текста
     * @note Ноль координат располагается в левом верхнем углу. Координата y считается по верхнему краю текста.
     */
    void draw_text(std::string_view text, uint8_t x_begin, uint8_t y_begin);
    void set_contrast(uint8_t value);
    void init_display();

    void inverse_display(bool inverse);

private:
    int fd_i2c;
    uint8_t addressI2C;
    std::string device_name_i2c;
    unsigned char initSequence[26] = {0x00,0xAE,0xA8,0x3F,0xD3,0x00,0x40,0xA1,0xC8,0xDA,0x12,0x81,0x7F,0xA4,0xA6,0xD5,0x80,0x8D,0x14,0xD9,0x22,0xD8,0x30,0x20,0x00,0xAF};
    unsigned char setFullRange[7] = {0x00,0x21,0x00,0x7F,0x22,0x00,0x07};
    unsigned char displayLines[8][128]={{0}};
    unsigned char lcd_display[DISPLAY_ROWS][DISPLAY_COLS]={{0}};
    Draw_Mode draw_mode_;

    void write_to_i2c(const unsigned char *data, size_t length);
    void update();
    void clear_display_lines();
    void clear_buffer();
    void lcd_display_to_display_lines();
    void draw_line_(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
};


}


#endif
