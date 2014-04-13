// TextureManager.h

#pragma once

#include "RenderBase.h"
#include "core/singleton.h"

#include <stack>
#include <list>
#include <map>
#include <memory>
#include <vector>
#include <string>

namespace FS
{
	class MemMap;
}

struct LogicalTexture
{
	DEV_TEXTURE dev_texture;

	float uvLeft;
	float uvTop;
	float uvRight;
	float uvBottom;
	float uvFrameWidth;
	float uvFrameHeight;
	vec2d uvPivot;

	float pxFrameWidth;
	float pxFrameHeight;
	int   xframes;
	int   yframes;

	std::vector<FRECT> uvFrames;
};

enum enumAlignText {
	alignTextLT = 0, alignTextCT = 1, alignTextRT = 2,
	alignTextLC = 3, alignTextCC = 4, alignTextRC = 5,
	alignTextLB = 6, alignTextCB = 7, alignTextRB = 8,
};

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	int LoadPackage(const std::string &packageName, std::shared_ptr<FS::MemMap> file);
	int LoadDirectory(const std::string &dirName, const std::string &texPrefix);
	void UnloadAllTextures();

	size_t FindSprite(const std::string &name) const;
	const LogicalTexture& Get(size_t texIndex) const { return _logicalTextures[texIndex]; }
	float GetFrameWidth(size_t texIndex, size_t /*frameIdx*/) const { return _logicalTextures[texIndex].pxFrameWidth; }
	float GetFrameHeight(size_t texIndex, size_t /*frameIdx*/) const { return _logicalTextures[texIndex].pxFrameHeight; }
	size_t GetFrameCount(size_t texIndex) const { return _logicalTextures[texIndex].xframes * _logicalTextures[texIndex].yframes; }

	bool IsValidTexture(size_t index) const;

	void GetTextureNames(std::vector<std::string> &names, const char *prefix, bool noPrefixReturn) const;

	float GetCharHeight(size_t fontTexture) const;

	void DrawSprite(const FRECT *dst, size_t sprite, SpriteColor color, unsigned int frame) const;
	void DrawBorder(const FRECT *dst, size_t sprite, SpriteColor color, unsigned int frame) const;
	void DrawBitmapText(float x, float y, size_t tex, SpriteColor color, const std::string &str, enumAlignText align = alignTextLT) const;
	void DrawSprite(size_t tex, unsigned int frame, SpriteColor color, float x, float y, vec2d dir) const;
	void DrawSprite(size_t tex, unsigned int frame, SpriteColor color, float x, float y, float width, float height, vec2d dir) const;
	void DrawIndicator(size_t tex, float x, float y, float value) const;
	void DrawLine(size_t tex, SpriteColor color, float x0, float y0, float x1, float y1, float phase) const;

	void SetCanvasSize(unsigned int width, unsigned int height);
	void PushClippingRect(const Rect &rect) const;
	void PopClippingRect() const;

private:
	struct TexDesc
	{
		DEV_TEXTURE id;
		int width;          // The Width Of The Entire Image.
		int height;         // The Height Of The Entire Image.
		int refCount;       // number of logical textures
	};
	typedef std::list<TexDesc>       TexDescList;
	typedef TexDescList::iterator    TexDescIterator;

	typedef std::map<std::string, TexDescIterator>    FileToTexDescMap;
	typedef std::map<DEV_TEXTURE, TexDescIterator> DevToTexDescMap;

	FileToTexDescMap _mapFile_to_TexDescIter;
	DevToTexDescMap  _mapDevTex_to_TexDescIter;
	TexDescList      _textures;
	std::map<std::string, size_t>   _mapName_to_Index;// index in _logicalTextures
	std::vector<LogicalTexture>  _logicalTextures;

	Rect _viewport;
	mutable std::stack<Rect> _clipStack;

	void LoadTexture(TexDescIterator &itTexDesc, const std::string &fileName);
	void Unload(TexDescIterator what);

	void CreateChecker(); // Create checker texture without name and with index=0
};

class DrawingContext : public TextureManager
{
};

/////////////////////////////////////////////////////////////

class ThemeManager
{
	struct ThemeDesc
	{
		std::string fileName;
		std::shared_ptr<FS::MemMap> file;
	};

	std::vector<ThemeDesc> _themes;

public:
	ThemeManager();
	~ThemeManager();

	size_t GetThemeCount();
	size_t FindTheme(const std::string &name);
	std::string GetThemeName(size_t index);

    bool ApplyTheme(size_t index);
};

typedef StaticSingleton<ThemeManager> _ThemeManager;


///////////////////////////////////////////////////////////////////////////////
// end of file
