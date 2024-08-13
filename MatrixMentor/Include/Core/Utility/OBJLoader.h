#pragma once

class RawModel;

class OBJLoader
{
public:
	static Ref<RawModel> LoadOBJ(std::string_view filepath);
};
