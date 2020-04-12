#ifndef LETTERS_SET_H
#define LETTERS_SET_H
#include <unordered_map>
#include <vector>
#include <unistd.h>


/**
  Набор параметров для отрисовки символов. Ключ - ASCII-код символа, значение - набор байт, для представления символа.
*/
std::unordered_map<uint16_t, std::vector<uint16_t>> symbols =
{
    std::make_pair(32, std::vector<uint16_t>({0x00, 0x00})), // Пробел
    std::make_pair(33, std::vector<uint16_t>({0x5E})), // !
    std::make_pair(34, std::vector<uint16_t>({0x02,0x00,0x02})), // "
    std::make_pair(35, std::vector<uint16_t>({0x24,0x7E,0x24,0x7E,0x24})), // #
    std::make_pair(36, std::vector<uint16_t>({0x44,0x4A,0x7E,0x52,0x22})), // $
    std::make_pair(37, std::vector<uint16_t>({0x22,0x10,0x08,0x04,0x42})), // %
    std::make_pair(38, std::vector<uint16_t>({0x34,0x4A,0x54,0x20,0x40})), // &
    std::make_pair(39, std::vector<uint16_t>({0x02})), // '
    std::make_pair(40, std::vector<uint16_t>({0x18,0x24,0x42})), // (
    std::make_pair(41, std::vector<uint16_t>({0x42,0x24,0x18})), // )
    std::make_pair(42, std::vector<uint16_t>({0x54,0x38,0x7C,0x38,0x54})), // *
    std::make_pair(43, std::vector<uint16_t>({0x08,0x08,0x7E,0x08,0x08})), // +
    std::make_pair(44, std::vector<uint16_t>({0x40,0x20})), // ,
    std::make_pair(45, std::vector<uint16_t>({0x08,0x08,0x08})), // -
    std::make_pair(46, std::vector<uint16_t>({0x40})), // .
    std::make_pair(47, std::vector<uint16_t>({0x60,0x10,0x08,0x06})), // /
    std::make_pair(48, std::vector<uint16_t>({0x7E,0x52,0x4A,0x7E})), // 0
    std::make_pair(49, std::vector<uint16_t>({0x44,0x7E,0x40})), // 1
    std::make_pair(50, std::vector<uint16_t>({0x64,0x52,0x4A,0x44})), // 2
    std::make_pair(51, std::vector<uint16_t>({0x42,0x4A,0x34})), // 3
    std::make_pair(52, std::vector<uint16_t>({0x18,0x14,0x7E,0x10})), // 4
    std::make_pair(53, std::vector<uint16_t>({0x4E,0x4A,0x32})), // 5
    std::make_pair(54, std::vector<uint16_t>({0x3C,0x4A,0x4A,0x32})), // 6
    std::make_pair(55, std::vector<uint16_t>({0x6E,0x1A,0x06})), // 7
    std::make_pair(56, std::vector<uint16_t>({0x34,0x4A,0x4A,0x34})), // 8
    std::make_pair(57, std::vector<uint16_t>({0x4C,0x52,0x56,0x3C})), // 9
    std::make_pair(58, std::vector<uint16_t>({0x14})), // :
    std::make_pair(59, std::vector<uint16_t>({0x20,0x14})), // ; ----посмотреть как выглядит, может перерисовать
    std::make_pair(60, std::vector<uint16_t>({0x10,0x28,0x44})), // <
    std::make_pair(61, std::vector<uint16_t>({0x28,0x28,0x28})), // =
    std::make_pair(62, std::vector<uint16_t>({0x44,0x28,0x10})), // >
    std::make_pair(63, std::vector<uint16_t>({0x02,0x5A,0x04})), // ?
    std::make_pair(64, std::vector<uint16_t>({0x7E,0x42,0x5A,0x52,0x5E})), // @
    std::make_pair(65, std::vector<uint16_t>({0x7E,0x12,0x12,0x7E})), // A
    std::make_pair(66, std::vector<uint16_t>({0x7E,0x4a,0x4a,0x34})), // B
    std::make_pair(67, std::vector<uint16_t>({0x7e,0x42,0x42,0x42})), // C
    std::make_pair(68, std::vector<uint16_t>({0x7E,0x42,0x42,0x3C})), // D
    std::make_pair(69, std::vector<uint16_t>({0x7E,0x52,0x52,0x42})), // E
    std::make_pair(70, std::vector<uint16_t>({0x7E,0x12,0x12,0x02})), // F
    std::make_pair(71, std::vector<uint16_t>({0x7E,0x42,0x42,0x72})), // G
    std::make_pair(72, std::vector<uint16_t>({0x7E,0x10,0x10,0x7E})), // H
    std::make_pair(73, std::vector<uint16_t>({0x42,0x7E,0x42,0x00})), // I
    std::make_pair(74, std::vector<uint16_t>({0x62,0x42,0x7E,0x02})), // J
    std::make_pair(75, std::vector<uint16_t>({0x7E,0x18,0x24,0x42})), // K
    std::make_pair(76, std::vector<uint16_t>({0x7E,0x40,0x40,0x40})), // L
    std::make_pair(77, std::vector<uint16_t>({0x7E,0x04,0x04,0x7E})), // M
    std::make_pair(78, std::vector<uint16_t>({0x7E,0x0C,0x30,0x7E})), // N
    std::make_pair(79, std::vector<uint16_t>({0x7E,0x42,0x42,0x7E})), // O
    std::make_pair(80, std::vector<uint16_t>({0x7E,0x12,0x12,0x1E})), // P
    std::make_pair(81, std::vector<uint16_t>({0x7E,0x42,0x4A,0x7E})), // Q
    std::make_pair(82, std::vector<uint16_t>({0x7E,0x12,0x32,0x6E})), // R
    std::make_pair(83, std::vector<uint16_t>({0x4E,0x4A,0x4A,0x72})), // S
    std::make_pair(84, std::vector<uint16_t>({0x02,0x7E,0x02,0x02})), // T
    std::make_pair(85, std::vector<uint16_t>({0x7E,0x40,0x40,0x7E})), // U
    std::make_pair(86, std::vector<uint16_t>({0x3E,0x60,0x60,0x3E})), // V
    std::make_pair(87, std::vector<uint16_t>({0x7E,0x20,0x20,0x7E})), // W
    std::make_pair(88, std::vector<uint16_t>({0x66,0x3C,0x3C,0x66})), // X
    std::make_pair(89, std::vector<uint16_t>({0x1E,0x10,0x10,0x7E})), // Y
    std::make_pair(90, std::vector<uint16_t>({0x62,0x52,0x4C,0x46})), // Z
    std::make_pair(91, std::vector<uint16_t>({0x7E,0x42})), // [
    std::make_pair(93, std::vector<uint16_t>({0x42,0x7E})), // ]

    std::make_pair(97, std::vector<uint16_t>({0x64, 0x54, 0x54, 0x78})), // a
    std::make_pair(98, std::vector<uint16_t>({0x7E, 0x48, 0x48, 0x70})), // b
    std::make_pair(99, std::vector<uint16_t>({0x3C, 0x42, 0x42, 0x24})), // c
    std::make_pair(100, std::vector<uint16_t>({0x70, 0x48, 0x48, 0x7E})), // d
    std::make_pair(101, std::vector<uint16_t>({0x3C, 0x52, 0x52, 0x5C})), // e
    std::make_pair(102, std::vector<uint16_t>({0x10, 0x7E, 0x12, 0x04})), // f
    std::make_pair(103, std::vector<uint16_t>({0x4C, 0x52, 0x52, 0x3C})), // g
    std::make_pair(104, std::vector<uint16_t>({0x7E, 0x08, 0x08, 0x70})), // h
    std::make_pair(105, std::vector<uint16_t>({0x00, 0x7A, 0x00, 0x00})), // i
    std::make_pair(106, std::vector<uint16_t>({0x40, 0x40, 0x1D, 0x00})), // j
    std::make_pair(107, std::vector<uint16_t>({0x7E, 0x30, 0x48, 0x00})), // k
    std::make_pair(108, std::vector<uint16_t>({0x00, 0x3E, 0x40, 0x40})), // l
    std::make_pair(109, std::vector<uint16_t>({0x78, 0x08, 0x70, 0x08, 0x08, 0x70})), // m
    std::make_pair(110, std::vector<uint16_t>({0x78, 0x08, 0x08, 0x70})), // n
    std::make_pair(111, std::vector<uint16_t>({0x30, 0x48, 0x48, 0x30})), // o
    std::make_pair(112, std::vector<uint16_t>({0x7C, 0x14, 0x14, 0x18})), // p
    std::make_pair(113, std::vector<uint16_t>({0x00, 0x18, 0x14, 0x7C})), // q
    std::make_pair(114, std::vector<uint16_t>({0x78, 0x10, 0x08, 0x08})), // r
    std::make_pair(115, std::vector<uint16_t>({0x40, 0x58, 0x68, 0x08})), // s
    std::make_pair(116, std::vector<uint16_t>({0x10, 0x78, 0x50, 0x00})), // t
    std::make_pair(117, std::vector<uint16_t>({0x78, 0x40, 0x78, 0x00})), // u
    std::make_pair(118, std::vector<uint16_t>({0x38, 0x40, 0x38, 0x00})), // v
    std::make_pair(119, std::vector<uint16_t>({0x38, 0x40, 0x30, 0x30, 0x40, 0x38})), // w
    std::make_pair(120, std::vector<uint16_t>({0x48, 0x30, 0x30, 0x48})), // x
    std::make_pair(121, std::vector<uint16_t>({0x00, 0x5C, 0x50, 0x3C})), // y
    std::make_pair(122, std::vector<uint16_t>({0x48, 0x68, 0x58, 0x48})), // z
    std::make_pair(123, std::vector<uint16_t>({0x18, 0x7E, 0x42, 0x00})), // {
    std::make_pair(124, std::vector<uint16_t>({0x00, 0x7E, 0x00, 0x00})), // |
    std::make_pair(125, std::vector<uint16_t>({0x00, 0x42, 0x7E, 0x18})), // }



};


#endif
