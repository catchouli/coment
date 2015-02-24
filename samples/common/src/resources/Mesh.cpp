#include "resources/Mesh.h"

#include "resources/Image.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <gl/glew.h>
#include <fstream>

namespace coment
{
	Mesh::Mesh(bool storeTextures, aiPostProcessSteps normalMode)
		: mLoaded(false),
		mStoreTextures(storeTextures),
		mNormalMode(normalMode)
	{

	}

	Mesh::Mesh(const char* filename, bool storeTextures, aiPostProcessSteps normalMode)
		: mLoaded(false),
		mStoreTextures(storeTextures),
		mNormalMode(normalMode)
	{
		load(filename);
	}

	void Mesh::unload()
	{
        mImages.clear();
        mSubMeshes.clear();
        mTextures.clear();

		mLoaded = false;
	}

	void Mesh::render()
	{
		// For each submesh
		for (size_t i = 0; i < mSubMeshes.size(); ++i)
		{
			SubMesh* currentMesh = &mSubMeshes[i];
				
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);

			if (hasTextures())
			{
				glEnable(GL_TEXTURE_2D);

				glEnableClientState(GL_TEXTURE_COORD_ARRAY);

                glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (void*)&currentMesh->vertices[0].texCoord);

				glBindTexture(GL_TEXTURE_2D, mTextures[currentMesh->materialIndex]);
			}

			glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (void*)currentMesh->vertices.data());
            glNormalPointer(GL_FLOAT, sizeof(Vertex), (void*)&currentMesh->vertices[0].normal);

            glDrawElements(GL_TRIANGLES, currentMesh->indices.size(), GL_UNSIGNED_INT, (void*)currentMesh->indices.data());
				
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		}
	}

	void Mesh::transform(const glm::mat4& matrix)
	{
		// Transform all points
		for (size_t i = 0; i < mSubMeshes.size(); ++i)
		{
			SubMesh& subMesh = mSubMeshes[i];

			for (auto& vertex : subMesh.vertices)
			{
                vertex.pos = glm::vec3(matrix * glm::vec4(vertex.pos, 1.0f));
                vertex.normal = glm::vec3(matrix * glm::vec4(vertex.normal, 0.0f));
			}
		}

		// Recalculate min/max
		calcMinMax();
	}

	void Mesh::calcMinMax()
	{
		// Calculate min/max
		mMin = mSubMeshes[0].vertices[0].pos;
		mMax = mSubMeshes[0].vertices[0].pos;

		for (size_t i = 0; i < mSubMeshes.size(); ++i)
		{
			SubMesh& subMesh = mSubMeshes[i];

			for (unsigned int j = 0; j < subMesh.vertices.size(); ++j)
			{
				glm::vec3 vert = subMesh.vertices[j].pos;
					
				if (vert.x < mMin.x)
					mMin.x = vert.x;
				if (vert.y < mMin.y)
					mMin.y = vert.y;
				if (vert.z < mMin.z)
					mMin.z = vert.z;

				if (vert.x > mMax.x)
					mMax.x = vert.x;
				if (vert.y > mMax.y)
					mMax.y = vert.y;
				if (vert.z > mMax.z)
					mMax.z = vert.z;
			}
		}
	}

	bool Mesh::load(const char* filename)
	{
		Assimp::Importer importer;

		const aiScene* scene;

		// Unload previously loaded mesh
		unload();

		// Check file exists
		if (!std::ifstream(filename))
		{
			fprintf(stderr, "Could not open model file %s\n", filename);
			return false;
		}

		// Attempt to load mesh
		scene = importer.ReadFile(filename,
			aiProcess_Triangulate | mNormalMode | aiProcess_FlipUVs);

		if (!scene)
		{
			fprintf(stderr, "Failed to parse model file %s\n", filename);
			return false;
		}

		// Load materials
		if (scene->HasMaterials())
		{
			mTextureCount = scene->mNumMaterials;

            mTextures.resize(mTextureCount);
            mImages.resize(mTextureCount);

			for (uint32_t i = 0; i < scene->mNumMaterials; ++i)
			{
				// Load material
				const aiMaterial* material = scene->mMaterials[i];

				if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
				{
					aiString path;

					if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
					{
						if (!mImages[i].load(path.C_Str()))
						{
							fprintf(stderr, "Failed to load texture: %s\n", path);
						}
						else
						{
							mTextures[i] = mImages[i].genGlTexture();
						}
					}
					else
					{
						fprintf(stderr, "No texture available for material\n");
					}
				}
				else
				{
					fprintf(stderr, "No diffuse texture for material\n");
				}
			}

			// Clean up images
			if (!mStoreTextures)
			{
                mImages.clear();
			}
		}

		// Load meshes from assimp scene
		// Allocate memory
        mSubMeshes.resize(scene->mNumMeshes);

		// Initialise meshes
		for (size_t i = 0; i < mSubMeshes.size(); ++i)
		{
			// Get assimp mesh
			const aiMesh* mesh = scene->mMeshes[i];
												
			// Get current submesh
			SubMesh* currentMesh = &mSubMeshes[i];

			// Set mesh texture
			currentMesh->materialIndex = mesh->mMaterialIndex;

			// Allocate memory
            currentMesh->indices.resize(mesh->mNumFaces * 3);
            currentMesh->vertices.resize(mesh->mNumVertices);

			// Load vertices
			const aiVector3D ZERO = aiVector3D(0, 0, 0);
			for (uint32_t j = 0; j < mesh->mNumVertices; ++j)
			{
				Vertex& vertex = currentMesh->vertices[j];
					
				// Load vertex data
				const aiVector3D* pos = &mesh->mVertices[j];
				const aiVector3D* normal = &mesh->mNormals[j];
				const aiVector3D* uv = &ZERO;

				if (mesh->HasTextureCoords((unsigned int)i))
					uv = &mesh->mTextureCoords[0][j];
					
				if (pos->x < mMin.x)
					mMin.x = pos->x;
				if (pos->y < mMin.y)
					mMin.y = pos->y;
				if (pos->z < mMin.z)
					mMin.z = pos->z;
					
				if (pos->x > mMax.x)
					mMax.x = pos->x;
				if (pos->y > mMax.y)
					mMax.y = pos->y;
				if (pos->z > mMax.z)
					mMax.z = pos->z;

				// Convert to vlr format
				vertex.pos = glm::vec3(pos->x, pos->y, pos->z);
				vertex.normal = -1.0f * glm::vec3(normal->x, normal->y, normal->z);
				vertex.texCoord = glm::vec2(uv->x, uv->y);
			}

			// Load indicies
			for (uint32_t j = 0; j < mesh->mNumFaces; ++j)
			{
				assert(mesh->mFaces[j].mNumIndices == 3);
					
				currentMesh->indices[j * 3 + 0] = mesh->mFaces[j].mIndices[2];
				currentMesh->indices[j * 3 + 1] = mesh->mFaces[j].mIndices[1];
				currentMesh->indices[j * 3 + 2] = mesh->mFaces[j].mIndices[0];
			}
		}

		mLoaded = true;

		calcMinMax();

		return true;
	}
}
