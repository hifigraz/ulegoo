#pragma once

void setup_ulegoo();
unsigned long millis();
unsigned long micros();
void delay(unsigned long to_wait);

void left_forward();
void left_backward();
void left_stop();
void left_enable();
void left_disable();

void right_forward();
void right_backward();
void right_stop();
void right_enable();
void right_disable();

void move_forward();
void move_backward();
void turn_right();
void turn_left();
void rotate_right();
void rotate_left();
void enable();
void disable();

void stop();

struct MILLIS_MICROS {
  unsigned long micros = 0;
  unsigned long last_millis_update = 0;
  unsigned long millis = 0;
};
