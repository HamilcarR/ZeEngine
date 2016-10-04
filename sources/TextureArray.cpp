#include "TextureArray.h"

using namespace std;

TextureArray::TextureArray()
{
	m_array = new list<Texture*>();
}


TextureArray::~TextureArray()
{
	delete m_array;
}




