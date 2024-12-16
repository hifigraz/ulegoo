#include "include/ulegoo.hpp"

#include <avr/interrupt.h>
#include <avr/io.h>

MILLIS_MICROS millis_micros_struct;

void left_forward() {
  PORTD |= _BV(PORTD7);
  PORTB &= ~_BV(PORTB0);
}
void left_backward() {
  PORTD &= ~_BV(PORTD7);
  PORTB |= _BV(PORTB0);
}
void left_stop() {
  PORTD &= ~_BV(PORTD7);
  PORTB &= ~_BV(PORTB0);
}
void left_enable() { PORTD |= _BV(PORTD5); }

void left_disable() { PORTD &= ~_BV(PORTD5); }

void right_forward() {
  // define R_EN PORTD6
  // define R_I0 PORTB1
  // define R_I1 PORTB3
  PORTB &= ~_BV(PORTB1);
  PORTB |= _BV(PORTB3);
}

void right_backward() {
  PORTB |= _BV(PORTB1);
  PORTB &= ~_BV(PORTB3);
}

void right_stop() {
  PORTB &= ~_BV(PORTB1);
  PORTB &= ~_BV(PORTB3);
}

void right_enable() { PORTD |= _BV(PORTD6); }

void right_disable() { PORTD &= ~_BV(PORTD6); }

void move_forward() {
  left_forward();
  right_forward();
}

void move_backward() {
  left_backward();
  right_backward();
}

void turn_right() {
  left_forward();
  right_stop();
}

void turn_left() {
  right_forward();
  left_stop();
}

void rotate_right() {
  left_forward();
  right_backward();
}

void rotate_left() {
  left_backward();
  right_forward();
}

void stop() {
  left_stop();
  right_stop();
}

void enable() {
  left_enable();
  right_enable();
}

void disable() {
  left_disable();
  right_disable();
}

void setup_ulegoo() {
  DDRD |= _BV(DDD5) | _BV(DDD6) | _BV(DDD7);
  DDRB |= _BV(DDB0) | _BV(DDB1) | _BV(DDB3);
  PORTD &= ~(_BV(DDD5) | _BV(DDD6) | _BV(DDD7));
  PORTB &= ~(_BV(DDB0) | _BV(DDB1) | _BV(DDB3));

  cli();
  TCCR0A = 0;
  TCCR0B = _BV(CS00);
  TCNT0 = 0;
  TIMSK0 = _BV(TOIE0);
  sei();
}

unsigned long millis() {
  cli();
  unsigned long tmp = millis_micros_struct.millis;
  sei();
  return tmp;
}

unsigned long micros() {
  cli();
  unsigned long tmp = millis_micros_struct.micros;
  sei();
  return tmp;
}

void delay(unsigned long to_wait) {
  unsigned long millis_start = millis();
  while (millis() - millis_start < to_wait) {
  }
}

ISR(TIMER0_OVF_vect) {
  millis_micros_struct.micros += 16;
  if ((millis_micros_struct.micros - millis_micros_struct.last_millis_update) >
      1000) {
    millis_micros_struct.millis += 1;
    millis_micros_struct.last_millis_update += 1000;
  }
}
