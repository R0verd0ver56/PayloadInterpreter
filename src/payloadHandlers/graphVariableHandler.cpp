#pragma once
#include "payloadHandler.h"

// DIAGNOSTIC BUILD: logs every graph variable set by a payload, with the actor and the value.
// Log lines look like:  SGV[P] I MCO_nextattack = 2   (P = player, N = npc)

static inline const char* SGVTag(RE::Actor* a) { return (a && a->IsPlayerRef()) ? "P" : "N"; }

void graphVariableHandler::setGraphVariableBool(RE::Actor* actor, std::vector<std::string_view>* in)
{
	bool b;
	if (!Utils::string_view::to_bool(in->at(2), b)) {
		printErrMsg(in, "Invalid argument for setGraphVariableBool.");
		return;
	}
	bool ok = actor->SetGraphVariableBool(std::string(in->at(1)), b);
	if (actor->IsPlayerRef())
		logger::info("SGV[{}] B {} = {} ok={}", SGVTag(actor), in->at(1), b, ok);
}

void graphVariableHandler::setGraphVariableFloat(RE::Actor* actor, std::vector<std::string_view>* in)
{
	float f;
	if (!Utils::string_view::to_float(in->at(2), f)) {
		printErrMsg(in, "Invalid argument for setGraphVariableFloat.");
		return;
	}
	bool ok = actor->SetGraphVariableFloat(std::string(in->at(1)), f);
	if (actor->IsPlayerRef())
		logger::info("SGV[{}] F {} = {} ok={}", SGVTag(actor), in->at(1), f, ok);
}

void graphVariableHandler::setGraphVariableInt(RE::Actor* actor, std::vector<std::string_view>* in)
{
	int i;
	if (!Utils::string_view::to_int(in->at(2), i)) {
		printErrMsg(in, "Invalid argument for setGraphVariableInt.");
		return;
	}
	bool ok = actor->SetGraphVariableInt(std::string(in->at(1)), i);
	if (actor->IsPlayerRef())
		logger::info("SGV[{}] I {} = {} ok={}", SGVTag(actor), in->at(1), i, ok);
}

void graphVariableHandler::process(RE::Actor* actor, std::vector<std::string_view>* param, GRAPHVARIABLETYPE graphVariableType)
{
	if (!checkParamCt(param, 2)) {
		return;
	}
	switch (graphVariableType) {
	case GRAPHVARIABLETYPE::Bool: setGraphVariableBool(actor, param); break;
	case GRAPHVARIABLETYPE::Float: setGraphVariableFloat(actor, param); break;
	case GRAPHVARIABLETYPE::Int: setGraphVariableInt(actor, param); break;
	}
}
