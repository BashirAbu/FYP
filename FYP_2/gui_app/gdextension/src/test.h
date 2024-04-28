#pragma once
#include "helper_macros.h"

#include <godot_cpp/classes/node3d.hpp>


namespace godot {

    class test : public Node3D
    {
        GDCLASS(test, Node3D)
    public:
        test();
        ~test();

        void _ready() override;
        void _process(double deltaTime) override;
        void _physics_process(double deltaTime) override;

    protected:
        static void _bind_methods();
    private:

    };
}