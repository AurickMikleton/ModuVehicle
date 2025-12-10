#include "engine.hpp"

MoVeEngine::MoVeEngine() {
    m_bore = 99.5;                 //mm
    m_stroke = 79.0;               //mm
    m_cylinders = 4;               // number
    peak_rpm_base = 4200.0; // rpm
    sigma_left = 1200.0;    // arbitrary
    sigma_right = 900.0;    // arbitrary
    wastegate_bar = 0.8;    // max boost (0.8bar ~ 11.6psi)
    spool_rpm = 2500.0;     // rpm, turbo reaches efficiency island
    spool_k = 600.0; 
}