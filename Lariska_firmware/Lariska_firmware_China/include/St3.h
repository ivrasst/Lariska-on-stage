#pragma once
#include <Arduino.h>
#include "Config.h"
#include "MyServos.h"
#include "Motor.h"

// --- НАСТРОЙКИ ПИНОВ ---
const int PIN_SENSOR_BACK  = A0; // Датчик между рейкой и ведущими колесами (ближний к заду)
const int PIN_SENSOR_FRONT = A3; // Датчик перед рулевой рейкой (ближний к переду)
// const int PIN_STEERING_SERVO = 9; // Пин управления рулевой сервой (или рейкой)

// --- ГЕОМЕТРИЯ И ЦЕЛЬ ---
const float TARGET_DISTANCE = 20.0; // Желаемое расстояние от робота до цилиндра (в см)

// Геометрические параметры датчиков (из ТЗ)
// Нам нужно расстояние МЕЖДУ датчиками для тригонометрии
// 27.3см (передний) - 9.5см (задний) = 17.8см
const float DISTANCE_BETWEEN_SENSORS = 17.8; 

// --- КОЭФФИЦИЕНТЫ PD-РЕГУЛЯТОРА ---
// Эти значения подбираются при отладке (начните с малых!)
float Kp_dist = 0.0;  // Влияние ошибки расстояния на поворот колес
float Kp_angle = -20.0; // Влияние перекоса робота на поворот колес
float Kd = 0.0;       // Влияние скорости изменения ошибки (гашение колебаний)

// --- ПЕРЕМЕННЫЕ ДЛЯ РЕГУЛЯТОРА ---
float last_error_dist = 0.0;
unsigned long last_time = 0;

// --- ФУНКЦИЯ ПЕРЕВОДА ADC В САНТИМЕТРЫ ---
float adcToCentimeters(int adc_value) {
  // Защита от деления на ноль и слишком близких объектов
  if (adc_value < 80) adc_value = 80; 
  
  float cm = 4800.0 / (adc_value - 20.0);

  // Ограничиваем физический диапазон датчика
  if (cm > 80.0) cm = 80.0;
  if (cm < 10.0) cm = 10.0;
  
  return cm;
}

void stPD_init() {
  Serial.begin(115200);
  pinMode(PIN_SENSOR_BACK, INPUT);
  pinMode(PIN_SENSOR_FRONT, INPUT);
  
  last_time = millis();
}

void st_pd() {
  unsigned long current_time = millis();
  float dt = (current_time - last_time) / 1000.0; // Время в секундах
  
  if (dt < 0.02) return; 
  last_time = current_time;

  int adc_back = analogRead(PIN_SENSOR_BACK);
  int adc_front = analogRead(PIN_SENSOR_FRONT);

  float dist_back = adcToCentimeters(adc_back);
  float dist_front = adcToCentimeters(adc_front);

  // 3. Вычисляем текущее состояние робота
  // Среднее расстояние до цилиндра по двум датчикам
  float current_distance = (dist_back + dist_front) / 2.0; 
  
  // Ошибка расстояния (на сколько мы дальше/ближе чем нужно)
  float error_dist = current_distance - TARGET_DISTANCE; 

  // Угол перекоса робота относительно касательной к цилиндру (в радианах)
  // Если dist_front > dist_back, робот отворачивает ОТ цилиндра
  float error_angle = atan2((dist_front - dist_back), DISTANCE_BETWEEN_SENSORS);

  // 4. Дифференциальная составляющая (скорость изменения ошибки расстояния)
  float derivative_dist = (error_dist - last_error_dist) / dt;
  last_error_dist = error_dist;

  // 5. Расчет управляющего сигнала PD-регулятора
  // Знак управления зависит от того, с какой стороны цилиндр (код написан для цилиндра СПРАВА)
  // Если цилиндр СЛЕВА — поменяйте знаки перед коэффициентами
  float control_output = (error_dist * Kp_dist) + (error_angle * Kp_angle) + (derivative_dist * Kd);

  // 6. Перевод сигнала в угол поворота сервопривода/рейки
  int steer_command = RUL_ZERO + (int)control_output;

  // Ограничиваем углы поворота рейки, чтобы механически её не сломать (например, диапазон 60-120 градусов)
  steer_command = constrain(steer_command, RUL_MIN, RUL_MAX);

  // 7. Исполнение команды (отправка на руль)
  // Тут должен быть ваш код управления сервой или мотором рейки, например:
  // steeringServo.write(steer_command);

    Rul.write(steer_command);
    m_drive(160);

  // Отладка в Plotter / Serial
  Serial.print("F:"); Serial.print(dist_front);
  Serial.print("  B:"); Serial.print(dist_back);
  Serial.print("  Ang:"); Serial.println(error_angle);

//   Serial.print("Dist_CM:"); Serial.print(current_distance);
//   Serial.print(",  Angle_Rad:"); Serial.print(error_angle);
//   Serial.print(",  Steer_Cmd:"); Serial.println(steer_command);
}
