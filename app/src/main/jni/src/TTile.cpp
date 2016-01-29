#include <TTile.h>
#include <SDL_image.h>


TTile::TTile(int x, int y)
{
	//Get the offsets
	mBox.x = x;
	mBox.y = y;

	//Set the collision box
	mBox.w = mTileWidth;
	mBox.h = mTileHeight;
}


TTile::~TTile()
{
	
}

void TTile::render(SDL_Renderer* gRenderer, SDL_Rect& camera)
{
	//If the tile is on screen
	if (checkCollision(camera, mBox))
	{
		//Show the tile
		mTileTexture -> render(gRenderer, mBox.x - camera.x, mBox.y - camera.y);
	}
}

void TTile::move(int offsetX, int offsetY)
{
	//Move the dot left or right
	mBox.x += offsetX;

	//Move the dot up or down
	mBox.y += offsetY;
}

void TTile::setXY(int x, int y) {
	mBox.x = x;
	mBox.y = y;
}

bool TTile::checkCollision(SDL_Rect a, SDL_Rect b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}

SDL_Rect TTile::getBox()
{
	return mBox;
}

LTexture* TTile::getTileTexture()
{
	return mTileTexture;
}

void TTile::setTileTexture(LTexture* tileTexture)
{
	mTileTexture = tileTexture;
}

