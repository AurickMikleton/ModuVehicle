#pragma once

#include "godot_cpp/core/object.hpp"
#include "godot_cpp/core/class_db.hpp"

using namespace godot;

class ModuWheel : public Object {
private:
    int m_sum;
    GDCLASS(ModuWheel, Object);
protected:
    static void _bind_methods();
public:
    ModuWheel();
    void add(int i);
    int get_total() const;
};