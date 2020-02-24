#include "TRAPPCH.h"
#include "TextureManager.h"
#include "Texture2D.h"
#include "TextureCube.h"

std::unordered_map<std::string, TRAP::Scope<TRAP::Graphics::Texture>> TRAP::Graphics::TextureManager::s_Textures;

//-------------------------------------------------------------------------------------------------------------------//

const TRAP::Scope<TRAP::Graphics::Texture>& TRAP::Graphics::TextureManager::Load(const std::string& filepath, const TextureParameters parameters)
{
	TP_PROFILE_FUNCTION();

	Scope<Texture> texture = Texture2D::CreateFromFile(filepath, parameters);
	if(texture)
	{
		const std::string name = std::string(texture->GetName());
		
		Add(std::move(texture));
		
		return Get(name, TextureType::Texture2D);
	}

	return Get("Fallback2D", TextureType::Texture2D);
}

//-------------------------------------------------------------------------------------------------------------------//

const TRAP::Scope<TRAP::Graphics::Texture>& TRAP::Graphics::TextureManager::Load(const std::string& name, const std::string& filepath, const TextureParameters parameters)
{
	TP_PROFILE_FUNCTION();

	Scope<Texture> texture = Texture2D::CreateFromFile(name, filepath, parameters);

	if(texture)
	{
		Add(std::move(texture));
		
		return Get(name, TextureType::Texture2D);
	}

	return Get("Fallback2D", TextureType::Texture2D);
}

//-------------------------------------------------------------------------------------------------------------------//

const std::unique_ptr<TRAP::Graphics::Texture2D>& TRAP::Graphics::TextureManager::Load(
	const std::string& name,
	const uint32_t width,
	const uint32_t height,
	const uint32_t bitsPerPixel,
	const ImageFormat format,
	const std::vector<uint8_t>& pixelData,
	const TextureParameters parameters)
{
	TP_PROFILE_FUNCTION();

	Scope<Texture> texture = Texture2D::CreateFromMemory(name, width, height, bitsPerPixel, format, pixelData, parameters);

	if (texture)
	{
		Add(std::move(texture));

		return Get2D(name);
	}

	return Get2D("Fallback2D");
}

//-------------------------------------------------------------------------------------------------------------------//

const std::unique_ptr<TRAP::Graphics::Texture2D>& TRAP::Graphics::TextureManager::Load(
	const std::string& name,
	const uint32_t width,
	const uint32_t height,
	const uint32_t bitsPerPixel,
	const ImageFormat format,
	const std::vector<uint16_t>& pixelData,
	const TextureParameters parameters)
{
	TP_PROFILE_FUNCTION();

	Scope<Texture> texture = Texture2D::CreateFromMemory(name, width, height, bitsPerPixel, format, pixelData, parameters);

	if (texture)
	{
		Add(std::move(texture));

		return Get2D(name);
	}

	return Get2D("Fallback2D");
}

//-------------------------------------------------------------------------------------------------------------------//

const std::unique_ptr<TRAP::Graphics::Texture2D>& TRAP::Graphics::TextureManager::Load(
	const std::string& name,
	const uint32_t width,
	const uint32_t height,
	const uint32_t bitsPerPixel,
	const ImageFormat format,
	const std::vector<float>& pixelData,
	const TextureParameters parameters)
{
	TP_PROFILE_FUNCTION();

	Scope<Texture> texture = Texture2D::CreateFromMemory(name, width, height, bitsPerPixel, format, pixelData, parameters);

	if (texture)
	{
		Add(std::move(texture));

		return Get2D(name);
	}

	return Get2D("Fallback2D");
}

//-------------------------------------------------------------------------------------------------------------------//

const TRAP::Scope<TRAP::Graphics::Texture>& TRAP::Graphics::TextureManager::Load(const std::string& name, const std::string& filepath, const InputFormat format, const TextureParameters parameters)
{
	TP_PROFILE_FUNCTION();

	Scope<Texture> texture = TextureCube::CreateFromCross(name, filepath, format, parameters);

	if(texture)
	{
		Add(std::move(texture));
		
		return Get(name, TextureType::TextureCube);
	}
	
	return Get("FallbackCube", TextureType::TextureCube);
}

//-------------------------------------------------------------------------------------------------------------------//

const TRAP::Scope<TRAP::Graphics::Texture>& TRAP::Graphics::TextureManager::Load(const std::string& filepath, const InputFormat format, const TextureParameters parameters)
{
	TP_PROFILE_FUNCTION();

	Scope<Texture> texture = TextureCube::CreateFromCross(filepath, format, parameters);

	if(texture)
	{
		const std::string name = std::string(texture->GetName());
		
		Add(std::move(texture));
		
		return Get(name, TextureType::TextureCube);
	}

	return Get("FallbackCube", TextureType::TextureCube);
}

//-------------------------------------------------------------------------------------------------------------------//

