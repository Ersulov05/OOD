#pragma once

#include "../AddShapeCommand.h"
#include "../ChangeShapeColorCommand.h"
#include "../ChangeShapeCommand.h"
#include "../DeleteShapeCommand.h"
#include "../DrawPictureCommand.h"
#include "../DrawShapeCommand.h"
#include "../IAppCommand.h"
#include "../MovePictureCommand.h"
#include "../MoveShapeCommand.h"
#include "../RunWindowCommand.h"
#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

class AppCommandFactory
{
public:
	using AppCommandCreator = std::function<std::unique_ptr<IAppCommand>(const std::vector<std::string>&)>;

	std::unique_ptr<IAppCommand> CreateAppCommand(const std::string& name, const std::vector<std::string>& params = {}) const
	{
		auto it = m_appCommandCreators.find(name);
		if (it == m_appCommandCreators.end())
		{
			throw std::invalid_argument("Unknown command: " + name);
		}
		return it->second(params);
	}

private:
	std::map<std::string, AppCommandCreator> m_appCommandCreators = {
		{ "addShape", [this](const std::vector<std::string>& params) { return std::make_unique<AddShapeCommand>(params); } },
		{ "drawShape", [this](const std::vector<std::string>& params) { return std::make_unique<DrawShapeCommand>(params); } },
		{ "moveShape", [this](const std::vector<std::string>& params) { return std::make_unique<MoveShapeCommand>(params); } },
		{ "changeShape", [this](const std::vector<std::string>& params) { return std::make_unique<ChangeShapeCommand>(params); } },
		{ "deleteShape", [this](const std::vector<std::string>& params) { return std::make_unique<DeleteShapeCommand>(params); } },
		{ "changeColor", [this](const std::vector<std::string>& params) { return std::make_unique<ChangeShapeColorCommand>(params); } },
		{ "movePicture", [this](const std::vector<std::string>& params) { return std::make_unique<MovePictureCommand>(params); } },
		{ "drawPicture", [this](const std::vector<std::string>& params) { return std::make_unique<DrawPictureCommand>(params); } },
		{ "run", [this](const std::vector<std::string>& params) { return std::make_unique<RunWindowCommand>(params); } },
	};
};