#pragma once

#include <stdio.h>
#include <glm/glm.hpp>
#include <gl/glew.h>
#include <stdint.h>
#include <assimp/postprocess.h>
#include "resources/Image.h"
#include <vector>

namespace coment
{
	struct Vertex
	{
		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec2 texCoord;
	};

	struct SubMesh
	{
		std::vector<int> indices;
		std::vector<Vertex> vertices;

		unsigned int materialIndex = -1;
	};

	class Mesh
	{
	public:
		Mesh(bool storeTextures = false, aiPostProcessSteps normalMode = aiProcess_GenSmoothNormals);
		Mesh(const char* filename, bool storeTextures = false, aiPostProcessSteps normalMode = aiProcess_GenSmoothNormals);

		void render();
			
		bool load(const char* filename);
		void unload();

		void transform(const glm::mat4& matrix);
		void calcMinMax();

		inline bool isLoaded() const;

		inline bool hasTextures() const;
			
		inline Image* getStoredTextures() const;

		inline int32_t getSubMeshCount() const;
		inline const SubMesh* getSubMesh(int32_t i) const;
			
		inline const glm::vec3* getMin() const;
		inline const glm::vec3* getMax() const;

	private:

		bool mLoaded;
		bool mStoreTextures;

		std::vector<SubMesh> mSubMeshes;

		aiPostProcessSteps mNormalMode;

		size_t mTextureCount;

		std::vector<GLuint> mTextures;
		std::vector<Image> mImages;

		glm::vec3 mMin;
		glm::vec3 mMax;
	};

	bool Mesh::isLoaded() const
	{
		return mLoaded;
	}

	bool Mesh::hasTextures() const
	{
		return mTextures.size() != 0;
	}

	Image* Mesh::getStoredTextures() const
	{
        return (Image*)mTextures.data();
	}

	int32_t Mesh::getSubMeshCount() const
	{
		return (int32_t)mSubMeshes.size();
	}

	const SubMesh* Mesh::getSubMesh(int32_t i) const
	{
		if (i < 0 || i >= (int32_t)mSubMeshes.size())
		{
			fprintf(stderr, "Attempted to access invalid submesh\n");

			return nullptr;
		}

		return &mSubMeshes[i];
	}
		
	const glm::vec3* Mesh::getMin() const
	{
		return &mMin;
	}

	const glm::vec3* Mesh::getMax() const
	{
		return &mMax;
	}
}
