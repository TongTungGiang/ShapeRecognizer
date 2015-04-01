//------------------------------------------------------------------------------------------
//
//  CommandButton.h
//
//  Created by CNTA.C++ Team in 2014
//
#ifndef COMMANDBUTTON_H
#define COMMANDBUTTON_H

#include "..\DollarRecognizer\GeometricRecognizerTypes.h"
#include "Framework.h"

namespace Framework
{

	enum ButtonState
	{
		NONACTIVE,
		HOVER,
		ACTIVE
	};

	class CommandButton
	{
	private:
		unsigned int iconTextureID_nonActive;
		unsigned int iconTextureID_active;
		DollarRecognizer::Vector2i originCoordinates;
		DollarRecognizer::Vector2i dimensions;
		unsigned int state;
		std::function<void()> command;

	public:
		CommandButton(DollarRecognizer::Vector2i coord, DollarRecognizer::Vector2i dimensions, 
			std::function<void()> command, unsigned int iconTextureID_nonActive, unsigned int iconTextureID_active)
			: originCoordinates(coord), dimensions(dimensions), command(command), iconTextureID_active(iconTextureID_active),
			iconTextureID_nonActive(iconTextureID_nonActive), state(NONACTIVE) {}

		~CommandButton() {};

		DollarRecognizer::Vector2i getOriginCoordinates()
		{
			return originCoordinates;
		}

		unsigned int getState()
		{
			return state;
		}

		void setState(unsigned int state)
		{
			this->state = state;
		}

		bool checkIntrusion(DollarRecognizer::Vector2i checkPosition)
		{
			int bx = originCoordinates.x,
				by = originCoordinates.y,
				tx = checkPosition.x,
				ty = checkPosition.y,
				dx = dimensions.x,
				dy = dimensions.y;

			return (bx < tx && tx < bx + dx && by < ty && ty < by + dy);
		}

		void doCommand()
		{
			command();
		}

		void render()
		{
			int x_coord = originCoordinates.x,
				y_coord = originCoordinates.y;

			if (state == NONACTIVE)
			{
				TextureManager::instance()->fwtm_renderTexture(iconTextureID_nonActive, x_coord, y_coord);


			}
			else if (state == HOVER || state == ACTIVE)
			{
				TextureManager::instance()->fwtm_renderTexture(iconTextureID_active, x_coord, y_coord);
			}
		}
	};

}

#endif
