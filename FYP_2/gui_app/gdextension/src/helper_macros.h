#pragma once 

#define PROPERTY_SETTER_GETTER(type, variable)\
void set_##variable(type _##variable)  \
{                                      \
	variable = _##variable;            \
}                                      \
type get_##variable()                  \
{                                      \
	return variable;                   \
}

#define EXPORT_PROPERTY(className, propertyInfo,variable)                                                      \
godot::ClassDB::bind_method(godot::D_METHOD("get_"#variable""), &##className::get_##variable);                 \
godot::ClassDB::bind_method(godot::D_METHOD("set_"#variable"", "_"#variable""),  &##className::set_##variable);\
godot::ClassDB::add_property(""#className"", propertyInfo, "set_"#variable"", "get_"#variable"");

#define GAME_NODE()                             \
if (Engine::get_singleton()->is_editor_hint())  \
{                                               \
	set_process(false);                         \
	set_physics_process(false);                 \
	return;										\
}