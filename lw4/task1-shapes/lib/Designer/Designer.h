#pragma once

#include "../Canvas/CCanvas.h"
#include "../PictureDraft/PictureDraft.h"
#include "../Shape/Factory/IShapeFactrory.h"
#include "../Shape/Factory/ShapeFactory.h"
#include "./IDesigner.h"
#include <string>

class Designer : public IDesigner
{
public:
	Designer()
		: m_factory(std::make_unique<ShapeFactory>())
	{
	}

	PictureDraft CreateDraft(std::istream& input)
	{
		PictureDraft pictureDraft;
		std::string line;
		bool isExit = false;
		while (getline(input, line) && !isExit)
		{
			HandleLine(pictureDraft, line, isExit);
		}

		return pictureDraft;
	}

private:
	std::unique_ptr<IShapeFactory> m_factory;
	static constexpr const std::string EXIT_COMMAND_NAME = "exit";

	void HandleLine(PictureDraft& pictureDraft, std::string& line, bool& isExit)
	{
		try
		{
			if (line.empty())
			{
				return;
			}
			auto params = GetParams(line);
			if (params[0] == EXIT_COMMAND_NAME)
			{
				isExit = true;
				return;
			}
			auto shape = m_factory->CreateShape(params);
			pictureDraft.AddShape(std::move(shape));
		}
		catch (const std::exception& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
		}
	}

	std::vector<std::string> GetParams(const std::string& line)
	{
		std::istringstream lineStream(line);
		std::string param;
		std::vector<std::string> params;
		while (lineStream >> param)
		{
			params.push_back(param);
		}

		return params;
	}
};