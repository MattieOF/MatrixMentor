#include "mmpch.h"
#include "Core/Utility/OBJLoader.h"

#include "Core/Rendering/RawModel.h"
#include "Vendor/stringutils.h"

Ref<RawModel> OBJLoader::LoadOBJ(std::string_view filepath)
{
	std::ifstream file(filepath.data());
	if (!file.is_open())
	{
		MM_ERROR("Failed to open file: {0}", filepath);
		return nullptr;
	}

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> tempTextureCoords, textureCoords;
	std::vector<glm::vec3> tempNormals, normals;
	
	std::vector<uint32_t> indices;
	
	// Iterate over each line
	std::string line;
	bool initialisedLists = false;
	while (std::getline(file, line))
	{
		if (utils::StringUtils::startsWith(line, "v "))
		{
			// Vertex
			glm::vec3 vertex;
			int matches = sscanf_s(line.c_str(), "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
			if (matches != 3)
				MM_ERROR("Failed to parse vertex: {0}", line);
			else
				vertices.push_back(vertex);
		} else if (utils::StringUtils::startsWith(line, "vt "))
		{
			// Texture coordinate
			glm::vec2 texCoord;
			int matches = sscanf_s(line.c_str(), "vt %f %f", &texCoord.x, &texCoord.y);
			if (matches != 2)
				MM_ERROR("Failed to parse texture coordinate: {0}", line);
			else
				tempTextureCoords.push_back(texCoord);
		} else if (utils::StringUtils::startsWith(line, "vn "))
		{
			// Normal vector
			glm::vec3 normal;
			int matches = sscanf_s(line.c_str(), "vn %f %f %f", &normal.x, &normal.y, &normal.z);
			if (matches != 3)
				MM_ERROR("Failed to parse normal: {0}", line);
			else
				tempNormals.push_back(normal);
		} else if (utils::StringUtils::startsWith(line, "f "))
		{
			// Face
			if (!initialisedLists)
			{
				// Initialise the lists
				textureCoords.resize(vertices.size());
				normals.resize(vertices.size());
				initialisedLists = true;
			}
			
			uint32_t vertexIndex[3], texCoordIndex[3], normalIndex[3];
			int matches = sscanf_s(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
				&vertexIndex[0], &texCoordIndex[0], &normalIndex[0],
				&vertexIndex[1], &texCoordIndex[1], &normalIndex[1],
				&vertexIndex[2], &texCoordIndex[2], &normalIndex[2]);
			if (matches != 9)
				MM_ERROR("Failed to parse face: {0}", line);
			else
			{
				indices.push_back(vertexIndex[0] - 1);
				indices.push_back(vertexIndex[1] - 1);
				indices.push_back(vertexIndex[2] - 1);

				textureCoords[vertexIndex[0] - 1] = tempTextureCoords[texCoordIndex[0] - 1];
				textureCoords[vertexIndex[1] - 1] = tempTextureCoords[texCoordIndex[1] - 1];
				textureCoords[vertexIndex[2] - 1] = tempTextureCoords[texCoordIndex[2] - 1];

				normals[vertexIndex[0] - 1] = tempNormals[normalIndex[0] - 1];
				normals[vertexIndex[1] - 1] = tempNormals[normalIndex[1] - 1];
				normals[vertexIndex[2] - 1] = tempNormals[normalIndex[2] - 1];
			}
		}
	}

	return CreateRef<RawModel>(vertices, textureCoords, normals, indices);
}
