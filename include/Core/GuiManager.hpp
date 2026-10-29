#pragma once
#include <SFML/Graphics.hpp>
#include "imgui.h"

#include "RenderContext.hpp"

class GuiManager {
public:
	static void render(const RenderContext& ctx);

private:
	static void renderControlPanel(const RenderContext& ctx);

	static void renderScaleSlider(const RenderContext& ctx);
	static void renderTimeAcceleration(const RenderContext& ctx);
	static void renderSpeedReset(const RenderContext& ctx, int targetInd);

	///

	static void renderInfo(const RenderContext& ctx);

	static void renderTypeInfo(const RenderContext& ctx, int targetInd);
	static void renderNameInfo(const RenderContext& ct, int targetIndx);
	static void renderMassInfo(const RenderContext& ctx, int targetInd);
	static void renderDistanceFromAnotherCbInfo(const RenderContext& ctx, const auto& targetCb, const auto& anotherCb);
	static void renderVelocityInfo(const RenderContext& ctx, int targetInd);
};