const TRAP::Scope<TRAP::Graphics::Texture>& TRAP::Graphics::TextureManager::Load(const std::string& name, const std::array<std::string, 6> & filepaths, const TextureParameters parameters)
{
	TP_PROFILE_FUNCTION();

	Scope<Texture> texture = TextureCube::CreateFromFiles(name, filepaths, parameters);

	if(texture)
	{
		Add(std::move(texture));
		
		return Get(name, TextureType::TextureCube);
	}
	
	return Get("FallbackCube", TextureType::TextureCube);
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::TextureManager::Add(Scope<Texture> texture)
{
	TP_PROFILE_FUNCTION();

	if(texture)
	{
		if (!Exists(std::string(texture->GetName())))
			s_Textures[std::string(texture->GetName())] = std::move(texture);
		else
			TP_ERROR("[TextureManager] Texture with Name: \"", texture->GetName(), "\" already exists! Ignoring new Texture");
	}
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::TextureManager::Remove(const Scope<Texture>& texture)
{
	TP_PROFILE_FUNCTION();

	if(texture)
	{
		if (Exists(std::string(texture->GetName())))
			s_Textures.erase(std::string(texture->GetName()));
		else
			TP_ERROR("[TextureManager] Could not find Texture with Name: \"", texture->GetName(), "\"!");
	}
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::TextureManager::Remove(const std::string_view name)
{
	TP_PROFILE_FUNCTION();

	if (Exists(std::string(name)))
		s_Textures.erase(std::string(name));
	else
		TP_ERROR("[TextureManager] Could not find Texture with Name: \"", name, "\"!");
}

//-------------------------------------------------------------------------------------------------------------------//

const TRAP::Scope<TRAP::Graphics::Texture>& TRAP::Graphics::TextureManager::Get(const std::string& name, const TextureType textureType)
{
	TP_PROFILE_FUNCTION();

	if(Exists(name))
		if (s_Textures[name]->GetType() == textureType)
				return s_Textures[name];

	if (textureType == TextureType::Texture2D)
		return Get("Fallback2D", TextureType::Texture2D);
	
	return Get("FallbackCube", TextureType::TextureCube);
}

//-------------------------------------------------------------------------------------------------------------------//

const TRAP::Scope<TRAP::Graphics::Texture2D>& TRAP::Graphics::TextureManager::Get2D(const std::string& name)
{
	TP_PROFILE_FUNCTION();

	return reinterpret_cast<const Scope<Texture2D>&>(Get(name, TextureType::Texture2D));
}

//-------------------------------------------------------------------------------------------------------------------//

const TRAP::Scope<TRAP::Graphics::TextureCube>& TRAP::Graphics::TextureManager::GetCube(const std::string& name)
{
	TP_PROFILE_FUNCTION();

	return reinterpret_cast<const Scope<TextureCube>&>(Get(name, TextureType::TextureCube));
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::TextureManager::Clean()
{
	s_Textures.clear();
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::TextureManager::Reload(const std::string& nameOrVirtualPath)
{
	TP_PROFILE_FUNCTION();

	//Name
	if (nameOrVirtualPath[0] != '/')
	{
		if(Exists(nameOrVirtualPath))
		{
			const std::string filePath = std::string(s_Textures[nameOrVirtualPath]->GetFilePath());
			if (filePath.empty())
			{
				TP_WARN("[TextureManager] Could not find Texture: \"", nameOrVirtualPath, "\" to reload.");
				return;
			}

			const std::string name = std::string(s_Textures[nameOrVirtualPath]->GetName());
			const TextureType textureType = s_Textures[nameOrVirtualPath]->GetType();
			const TextureParameters textureParameters = s_Textures[nameOrVirtualPath]->GetParameters();

			if (textureType == TextureType::Texture2D)
			{
				s_Textures[nameOrVirtualPath].reset();
				s_Textures[nameOrVirtualPath] = Texture2D::CreateFromFile(name, filePath, textureParameters);
				TP_INFO("[TextureManager][Texture2D] Reloaded: \"", nameOrVirtualPath, "\"");
			}
			else if (textureType == TextureType::TextureCube)
			{
				if (s_Textures[nameOrVirtualPath])
				{
					const InputFormat inputFormat = dynamic_cast<TextureCube*>(s_Textures[nameOrVirtualPath].get())->GetInputFormat();

					std::array<std::string, 6> filePaths{};
					for (uint32_t i = 0; i < dynamic_cast<TextureCube*>(s_Textures[nameOrVirtualPath].get())->GetFilePaths().size(); i++)
						filePaths[i] = dynamic_cast<TextureCube*>(s_Textures[nameOrVirtualPath].get())->GetFilePaths()[i];

					s_Textures[nameOrVirtualPath].reset();
					if (inputFormat == InputFormat::Vertical_Cross || inputFormat == InputFormat::Horizontal_Cross)
						s_Textures[nameOrVirtualPath] = TextureCube::CreateFromCross(name, filePath, inputFormat, textureParameters);
					else
						s_Textures[nameOrVirtualPath] = TextureCube::CreateFromFiles(name, filePaths, textureParameters);

					TP_INFO("[TextureManager][TextureCube] Reloaded: \"", nameOrVirtualPath, "\"");
				}
			}
			else
				//Shouldn't be reached
				TP_WARN("[TextureManager] Unknown TextureType: \"", nameOrVirtualPath, "\"");
		}
		else
			TP_WARN("[TextureManager] Could not find Texture: \"", nameOrVirtualPath, "\" to reload.");
	}
	else //Virtual Path
	{
		for (const auto& [name, texture] : s_Textures)
			if (texture->GetType() == TextureType::Texture2D)
			{
				if (nameOrVirtualPath == texture->GetFilePath())
				{
					Reload(texture);
					return;
				}
			}
			else if(texture->GetType() == TextureType::TextureCube)
				for (uint32_t i = 0; i < dynamic_cast<TextureCube*>(texture.get())->GetFilePaths().size(); i++)
					if (!dynamic_cast<TextureCube*>(texture.get())->GetFilePaths()[i].empty())
						if (nameOrVirtualPath == dynamic_cast<TextureCube*>(texture.get())->GetFilePaths()[i])
						{
							Reload(texture);
							return;
						}
		
		TP_WARN("[TextureManager] Could not find Texture: \"", nameOrVirtualPath, "\" to reload.");
	}
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::TextureManager::Reload(const Scope<Texture>& texture)
{
	TP_PROFILE_FUNCTION();

	if(Exists(std::string(texture->GetName())))
	{
		const std::string name = std::string(texture->GetName());
		const std::string filepath = std::string(texture->GetFilePath());
		if (filepath.empty())
		{
			TP_WARN("[TextureManager] Could not find Texture: \"", name, "\" to reload.");
			return;
		}

		const TextureType textureType = texture->GetType();
		const TextureParameters textureParameters = texture->GetParameters();

		if (textureType == TextureType::Texture2D)
		{
			s_Textures[name].reset();
			s_Textures[name] = Texture2D::CreateFromFile(name, filepath, textureParameters);
			TP_INFO("[TextureManager][Texture2D] Reloaded: \"", name, "\"");
		}
		else if (textureType == TextureType::TextureCube)
		{
			if (texture)
			{
				const InputFormat inputFormat = dynamic_cast<TextureCube*>(texture.get())->GetInputFormat();

				std::array<std::string, 6> filePaths{};
				for (uint32_t i = 0; i < dynamic_cast<TextureCube*>(texture.get())->GetFilePaths().size(); i++)
					filePaths[i] = dynamic_cast<TextureCube*>(texture.get())->GetFilePaths()[i];

				s_Textures[name].reset();
				if (inputFormat == InputFormat::Vertical_Cross || inputFormat == InputFormat::Horizontal_Cross)
					s_Textures[name] = TextureCube::CreateFromCross(name, filepath, inputFormat, textureParameters);
				else
					s_Textures[name] = TextureCube::CreateFromFiles(name, filePaths, textureParameters);

				TP_INFO("[TextureManager][TextureCube] Reloaded: \"", name, "\"");
			}
		}
		else
			TP_WARN("[TextureManager] Unknown TextureType: \"", name, "\"");
	}
	else
		TP_WARN("[TextureManager] Could not find Texture: \"", texture->GetName(), "\" to reload.");
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::TextureManager::ReloadAll()
{
	TP_PROFILE_FUNCTION();

	TP_INFO("[TextureManager] Reloading all may take a while...");
	for (auto& [name, texture] : s_Textures)
		Reload(texture);
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::TextureManager::Shutdown()
{
	TP_PROFILE_FUNCTION();

	TP_DEBUG("[TextureManager] Destroying Textures");
	Clean();
}

//-------------------------------------------------------------------------------------------------------------------//

bool TRAP::Graphics::TextureManager::Exists(const std::string& name)
{
	return s_Textures.find(name) != s_Textures.end();
}

//-------------------------------------------------------------------------------------------------------------------//

bool TRAP::Graphics::TextureManager::ExistsVirtualPath(const std::string& virtualPath)
{
	for (const auto& [name, texture] : s_Textures)
	{
		if (texture->GetType() == TextureType::Texture2D)
		{
			if (texture->GetFilePath() == virtualPath)
				return true;
		}
		else if(texture->GetType() == TextureType::TextureCube)
		{
			const std::array<std::string, 6> imageFilePaths = reinterpret_cast<const Scope<TextureCube>&>(texture)->GetFilePaths();
			for(const auto& filePath : imageFilePaths)
				if (filePath == virtualPath)
					return true;
		}
	}
	
	return false;
}